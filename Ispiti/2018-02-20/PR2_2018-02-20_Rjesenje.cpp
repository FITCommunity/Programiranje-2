#include <iostream>
#include <vector>
#include<sstream>
#include<string>
#include<regex>
#include<thread>
#include<mutex>
#include<iterator>
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum OznakaKrvneGrupe { O, A, B, AB };
const char* ispisKrvneGrupe[] = { "O", "A", "B", "AB" };
char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int _dan, _mjesec, _godina;
public:
	Datum(int dan, int mjesec, int godina) :
		_dan(dan), _mjesec(mjesec), _godina(godina) {}
	string ToString(string separator = ".")
	{
		stringstream ss;
		ss << _dan << separator << _mjesec << separator << _godina << endl;
		return ss.str();
	}
	int toDane()const {
		return _godina * 365 + _mjesec * 30 + _dan;
	}
};

bool ValidanDatumDonacije(Datum prvi, Datum drugi)
{
	return prvi.toDane() - drugi.toDane() >= 90;
}

template <class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int _trenutnoElemenata;
	int _keyElement; // kljucni element, a podrazumijevano T1 predstavlja kljucni element i tada je vrijednost 1, a u slucaju da je T2 onda ce vrijednost biti 2
	bool Uslov(string sort,int i)
	{
		if (_keyElement == 1)
		{
			if (sort == "ASC" && _elementi1[i] > _elementi1[i + 1])
				return true;

			if (sort == "DESC" && _elementi1[i] < _elementi1[i + 1])
				return true;
		}

		if (_keyElement == 2)
		{
			if (sort == "ASC" && _elementi2[i] > _elementi2[i + 1])
				return true;

			if (sort == "DESC" && _elementi2[i] < _elementi2[i + 1])
				return true;
		}
		return false;
	}
public:
	Kolekcija(int keyElement = 1) {
		_trenutnoElemenata = 0;
		_keyElement = keyElement;
	}
	bool AddElement(T1 ele1, T2 ele2) {
		if (_trenutnoElemenata == max)
			return false;
		_elementi1[_trenutnoElemenata] = ele1;
		_elementi2[_trenutnoElemenata] = ele2;
		_trenutnoElemenata++;
		return true;
	}
	void SetElement2(int lokacija, T2 ele2) {
		_elementi2[lokacija] = ele2;
	}
	void SetKeyElement(int keyElement) {
		if (keyElement < 1 || keyElement>2)
			throw exception("Nedozvoljena vrijednost!");
		_keyElement = keyElement;
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }
	T1& GetElement1(int lokacija)  {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception("Nepostojeca lokacija!");
		return _elementi1[lokacija];
	}
	T2& GetElement2(int lokacija)  {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception("Nepostojeca lokacija!");
		return _elementi2[lokacija];
	}

	void Sort(string sort)
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < _trenutnoElemenata-1; i++)
			{
				if (Uslov(sort, i))
				{
					T1 temp1 = _elementi1[i];
					_elementi1[i] = _elementi1[i + 1];
					_elementi1[i + 1] = temp1;

					T2 temp2 = _elementi2[i];
					_elementi2[i] = _elementi2[i + 1];
					_elementi2[i + 1] = temp2;
					prolaz = true;
				}
			}
		}
	}
	friend ostream& operator<<(ostream& COUT,  Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << "   " << obj.GetElement2(i) << endl;
		return COUT;
	}
};

class KrvnaGrupa {
	/*postoje 4 krvne grupe koje su navedene u enumeracije OznakaKrvneGrupe, pri cemu svaka od navedenih moze imati pozitivan (+) i negativan (-) Rh faktor*/
	OznakaKrvneGrupe _oznaka;//npr: AB
	char _rhFaktor; // + ili -
					/*prethodno pomenuto je izuzetno bitno iz razloga sto postoje jasna pravila vezana za darivanje krvi tj. koji primalac moze primiti krv od kojeg donatora sto je prikazano u tabeli, a naredna dva vector-a su zaduzena da cuvaju informacije o tome, npr. za krvnu grupu A+ vector donatori ce cuvati vrijednosti: A+ i AB+ */
	vector<KrvnaGrupa> _donatori; //krvne grupe kojima odredjena krvna grupa moze donirati krv.
	vector<KrvnaGrupa> _primaoci; //krvne grupe od kojih odredjena krvna grupa moze primiti krv.
public:
	KrvnaGrupa(OznakaKrvneGrupe oznaka, char rhFaktor) :_oznaka(oznaka), _rhFaktor(rhFaktor) {}
	KrvnaGrupa(const KrvnaGrupa& obj) : _oznaka(obj._oznaka), _rhFaktor(obj._rhFaktor), _donatori(obj._donatori), _primaoci(obj._primaoci) {}
	void SetDonatori(vector<KrvnaGrupa> donatori) {
		_donatori = donatori;
	}
	void SetPrimaoci(vector<KrvnaGrupa> primaoci) {
		_primaoci = primaoci;
	}
	vector<KrvnaGrupa> GetPrimaoci() { return _primaoci; }
	vector<KrvnaGrupa> GetDonatori() { return _donatori; }

