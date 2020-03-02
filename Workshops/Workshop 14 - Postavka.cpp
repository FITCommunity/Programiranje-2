#include <iostream>	
#include <string>	
#include <vector>	

using namespace std;

template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max];
	T2* _elementi2[max];
	int _trenutno;
public:
	Kolekcija()
	{
		for (int i = 0; i < max; i++)
		{
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
		_trenutno = 0;
	}

	Kolekcija(const Kolekcija& k)
	{
		for (int i = 0; i < max; i++)
		{
			if (i < k._trenutno)
			{
				_elementi1[i] = new T1(*k._elementi1[i]);
				_elementi2[i] = new T2(*k._elementi2[i]);
			}
			else
			{
				_elementi1[i] = nullptr;
				_elementi2[i] = nullptr;
			}
		}

		_trenutno = list._trenutno;

	}
	~Kolekcija()
	{
		for (int i = 0; i < _trenutno; i++)
		{
			delete _elementi1[i];
			_elementi1[i] = nullptr;

			delete _elementi2[i];
			_elementi2[i] = nullptr;
		}
	}

	void Dodaj(T1& el1, T2& el2)
	{
		if (_trenutno == _max)
			throw exception("Dostigli ste kapacitet kolekcije.");

		_elementi1[_trenutno] = new T1(el1);
		_elementi2[_trenutno] = new T2(el2);

		_trenutno++;

	}

	T1& GetElement1(int index)
	{
		if (index >= 0 && index < _trenutno)
			return *_elementi1[index];

		throw exception("Vrijednost indeksa nije validna.");
	}

	T2& GetElement2(int index)
	{
		if (index >= 0 && index < _trenutno)
			return *_elementi2[index];

		throw exception("Vrijednost indeksa nije validna.");

	}

	int GetTrenutno()const { return _trenutno; }

};

class Uplata {
	char* _datum;
	double _iznos;
public:
	Uplata(const char* datum, double iznos)
	{
		int vel = strlen(datum) + 1;
		_datum = new char[vel];
		strcpy_s(_datum, vel, datum);

		_iznos = iznos;
	}

	~Uplata()
	{
		delete[] _datum;
		_datum = nullptr;
	}

	friend ostream& operator<<(ostream&, const Uplata&);
};

ostream& operator<<(ostream& cout, const Uplata& u)
{
	cout << "Datum uplate: " << u._datum << endl;
	cout << "Iznos: " << u._iznos << endl;

	return cout;
}

class Oprema
{
	string _naziv;
	string* _proizvodjac;
	double _cijena;
	int _dostupnoNaStanju;
public:
	//Konstruktor i destruktor

	//Osnovne funkcije za rad sa klasom
};

class Ucenik
{
	string _imePrezime;
	int _godiste;
	bool _posjedujeOpremu;
	vector<Oprema>* _iznajmljenaOprema; //Trenutno iznajmljena oprema
	Kolekcija<Uplata, string, 100> _uplate; //Drugi parametar tipa string predstavlja svrhu uplate: trening ili oprema
public:
	Ucenik(string imePrezime, int godiste, bool posjedujeOpremu = false)
	{
		//Konstruktor dopuniti po potrebi
		_imePrezime = imePrezime;
		_godiste = godiste;
		_posjedujeOpremu = posjedujeOpremu;
	}

	//Destruktor

	//Preklopljeni operator+= za evidenciju iznajmljene opreme.

	//Preklopljeni operator-= za uklanjanje opreme kada se vrati.

	//Funkciju za dodavanje uplata.

};

enum TipTreninga { Pocetnicki, Rekreativni, Profesionalni };
class SkiTrener
{
	string _imePrezime;
	bool _certificiran;
	char _spol;
	TipTreninga  _tipTreninga;
public:
	//Osnovne funkcije za rad sa klasom
};

class Trening
{
	string* _datum;
	SkiTrener* _trener;
	vector<Ucenik*> _ucenici;
	int _brojCasova;
public:
	//Konstruktor i destruktor
	//Napomena: Atributi _trener i _ucenici čuvaju samo adrese objekata koji su pohranjeni u glavnoj klasi SkiKurs.

	//Operator += za dodavanje ucenika na trening.

	//Operator za ispis.
};

class SkiKurs {
	string _periodOdrzavanja;
	vector<SkiTrener> _treneri;
	vector<Ucenik> _polaznici;
	vector<Trening> _treninzi;
public:
	//Konstruktor

	//Funkciju za dodavanje trenera (bez dupliranja elemenata).

	//Funkciju za dodavanje polaznika (bez dupliranja elemenata).

	//Funkciju za dodavanje odrzanih treninga.

	//Funkciju za dodavanje uplate uceniku za odredjeni trening (dakle, funkcija prima 3 parametra: uplata, ucenik, trening).
	//Prvenstveno je potrebno provjeriti da li je ucenik uopste evidentiran na datom treningu.
	//Cijena jednog casa zavisi od tipa treninga na kojem je ucenik bio:
	//Pocetnicki - 10KM
	//Rekreativni - 15KM
	//Profesionalni - 20KM
	//Uplata treba da bude tacnog iznosa proracunatog na osnovu prethodne kategorizacije i broja casova odrzanog treninga.
	//U svim slucajevima kada je neko od ogranicenja naruseno, baciti izuzetak.

	//Funkciju koja pronalazi ski trenera sa najvecim brojem odrzanih casova i ispisuje njegov ostvareni profit.

	//Funkciju koja pronalazi ucenika od kojeg je ostvarena najveca zarada, ukljucujuci uplate za iznajmljenu opremu.

	//Funkciju koja sortira podatke o kompletnom kursu. Podaci trebaju biti sortirani na sljedeci nacin: 
	//- treneri prema kategoriji
	//- treninzi prema broju ucenika koji su prisustvovali
	//- polaznici prema godistu.
	//Ovu funkciju je potrebno pozvati kreiranjem posebnog thread-a.

	//Funkciju koja vrsi ispis svih podataka po kategorijama i sortirano u skladu sa zahtijevima
};


int main() {


	system("pause");
	return 0;
}