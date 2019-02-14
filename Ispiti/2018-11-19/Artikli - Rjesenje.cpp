#include <iostream>
/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI 
OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, 
OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
using namespace std;

const char * crt = "\n------------------------------------\n";

char * AlocirajNizKaraktera(const char * sadrzaj) 
{
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
class Datum 
{
	int *_dan, *_mjesec, *_godina;

	int GetBrojPrestupnihGodina() const
	{
		int godina = *_godina;
		if (*_mjesec <= 2) godina--;
		return godina / 4 - godina / 100 + godina / 400;
	}

	long int GetUkupnoDana() const
	{
		const int daniUMjesecu[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		long int broj = *_godina * 365 + *_dan;
		for (int i = 0; i < *_mjesec - 1; i++)
			broj += daniUMjesecu[i];
		broj += GetBrojPrestupnihGodina();
		return broj;
	}
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) 
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum &d)
	{
		delete _dan;
		_dan = new int(*d._dan);
		delete _mjesec;
		_mjesec = new int(*d._mjesec);
		delete _godina;
		_godina = new int(*d._godina);
	}

	~Datum() 
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	friend int operator -(const Datum &d1, const Datum &d2);
	friend ostream& operator<< (ostream &COUT, const Datum &obj) 
	{
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};

int operator -(const Datum &d1, const Datum &d2)
{
	return d1.GetUkupnoDana() - d2.GetUkupnoDana();
}

template<class T>
class Kolekcija 
{
	T * _niz;
	int _trenutno;
public:
	Kolekcija() : _trenutno(0), _niz(nullptr) {}
	Kolekcija(const Kolekcija &k) : _trenutno(k._trenutno), _niz(new T[k._trenutno])
	{
		for (int i = 0; i < _trenutno; i++)
			_niz[i] = k._niz[i];	
	}

	Kolekcija(Kolekcija &&k) : _trenutno(k._trenutno), _niz(new T[k._trenutno])
	{
		_niz = k._niz;
		k._niz = nullptr;
	}

	Kolekcija<T> &operator =(const Kolekcija &k)
	{
		_trenutno = k._trenutno;
		_niz = new T[_trenutno];
		for (int i = 0; i < _trenutno; i++)
			_niz[i] = k._niz[i];
		return this;
	}

	
	~Kolekcija() { delete[] _niz; _niz = nullptr; _trenutno = 0; }
	T * GetNiz() const { return _niz; }
	int GetTrenutno() const { return _trenutno; }
	void Add(const T &element)
	{
		T *temp = new T[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
			temp[i] = _niz[i];
		temp[_trenutno] = element;
		delete[] _niz;
		_niz = temp;
		_trenutno++;
	}

	template<typename T>
	friend ostream &operator <<(ostream &OUT, const Kolekcija<T> &k);

	T &operator [](int i) const
	{
		if (i >= 0 && i < _trenutno)
			return _niz[i];
	}
	
};

template<typename T>
ostream &operator <<(ostream &OUT, const Kolekcija<T> &k)
{
	for (int i = 0; i < k.GetTrenutno(); i++)
		OUT << k.GetNiz()[i] << endl;
	return OUT;
}

class Usluga {
	char* _naziv;
	double _cijena;//cijena usluge je izrazena po danu koristenja
public:
	Usluga() : _naziv(nullptr), _cijena(0) {}
	Usluga(const char* naziv, double cijena) : _cijena(cijena) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	Usluga(const Usluga &u) : _naziv(AlocirajNizKaraktera(u._naziv)), _cijena(u._cijena) { cout << "UMove" << endl; }
	Usluga &operator =(const Usluga &u);
	~Usluga() { delete[] _naziv; _naziv = nullptr; }
	double GetCijena() { return _cijena; }
	const char * GetNaziv() { return _naziv; }
	friend bool operator ==(const Usluga &u1, const Usluga &u2);
	friend ostream& operator<< (ostream &COUT, const Usluga &obj);
};

Usluga &Usluga::operator =(const Usluga &u)
{
	if (this != &u)
	{
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(u._naziv);
		_cijena = u._cijena;
	}
	cout << "uMove" << endl;
	return *this;
}

bool operator ==(const Usluga &u1, const Usluga &u2)
{
	return strcmp(u1._naziv, u2._naziv) == 0;
}


ostream& operator<< (ostream &COUT, const Usluga &obj) 
{
	COUT << obj._naziv << " -> \t\t" << obj._cijena << " KM" << endl;
	return COUT;
}

class Rezervacija 
{
	static int _rezervacijeIDBrojac;
	const int _rezervacijaID; ///broj rezervacije krece od 160000
	Datum _rezervacijaOD;
	Datum _rezervacijaDO;
	double _cijenaPoDanu; //cijena osnovnih usluga koja ne ukljucuje dodatne usluge
	Kolekcija<Usluga> _dodatneUsluge; //dodatne usluge mogu biti: sauna, sportski tereni, kuglanje, masaza i sl. 
public:
	Rezervacija(Datum OD, Datum DO, double cijenaPoDanu) :
		_rezervacijaOD(OD), 
		_rezervacijaDO(DO), 
		_cijenaPoDanu(cijenaPoDanu), 
		_rezervacijaID(_rezervacijeIDBrojac++)
	{}
	void PrintRacun();
	friend bool operator +=(Rezervacija &r, const Usluga &u);
	Usluga *operator [](const char *nazivUsluge);
	Kolekcija<Usluga> operator()(double x, double y);
	
};

int Rezervacija::_rezervacijeIDBrojac = 160000;

void Rezervacija::PrintRacun()
{
	int trajanjeRezervacije = _rezervacijaDO - _rezervacijaOD;
	if (trajanjeRezervacije > 30) trajanjeRezervacije = 30;
	double cijenaDodatneUsluge = 0, cijenaOsnovneUsluge = _cijenaPoDanu * trajanjeRezervacije;
	/*
	for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		cijenaDodatneUsluge += _dodatneUsluge.GetNiz()[i].GetCijena();

	cout << crt
		<< "R.ID: " << _rezervacijaID << endl
		<< "OD: " << _rezervacijaOD << endl
		<< "DO: " << _rezervacijaDO << crt
		<< "DODATNE USLUGE : " << crt << _dodatneUsluge << crt
		<< "Osnovne usluge-> " << cijenaOsnovneUsluge << " KM" << crt
		<< "Dodatne usluge-> " << cijenaDodatneUsluge << " KM" << crt
		<< "Ukupno -> " << cijenaOsnovneUsluge + cijenaDodatneUsluge << " KM" << crt;
	*/

	cout << crt
		<< "R.ID: " << _rezervacijaID << endl
		<< "OD: " << _rezervacijaOD << endl
		<< "DO: " << _rezervacijaDO << crt
		<< "DODATNE USLUGE : " << crt;
	for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
	{
		cout << _dodatneUsluge.GetNiz()[i].GetNaziv() << " -> " << _dodatneUsluge.GetNiz()[i].GetCijena();
		if (i != _dodatneUsluge.GetTrenutno() - 1) cout << endl;
		cijenaDodatneUsluge += _dodatneUsluge.GetNiz()[i].GetCijena();
	}
	cout << crt 
		<< "Osnovne usluge-> " << cijenaOsnovneUsluge << " KM" << crt
		<< "Dodatne usluge-> " << cijenaDodatneUsluge << " KM" << crt
		<< "Ukupno -> " << cijenaOsnovneUsluge + cijenaDodatneUsluge << " KM" << crt;
}
Usluga *Rezervacija::operator[](const char * nazivUsluge)
{
	for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		if (strcmp(_dodatneUsluge.GetNiz()[i].GetNaziv(), nazivUsluge) == 0)
			return &_dodatneUsluge.GetNiz()[i];
	return nullptr;
}
bool operator +=(Rezervacija &r, const Usluga &u)
{
	for (int i = 0; i < r._dodatneUsluge.GetTrenutno(); i++)
		if (r._dodatneUsluge.GetNiz()[i] == u)
			return false;
	r._dodatneUsluge.Add(u);
	return true;
}

Kolekcija<Usluga> Rezervacija::operator ()(double x, double y)
{
	Kolekcija<Usluga> temp;
	for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
		if (x <= _dodatneUsluge.GetNiz()[i].GetCijena() && _dodatneUsluge.GetNiz()[i].GetCijena() <= y)
			temp.Add(_dodatneUsluge.GetNiz()[i]);
	return temp;
}

void main() 
{
	cout << crt << "TRAJANJE ISPITA -> 90 minuta " << crt;
	Kolekcija<int> brojevi;
	for (int i = 0; i < 15; i++)
		brojevi.Add(i);
	cout << brojevi << crt;

	//u okviru klase Usluga implementirati MOVE konstruktor
	Usluga Parking("Parking", 5), Dorucak("Dorucak", 10), Rucak("Rucak", 15), Veseraj("Veseraj", 10);

	//rezervacijaOD, rezervacijaDO, cijenaPoDanu
	Rezervacija rezervacija(Datum(25, 10, 2018), Datum(30, 10, 2018), 59.9);

	//dodaje novu uslugu u rezervaciju. onemoguciti ponavljanje usluga
	if (rezervacija += Parking)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Dorucak)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Rucak)
		cout << "Usluga uspjesno dodana!" << endl;
	if (rezervacija += Veseraj)
		cout << "Usluga uspjesno dodana!" << endl;
	if (!(rezervacija += Dorucak))
		cout << "Usluga vec postoji!" << endl;

	/*prikazuje racun formatiran na nacin prikazan na slici. prilikom izracunavanja iznosa 
	koristiti cijene osnovnih i dodatnih usluga, kao i broj dana za koje je napravljena rezervacija 
	(napomena: duzina trajanja rezervacije je maksimalno 30 dana)*/
	rezervacija.PrintRacun();

	//vraca pokazivac na uslugu sa proslijedjenim nazivom
	Usluga * p = rezervacija["Dorucak"];
	if (p != nullptr)
		cout << *p << crt;

	//vraca sve dodatne usluge koje imaju cijenu u opsegu vrijednosti parametara
	Kolekcija<Usluga> uslugePoCijeni = rezervacija(8, 12);
	for (size_t i = 0; i < uslugePoCijeni.GetTrenutno(); i++)
		cout << uslugePoCijeni[i] << crt;

	cin.get();
}

/*
------------------------------------
R.ID: 160000
OD: 25 10 2018
DO: 30 10 2018
------------------------------------
DODATNE USLUGE:
------------------------------------
Parking -> 5 KM
Dorucak -> 10 KM
Rucak -> 15 KM
Veseraj -> 10 KM
------------------------------------
Osnovne usluge-> 299.5 KM
------------------------------------
Dodatne usluge-> 200 KM
------------------------------------
Ukupno -> 499.5 KM
------------------------------------
*/