#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<thread>
#include<mutex>
#include<iterator>
using namespace std;



const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI , DRUGI, TRECI, CETVRTI };
const char* ispisRazreda[] = { "PRVI" , "DRUGI", "TRECI", "CETVRTI" };
enum SortirajPo { T1, T2 };

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
	bool ProvjeriDupli(T1 el1,T2 el2)
	{
		for (int i = 0; i < _trenutno; i++)
		{
			if (!_omoguciDupliranje && (_elementi1[i] == el1 && _elementi2[i] == el2))
				return true;
		}
		return false;
	}
	void Dodaj(T1 el1, T2 el2)
	{
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;
		temp1[_trenutno] = el1;
		temp2[_trenutno] = el2;
		_trenutno++;
		_elementi1 = temp1;temp1=nullptr;
		_elementi2 = temp2;temp2=nullptr;
	}
	bool Uslov(SortirajPo sort, int lok1, int lok2)
	{
		if (sort == SortirajPo::T1 && _elementi1[lok1] > _elementi1[lok2])
			return true;
		if (sort == SortirajPo::T2 && _elementi2[lok1] > _elementi2[lok2])
			return true;
		return false;
	}
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
	}
	Kolekcija(const Kolekcija& original) : _omoguciDupliranje(original._omoguciDupliranje), _trenutno(original._trenutno)
	{
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& drugi)
	{
		if (this != &drugi)
		{
			if (_trenutno != 0)
			{
				delete[]_elementi1;
				delete[]_elementi2;
			}
			_trenutno = drugi._trenutno;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = drugi._elementi1[i];
				_elementi2[i] = drugi._elementi2[i];
			}
		}
		return *this;
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT,  Kolekcija& obj) {
		for (size_t i = 0; i < obj.getTrenutno(); i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
	void AddElement(T1 el1, T2 el2)
	{
		if (ProvjeriDupli(el1, el2))
			throw exception("Pokusavate dodati dupli element,a dupliranje nije dozvoljeno!");
		Dodaj(el1, el2);
	}
	void SortirajRastuci(SortirajPo sort)
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < _trenutno-1; i++)
			{
				if (Uslov(sort, i, i + 1))
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
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& original)
	{
		_dan = new int(*original._dan);
		_mjesec = new int(*original._mjesec);
		_godina = new int(*original._godina);
		_sati = new int(*original._sati);
		_minuti = new int(*original._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& drugi)
	{
		if (this != &drugi)
		{
			*_dan = *drugi._dan;
			*_mjesec = *drugi._mjesec;
			*_godina = *drugi._godina;
			*_sati = *drugi._sati;
			*_minuti = *drugi._minuti;
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << "-> " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	int GetMinute()const {
		return *_godina * 365 * 24 * 60 + *_mjesec * 30 * 24 * 60 + *_dan * 24 * 60 + *_sati * 60 + *_minuti;
	}
	bool operator==(const DatumVrijeme& drugi)
	{
		return *_dan == *drugi._dan && *_mjesec == *drugi._mjesec && *_godina == *drugi._godina && *_sati == *drugi._sati && *_minuti == *drugi._minuti;
	}
};

int GetRazmakDatuma(const DatumVrijeme& d1, const DatumVrijeme& d2)
{
	return abs(d1.GetMinute() - d2.GetMinute());
}

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& original) : _naziv(Alociraj(original._naziv)),_ocjena(original._ocjena),_napomena(original._napomena){}
	Predmet& operator=(const Predmet& drugi)
	{
		if (this != &drugi)
		{
			delete[] _naziv;
			_naziv = Alociraj(drugi._naziv);
			_ocjena = drugi._ocjena;
			_napomena = drugi._napomena;
		}
		return *this;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT <<"Predmet -> "<< obj._naziv << "  Ocjena (" << obj._ocjena << ")    Napomena -> " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
	bool operator==(const Predmet& drugi)
	{
		return strcmp(_naziv, drugi._naziv) == 0 && _ocjena == drugi._ocjena && _napomena == drugi._napomena;
	}
};

class Uspjeh {
	eRazred* _razred;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	Uspjeh(const Uspjeh& original) : _razred(new eRazred(*original._razred)), _predmeti(original._predmeti) {}
	Uspjeh& operator=(const Uspjeh& drugi)
	{
		if (this != &drugi)
		{
			delete _razred;
			_razred = new eRazred(*drugi._razred);
			_predmeti = drugi._predmeti;
		}
		return *this;
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }
	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() { return _razred; }
	bool PostojiLiIsti(Predmet& p)
	{
		for (int i = 0; i < _predmeti.getTrenutno(); i++)
		{
			if (_predmeti.getElement1(i) == p)
				return true;
		}
		return false;
	}
	float ProsjekPredmeta(eRazred razred)
	{
		float prosjek = 0;
		for (int i = 0; i < _predmeti.getTrenutno(); i++)
		{
			if (*_razred == razred)
			{
				prosjek += _predmeti.getElement1(i).GetOcjena();
			}
		}
		return prosjek / _predmeti.getTrenutno();
	}
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << ispisRazreda[*obj._razred] << endl;
		for (int i = 0; i < obj._predmeti.getTrenutno(); i++)
		{
			COUT << "Datum dodavanja predmeta -> " << obj._predmeti.getElement2(i);
			COUT << "Predmet -> " << obj._predmeti.getElement1(i);
		}
		return COUT;
	}
};

mutex mjutex;

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
	bool ValidanMail(string email)
	{
		return regex_match(email, regex("[a-zA-z]{3,12}@(outlook.com|edu.fit.ba)"));
	}
	void PosaljiMail(int indeks)
	{
		mjutex.lock();

		cout << "FROM: info@edu.fit.ba\n";
		cout << "TO: " << _emailAdresa << endl;
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << ispisRazreda[*_uspjeh[indeks].GetERazred()] << " razred\n";
		cout << "Pozdrav.\n";
		cout << "FIT Team\n";

		mjutex.unlock();
	}
	void PosaljiSMS(float prosjek,eRazred razred)
	{
		mjutex.lock();
		cout << "Svaka cast za uspjeh " << prosjek << " u " << ispisRazreda[razred] << endl;
		mjutex.unlock();
	}
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		if (ValidanMail(emailAdresa))
			_emailAdresa = emailAdresa;
		else
			_emailAdresa = "not_set@edu.fit.ba";
		_brojTelefona = brojTelefona;
	}
	Kandidat(const Kandidat& original) : _imePrezime(Alociraj(original._imePrezime)), _emailAdresa(original._emailAdresa), _brojTelefona(original._brojTelefona), _uspjeh(original._uspjeh) {}
	Kandidat& operator=(const Kandidat& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(drugi._imePrezime);
			_brojTelefona = drugi._brojTelefona;
			_emailAdresa = drugi._emailAdresa;
			_uspjeh = drugi._uspjeh;
		}
		return *this;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT <<"Kandidat -> "<< obj._imePrezime << "    Mail-Adresa -> " << obj._emailAdresa << "   Kontakt -> " << obj._brojTelefona << endl;
		COUT << ":::::USPJESI KANDIDATA:::::" << crt;
		ostream_iterator<Uspjeh> out_iter(COUT, "\n");
		copy(obj._uspjeh.begin(), obj._uspjeh.end(), out_iter);
		return COUT;
	}
	bool AddPredmet(eRazred razred, Predmet& p, DatumVrijeme& d)
	{
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetERazred() == razred)
			{
				if (_uspjeh[i].PostojiLiIsti(p))
					return false;

				int trenutno = _uspjeh[i].GetPredmeti()->getTrenutno();
				if (GetRazmakDatuma(_uspjeh[i].GetPredmeti()->getElement2(trenutno - 1), d) < 5)
					return false;

				_uspjeh[i].GetPredmeti()->AddElement(p, d);
				thread saljiMail(&Kandidat::PosaljiMail, this, i);
				saljiMail.join();

				float prosjek = _uspjeh[i].ProsjekPredmeta(razred);
				if (prosjek > 4.5)
				{
					thread saljiSMS(&Kandidat::PosaljiSMS, this, prosjek,razred);
					saljiSMS.join();
				}
				return true;
			}
		}

		Uspjeh u(razred);
		u.GetPredmeti()->AddElement(p, d);
		_uspjeh.push_back(u);
		return true;
	}
	int BrojPonavljanjaRijeci(string rijec)
	{
		regex regegz(rijec);
		int brojRijeci = 0;
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				string tekst = _uspjeh[i].GetPredmeti()->getElement1(i).GetNapomena();
				sregex_iterator it_poc(tekst.begin(), tekst.end(), regegz);
				sregex_iterator it_kraj;
				while (it_kraj!=it_poc )
				{
					it_poc++;
					brojRijeci++;
				}
			}
		}
		return brojRijeci;
	}
	Uspjeh* operator[](eRazred razred)
	{
		Uspjeh* u = nullptr;
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetERazred() == razred)
			{
				u = &_uspjeh[i];
			}
		}
		return u;
	}
	vector<Predmet> operator()(DatumVrijeme d1, DatumVrijeme d2)
	{
		vector<Predmet> novi;
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
		{
			for (int j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
			{
				if (i->GetPredmeti()->getElement2(j).GetMinute() > d1.GetMinute() && i->GetPredmeti()->getElement2(j).GetMinute() < d2.GetMinute())
				{
					novi.push_back(i->GetPredmeti()->getElement1(j));
				}
			}
		}
		return novi;
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception & err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;

	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;


	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;

	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.
	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	////vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	////vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	for (size_t i = 0; i < jasminUspjeh.size(); i++)
		cout << jasminUspjeh[i] << endl;

	Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	if (uspjeh_Irazred != nullptr)
		cout << *uspjeh_Irazred << endl;

	system("pause>0");
}