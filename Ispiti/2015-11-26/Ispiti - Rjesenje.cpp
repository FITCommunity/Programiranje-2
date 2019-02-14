// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
#include <iostream>

using namespace std;

template<class T1, class T2>
class Kolekcija
{
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutnoElemenata;
public:
	Kolekcija() : _elementi1(nullptr), _elementi2(nullptr), _trenutnoElemenata(0) {}
	Kolekcija(const Kolekcija &k) :
		_elementi1(new T1[k._trenutnoElemenata]),
		_elementi2(new T2[k._trenutnoElemenata]),
		_trenutnoElemenata(k._trenutnoElemenata)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
	}

	Kolekcija &operator =(const Kolekcija &k)
	{
		if (this != &k)
		{
			delete[] _elementi1;
			_elementi1 = new T1[k._trenutnoElemenata];
			delete[] _elementi2;
			_elementi2 = new T2[k._trenutnoElemenata];
			_trenutnoElemenata = k._trenutnoElemenata;
			for (int i = 0; i < _trenutnoElemenata; i++)
			{
				_elementi1[i] = k._elementi1[i];
				_elementi2[i] = k._elementi2[i];
			}
		}
		return *this;
		
	}
	~Kolekcija()
	{
		delete[] _elementi1;
		delete[] _elementi2;
	}

	void AddElement(const T1 &e1, const T2 &e2)
	{
		T1 *temp1 = new T1[_trenutnoElemenata + 1];
		T2 *temp2 = new T2[_trenutnoElemenata + 1];
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		temp1[_trenutnoElemenata] = e1;
		temp2[_trenutnoElemenata] = e2;
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_trenutnoElemenata++;
	}

	void RemoveElement(int pozicija)
	{
		if (pozicija >= 0 && pozicija < _trenutnoElemenata)
		{
			for (int i = pozicija; i < _trenutnoElemenata - 1; i++)
			{
				_elementi1[i] = _elementi1[i + 1];
				_elementi2[i] = _elementi2[i + 1];
			}

			_trenutnoElemenata--;
		}
	}
	int getTrenutno() const { return _trenutnoElemenata; }
	T1 *getElementi1() const { return _elementi1; }
	T2 *getElementi2() const { return _elementi2; }
	friend ostream &operator <<(ostream &OUT, const Kolekcija &k)
	{
		for (int i = 0; i < k.getTrenutno(); i++)
		{
			OUT << k.getElementi1()[i] << " " << k.getElementi2()[i];
			if (i != k.getTrenutno() - 1) OUT << endl;
		}

		return OUT;
	}
};


class Datum
{
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000)
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum &d) : _dan(new int(*d._dan)), _mjesec(new int(*d._mjesec)), _godina(new int(*d._godina)) {}
	Datum &operator =(const Datum &d)
	{
		if (this != &d)
		{
			*_dan = *d._dan;
			*_mjesec = *d._mjesec;
			*_godina = *d._godina;
		}
		return *this;
	}
	friend bool operator ==(const Datum &d1, const Datum &d2)
	{
		return *d1._dan == *d2._dan && *d1._mjesec == *d2._mjesec && *d1._godina == *d2._godina;
	}
	~Datum()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream &COUT, const Datum &obj)
	{
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};
class Student
{
	char * _imePrezime;
	Datum * _datumRodjenja;
public:
	Student(char * imePrezime = "---", Datum d = Datum())
	{
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
		_datumRodjenja = new Datum(d);
	}

	Student(const Student &s)
	{
		int size = strlen(s._imePrezime) + 1;
		delete[] _imePrezime;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, s._imePrezime);

		delete _datumRodjenja;
		_datumRodjenja = new Datum(*s._datumRodjenja);
	}

	Student &operator =(const Student &s)
	{
		if (this != &s)
		{
			int size = strlen(s._imePrezime) + 1;
			delete[] _imePrezime;
			_imePrezime = new char[size];
			strcpy_s(_imePrezime, size, s._imePrezime);

			delete _datumRodjenja;
			_datumRodjenja = new Datum(*s._datumRodjenja);
		}
		return *this;
	}

	friend bool operator ==(const Student &s1, const Student &s2)
	{
		return strcmp(s1._imePrezime, s2._imePrezime) == 0 && *s1._datumRodjenja == *s2._datumRodjenja;
	}
	friend ostream &operator <<(ostream &OUT, const Student &s)
	{
		return OUT << s._imePrezime << " " << *s._datumRodjenja;
	}
	~Student() { delete[] _imePrezime; delete _datumRodjenja; }
};
class Ispit
{
	Datum _datumOdrzavanja;
	char * _opisIspita;
	Kolekcija<Student, Datum> _prijave;
	Kolekcija<Student, int> _rezultati;
public:
	Ispit(const char *opis, const Datum &datum) : _datumOdrzavanja(datum)
	{
		int size = strlen(opis) + 1;
		_opisIspita = new char[size];
		strcpy_s(_opisIspita, size, opis);
	}

