#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<fstream>
#include<regex>
#include<iterator>
#include<mutex>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const char* crt = "\n-------------------------------\n";
enum Sortiranje { ASC, DESC };
enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
enum Razred { I , II, III, IV };
const char* ispisPredmeta[] = { "MATEMATIKA", "FIZIKA", "HEMIJA", "GEOGRAFIJA"," NOT_SET" };
const char* ispisRazreda[] = { " I ", "II"," III", "IV" };

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template <class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int _trenutnoElemenata;
	bool _dozvoliDupliranje;
	Sortiranje _sortiranje;
	bool Uslov(Sortiranje sort, int i)
	{
		if (sort == ASC && *_elementi1[i] > * _elementi1[i + 1])
			return true;

		if (sort == DESC && *_elementi1[i] < * _elementi1[i + 1])
			return true;
		return false;
	}
	bool ProvjeraDuplih(T1 el1, T2 el2)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			if (!_dozvoliDupliranje && (*_elementi1[i] == el1 && *_elementi2[i] == el2))
				return true;
		}
		return false;
	}
	void Sortiraj()
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < _trenutnoElemenata-1; i++)
			{
				if (Uslov(_sortiranje, i))
				{
					T1 temp1 = *_elementi1[i];
					*_elementi1[i] = *_elementi1[i + 1];
					*_elementi1[i + 1] = temp1;

					T2 temp2 = *_elementi2[i];
					*_elementi2[i] = *_elementi2[i + 1];
					*_elementi2[i + 1] = temp2;
					prolaz = true;
				}
			}
		}
	}
	void ADD(T1 el1, T2 el2)
	{
		_elementi1[_trenutnoElemenata] = new T1(el1);
		_elementi2[_trenutnoElemenata] = new T2(el2);
		_trenutnoElemenata++;
	}
public:
	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
		_trenutnoElemenata = 0;
		_sortiranje = sortiranje;
		_dozvoliDupliranje = dozvoliDupliranje;
	}
	Kolekcija(const Kolekcija& original) : _trenutnoElemenata(original._trenutnoElemenata), _dozvoliDupliranje(original._dozvoliDupliranje)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = new T1(*original._elementi1[i]);
			_elementi2[i] = new T2(*original._elementi2[i]);
		}

		for (int i = _trenutnoElemenata; i < max; i++)
		{
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
	}
	Kolekcija& operator=(const Kolekcija& druga)
	{
		if (this != &druga)
		{
			if (_trenutnoElemenata != 0)
			{
				for (int i = 0; i < _trenutnoElemenata; i++)
				{
					delete _elementi1[i];
					delete _elementi2[i];
				}
			}
			_trenutnoElemenata = druga._trenutnoElemenata;
			_dozvoliDupliranje = druga._dozvoliDupliranje;
			for (int i = 0; i < _trenutnoElemenata; i++)
			{
				_elementi1[i] = new T1(*druga._elementi1[i]);
				_elementi2[i] = new T2(*druga._elementi2[i]);
			}
		}
		return *this;
	}
	~Kolekcija() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }

	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi2[lokacija];
	}
	void SetElement2(int lokacija, T2 ele2) {
		_elementi2[lokacija] = ele2;
	}

	bool AddElement(T1 el1, T2 el2)
	{
		if (_trenutnoElemenata >= max)
			throw exception("Dosegli ste maksimum kolekcije!\n");
		if (ProvjeraDuplih(el1, el2))
			throw exception("Pokusavate dodati duple elemente!\n");
		ADD(el1, el2);
		Sortiraj();
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << "    " << obj.GetElement2(i) << endl;
		return COUT;
	}
};

class Aktivnost {
	shared_ptr<Razred> _razred;
	string _opis;
	int _ocjena;//1-5
public:
	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
		_ocjena = ocjena;
		_opis = opis;
		_razred = make_shared<Razred>(razred);
	}
	Aktivnost(const Aktivnost& original) : _ocjena(original._ocjena), _opis(original._opis), _razred(original._razred) {}
	Aktivnost& operator=(const Aktivnost& druga)
	{
		if (this != &druga)
		{
			_razred = druga._razred;
			_ocjena = druga._ocjena;
			_opis = druga._opis;
		}
		return *this;
	}
	int  GetOcjenu() const { return _ocjena; }
	string GetOpis() const { return _opis; }
	Razred GetRazred() const { return *_razred; }
	bool operator==(const Aktivnost& druga)
	{
		return _opis == druga._opis && _ocjena == druga._ocjena && *_razred == *druga._razred;
	}
	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
		COUT << "Aktivnost -> "<<ispisRazreda[*obj._razred] << "  Ocjena ( " << obj._ocjena << " )    Opis->  " << obj._opis << endl;
		return COUT;
	}
};

