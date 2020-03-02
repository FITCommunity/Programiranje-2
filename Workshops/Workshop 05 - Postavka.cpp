#include<iostream>

using namespace std;

auto crt = "----------------------------------------------------\n";

char* AlocirajChar(const char *sadrzaj)
{
	int vel = strlen(sadrzaj) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Vrijeme
{
	int* _sati;
	int* _minute;
	int* _sekunde;
public:
	Vrijeme(int sati, int minute, int sekunde = 0) {
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}

	Vrijeme(const Vrijeme& v)
	{
		_sati = new int(*v._sati);
		_minute = new int(*v._minute);
		_sekunde = new int(*v._sekunde);
	}

	//Preklopiti operator << za ispis objekata tipa Vrijeme

};

class Let
{
	static const  int _oznakaSize = 10;
	char _oznaka[_oznakaSize];
	char* _odrediste;
	int _brIzlazneKapije;
	Vrijeme _vrijemePolijetanja; //sati i minute
	int _trajanje; //izraženo u minutama
	int _kasnjenje; //izraženo u minutama

public:
	//Potrebne konstruktor i destruktor funkcije

	//Funkciju sa jednim parametrom koja postavlja informaciju o eventualnom kašnjenju na vrijednost zadanu parametrom.

	/*Preklopiti unarni operator "!" putem kojeg je moguće saznati da li odgovarajući let kasni ili ne (vratiti logičku
	vrijednost "true" u slučaju kašnjenja, u suprotnom vratiti "false").*/

	//Funkciju koja kao rezultat vraća trajanje leta.

	/*Preklopiti operator + na način da omogućava sabiranje objekata tipa "Let" i cijelog broja, pri
	čemu se kao rezultat dobiva novi objekat tipa "Let", u kojem je vrijeme polijetanja pomjereno
	unaprijed za iznos određen drugim sabirkom (računato u minutama).
	Također preklopiti i operator "+=" koji osigurava da izraz oblika "X += Y uvijek ima isto značenje kao i izraz
	"X = X + Y" */

	/* Funkciju kojom je moguće saznati očekivano vrijeme polijetanja kada se uračuna iznos kašnjenja
	u odnosu na predviđeno vrijeme polijetanja (preklopiti operator + u klasi Vrijeme). */

	//Funkciju koja vraća očekivano vrijeme slijetanja

	/*Preklopiti operator "++" na način da pomijera vrijeme polaska za jedan sat unaprijed.
	  Potrebno je podržati i prefiksnu i postfiksnu verziju ovog operatora.*/

	  /*Preklopiti relacione operatore "<" i ">" koji ispituju koji let nastupa ranije, odnosno kasnije.
		Operator "<" vraća logičku vrijednost "true" ukoliko polijetanje leta sa lijeve strane nastupa
		prije polijetanje leta sa desne strane, a u suprotnom vraća logičku vrijednost "false".
		Analogno vrijedi za operator ">". Prilikom upoređivanja treba uzeti u obzir i očekivano vrijeme kašnjenja,
		a ne samo planirano vrijeme polijetanja.*/

		/*Preklopiti operator "<<" koji treba da podrži ispis objekata tipa "Let" na ekran. U slučaju da
		se radi o polijetanju bez kašnjenja, ispis bi trebao da izgleda kako slijedi:

			JFK 156 Atalanta    12:50   19:30   5

		Podaci predstavljaju redom: oznaku leta, naziv odredišta, vrijeme polijetanja, očekivano
		vrijeme slijetanja i broj izlazne kapije.

		U slučaju da se radi o letu koji kasni, ispis bi trebao izgledati kako slijedi:

			ZGK 932 Zagreb    15:50 (Planirano 15:30, Kasni 20 min)*/
};


class RasporedLetova
{
	int _brojRegistrovanihLetova;
	const int _maksimalanBrojLetova;
	Let** _letovi;

public:
	RasporedLetova(int maksimalanBrojLetova) : _maksimalanBrojLetova(maksimalanBrojLetova),
		_letovi(new Let*[_maksimalanBrojLetova]), _brojRegistrovanihLetova(0)
	{

	}

	/*
    Preklopiti operator "+=" na način da registruje novi let u raspored. 
    Raspored letova u svakom momentu treba biti sortiran
	prema vremenu polijetanja. Voditi računa o maksimalnom broju letova.  
    Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme.*/

	/*
    Preklopiti operator "-=" na način da ukljanja registrovani let sa oznakom definisanom putem desnog operanda.
	Pri tome sačuvati redoslijed prethodno registrovanih letova. */

	 //Preklopiti operator "[]" na način da vraća objekat tipa Let na osnovu proslijeđene pozicije u rasporedu (pozicije kreću od 1).

	/*Preklopiti operator "()" na način da letu sa definisanom oznakom pomjeri vrijeme polijetanja za vrijednost 
    drugog parametra izraženog
	u minutama. */


	//Funkciju koja daje prosječno trajanje svih pohranjenih letova.


	/*
    Preklopiti operator "<<" koji ispisuje kompletan spisak svih letova, sortiran po očekivanim vremenima polazaka.
	Za potrebe poređenja vremena polaska letova preklopiti odgovarajuće operatore u klasi Vrijeme. */

};

int main()
{
	
    system("pause");
	return 0;
}

