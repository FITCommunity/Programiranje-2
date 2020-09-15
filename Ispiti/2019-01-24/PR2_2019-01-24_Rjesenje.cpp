#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iterator>
#include <thread>
#include <mutex>

using namespace std;

const char *crt = "\n-------------------------------------------\n";
enum GodinaStudija { PRVA = 1, DRUGA, TRECA };

char * Alociraj(const char * sadrzaj) 
{
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

mutex m;

template<class T1, class T2>
class Dictionary 
{
	T1 * _elementi1;
	T2 * _elementi2;
	int * _trenutno;
public:
	Dictionary() 
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	Dictionary(const Dictionary<T1, T2> &d)
	{
		_trenutno = new int(*d._trenutno);
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (int i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = d._elementi1[i];
			_elementi2[i] = d._elementi2[i];
		}
	}
	Dictionary<T1, T2> operator= (const Dictionary<T1, T2> &d)
	{
		if (this != &d)
		{
			*_trenutno = *d._trenutno;
			delete[] _elementi1;
			delete[] _elementi2;
			_elementi1 = new T1[*_trenutno];
			_elementi2 = new T2[*_trenutno];
			for (int i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = d._elementi1[i];
				_elementi2[i] = d._elementi2[i];
			}
		}

		return *this;
	}
	~Dictionary() 
	{
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	void AddElement(const T1 &e1, const T2 &e2)
	{
		T1 *temp1 = nullptr; T2 *temp2 = nullptr;
		try
		{
			temp1 = new T1[*_trenutno + 1];
			temp2 = new T2[*_trenutno + 1];
			for (int i = 0; i < *_trenutno; i++)
			{
				temp1[i] = _elementi1[i];
				temp2[i] = _elementi2[i];
			}
			temp1[*_trenutno] = e1;
			temp2[*_trenutno] = e2;
			delete[] _elementi1;
			delete[] _elementi2;
			_elementi1 = temp1;
			_elementi2 = temp2;
			(*_trenutno)++;

		}
		catch (bad_alloc e)
		{
			cout << "Nedovoljno memorije!";
			delete[] temp1;
			delete[] temp2;
		}
		
	}

	Dictionary<T1, T2> getRange(int OD, int DO) const
	{
		if (OD < 0 || DO < 0 || DO > *_trenutno)
			throw exception("Lokacije ne postoji");
		if (DO < OD)
			throw exception("Posljednja lokacije ne moze biti manja od pocetne");

		Dictionary<T1, T2> temp;
		for (int i = OD; i < DO; i++)
			temp.AddElement(_elementi1[i], _elementi2[i]);

		return temp;
	}
	T1& getElement1(int lokacija) const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) const { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream &COUT, const Dictionary &obj) 
	{
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class DatumVrijeme 
{
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
	int toMinute() const
	{
		return *_godina * 365 * 24 * 60 * 60 + *_mjesec * 30 * 24 * 60 * 60 + *_dan * 60 * 60 + *_sati * 60 + *_minuti;
	}
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) 
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme &d)
	{
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		_sati = new int(*d._sati);
		_minuti = new int(*d._minuti);
	}
	DatumVrijeme &operator =(const DatumVrijeme &d)
	{
		*_dan = *d._dan;
		*_mjesec = *d._mjesec;
		*_godina = *d._godina;
		*_sati = *d._sati;
		*_minuti = *d._minuti;

		return *this;
	}
	~DatumVrijeme() 
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, const DatumVrijeme &obj) 
	{
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}

	friend bool operator <(const DatumVrijeme &d1, const DatumVrijeme &d2)
	{
		if (*d1._godina != *d2._godina) return *d1._godina < *d2._godina;
		else if (*d1._mjesec != *d2._mjesec) return *d1._mjesec < *d2._mjesec;
		else if (*d1._dan != *d2._dan) return *d1._dan < *d2._dan;
		else if (*d1._sati != *d2._sati) return *d1._sati < *d2._sati;
		else if (*d1._minuti != *d2._minuti) return *d1._minuti < *d2._minuti;
		return false;
	}

	char *ToCharArray() const
	{
		ostringstream o;
		o << setw(2) << setfill('0') << *_dan << "/"
			<< setw(2) << setfill('0') << *_mjesec << "/"
			<< *_godina << " " << *_sati << ":" << *_minuti;

		return Alociraj(o.str().c_str());
	}

	friend bool ProsaoMinSat(const DatumVrijeme &d1, const DatumVrijeme &d2)
	{
		return d1.toMinute() - d2.toMinute() >= 60;
	}
};