	OznakaKrvneGrupe GetOznakaGrupe() { return _oznaka; }
	char GetRHFaktor() { return _rhFaktor; }

	string ToString()
	{
		stringstream ss;
		ss << crt;
		ss << "Krvna grupa -> " << ispisKrvneGrupe[_oznaka] << _rhFaktor << crt;
		ss << "Donori -> ";
		for (int i = 0; i < _donatori.size(); i++)
		{
			ss << ispisKrvneGrupe[_donatori[i].GetOznakaGrupe()] << _donatori[i]._rhFaktor << ", ";
		}
		ss << "\nPrimaoci -> ";
		for (int i = 0; i < _primaoci.size(); i++)
		{
			ss << ispisKrvneGrupe[_primaoci[i].GetOznakaGrupe()] << _primaoci[i]._rhFaktor << ", ";
		}
		ss << crt;
		return ss.str();
	}
	friend ostream& operator<<(ostream& COUT, KrvnaGrupa& obj)
	{
		COUT <<ispisKrvneGrupe[obj.GetOznakaGrupe()] << obj._rhFaktor;
		return COUT;
	}
	bool operator==(const KrvnaGrupa& druga)
	{
		return _rhFaktor == druga._rhFaktor && _oznaka == druga._oznaka;
	}

};

//Klasu proglasiti apstraktnom
class Osoba {
protected:
	char* _imePrezime;
	KrvnaGrupa _krvnaGrupa;
public:
	Osoba(const char* imePrezime, KrvnaGrupa krvnaGrupa) : _krvnaGrupa(krvnaGrupa) {
		_imePrezime = Alociraj(imePrezime);
	}
	Osoba(const Osoba& original) : _krvnaGrupa(original._krvnaGrupa)
	{
		_imePrezime = Alociraj(original._imePrezime);
	}
	Osoba& operator=(const Osoba& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(drugi._imePrezime);
			_krvnaGrupa = drugi._krvnaGrupa;
		}
		return *this;
	}
	~Osoba() {
		delete[] _imePrezime;
		_imePrezime = nullptr;
	}
	KrvnaGrupa& GetKrvnaGrupa() { return _krvnaGrupa; }
	char* GetImePrezime() { return _imePrezime; }
	virtual void info() = 0;

};