	Ispit(const Ispit &i) : 
		_datumOdrzavanja(i._datumOdrzavanja), 
		_prijave(i._prijave), 
		_rezultati(i._rezultati)
	{
		int size = strlen(i._opisIspita) + 1;
		delete[] _opisIspita;
		_opisIspita = new char[size];
		strcpy_s(_opisIspita, size, i._opisIspita);
	}
	bool DodajPrijavu(const Student &s, const Datum &d)
	{
		for (int i = 0; i < _prijave.getTrenutno(); i++)
			if (_prijave.getElementi1()[i] == s)
				return false;
		_prijave.AddElement(s, d);
		return true;
	}

	void DodajRezultat(const Student &s, int ocjena)
	{
		if (ocjena >= 5 && ocjena <= 10)
			for (int i = 0; i < _prijave.getTrenutno(); i++)
				if (_prijave.getElementi1()[i] == s)
				{
					for (int j = 0; j < _rezultati.getTrenutno(); j++)
						if (_rezultati.getElementi1()[j] == s)
							return;
					_rezultati.AddElement(s, ocjena);
					return;
				}
	}
	
	void Sortiraj()
	{
		for(int i = 0; i < _rezultati.getTrenutno() - 1; i++)
			for(int j = i + 1; j < _rezultati.getTrenutno(); j++)
				if (_rezultati.getElementi2()[i] < _rezultati.getElementi2()[j])
				{
					int tempO = _rezultati.getElementi2()[i];
					Student tempS = _rezultati.getElementi1()[i];

					_rezultati.getElementi2()[i] = _rezultati.getElementi2()[j];
					_rezultati.getElementi1()[i] = _rezultati.getElementi1()[j];

					_rezultati.getElementi2()[j] = tempO;
					_rezultati.getElementi1()[j] = tempS;
				}
	}

	void ZakljuciRezultate()
	{
		for (int i = 0; i < _prijave.getTrenutno(); i++)
		{
			bool pronaden = false;
			for(int j = 0; j < _rezultati.getTrenutno(); j++)
				if (_prijave.getElementi1()[i] == _rezultati.getElementi1()[j])
				{
					pronaden = true;
					break;
				}

			if (!pronaden)
			{
				_rezultati.AddElement(_prijave.getElementi1()[i], 5);
			}
		}
	}

	friend ostream &operator <<(ostream &OUT, const Ispit &ispit)
	{
		return OUT << "Opis ispita: " << ispit._opisIspita << endl
				   << "Datum odrzavanja: " << ispit._datumOdrzavanja << endl
			       << "Rezultati: " << endl << ispit._rezultati;
		
	}
	~Ispit() { delete[] _opisIspita; }
};
char *crt = "\n--------------------------------------------------\n";
void main()
{
	//REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost

#pragma region TestiranjeKolekcije
	Kolekcija<int, double> kolekcija1;
	for (size_t i = 0; i < 50; i++)
		kolekcija1.AddElement(i, i + 0.3);
	cout << kolekcija1 << endl;
	cout << crt;

	Kolekcija<int, double> kolekcija2;
	kolekcija2 = kolekcija1;
	kolekcija1.RemoveElement(2);//UMANJITI VELIÈINU NIZA
	cout << kolekcija2 << crt;

	if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;

	Kolekcija<int, double> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeStudenta
	Student denis("Denis Music", Datum(26, 11, 1990));
	Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
	Student goran;
	goran = jasmin;
	Student adel("Adel Handzic", Datum(25, 8, 1990));
	Student marija("Marija Herceg", Datum(15, 6, 1990));
#pragma endregion

#pragma region TestiranjeIspita
	Ispit prIII("PRIII::26.11.2015", danas);
	//DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispti. 
	//onemoguciti dodavanje dva ista studenta
	if (prIII.DodajPrijavu(denis, danas))
		cout << denis << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(jasmin, danas))
		cout << jasmin << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(goran, danas))
		cout << jasmin << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(adel, danas))
		cout << adel << " DODAT na spisak" << endl;
	if (prIII.DodajPrijavu(marija, danas))
		cout << adel << " DODAT na spisak" << endl;

	cout << crt << endl;
	/*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu.
	za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
	*/
	prIII.DodajRezultat(goran, 7);
	prIII.DodajRezultat(jasmin, 6);
	prIII.DodajRezultat(adel, 8);
	prIII.DodajRezultat(marija, 9);

	/*Sortiraj - sortira rezultate ispita prema ocjeni*/
	prIII.Sortiraj();
	/*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit
	a nije im evidentirana ocjena*/
	prIII.ZakljuciRezultate();
	//rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuèeni
	cout << prIII << crt;

	Ispit prIII_2(prIII);
	cout << prIII_2 << crt;
#pragma endregion
	system("pause>0");
}