class Predmet
{
	char * _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char * naziv = "", int ocjena = 0, string napomena = "")
	{
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet &p)
	{
		_naziv = Alociraj(p._naziv);
		_ocjena = p._ocjena;
		_napomena = p._napomena;
	}
	Predmet operator= (const Predmet &p)
	{
		if (this != &p)
		{
			delete[] _naziv;
			_naziv = Alociraj(p._naziv);
			_ocjena = p._ocjena;
			_napomena = p._napomena;
		}
		return *this;
	}
	~Predmet()
	{
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, Predmet &obj)
	{
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() const { return _napomena; }
	char * GetNaziv() const { return _naziv; }
	int GetOcjena() const { return _ocjena; }

	void DodajNapomenu(string napomena)
	{
		_napomena += " " + napomena;
	}

	friend bool operator ==(const Predmet &p1, const Predmet &p2)
	{
		return strcmp(p1._naziv, p2._naziv) == 0;
	}
};
class Uspjeh
{
	GodinaStudija * _godina;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Dictionary<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(GodinaStudija godina)
	{
		_godina = new GodinaStudija(godina);
	}
	Uspjeh(const Uspjeh &u)
	{
		_godina = new GodinaStudija(*u._godina);
		_predmeti = u._predmeti;
	}
	Uspjeh operator=(const Uspjeh &u)
	{
		*_godina = *u._godina;
		_predmeti = u._predmeti;

		return *this;
	}
	~Uspjeh() { delete _godina; _godina = nullptr; }

	Dictionary<Predmet, DatumVrijeme> * GetPredmeti() { return &_predmeti; }
	GodinaStudija * GetGodinaStudija() const { return _godina; }

	friend ostream& operator<< (ostream &COUT, const Uspjeh &obj) {
		COUT << *obj._godina << " " << obj._predmeti << endl;
		return COUT;
	}
};