class Donator : public Osoba {
	//u slucaju da broj telefona nije u validnom formatu potrebno ga je postaviti na podrazumijevanu vrijednost: 000-000-000
	string _telefon; //regex: 000/000-000 ili 000-000-000
	Datum _datumPosljednjegDoniranja;
	bool _podsjetiMe;
	bool _kontaktirajMe;
	bool ValidanFormat(string telefon)
	{
		return regex_match(telefon, regex("[0-9]{3}(/|-)[0-9]{3}-[0-9]{3}"));
	}
public:
	void info() {}
	Donator(const char* imePrezime, KrvnaGrupa krvnaGrupa, string telefon, Datum dpd, bool remind = true, bool contact = true)
		: Osoba(imePrezime, krvnaGrupa), _datumPosljednjegDoniranja(dpd) {
		if (ValidanFormat(telefon))
			_telefon = telefon;
		else
			_telefon = "000-000-000";
		_podsjetiMe = remind;
		_kontaktirajMe = contact;
	}
	Donator(const Donator& original) : Osoba(original), _telefon(original._telefon), _datumPosljednjegDoniranja(original._datumPosljednjegDoniranja), _podsjetiMe(original._podsjetiMe),
		_kontaktirajMe(original._kontaktirajMe) {}
	Donator& operator=(const Donator& drugi)
	{
		if (this != &drugi)
		{
			Osoba::operator=(drugi);
			_telefon = drugi._telefon;
			_datumPosljednjegDoniranja = drugi._datumPosljednjegDoniranja;
			_podsjetiMe = drugi._podsjetiMe;
			_kontaktirajMe = drugi._kontaktirajMe;
		}
		return *this;
	}
	Datum& GetDatumPosljednjegDoniranja() { return _datumPosljednjegDoniranja; }
	string GetTelefon() { return _telefon; }
	bool GetPodsjeti() { return _podsjetiMe; }
	bool GetKontaktiraj() { return _kontaktirajMe; }
	void SetDatumPosljednjegDoniranja(Datum datum) { _datumPosljednjegDoniranja = datum; }
	friend ostream& operator<<(ostream& COUT, Donator& obj)
	{
		COUT << "Donator -> " << obj._imePrezime << "   Kontakt ->  " << obj._telefon << "   Datum posljednjeg doniranja ->  " << obj._datumPosljednjegDoniranja.ToString() << endl;
		if (obj._podsjetiMe)
			COUT << "Donator zeli da ga se podsjeti ako trebao donirati krv" << endl;
		else
			COUT << "Donator ne zeli da ga se podsjeti za novu donaciju krvi" << endl;
		return COUT;
	}

};

class Zahtjev {
	string _ustanova;
	Datum _datumZahtjeva;
	KrvnaGrupa _krvnaGrupa;
	double _kolicina;
public:
	Zahtjev(string ustanova, Datum datum, KrvnaGrupa krvnaGrupa, double kolicina) :
		_ustanova(ustanova), _datumZahtjeva(datum), _krvnaGrupa(krvnaGrupa), _kolicina(kolicina) { }
	void SetNovaKolicina(double kolicina) { _kolicina += kolicina; }
	KrvnaGrupa GetZahtjevanaKRGrupa() { return _krvnaGrupa; }
	double GetZahjevanaKolicina() { return _kolicina; }
	Datum& GetDatumZahtjeva() { return _datumZahtjeva; }
	friend ostream& operator<<(ostream& COUT,  Zahtjev& obj)
	{
		COUT << "Ustanova: " << obj._ustanova << endl;
		COUT << "Datum: " << obj._datumZahtjeva.ToString() << endl;
		COUT << "Krvna grupa: " <<ispisKrvneGrupe[ obj._krvnaGrupa.GetOznakaGrupe()]<<obj._krvnaGrupa.GetRHFaktor() << endl;
		COUT << "Kolicina: " << obj._kolicina << endl;
		return COUT;
	}
};


mutex mjuteks;
class TransfuzijskiCentar {
	//stanje zaliha za svaku pojedinu krvnu grupu
	Kolekcija<KrvnaGrupa*, double, 8> _zalihe;
	//evidentira svaku donaciju krvi
	Kolekcija<Osoba*, double, 100> _donacije;
	vector<Zahtjev> _zahtjevi;
	void SaljiSMS(const char* imePrezime)
	{
		mjuteks.lock();
		cout << "Postovani " << imePrezime << " treba nam donacija vase krvi!" << crt;
		mjuteks.unlock();
	}
public:

	void AddDonaciju(Datum datumDoniranja, Osoba* osoba, double kolicina)
	{
		Donator* donator = dynamic_cast<Donator*>(osoba);

		for (int i = 0; i < _zalihe.GetTrenutno(); i++)
		{
			if (*_zalihe.GetElement1(i) == donator->GetKrvnaGrupa())
			{
				_zalihe.GetElement2(i) = _zalihe.GetElement2(i) + kolicina;
				donator->SetDatumPosljednjegDoniranja(datumDoniranja);
				return;
			}
		}

		_zalihe.AddElement(&osoba->GetKrvnaGrupa(), kolicina);
		donator->SetDatumPosljednjegDoniranja(datumDoniranja);
		_donacije.AddElement(osoba, kolicina);
	}

	

