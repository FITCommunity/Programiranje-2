#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<mutex>
#include<regex>
using namespace std;
enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char* ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char* ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
const char* crt = "\n------------------------\n";
char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr) return nullptr;
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
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	Kolekcija(const Kolekcija& original) : _trenutno(original._trenutno)
	{
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& druga)
	{
		if (this != &druga)
		{
			if (_trenutno != 0)
			{
				delete[] _elementi1;
				delete[] _elementi2;
			}
			_trenutno = druga._trenutno;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = druga._elementi1[i];
				_elementi2[i] = druga._elementi2[i];
			}
		}
		return *this;
	}
	~Kolekcija()
	{
		delete[]_elementi1;_elementi1=nullptr;
		delete[]_elementi2;_elementi2=nullptr;
	}
	int GetTrenutno()const { return _trenutno; }
	T1& GetElement1(int indeks)
	{
		if (indeks<0 || indeks>_trenutno)
			throw exception("Indeks nije validan!");
		return _elementi1[indeks];
	}
	T2& GetElement2(int indeks)
	{
		if (indeks<0 || indeks>_trenutno)
			throw exception("Indeks nije validan!");
		return _elementi2[indeks];
	}
	void AddElement(T1 el1, T2 el2)
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
	void RemoveElement(int indeks)
	{
		for (int i = indeks; i < _trenutno-1; i++)//paziti da ovdje ide do _trenutno-1 jer ako dodje do zadnjeg i nema ga sa cim zamjeniti bude error
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;
	}
	friend ostream& operator<<(ostream& COUT, Kolekcija& obj)
	{
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << "   " << obj.GetElement2(i) << endl;
		return COUT;
	}

};