class Student 
{
	char * _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
	bool isValidanEmail(string email)
	{
		return regex_match(email, regex("\\w*\\.?\\w*\\@(hotmail.com|outlook.com|fit.ba)"));
	}
	bool isValidanTelefon(string broj)
	{
		return regex_match(broj, regex("\\d{3}\\s\\d{3}\\s\\d{3}"));
	}
	void PosaljiSMS(const GodinaStudija &g, double prosjek)
	{
		m.lock();
		cout << "Svaka cast za uspjeh " << prosjek << " ostvaren u " << g << " godini studija" << endl;
		m.unlock();
	}
	void PosaljiEmail(const GodinaStudija &g, double prosjek)
	{
		m.lock();
		cout << "FROM:info@fit.ba" << endl
			<< "TO :" << _emailAdresa << endl
			<< "Postovani " << _imePrezime << " evidentirali ste uspjeh za " << g << ". godinu studija." << endl
			<< "Pozdrav." << endl
			<< "FIT Team." << endl;
		m.unlock();
		if (prosjek > 8.0)
		{
			thread sms(&Student::PosaljiSMS, this, g, prosjek);
			sms.join();
		}
		
	}
	void EvidentirajUspjeh(Uspjeh u)
	{
		m.lock();
		double suma = 0;
		for (int i = 0; i < u.GetPredmeti()->getTrenutno(); i++)
			suma += u.GetPredmeti()->getElement1(i).GetOcjena();
		suma /= u.GetPredmeti()->getTrenutno();
		m.unlock();

		thread email(&Student::PosaljiEmail, this, *u.GetGodinaStudija(), suma);
		email.join();
	}
public:
	Student(const char * imePrezime, string emailAdresa, string brojTelefona) 
	{
		_imePrezime = Alociraj(imePrezime);
		_emailAdresa = isValidanEmail(emailAdresa) ? emailAdresa : "notSet@fit.ba";
		_brojTelefona = isValidanTelefon(brojTelefona) ? brojTelefona : "000 000 000";
	}
	Student(const Student &s)
	{
		_imePrezime = Alociraj(s._imePrezime);
		_emailAdresa = s._emailAdresa;
		_brojTelefona = s._brojTelefona;
		_uspjeh = s._uspjeh;
	}
	Student &operator= (const Student &s)
	{
		if (this != &s)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(s._imePrezime);
			_emailAdresa = s._emailAdresa;
			_brojTelefona = s._brojTelefona;
			_uspjeh = s._uspjeh;
		}
		return *this;
	}
	~Student() 
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, Student &obj) 
	{
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		copy(obj._uspjeh.begin(), obj._uspjeh.end(), ostream_iterator<Uspjeh>(COUT, "\n"));
		return COUT;
	}

	bool AddPredmet(const Predmet &p, const GodinaStudija &g, const DatumVrijeme &d)
	{
		for (auto i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			if (*i->GetGodinaStudija() == g)
			{
				for (int j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
					if (i->GetPredmeti()->getElement1(j) == p)
						return false;

				if (!ProsaoMinSat(d, i->GetPredmeti()->getElement2(i->GetPredmeti()->getTrenutno() - 1)))
					return false;

				i->GetPredmeti()->AddElement(p, d);
				thread t(&Student::EvidentirajUspjeh, this, *i);
				t.join();
				return true;
			}

		_uspjeh.emplace_back(g);
		_uspjeh.at(_uspjeh.size() - 1).GetPredmeti()->AddElement(p, d);
		thread t(&Student::EvidentirajUspjeh, this, _uspjeh.at(_uspjeh.size() - 1));
		t.join();
		return true;
	}
	vector<Uspjeh> * GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char * GetImePrezime() { return _imePrezime; }
	int BrojPonavljanjaRijeci(string rijec)
	{
		regex pravilo(rijec);
		int suma = 0;
		for (auto i = _uspjeh.begin(); i != _uspjeh.end(); i++)
		{
			for (int j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
			{
				string temp = i->GetPredmeti()->getElement1(j).GetNapomena();
				auto pocetak = sregex_iterator
				(
					temp.begin(),
					temp.end(),
					pravilo
				);
				auto kraj = sregex_iterator();
				
				suma += distance(pocetak, kraj);
			}
		}

		return suma;
	}
	vector<Predmet> operator()(DatumVrijeme *d1, DatumVrijeme *d2)
	{
		vector<Predmet> temp;
		for (auto i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			for (int j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
				if (*d1 < i->GetPredmeti()->getElement2(j) && i->GetPredmeti()->getElement2(j) < *d2)
					temp.emplace_back(i->GetPredmeti()->getElement1(j));
		return temp;
	}

	Uspjeh *operator[](const char *godina)
	{
		GodinaStudija g;
		if (strcmp(godina, "PRVA") == 0) g = PRVA;
		else if(strcmp(godina, "DRUGA") == 0) g = DRUGA;
		else if(strcmp(godina, "TRECA") == 0) g = TRECA;
		else return nullptr;

		Uspjeh *u = nullptr;
		for (auto i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			if (*i->GetGodinaStudija() == g)
			{
				u = new Uspjeh(g);
				*u = *i;
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
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU
	DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/
	cout << "NA KRAJU ISPITA, RAD PREDAJTE U ODGOVARAJUCI FOLDER NA FTP SERVERU (INTEGRALNI)!" << endl;
	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);
	//funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
	//voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca 
	//iskazane kao dvije cifre
	cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
	temp = datum05072019_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31

	const int DictionaryTestSize = 9;
	Dictionary<int, int> Dictionary1;
	for (size_t i = 0; i < DictionaryTestSize; i++)
		Dictionary1.AddElement(i + 1, i*i);

	try 
	{
		//vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
		//funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost 
		//posljednje lokacije manja od pocetne
		Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
		cout << opseg << endl;
		Dictionary1.getRange(7, 11);
	}
	catch (exception& err) 
	{
		cout << err.what() << endl;
	}
	cout << Dictionary1 << endl;

	Dictionary<int, int> Dictionary2 = Dictionary1;
	cout << Dictionary2 << crt;

	Dictionary<int, int> Dictionary3;
	Dictionary3 = Dictionary1;
	cout << Dictionary3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet MAT("Matematika", 7, "Ucesce na takmicenju"),
		UIT("Uvod u informacijske tehnologije", 9),
		RM("Racunarske mreze", 8),
		EN("Engleski jezik", 6);
	UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << MAT << endl;

	/*
	email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili
	outlook.com ili fit.ba. Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
	za provjeru koristiti regex
	*/
	Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
	Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
	Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");

	/*
	uspjeh se dodaje za svaki predmet na nivou godine studija.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jedne godine,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju 
	dodavanja pojedinih predmeta mora biti najmanje 1 sat).
	godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom 
	(npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati MAT jer je vec dodana u prvoj godini
	if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;

	/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije 
	AddPredmet, Studentu se salje email sa sadrzajem:
	FROM:info@fit.ba
	TO: emailStudenta
	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
	Pozdrav.
	FIT Team.

	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, 
	salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X ostvaren u X godini studija".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTEÆI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
	for (Predmet u : jasminUspjeh)
		cout << u << endl;

	Uspjeh * uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
	if (uspjeh_I_godina != nullptr)
		cout << *uspjeh_I_godina << endl;

	cin.get();
	system("pause>0");
}