	void DodajZahtjev(Zahtjev& zahtjev)
	{
		for (int i = 0; i < _zalihe.GetTrenutno(); i++)
		{
			//ako postoji ta krvna grupa koja se trazi i kolicina u zalihama je veca od zahtjevane, onda samo sa zalihe skinuti ono sto je zahtjev trazio
			if (*_zalihe.GetElement1(i) == zahtjev.GetZahtjevanaKRGrupa() && _zalihe.GetElement2(i) >= zahtjev.GetZahjevanaKolicina())
			{
				_zalihe.GetElement2(i) = _zalihe.GetElement2(i) - zahtjev.GetZahjevanaKolicina();
				_zahtjevi.push_back(zahtjev);
				return;
			}
		}

		_zahtjevi.push_back(zahtjev);

		//da bi slali thread treba proci kroz donacije,pa castati u donatora i provjeriti je li ista krvna grupa kod donatora i moze li trazena krvna grupa primiti njegovu krv
		//tj. proci kroz primaoce zahtjevane krvne grupe i da li je _kontaktirajMe oznaceno kao true(jest defaultno)
		// i provjeriti je li razlika izmedju datum zahtjeva i datuma zadnje donacije veca ili jednaka od 3 mjeseca
		for (int i = 0; i < _donacije.GetTrenutno(); i++)
		{
			Donator* donator = dynamic_cast<Donator*>(_donacije.GetElement1(i));
			for (int j = 0; j < zahtjev.GetZahtjevanaKRGrupa().GetPrimaoci().size(); j++)
			{
				if (_donacije.GetElement1(i)->GetKrvnaGrupa() == zahtjev.GetZahtjevanaKRGrupa().GetPrimaoci()[j] && donator->GetKontaktiraj() && ValidanDatumDonacije(zahtjev.GetDatumZahtjeva(),donator->GetDatumPosljednjegDoniranja()))
				{
					thread t1(&TransfuzijskiCentar::SaljiSMS, this, donator->GetImePrezime());
					t1.join();
				}
			}
		}
	}

	friend ostream& operator<<(ostream& COUT, TransfuzijskiCentar& obj)
	{
		COUT << "::: ZALIHE CENTRA ::: " << crt;
		for (int i = 0; i < obj._zalihe.GetTrenutno(); i++)
		{
			COUT << "Krvna grupa -> " <<ispisKrvneGrupe[obj._zalihe.GetElement1(i)->GetOznakaGrupe()]<<obj._zalihe.GetElement1(i)->GetRHFaktor() << "      Kolicina na stanju -> " << obj._zalihe.GetElement2(i) << endl;
		}
		COUT << "\n::: DONACIJE :::" << crt;
		for (int i = 0; i < obj._donacije.GetTrenutno(); i++)
		{
			COUT << "Donator ->  " << obj._donacije.GetElement1(i)->GetImePrezime() << "   Donirao za krvnu grupu ->  " << ispisKrvneGrupe[obj._donacije.GetElement1(i)->GetKrvnaGrupa().GetOznakaGrupe()] << obj._donacije.GetElement1(i)->GetKrvnaGrupa().GetRHFaktor() << "      Kolicina donacije ->  " << obj._donacije.GetElement2(i) << endl;
		}
		COUT << "\n::: ZAHTJEVI ::: " << crt;
		for (int i = 0; i < obj._zahtjevi.size(); i++)
		{
			COUT << "Zahtjev   -> " << i + 1 << endl;
			COUT << obj._zahtjevi[i] << crt;
		}
		return COUT;
	}
};

