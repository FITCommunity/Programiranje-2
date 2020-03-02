#include<iostream>
using namespace std;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}


template <class T1, class T2, int max>
class Kolekcija
{
	T1 _elementi1[max];
	T2 _elementi2[max];
	int _trenutno;
public:
	//Implementirati potrebne funkcije za rad sa kolekcijom
	Kolekcija() : _trenutno(0){}

	void AddElement(T1 el1, T2 el2)
	{
		if (_trenutno == max)
			return;

		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno++] = el2;

	}

	friend ostream& operator<<<>(ostream&, const Kolekcija&);
};

template <class T1, class T2, int max>
ostream& operator<<(ostream& cout, const Kolekcija<T1, T2, max>& k)
{
	for (size_t i = 0; i < k._trenutno; i++)
	{
		cout << k._elementi1[i]<<endl;
		cout << k._elementi2[i];
	}

	return cout;
}

class Ispit
{
	char* _predmet;
	char _datumOdrzavanja[12];
	char _vrijemeOdrzavanja[6]; // početak ispita
	int _trajanje; //trajanje ispita u minutama
	int _maxBrojBodova;
	double _rezultat; //procentualni rezultat ispita
public:
	Ispit(const char* predmet, const char* datumOdrzavanja, const char* vrijemeOdrzavanja, int trajanje)
	{
		_predmet = AlocirajNizKaraktera(predmet);

		strncpy_s(_datumOdrzavanja, datumOdrzavanja, _TRUNCATE);
		strncpy_s(_vrijemeOdrzavanja, vrijemeOdrzavanja, _TRUNCATE);

		_trajanje = trajanje;

	}

	~Ispit()
	{
		delete[] _predmet;
		_predmet = NULL;
	}

void Info()
	{
		cout << "Predmet: " << _predmet<<endl;
		cout << "Termin ispita: " << _datumOdrzavanja << " u " << _vrijemeOdrzavanja << endl;
		cout << "Trajanje: " << _trajanje << endl;

		cout << "Maksimalan broj bodova: " << _maxBrojBodova << endl;
		cout << "Rezultat: " << _rezultat << endl;
	}

};


class PismeniIspit
{
	Kolekcija<char*, int, 50>* _pitanja; //kolekcija pitanja sa brojem bodova
	Kolekcija<char*, int, 50> _odgovori; //kolekcija odgovora sa brojem osvojenih bodova
	int _brTacnihOdgovora;
	int _brOsvojenihBodova;
public:

	//Konstruktor i destruktor funkcije

	//Konstruktor kopije

	//Operator() za dodavanje pitanja u kolekciju uz pripadajući broj bodova.
	//Ispit ne smije sadržavati ista pitanja. Broj bodova na jednom pitanju ne smije biti negativan.

	//Operator+= za dodavanje odgovora na pitanje. Odgovori se dodaju u redoslijedu dodavanja pitanja.
	//Broj osvojenih bodova se inicijalno postavlja na 0. Moguće je dodati i prazan tekst kao odgovor.

	//Funkciju za ocjenu tačnog odgovora koja kao parametar prima redni broj pitanja u kolekciji i tačan odgovor. 
	//Funkcija treba da pronađe odgovor na traženo pitanje, te da taj odgovor uporedi sa tačnim odgovorom i postavi
	//osvojene bodove. Student može osvojiti 0 ili maksimalan broj bodova na pitanju. U skladu sa rezultatom
	//provjere postaviti vrijednosti odgovarajućih atributa.
};

class PrakticniIspit
{
	Kolekcija<char*, char*, 3> _alati; //potrebni alati i njihove verzije, npr. alat "Visual Studio", verzija "2017"
	char* _zadatak; //tekst zadatka
	bool _zadovoljeno; //true ako je student zadovoljio na ispitu, u suprotnom false
public:
	//Na osnovu prethodne implementacije klase PismeniIspit osmisliti i implementirati
	//potrebne funkcije za rad sa klasom PrakticniIspit.
};

int main()
{
	//Testirati sve dostupne funkcionalnosti putem datih kolekcija.
	//Drugi parametar kolekcije predstavlja broj indeksa studenta.

	Kolekcija<PismeniIspit, char*, 100> _pismeniIspiti;
	Kolekcija<PrakticniIspit, char*, 100> _prakticniIspiti;

	system("pause");
	return 0;
}
