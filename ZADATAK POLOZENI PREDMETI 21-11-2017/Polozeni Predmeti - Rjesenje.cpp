#include <iostream>
using namespace std;


char * crt = "\n----------------------------------------------------\n";
class Datum
{
	int * _dan, *_mjesec, *_godina;
public:
	Datum(int d, int m, int g)
	{
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}

	Datum(const Datum &d)
	{
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
	}

	Datum &operator =(const Datum &d)
	{
		if (this != &d)
		{
			delete _dan;
			_dan = new int(*d._dan);
			delete _mjesec;
			_mjesec = new int(*d._mjesec);
			delete _godina;
			_godina = new int(*d._godina);
		}
		return *this;
	}
	~Datum()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, Datum obj)
	{
		COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina;
		return COUT;
	}
};

template<class T, int velicina>
class FITArray
{
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;
public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
	FITArray(const FITArray &obj);
	FITArray &operator =(const FITArray &obj);
	int GetTrenutno() { return _trenutno; }
	T * GetNiz() { return _niz; }

	bool operator +=(const T &element);
	bool operator -=(const T &element);
	FITArray<T, velicina> operator ()(int OD, int DO);
	template<typename Tip, int v>
	friend ostream &operator << (ostream &OUT, const FITArray<Tip, v> &obj);
};

template<typename T, int velicina>
FITArray<T, velicina> &FITArray<T, velicina>::operator =(const FITArray<T, velicina> &obj)
{
	if (this != &obj)
	{
		_trenutno = obj._trenutno;
		_dozvoliDupliciranje = obj._dozvoliDupliciranje;
		for (int i = 0; i < _trenutno; i++)
			_niz[i] = obj._niz[i];
	}
	return *this;
}

template<typename T, int velicina>
FITArray<T, velicina>::FITArray(const FITArray<T, velicina> &obj) :
	_trenutno(obj._trenutno),
	_dozvoliDupliciranje(obj._dozvoliDupliciranje)
{
	for (int i = 0; i < _trenutno; i++)
		_niz[i] = obj._niz[i];
}

template<typename T, int velicina>
bool FITArray<T, velicina>::operator +=(const T &element)
{
	if (_trenutno == velicina) return false;

	if (!_dozvoliDupliciranje)
		for (int i = 0; i < _trenutno; i++)
			if (_niz[i] == element)
				return false;

	_niz[_trenutno++] = element;
	return true;

}

template<typename T, int velicina>
bool FITArray<T, velicina>::operator -=(const T &element)
{
	bool uklonjeno = false;
	for (int i = 0; i < _trenutno; i++)
		if (_niz[i] == element)
		{
			for (int j = i; j < _trenutno - 1; j++)
				_niz[j] = _niz[j + 1];
			_trenutno--;
			uklonjeno = true;
		}
	return uklonjeno;
}
template<typename T, int velicina>
FITArray<T, velicina> FITArray<T, velicina>::operator ()(int OD, int DO)
{
	FITArray<T, velicina> temp(_dozvoliDupliciranje);
	if (OD >= 0 && OD < _trenutno)
	{
		if (DO > _trenutno) DO = _trenutno;
		for (int i = OD; i < DO; i++)
			temp += _niz[i];

	}
	return temp;
}
template<typename Tip, int v>
ostream &operator <<(ostream &OUT, const FITArray<Tip, v> &obj)
{
	for (int i = 0; i < obj._trenutno; i++)
		OUT << obj._niz[i] << " ";
	return OUT;
}


class PolozeniPredmet
{
	char * _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	PolozeniPredmet() : _naziv(nullptr), _ocjena(5), _datumPolaganja(1, 1, 2000) {}
	PolozeniPredmet(const Datum &d, const char *naziv, int ocjena);
	PolozeniPredmet(const PolozeniPredmet &p);
	PolozeniPredmet &operator =(const PolozeniPredmet &p);
	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }
	int GetOcjena() const { return _ocjena; }
	friend bool operator ==(const PolozeniPredmet &p1, const PolozeniPredmet &p2);
	friend ostream & operator<<(ostream & COUT, const PolozeniPredmet & obj)
	{
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}
};

PolozeniPredmet::PolozeniPredmet(const PolozeniPredmet &p) : _datumPolaganja(p._datumPolaganja), _ocjena(p._ocjena)
{
	int size = strlen(p._naziv) + 1;
	_naziv = new char[size];
	strcpy_s(_naziv, size, p._naziv);
}

PolozeniPredmet::PolozeniPredmet(const Datum &d, const char *naziv, int ocjena) : _datumPolaganja(d)
{
	if (!naziv) return;
	if (ocjena < 5 || ocjena > 10) return;

	_ocjena = ocjena;

	int size = strlen(naziv) + 1;
	_naziv = new char[size];
	strcpy_s(_naziv, size, naziv);
}

PolozeniPredmet &PolozeniPredmet::operator =(const PolozeniPredmet &p)
{
	if (this != &p)
	{
		delete[] _naziv;
		int size = strlen(p._naziv) + 1;
		_naziv = new char[size];
		strcpy_s(_naziv, size, p._naziv);

		_ocjena = p._ocjena;
		_datumPolaganja = p._datumPolaganja;
	}
	return *this;
}

bool operator ==(const PolozeniPredmet &p1, const PolozeniPredmet &p2)
{
	return strcmp(p1._naziv, p2._naziv) == 0;
}

class Student
{
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char * _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:
	Student(const char *imePrezime);
	~Student()
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	void DodajPredmet(const PolozeniPredmet &predmet);
	double GetProsjek();
	Student &operator =(const Student &s);
	friend ostream & operator<<(ostream & COUT, Student & obj)
	{
		COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
		return COUT;
	}
};

int Student::_indeksCounter(160000);

Student::Student(const char *imePrezime) : _indeks(_indeksCounter++)
{
	if (!imePrezime) return;

	int size = strlen(imePrezime) + 1;
	_imePrezime = new char[size];
	strcpy_s(_imePrezime, size, imePrezime);
}

void Student::DodajPredmet(const PolozeniPredmet &predmet)
{
	_polozeniPredmeti += predmet;
}

double Student::GetProsjek()
{
	double suma = 0;
	for (int i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
		suma += _polozeniPredmeti.GetNiz()[i].GetOcjena();
	return suma / _polozeniPredmeti.GetTrenutno();
}

Student &Student::operator =(const Student &s)
{
	if (this != &s)
	{
		_polozeniPredmeti = s._polozeniPredmeti;
	}
	return *this;
}



void main()
{
	const int max = 20;

	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);

	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza

	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;

	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza

	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;

	FITArray<int, max> noviNizIntegera(nizIntegera);

	cout << crt << noviNizIntegera << crt;

	// parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u 
	// slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije 
	// OD pa do posljednje dostupnog elementa 
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;

	system("pause>0");
}