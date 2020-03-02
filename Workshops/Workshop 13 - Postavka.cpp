#include<iostream>
#include<string>
#include<regex>

using namespace std;

//Koristiti klasu NedozvoljenaOperacija za bacanje izuzetaka u cijelom programu
class NedozvoljenaOperacija : public exception
{
	int _linijaKoda;
public:
	NedozvoljenaOperacija(const char* poruka, int linijaKoda) : exception(poruka)
	{
		_linijaKoda = linijaKoda;
	}

	void Info()
	{
		cout << "Greska u liniji koda " << _linijaKoda << ": " << exception::what() << endl;
	}
};

template<class T1, class T2>
class FITKolekcija
{
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	//Konstruktor, destruktor i ostale funkcije potrebne za rad sa klasom
};

enum Kategorija { GameChallenge, InnovationChallenge, MobileChallenge, SQLChallenge, CodingChallenge };

//Klasu proglasiti apstraktnom
class Osoba
{
	char* _ime;
	char* _prezime;
	int _godiste;
public:
	Osoba(const char* ime, const char* prezime, int godiste)
	{
		int vel = strlen(ime) + 1;
		_ime = new char[vel];
		strcpy_s(_ime, vel, ime);

		vel = strlen(prezime) + 1;
		_prezime = new char[vel];
		strcpy_s(_prezime, vel, prezime);

		_godiste = godiste;
	}

	~Osoba()
	{
		delete[] _ime;
		_ime = nullptr;

		delete[] _prezime;
		_prezime = nullptr;
	}


};

//Prepoznati nasljedjivanje izmedju odgovarajućih klasa
//I učesnici i članovi komisije trebaju imati podatke za pristup sistemu (email i password)
class Ucesnik
{
	char* _email;
	string password; //Najmanje 5 karaktera, kombinacija brojeva i velikih slova (dopuniti sa regex-ima)
	string _obrazovnaInstitucija;
public:
	//Potrebne funkcije za rad sa klasom
};

class ClanKomisije {
	char* _pozicija; //Radno mjesto u firmi
	string _firma;
public:
	//Potrebne funkcije za rad sa klasom
};

//Prijave koje ne uključuju izradu i predaju projekata (kategorije: SQLChallenge i CodingChallenge)
class Prijava {
	string _datum; //Podržani format: dd.MM.yyyy (dopuniti sa regex-ima)
	Kategorija _kategorija;
	FITKolekcija<Ucesnik, bool> _tim; //Tim se sastoji od jednog ili više učesnika, drugi parametar označava predstavnika tima
public:
	//Konstruktor

	//Funkciju za dodavanje članova tima uz poštivanje ograničenja maksimalno dozvoljenog broja članova u timu.
	//SQLChallenge i CodingChallenge: 2
	//GameChallenge i MobileChallenge: 3
	//InnovationChallenge: 4
	//Onemogućiti dodavanje istog učesnika više puta. Tim može imati najviše jednog predstavnika.

	//Funkciju za promjenu predstavnika tima.
};

//Prijave koje uključuju izradu projekata (kategorije: GameChallenge, InnovationChallenge i MobileChallenge)
class PrijavaProjekta : public Prijava {
	char* _nazivProjekta;
	string _opisProjekta;
	bool _finalizirano; //Atribut označava da li je projekat završen i predan u predviđenom roku
	bool _prezentacija; //Projekti koji se prezentuju i ocjenjuju
public:
	//Konstruktor i destruktor

	//Ostale potrebne funkcije za rad sa klasom

};

class FITCodingChallenge
{
	int godina;
	string _prijaveDo; //Podržani format unosa: dd.MM.yyyy (dopuniti sa regex-ima)
	vector<Prijava*> _prijave;
	FITKolekcija<ClanKomisije, Kategorija> _komisija;
	FITKolekcija<Prijava*, FITKolekcija<ClanKomisije*, double>> _ocjene;
public:
	//Konstruktor

	//Operator += za dodavanje novih prijava. Isti učesnik ne može imati više prijava u sklopu iste kategorije.
	//Poštovati ograničenje roka za prijave (_prijaveDo).
	//Voditi računa o alokaciji memorije za prijave (ne zadržavati adresu proslijeđenog objekta)

	//Funkciju koja određenu prijavu označava kao finaliziranu i odabranu za prezentaciju ili ne.

	//Operator () za dodavanje članova komisije po kategorijama. Spriječiti dodavanje istih članova u sklopu jedne kategorije.

	//Funkciju za ispis svih prijava po kategorijama. Funkcija neobavezno prima parametar kategoriju.
	//Ispis treba da uključi i podatke o učesnicima, odnosno članovima tima.
	//Ukoliko kategorija nije proslijeđena, podaci treba da budu grupisani po kategorijama.

	//Funkciju za ocjenu projekata (radova) od strane članova komisije (kolekcija _ocjene).
	//Kolekcija sadrzi samo pokazivače (bez alokacije nove memorije) na postojeće prijave i vec definisane članove komisije.
	//Voditi računa da se ne mogu ocijeniti projekti koji nisu finalizirani i nisu odabrani za prezentaciju, 
    //niti da ocjenu mogu dati članovi komisije koji
	//nisu pridruženi odgovarajućoj kategoriji prijave. Svaki član komisije daje ocjenu za svaki projekat, odnosno rad, u
	//kategoriji gdje je dodijeljen. Ocjene se kreću u rasponu od 1 do 10 za projekte, a za radove u kategoriji SQL ili CodingChallenge
	//u rasponu osvojenih bodova od 0 do 100. Pretpostaviti da su svi učesnici prijavljeni u kategorijama SQL i CodingChallenge predali radove.

	//Funkcija koja na osnovu imena i prezimena člana komisije ispisuje podatke o njegovim ocjenama uključujući
	//prijave na koje se one odnose.

	//Funkcija koja na osnovu imena i prezimena učesnika ispisuje podatke o njegovim prijavama na takmičenju, zajedno sa 
	//ocjenama, ukoliko su one definisane za prijavu/e datog učesnika.

	//Funkciju za rangiranje kandidata na osnovu kategorije proslijeđene kao parametar.
	//Funkcija treba da na osnovu ocjena članova komisije ispiše rang liste timova zajedno sa prosječnim ocjenama njihovih projekata (radova).
	//Dakle, konačna rang lista uključuje nazive timova (u zavisnosti od kategorije i naziv projekta), te prosječnu ocjenu.

	//Funkciju Info koja ispisuje sve podatke o takmičenju.
};


int main()
{
	//Kreirati objekat klase FITCodingChallenge, te demonstrirati sve implementirane funkcionalnosti.

	system("pause");

	return 0;
}