class Polaznik {
protected:
	char* _imePrezime;
	string _brojTelefona;
	bool ValidanTelefon(string telefon)
	{
		return regex_match(telefon, regex("\\+[0-9]{3}(\\([0-9]{2}\\)|\\s[0-9]{2}\\s)[0-9]{3}-[0-9]{3}"));
	}
public:
	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str()))
	{
		if (ValidanTelefon(brojTelefona))
			_brojTelefona = brojTelefona;
		else
			_brojTelefona = not_set;
	}
	Polaznik(const Polaznik& original) : _imePrezime(AlocirajNizKaraktera(original._imePrezime)), _brojTelefona(original._brojTelefona) {}
	Polaznik& operator=(const  Polaznik& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = AlocirajNizKaraktera(drugi._imePrezime);
			_brojTelefona = drugi._brojTelefona;
		}
		return *this;
	}
	~Polaznik() { delete[] _imePrezime; }
	char* GetImePrezime() { return _imePrezime; }
	string GetTelefon() { return _imePrezime; }
	virtual void PredstaviSe() = 0;
};

class Ucenik : public Polaznik {
	Kolekcija<Predmet, Aktivnost, 16>* _aktivnosti;
public:
	void PredstaviSe() {}
	Ucenik(const char* imePrezime, string brojTelefona) : Polaznik(imePrezime, brojTelefona)
	{
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>;
	}
	Ucenik(const Ucenik& original) : Polaznik(original)
	{
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(*original._aktivnosti);
	}
	Ucenik& operator=(const Ucenik& drugi)
	{
		if (this != &drugi)
		{
			Polaznik::operator=(drugi);
			*_aktivnosti = *drugi._aktivnosti;
		}
		return *this;
	}
	~Ucenik() { delete _aktivnosti; _aktivnosti = nullptr; }
	Kolekcija<Predmet, Aktivnost, 16>& GetAktivnosti() { return *_aktivnosti; };
	friend ostream& operator<<(ostream& COUT, Ucenik& n)
	{
		COUT << "Ucenik ->  " << n._imePrezime << "    Kontakt->  " << n._brojTelefona << endl;
		COUT << ":::: AKTIVNOSTI UCENIKA ::::" << crt;
		for (int i = 0; i < n._aktivnosti->GetTrenutno(); i++)
		{
			COUT << "Predmet -> " << ispisPredmeta[n._aktivnosti->GetElement1(i)] << endl;
			COUT  << n._aktivnosti->GetElement2(i) << crt;
		}
		return COUT;
	}

	bool ImaValidnuAktivnost(Aktivnost aktivnost)
	{
		int brojac = 0;
		for (int i = 0; i < _aktivnosti->GetTrenutno(); i++)
		{
			if (_aktivnosti->GetElement2(i).GetOcjenu() > 1 && _aktivnosti->GetElement2(i).GetRazred() == aktivnost.GetRazred())
				brojac++;
		}
		return brojac == 4;
	}
	float GetProsjek()
	{
		float prosjek = 0;
		for (int i = 0; i < _aktivnosti->GetTrenutno(); i++)
		{
			prosjek += _aktivnosti->GetElement2(i).GetOcjenu();
		}
		return prosjek / _aktivnosti->GetTrenutno();
	}

};

mutex mjuteks;

class Skola {
	char* _naziv;
	vector<Ucenik> _ucenici;
	void Mail(Razred razred, float prosjek)
	{
		mjuteks.lock();
		cout << "Uspjesno ste okoncali aktivnosti u okviru " << ispisRazreda[razred] << " sa prosjecnom ocjenom -> " << prosjek << crt;
		mjuteks.unlock();
	}
public:
	Skola(const char* naziv = nullptr) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	Skola(const Skola& original) : _naziv(AlocirajNizKaraktera(original._naziv)), _ucenici(original._ucenici) {}
	Skola& operator=(const Skola& druga)
	{
		if (this != &druga)
		{
			delete[] _naziv;
			_naziv = AlocirajNizKaraktera(druga._naziv);
			_ucenici = druga._ucenici;
		}
		return *this;
	}
	~Skola() {
		delete[] _naziv; _naziv = nullptr;
	}
	char* GetNaziv()const { return _naziv; }
	vector<Ucenik>& GetUcenici() { return _ucenici; };
	friend ostream& operator<<(ostream& COUT, Skola& obj)
	{
		COUT << "Naziv skole -> " << ((obj._naziv != nullptr) ? obj._naziv : "nije postavljen") << endl;
		COUT << "Ucenici: " << crt;
		for (int i = 0; i < obj._ucenici.size(); i++)
			COUT << obj._ucenici[i] << endl;
		return COUT;
	}

