#include<iostream>
using namespace std;

template<class T1, class T2>
class List {
	T1* _elementi1;
	T2* _elementi2;
	const int _max;
	int _trenutno;
public:
	List(int max) : _max(max)
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}

	List(const List& list) : _max(list._max)
	{
		_elementi1 = new T1[list._trenutno];
		_elementi2 = new T2[list._trenutno];

		for (int i = 0; i < list._trenutno; i++)
		{
			_elementi1[i] = list._elementi1[i];
			_elementi2[i] = list._elementi2[i];
		}

		_trenutno = list._trenutno;

	}
	~List()
	{
		delete[] _elementi1;
		_elementi1 = nullptr;

		delete[] _elementi2;
		_elementi2 = nullptr;
	}

	bool Add(T1& el1, T2& el2)
	{
		if (_trenutno == _max)
			return false;

		for (int i = 0; i < _trenutno; i++)
		{
			if (_elementi1[i] == el1 && _elementi2[i] == el2)
				return false;
		}

		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];


		for (int i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;
	}

	bool Remove(int index)
	{
		if (index < 0 || index > _trenutno)
			return false;

		T1* temp1 = new T1[_trenutno - 1];
		T2* temp2 = new T2[_trenutno - 1];

		int j = 0;
		for (int i = 0; i < _trenutno; i++)
		{
			if (i != index)
			{
				temp1[j] = _elementi1[i];
				temp2[j] = _elementi2[i];
				j++;
			}
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		_trenutno--;

		return true;
	}

	T1& GetElement1(int index)
	{
		if (index >= 0 && index < _trenutno)
			return _elementi1[index];
	}

	T2& GetElement2(int index)
	{
		if (index >= 0 && index < _trenutno)
			return _elementi2[index];

	}

	int GetTrenutno()const { return _trenutno; }

	friend ostream& operator<<(ostream&, const List&);
};

template<class T1, class T2>
ostream& operator<<(ostream& cout, const List<T1, T2>& list)
{
	for (int i = 0; i < list._trenutno; i++)
	{
		cout << list._elementi1[i] << "\t" << list._elementi2[i] << endl;
	}

	return cout;
}

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Pitanje
{
	int _id;
	char* _oblast;
	char* _tekst;
	double _bodovi;
public:
	Pitanje(int id, const char* tekst, const char* oblast, double bodovi) :
		_id(id), _bodovi(bodovi)
	{
		_tekst = AlocirajNizKaraktera(tekst);
		_oblast = AlocirajNizKaraktera(oblast);
	}

	virtual ~Pitanje() = 0
	{
		delete[] _tekst;
		_tekst = nullptr;

		delete[] _oblast;
		_oblast = nullptr;
	}

	virtual void Info()
	{
		cout << "Pitanje: " << _tekst << endl;
	}
};

//Pitanje na kojem studenti upisuju odgovore.
//Pohranjuje se tačan odgovor od strane edukatora.
class EsejskoPitanje : public Pitanje {
	char* _tacanOdgovor;
	char* _odgovorStudenta;
public:
	//Konstruktor i destruktor

	//Funkciju za izmjenu svih atributa klase
};

//Pitanje koje može imati više tačnih odgovora. Student bira ponuđene opcije. 
class MCMAPitanje : public Pitanje
{
	List<char*, bool> _odgovori; //ponuđeni odgovori sa oznakama tačnih odgovora
	int* _oznaceniOdgovoriStudenta; //čuvaju se redni brojevi (npr. 1 - 3 - 5) ponuđenih odgovora koje je odabrao student
public:
	//Konstruktor i destruktor
	//Broj bodova inicijalno postaviti na 0 i uvećavati svakim označenim tačnim odgovorom.

	//Funkciju za izmjenu potrebnih podataka o pitanju

	//Funkciju za dodavanje odgovora u listu koja treba da osigura da su najmanje 2 (od max) odgovora označena kao tačna.
	//Dok se ne dodaju svi predviđeni odgovori pitanje ne treba biti upotrebljivo ukoliko prethodni uslov nije ispunjen 
    //(ne prikazivati
	//pitanja na ispisu).
	//Napomena: Podatke o odgovorima čuvati u zasebnoj memoriji i istu dealocirati unutar same klase.

	//Funkciju za uklanjanje odgovora na osnovu rednog broja u listi. Ukoliko se uklanja odgovor koji je označen kao tačan i 
	//pri tome u listi ostaje samo još jedan odgovor označen kao tačan, pitanje postaje neupotrebljivo dok se ne doda još jedan
	//tačan odgovor.

	//Funkciju za promjenu odgovora na određenom rednom broju.
};

//Pitanje koje može imati jedan tačan odgovor. Student bira jednu od ponuđenih opcija.
class MCSAPitanje : public MCMAPitanje
{
public:
	//Konstruktor
	//Broj bodova se postavlja na vrijednost proslijeđenog parametra.

	//Preklopljene verzije funkcija za dodavanje i uklanjanje odgovora koje dozvoljavaju da samo jedan odgovor bude označen kao tačan.
	//Svi prethodno navedeni uslovi trebaju biti ispunjeni, ali u ovom slučaju sa isključivo jednim tačnim odgovorom.
};

//Pojam je tip pitanja kod kojeg se definiše pojam zadat tekstom pitanja. Definicija/Opis pojma se tretira kao
//esejski dio pitanja, dok se karakteristike tog pojma postavljaju kroz MCMA tip pitanja.
class Pojam : public EsejskoPitanje, public MCMAPitanje
{
	bool _slozen; //pojam moze biti prost ili slozen
public:
	//Konstruktor
	//Jednostavno pitanje tipa Pojam nosi minimalno 3 boda, a ukoliko je riječ o složenom pojmu minimalno 5 bodova.

	//Dodati ostale potrebne funkcije za rad sa klasom.
};

class Test {
	char _brojIndeksa[10]; //broj indeksa studenta za kojeg je formiran test
	Pitanje* _pitanja[30]; // test studenta sadrži najviše 30 pitanja različitog tipa
	double _maksimalnoBodova;
	double _osvojenoBodova;
	double _rezultat; //izražen u procentima
	int ocjena;
public:
	//Omogućiti formiranje testa sa različitim tipom pitanja, te dodati funkcije za unos, provjeru tačnih odgovora i ocjenu studenta.
	//Po potrebi dopuniti i prethodne klase novim atributima/funkcijama.

};

int main()
{
	//Testirati sve implementirane funkcionalnosti programa. 
	//Kreirati najmanje jedan test sa 10 pitanja.

	system("pause");
	return 0;
}