void main() {

	/**************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU code.TXT
	5. NAZIVI FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI PO ŽELJI. TAKOÐER, MOŽETE DODAVATI KOLIKO ŽELITE TESTNIH PODATAKA
	****************************************************************************/
	Datum dat_12_01_2018(12, 1, 2018), dat_01_02_2018(1, 2, 2018);
	cout << dat_01_02_2018.ToString() << endl; //podrazumijevani separator je tacka ".", pa ispisuje 1.2.2018
	cout << dat_12_01_2018.ToString("/") << endl; //separator je proslijedjen, pa ispisuje 12/1/2018

	Kolekcija<int, int, 10> kolekcija1;
	for (size_t i = 0; i < kolekcija1.GetMax(); i++)
		if (!kolekcija1.AddElement(i, 170000 + i))
			cout << "Elementi " << i << " i " << 170000 + i << " nisu dodati u kolekciju" << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;

	kolekcija1.Sort("ASC"); //kljucne rijeci za sortiranje su ASC i DESC, a sortiranje se vrsi prema kljucnom elementu
	cout << kolekcija1 << endl << endl << endl;
	kolekcija1.Sort("DESC");
	cout << kolekcija1 << endl;

	kolekcija1.SetKeyElement(2);//postavlja kljucni element na T2

	kolekcija1.Sort("DESC"); //sada se sortiranje vrsi po elementu T2
	cout << kolekcija1 << endl;

	KrvnaGrupa
		O_poz(O, '+'), O_neg(O, '-'),
		A_poz(A, '+'), A_neg(A, '-'),
		B_poz(B, '+'), B_neg(B, '-'),
		AB_poz(AB, '+'), AB_neg(AB, '-');

	vector<KrvnaGrupa> donori_O_poz{ O_poz, A_poz, B_poz, AB_poz };
	O_poz.SetDonatori(donori_O_poz);
	//ili krace napisano
	O_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, B_poz});//dodano B_poz zbog testiranja (to je jasminova krv koju donira i treba O_poz da je moze primiti)
	A_poz.SetDonatori(vector<KrvnaGrupa>{A_poz, AB_poz});
	A_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, A_poz, O_neg, A_neg});

	B_poz.SetDonatori(vector<KrvnaGrupa>{B_poz, AB_poz});
	B_poz.SetPrimaoci(vector<KrvnaGrupa>{O_poz, B_poz, O_neg, B_neg});
	/*
	Ispis podataka o krvnoj grupi treba biti u formatu:
	-------------------------------------------
	Krvna grupa -> 0+
	-------------------------------------------
	Donori  ->  0+, A+, B+, AB+
	Primaoci ->	0+, 0-
	-------------------------------------------
	*/
	cout << O_poz.ToString() << endl;

	Osoba* jasmin = new Donator("Jasmin Azemovic", B_poz, "061-111-222", Datum(12, 2, 2017), true, true);
	Osoba* adel = new Donator("Adel Handzic", A_neg, "061-222-333", Datum(9, 1, 2017), true, true);
	Osoba* goran = new Donator("Goran Skondric", B_neg, "061-333-444", Datum(9, 3, 2017), true, true);


	TransfuzijskiCentar tcMostar;
	/*
	prilikom svake donacije je potrebno povecati zalihe za tu krvnu grupu
	ukoliko krvna grupa vec postoji na zalihi onda se uvecava samo njena kolicina
	takodjer, donatoru se postavlja nova vrijednost datuma posljednje donacije
	*/
	//datum donacije, donator, kolicina
	tcMostar.AddDonaciju(Datum(20, 5, 2017), jasmin, 2.5);
	tcMostar.AddDonaciju(Datum(20, 5, 2017), adel, 3);
	tcMostar.AddDonaciju(Datum(6, 5, 2017), goran, 1.2);



	tcMostar.AddDonaciju(Datum(10, 9, 2017), jasmin, 2);
	tcMostar.AddDonaciju(Datum(18, 10, 2017), adel, 1.8);
	tcMostar.AddDonaciju(Datum(15, 9, 2017), goran, 3.8);

	Zahtjev zahtjev_0_poz("Tranfuziologija KCUS", Datum(18, 2, 2018), O_poz, 2),
		zahtjev_0_neg("Tranfuziologija Bakir Nakas", Datum(20, 2, 2018), O_neg, 8);

	/*ukoliko transfuzijski centar posjeduje zahtijevane kolicine na stanju, odmah ce ih ustupiti prema zahtjevu,
	a u slucaju da ne posjeduje onda ce (koristeci multithreading) kontaktirati (poslati SMS poruku sa odgovarajucim sadrzajem)
	sve donore koji zadovoljavaju sljedece uslove:
	- mogu donirati krv zahtijevanoj krvnoj grupi
	- oznacili su da zele biti kontaktirani
	- nisu davali krv u posljednja 3 mjeseca
	*/
	tcMostar.DodajZahtjev(zahtjev_0_poz);
	tcMostar.DodajZahtjev(zahtjev_0_neg);

	cout << tcMostar;
	////printa zahvalnice (zahvaljujemo se ime i prezime donatoru na ukupno doniranih X doza krvi) za TOP 2 donatora krvi
	//tcMostar.GetZahvalniceZahvalnice(2);

	delete adel;
	delete jasmin;
	delete goran;

	system("pause>0");
}