	void operator()(const char* nazivUcenika, string brojTelefona)
	{
		for (int i = 0; i < _ucenici.size(); i++)
		{
			if (strcmp(_ucenici[i].GetImePrezime(), nazivUcenika) == 0 || _ucenici[i].GetTelefon() == brojTelefona)
				throw exception("Pokusavate dodati istog ucenika!\n");
		}
		_ucenici.push_back(Ucenik(nazivUcenika, brojTelefona));
	}

	bool DodajAktivnost(const char* imeUcenika, Predmet predmet, Aktivnost aktivnost)
	{
		for (int i = 0; i < _ucenici.size(); i++)
		{
			if (strcmp(_ucenici[i].GetImePrezime(), imeUcenika) == 0)
			{
				int brojacAktivnosti = 0;

				for (int j = 0; j < _ucenici[i].GetAktivnosti().GetTrenutno(); j++)
				{
					if (_ucenici[i].GetAktivnosti().GetElement2(j).GetRazred() == aktivnost.GetRazred() && _ucenici[i].GetAktivnosti().GetElement1(j) == predmet)
						return false;
					
					if (_ucenici[i].GetAktivnosti().GetElement2(j).GetRazred() == aktivnost.GetRazred() && _ucenici[i].GetAktivnosti().GetTrenutno()==4)
							return false;
				}

				_ucenici[i].GetAktivnosti().AddElement(predmet, aktivnost);
				if (_ucenici[i].ImaValidnuAktivnost(aktivnost))
				{
					Razred razred = aktivnost.GetRazred();
					float prosjek = _ucenici[i].GetProsjek();
					thread t1(&Skola::Mail, this, razred,prosjek);
					t1.join();
				}
				return true;
			}
		}
		return false;
	}

	pair<Polaznik*, float> GetNajboljegUcenika()
	{
		pair<Polaznik*, float> novi;
		float najProsjek = INT_MIN;
		int indeksUcenika = 0;
		for (int i = 0; i < _ucenici.size(); i++)
		{
			if (_ucenici[i].GetProsjek() > najProsjek)
			{
				najProsjek = _ucenici[i].GetProsjek();
				indeksUcenika = i;
			}
		}

		Polaznik* polaznik = dynamic_cast<Polaznik*>(&_ucenici[indeksUcenika]);
		if (polaznik != nullptr)
		{
			novi.first = polaznik;
			novi.second = najProsjek;
		}
		return novi;
	}

	bool SpasiUFajl(const char* nazivfajla,bool trebalBrisat=false)
	{
		ofstream upis;
		if (trebalBrisat)
		{
			upis.open(nazivfajla,ios::out);
			if (upis.fail())
				return false;
			upis << *this << endl;
			upis.close();
			return true;
		}
		else {
			upis.open(nazivfajla, ios::app);
			if (upis.fail())
				return false;
			upis << *this << endl;
			upis.close();
			return true;
		}
	}
};

int main() {
	Kolekcija<int, int, 10> kolekcija1(DESC, false);
	try {
		kolekcija1.AddElement(1, 2);
		//dupliranje elemenata nije dozvoljeno
		kolekcija1.AddElement(1, 2);
	}
	catch (exception & ex) {
		cout << ex.what();
	}

	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
		kolekcija1.AddElement(rand(), rand());

	cout << kolekcija1 << endl;

	try {
		//prekoracen maksimalan broj elemenata
		kolekcija1.AddElement(rand(), rand());
	}
	catch (exception & ex) {
		cout << ex.what();
	}
	cout << kolekcija1 << endl;

	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
	cout << kolekcija2 << endl;

	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
	//dodaje novog ucenika u skolu
	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
	gimnazijaMostar("Adel Handzic", "+387(61)333-444");

	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(62)123-132 ili +387 61 321-123
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");

	try
	{
		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
	}


	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematije koje se odrzava u Konjicu 07.02.2019")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
		cout << "Aktivnost nije uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
		cout << "Aktivnost uspjesno dodana" << endl;
	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
		cout << "Aktivnost uspjesno dodana" << endl;
	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
		cout << "Aktivnost uspjesno dodana" << endl;

	////ispisuje sve ucenike i njihove aktivnosti
	cout << gimnazijaMostar << endl;


	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;

	///*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	//Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/

	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt",true))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;

	system("pause>0");
	return 0;
}