class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj)
	{
		if (this != &obj)
		{
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	bool operator==(const Datum& drugi)
	{
		return *_dan == *drugi._dan && *_mjesec == *drugi._mjesec && *_godina == *drugi._godina;
	}
	int toDane()const {
		return *_godina * 365 + *_mjesec * 30 + *_dan;
	}
	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
};


bool ProvjeriValidnostBrojaTelefona(string telefon) {//globalna funkcija
	/*
	broj telefona treba biti u formatu: +387(61)-222-333
	*/
	return regex_match(telefon, regex("\\+[0-9]{3}\\([0-9]{2}\\)-[0-9]{3}-[0-9]{3}"));
}


class Osoba {
protected:
	char* _imePrezime;
	Datum* _datumRodjenja;
	string _brojTelefona;
public:
	Osoba(const char* imePrezime, Datum datum) {
		_imePrezime = Alociraj(imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";
	}
	Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona) {
		_imePrezime = Alociraj(obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	Osoba& operator=(const Osoba& druga)
	{
		if (this != &druga)
		{
			delete[] _imePrezime;
			delete _datumRodjenja;
			_datumRodjenja = new Datum(*druga._datumRodjenja);
			_imePrezime = Alociraj(druga._imePrezime);
			_brojTelefona = druga._brojTelefona;
		}
		return *this;
	}
	~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
	char* GetImePrezime() { return _imePrezime; }
	Datum& GetDatumRodjenja() { return *_datumRodjenja; }
	virtual void info() = 0;
	bool setBrojTelefona(string brojTelefona) {
		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}

};

class Nastavnik :public Osoba {
	Kolekcija<Predmeti, Razredi>* _predmetiRazredi;
public:
	void info() {}
	Nastavnik(const char* imePrezime, Datum datum) : Osoba(imePrezime, datum)
	{
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
	}
	Nastavnik(const Nastavnik& original) : Osoba(original),_predmetiRazredi(new Kolekcija<Predmeti, Razredi>(*original._predmetiRazredi)){}
	Nastavnik& operator=(const Nastavnik& drugi)
	{
		if (this != &drugi)
		{
			Osoba::operator=(drugi);
			delete _predmetiRazredi;
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*drugi._predmetiRazredi);
		}
		return *this;
	}
	~Nastavnik() { delete _predmetiRazredi; _predmetiRazredi = nullptr; }
	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() { return *_predmetiRazredi; }
	bool operator==(const Nastavnik& drugi)
	{
		return strcmp(_imePrezime, drugi._imePrezime) == 0 && *_datumRodjenja == *drugi._datumRodjenja;
	}
	friend ostream& operator<<(ostream& COUT, Nastavnik& obj)
	{
		COUT << "Nastavnik -> " << obj._imePrezime << "    Datum rodjenja -> " << *obj._datumRodjenja << "    Kontakt -> " << obj._brojTelefona << endl;
		COUT << "::: PREDMETI I RAZREDI ::: " << crt;
		for (int i = 0; i < obj._predmetiRazredi->GetTrenutno(); i++)
		{
			COUT << "Predmet -> " << ispisPredmeti[obj._predmetiRazredi->GetElement1(i)] << "    Razred -> " << ispisRazredi[obj._predmetiRazredi->GetElement2(i)] << endl;
		}
		return COUT;
	}

	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	bool AddPredmetRazred(Predmeti predmet, Razredi razred)
	{
		int brojacRazreda = 0;
		for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement2(i) == razred && _predmetiRazredi->GetElement1(i) == predmet)
				return false;

			if (_predmetiRazredi->GetElement2(i) == razred)
			{
				brojacRazreda++;//ako je isti razred poveca brojac
				if (brojacRazreda == 2 && _predmetiRazredi->GetElement1(i)==predmet)//ako je brojac 2 i isti predmet onda vraca false
					return false;
			}
		}
		_predmetiRazredi->AddElement(predmet, razred);
		return true;
	}
};
class Ucenik : public Osoba {
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik*> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
public:
	void info() {}
	Ucenik(const char* imePrezime, Datum datum, int brojUDnevniku, Razredi razred) : Osoba(imePrezime, datum), _brojUDnevniku(brojUDnevniku), _razred(razred) {}
	Ucenik(const Ucenik& original) : Osoba(original), _brojUDnevniku(original._brojUDnevniku), _razred(original._razred), _predmetiOcjene(original._predmetiOcjene), _nastavnici(original._nastavnici) {}
	Ucenik& operator=(const Ucenik& drugi)
	{
		if (this != &drugi)
		{
			Osoba::operator=(drugi);
			_brojUDnevniku = drugi._brojUDnevniku;
			_razred = drugi._razred;
			_nastavnici = drugi._nastavnici;
			_predmetiOcjene = drugi._predmetiOcjene;
		}
		return *this;
	}
	Kolekcija<Predmeti, int>& GetPredmetiOcjene() { return _predmetiOcjene; }
	Razredi GetRazred() { return _razred; }
	vector<Nastavnik*>& getNastavnici() { return _nastavnici; }
	Kolekcija<Predmeti, int>& getPredmetiOcjene() { return _predmetiOcjene; }
	friend ostream& operator<<(ostream& COUT, Ucenik& obj)
	{
		COUT << "Ucenik -> " << obj._imePrezime << "  Datum rodjenja -> " << *obj._datumRodjenja << "   Kontakt -> " << obj._brojTelefona << endl;
		COUT << "Broj u dnevniku -> " << obj._brojUDnevniku << "   Razred -> " << ispisRazredi[obj._razred] << endl;
		COUT << "::: NASTAVNICI KOJI PREDAJU UCENIKU ::: " << crt;
		for (int i = 0; i < obj._nastavnici.size(); i++)
		{
			COUT << *obj._nastavnici[i] << endl;
		}
		COUT << "::: PREDMETI I OCJENE UCENIKA ::: " << crt;
		for (int i = 0; i < obj._predmetiOcjene.GetTrenutno(); i++)
		{
			COUT << "Predmet -> " << ispisPredmeti[obj._predmetiOcjene.GetElement1(i)] << "    Ocjena ( " << obj._predmetiOcjene.GetElement2(i) << " ) " << endl;
		}
		return COUT;
	}
	bool imaIsti(Nastavnik& nastavnik)
	{
		for (int i = 0; i < _nastavnici.size(); i++)
		{
			if (*_nastavnici[i] == nastavnik)
				return true;
		}
		return false;
	}
	bool AddNastavnik(Nastavnik& nastavnik)
	{
		bool predaje = false;
		for (int j = 0; j < nastavnik.getPredmetiRazredi().GetTrenutno(); j++)
		{
			if (nastavnik.getPredmetiRazredi().GetElement2(j) == _razred) //ako proslijedjeni nastavnik predaje u tom razredu
			{
				predaje = true;
				if (_nastavnici.size() == 0 && predaje) //ako ih nema nikako u vektoru i taj proslijedjeni predaje dodajemo ga
				{
					_nastavnici.push_back(&nastavnik);
					return true;
				}

			}
			if (imaIsti(nastavnik) || _nastavnici.size() == 0 || !predaje) //ako ili ima isti ili ih nema nikako ili ne predaje u bilo kojem slucaju vrati false
				return false;
			_nastavnici.push_back(&nastavnik);
			return true;
		}
		
	}
	float Izracunaj()
	{
		float prosjek = 0;
		for (int i = 0; i < _predmetiOcjene.GetTrenutno(); i++)
			prosjek += _predmetiOcjene.GetElement2(i);
		return prosjek / _predmetiOcjene.GetTrenutno();
	}
	bool AddPredmetOcjenu(Predmeti predmet, int ocjena)
	{
		for (int i = 0; i < _nastavnici.size(); i++)
			for (int j = 0; j < _nastavnici[i]->getPredmetiRazredi().GetTrenutno(); j++)
				if (_nastavnici[i]->getPredmetiRazredi().GetElement1(j) == predmet)
				{
					_predmetiOcjene.AddElement(predmet, ocjena);
					return true;
				}
		return false;
	}
	float GetProsjekByNastavnik(const char* imeNastavnika)
	{
		float prosjek = 0;
		for (int i = 0; i < _nastavnici.size(); i++)
			if (strcmp(_nastavnici[i]->GetImePrezime(), imeNastavnika) == 0)//prodje kroz sve nastavnike i ako je isto ime saberemo prosjek
				prosjek+=Izracunaj();
		return prosjek;
	}
};


void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int> kolekcija1;
	int brojElemenata = 15;
	for (size_t i = 0; i < brojElemenata; i++)
		kolekcija1.AddElement(i, i);
	kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;
	Kolekcija<int, int> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;

	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;

	/*if (adel.RemovePredmetRazred(Historija))
		cout << "Predmet uklonjen!" << endl;*/

	Nastavnik goran(adel);
	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;

	Kolekcija<Predmeti, Razredi>& predmetiRazredi = jasmin.getPredmetiRazredi();

	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;


#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	if (denis.AddNastavnik(jasmin)) //ne doda jer jasmin ne predaje u III1 
		cout << "Nastavnik uspjesno dodan" << endl;
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;

	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "Ocjena uspjesno dodana" << endl; //ne doda matematiku jer nema jasmina a on to predaje
	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;

	vector<Nastavnik*>& nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

	Kolekcija<Predmeti, int>& uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
	cout << "Prosjecna ocjena kod nastavnika Adel Handzic je " << denis.GetProsjekByNastavnik("Adel Handzic") << endl;//promjenjeno na Adel Handzic zato jer jasmina nema pa ne ispise nista

	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause");
}