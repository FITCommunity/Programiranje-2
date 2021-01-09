#include <iostream>
#include<string>
#include<vector>
#include<regex>
#include<mutex>
#include<regex>
using namespace std;

#pragma warning(disable:4996)
const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI, DRUGI, TRECI, CETVRTI };
const char* ispisRazreda[] = { "PRVI"," DRUGI", "TRECI", "CETVRTI" };
const float minimalan_prosjek = 4.5;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Kolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	Kolekcija(const Kolekcija& original) : _trenutno(new int(*original._trenutno))
	{
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (int i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& drugi)
	{
		if (this != &drugi)
		{
			if (*_trenutno != 0)
			{
				delete[] _elementi1;
				delete[] _elementi2;
			}
			*_trenutno = *drugi._trenutno;
			_elementi1 = new T1[*_trenutno];
			_elementi2 = new T2[*_trenutno];
			for (int i = 0; i < *_trenutno; i++)
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
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }
	void AddElement(T1 el1, T2 el2)
	{
		T1* temp1 = new T1[*_trenutno + 1];
		T2* temp2 = new T2[*_trenutno + 1];
		for (int i = 0; i < *_trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;
		temp1[*_trenutno] = el1;
		temp2[*_trenutno] = el2;
		(*_trenutno)++;
		_elementi1 = temp1;temp1=nullptr;
		_elementi2 = temp2;temp2=nullptr;
	}

	void SortOpadajuciByT2()
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < *_trenutno-1; i++)
			{
				if (_elementi2[i] < _elementi2[i + 1])
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
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
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
	char* ToCharArray()
	{
		string sve = to_string(*_dan) + "." + to_string(*_mjesec) + "." + to_string(*_godina) + "-> " + to_string(*_sati) + ":" + to_string(*_minuti);
		int vel = sve.length() + 1;
		char* temp = new char[vel];
		strcpy_s(temp, vel, sve.c_str());
		return temp;
	}
	int toMinute()const
	{
		return *_godina * 365 * 24 * 60 + *_mjesec * 30 * 24 * 50 + *_dan * 24 * 60 + *_sati * 60 + *_minuti;
	}
	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << "-> " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
};

int GetRazlika( DatumVrijeme& prvi,  DatumVrijeme& drugi)
{
	int prvi1 = prvi.toMinute();
	int drugi1 = drugi.toMinute();
	return abs(prvi1 - drugi1);
}


class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	Predmet(const Predmet& original) : _naziv(AlocirajNizKaraktera(original._naziv)), _ocjena(original._ocjena), _napomena(original._napomena) {}
	Predmet& operator=(const Predmet& drugi)
	{
		if (this != &drugi)
		{
			delete[] _naziv;
			_naziv = AlocirajNizKaraktera(drugi._naziv);
			_napomena = drugi._napomena;
			_ocjena = drugi._ocjena;
		}
		return *this;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	bool operator==(const Predmet& drugi)
	{
		return strcmp(_naziv, drugi._naziv) == 0 && _ocjena == drugi._ocjena && _napomena == drugi._napomena;
	}
	char* GetNaziv() { return _naziv; }
	string GetNapomena() { return _napomena; }
	int GetOcjena() { return _ocjena; }
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};
struct Uspjeh {
	eRazred _razred;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet*, DatumVrijeme>* _predmeti;
public:
	Uspjeh() {}
	Uspjeh(eRazred razred) :_razred(razred) {
		_predmeti = new Kolekcija<Predmet*, DatumVrijeme>;
	}
	Uspjeh(const Uspjeh& original) : _razred(original._razred)
	{
		_predmeti = new Kolekcija<Predmet*, DatumVrijeme>(*original._predmeti);
	}
	Uspjeh& operator=(const Uspjeh& drugi)
	{
		if (this != &drugi)
		{
			delete _predmeti;
			_predmeti = new Kolekcija<Predmet*, DatumVrijeme>(*drugi._predmeti);
			_razred = drugi._razred;
		}
		return *this;
	}
	~Uspjeh() {
		delete _predmeti; _predmeti = nullptr;
	}

	Kolekcija<Predmet*, DatumVrijeme>* GetPredmeti() { return _predmeti; }
	eRazred GetRazred() { return _razred; }
	double ProsjekPredmeta()
	{
		double prosjek = 0;
		for (int i = 0; i < _predmeti->getTrenutno(); i++)
		{
			prosjek += _predmeti->getElement1(i)->GetOcjena();
		}
		return prosjek / _predmeti->getTrenutno();
	}
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << "Razred-> "<<ispisRazreda[obj._razred] << endl;
		for (int i = 0; i < obj._predmeti->getTrenutno(); i++)
		{
			COUT << "Predmet->  " << *obj._predmeti->getElement1(i) << endl;
			COUT << "Datum evidentiranja->  " << obj._predmeti->getElement2(i) << crt;
		}
		return COUT;
	}
};


mutex mutegz;

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh*> _uspjeh;
	void PosaljiMAIL(int indeks)
	{
		mutegz.lock();
		cout << "Saljem mail na-> " << _emailAdresa << endl;
		cout << "Uspjesno ste evidentirali uspjeh za " << ispisRazreda[_uspjeh[indeks]->GetRazred()] << endl;
		mutegz.unlock();
	}
	void PosaljiSMS(int indeks)
	{
		if (_uspjeh[indeks]->ProsjekPredmeta() >= minimalan_prosjek)
		{
			mutegz.lock();
			cout << "Saljem na broj  " << _brojTelefona << "," << endl;
			cout << "Svaka cast za uspjeh ->  " << _uspjeh[indeks]->ProsjekPredmeta() << crt;
			mutegz.unlock();
		}
	}
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) :_emailAdresa(emailAdresa), _brojTelefona(brojTelefona) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	Kandidat(const Kandidat& original) : _imePrezime(AlocirajNizKaraktera(original._imePrezime)), _emailAdresa(original._emailAdresa), _brojTelefona(original._brojTelefona)
	{
		for (int i = 0; i < original._uspjeh.size(); i++)
		{
			_uspjeh.push_back(new Uspjeh(*original._uspjeh[i]));
		}
	}
	Kandidat& operator=(const Kandidat& drugi)
	{
		if (this != &drugi)
		{
			for (int i = 0; i < _uspjeh.size(); i++)
			{
				delete _uspjeh[i];
			}
			_uspjeh.clear();
			for (int i = 0; i < drugi._uspjeh.size(); i++)
			{

				_uspjeh.push_back(new Uspjeh(*drugi._uspjeh[i]));
			}

			delete[] _imePrezime;
			_imePrezime = AlocirajNizKaraktera(drugi._imePrezime);
			_emailAdresa = drugi._emailAdresa;
			_brojTelefona = drugi._brojTelefona;
		}
		return *this;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjeh.size(); i++) {
			delete _uspjeh[i];
			_uspjeh[i] = nullptr;
		}
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << "Kandidat-> "<<obj._imePrezime << "    Email->  " << obj._emailAdresa << "    Kontakt->  " << obj._brojTelefona << endl;
		for (size_t i = 0; i < obj._uspjeh.size(); i++)
			COUT << *obj._uspjeh[i];
		return COUT;
	}
	bool operator==(const Kandidat& drugi)
	{
		return strcmp(_imePrezime,drugi._imePrezime)==0 && _brojTelefona==drugi._brojTelefona;
	}
	string GetEmail() { return _emailAdresa; }
	vector<Uspjeh*> GetUspjeh() { return _uspjeh; }

	bool AddPredmet(eRazred razred, Predmet& p, DatumVrijeme& d)
	{
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (_uspjeh[i]->GetRazred() == razred)
			{
				if (_uspjeh[i]->GetPredmeti()->getTrenutno() >= 6)
					return false;

				for (int j = 0; j < _uspjeh[i]->GetPredmeti()->getTrenutno(); j++)
				{
					if (*_uspjeh[i]->GetPredmeti()->getElement1(j) == p)
						return false;
				}

				int trenutno = _uspjeh[i]->GetPredmeti()->getTrenutno();
				if (GetRazlika(_uspjeh[i]->GetPredmeti()->getElement2(trenutno - 1), d) < 60)
					return false;

				_uspjeh[i]->GetPredmeti()->AddElement(&p, d);
				if (_uspjeh[i]->GetPredmeti()->getTrenutno() == 3)
				{
					thread t1(&Kandidat::PosaljiMAIL, this, i);
					//prvo funkcija clanica , this ( objekata nad kojim se poziva), argumenti koje funkcija prima gore)
					t1.join();
					thread t2(&Kandidat::PosaljiSMS, this, i);
					//prvo funkcija clanica , this ( objekata nad kojim se poziva), argumenti koje funkcija prima gore)
					t2.join();
				}
				return true;
			}
		}

		Uspjeh* u=new Uspjeh(razred);
		u->GetPredmeti()->AddElement(&p, d);
		_uspjeh.push_back(u);
		return true;
	}
	Uspjeh* operator()(eRazred razred)
	{
		Uspjeh* u = nullptr;
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (_uspjeh[i]->GetRazred() == razred)
				u = new Uspjeh(*_uspjeh[i]);
		}
		return u;
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/

	DatumVrijeme temp,
		datum19062018_1015(19, 6, 2018, 10, 15),
		datum20062018_1115(20, 6, 2018, 11, 15),
		datum30062018_1215(30, 6, 2018, 12, 15),
		datum05072018_1231(5, 7, 2018, 12, 31),
		datum20062018_1115_Copy(datum20062018_1115);
	//funkcija ToCharArray vraca datum i vrijeme kao char *
	cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
	temp = datum05072018_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
	cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15

	const int kolekcijaTestSize = 10;
	Kolekcija<int, int> kolekcija1;
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, i * i);
	cout << kolekcija1 << endl;

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
	cout << Matematika << endl;

	Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");

	///*
	//uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	//tom prilikom onemoguciti:
	//- dodavanje vise od 6 predmeta za jedan razred
	//- dodavanje istoimenih predmeta na nivou jednog razreda,
	//- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje minut).
	//razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
	//razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	//*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	///*pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
	//upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
	//sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od minimalan_prosjek
	//kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova implemenitrati koristeci
	//zasebne thread-ove.
	//*/

	Uspjeh* u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
	if (u != nullptr)
		cout << *u << endl;


	system("pause>0");
}