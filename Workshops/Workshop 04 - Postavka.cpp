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

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	Datum(int d, int m, int g) : _dan(d), _mjesec(m), _godina(g) {}
	void Info()
	{
		cout << _dan << "." << _mjesec << "." << _godina << endl;
	}

};

enum TipNaplate {PoOsobi, Jednokratno, PoNocenju};
class Usluga
{
	char* _naziv;
	double _cijena;
	TipNaplate _tipNaplate;
public:
	Usluga(): _naziv(nullptr), _cijena(0), _tipNaplate(TipNaplate(0)) {}
	Usluga(const char* naziv, int cijena, TipNaplate tipNaplate) : 
		_cijena(cijena), _tipNaplate(tipNaplate)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

	~Usluga()
	{
		delete[] _naziv;
		_naziv = nullptr;
	}

	void Info()
	{
		cout << "Naziv usluge: " << _naziv << endl;
		cout << "Cijena: " << _cijena << endl;
	}
};

enum TipSmjestaja { StudioApartman, SingleRoom, DoubleRoom, SuperiorApartman };
const char* TipSmjestajaString[] = {"StudioApartman", "SingleRoom", "DoubleRoom", "SuperiorApartman"};


class Smjestaj
{
	int _broj; //Broj sobe, apartmana
	TipSmjestaja* _tipSmjestaja;
	int _maxBrojOsoba;
	double _cijenaPoOsobi;
public:
	Smjestaj(int broj, TipSmjestaja tip, int maxBrojOsoba, double cijenaPoOsobi) :
		_broj(broj), _tipSmjestaja(new TipSmjestaja(tip)),_maxBrojOsoba(maxBrojOsoba), _cijenaPoOsobi(cijenaPoOsobi)
	{
	}

	~Smjestaj()
	{
		delete _tipSmjestaja;
		_tipSmjestaja = nullptr;
	}

	void Info() const
	{
		cout << "Broj sobe: " << _broj << endl;
		cout << "Tip smjestaja: " << TipSmjestajaString[*_tipSmjestaja] << endl;
		cout << "Kapacitet smjestaja: " << _maxBrojOsoba << endl;
		cout << "Cijena po osobi: " << _cijenaPoOsobi << endl;

	}

};

class Gost
{
	char* _imePrezime;
	char* _kontakTelefon;
public:
	Gost(const char* imePrezime, const char* kontaktTelefon)
	{
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_kontakTelefon = AlocirajNizKaraktera(kontaktTelefon);
	}

	void Info()
	{
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Kontakt telefon: " << _kontakTelefon << endl;
	}

};

enum StatusRezervacije { Aktivna, Potvrdjena, BoravakUToku, Otkazana };
class Rezervacija
{
	Datum _pocetakBoravka;
	Datum _krajBoravka;
	Gost* _gost; //Gost koji je rezervisao smještaj
	Smjestaj _smjestaj;
	int _brojOsoba; //Ukupan broj osoba koji boravi u smjestaju
	Usluga* _usluge; //Dodatne usluge koje je gost koristio tokom boravka
	int _brojUsluga;
	double _ukupanIznos;
	StatusRezervacije _status;
public:


	void RezervisiUslugu(const Usluga& u)
	{
		Usluga* temp = new Usluga[_brojUsluga + 1];
		for (size_t i = 0; i < _brojUsluga; i++)
		{
			temp[i] = _usluge[i];
		}

		delete[] _usluge;
		_usluge = temp;

		_usluge[_brojUsluga++] = u;
	}
	
};

class Hotel
{
	char* _naziv;
	//Ponuda smještaja
	Smjestaj* _smjestaji;
	int _brojSmjestaja;
	//Rezervacije hotela (protekle, aktivne i nadolazeće)
	Rezervacija* _rezervacije;
	int _brojRezervacija;
       static int _stopaPDV;
public:
	Hotel(const char* naziv) : _smjestaji(nullptr), _brojSmjestaja(0),
		_rezervacije(nullptr), _brojRezervacija(0)
	{
		_naziv = AlocirajNizKaraktera(naziv);
	}

};

int main()
{

#pragma region Hotel

	const int brojUsluga(5);
	Hotel hotel1("Hotel Mostar");

	Usluga* usluge[brojUsluga];
	usluge[0] = new Usluga("Parking", 5, TipNaplate(1));
	usluge[1] = new Usluga("Dorucak", 10, TipNaplate(0));
	usluge[2] = new Usluga("Rucak", 15, TipNaplate(0));
	usluge[3] = new Usluga("Wellness & SPA", 40, TipNaplate(2));
	usluge[4] = new Usluga("Veseraj", 10, TipNaplate(2));

	Smjestaj apartman(1, TipSmjestaja(0), 5, 30);
	Smjestaj soba1(2, TipSmjestaja(1), 2, 20);
	Smjestaj soba2(3, TipSmjestaja(2), 4, 20);
	Smjestaj soba3(1, TipSmjestaja(0), 2, 15);

	//Funkciju za dodavanje smjestajnih kapaciteta hotela. Hotel ne moze imati više smještaja
	//pod istim brojem.
	hotel1.DodajSmjestaj(apartman);
	hotel1.DodajSmjestaj(soba1);
	hotel1.DodajSmjestaj(soba2);
	hotel1.DodajSmjestaj(soba3); //Neće se dodati radi zauzetosti broja smještaja

	//Funkcija koja vrši ispis podataka o svim slobodnim smještajima hotela u zadatom periodu.
	hotel1.IspisiSlobodneSmjestaje(Datum(24, 10, 2018), Datum(1, 11, 2018));

	//Ispis dodatnih usluga
	for (size_t i = 0; i < brojUsluga; i++)
	{
		usluge[i]->Info();
	}

#pragma endregion

#pragma region RezervacijaGost1

	Gost gost1("Marija Perić", "033/222-555");
	Rezervacija rezervacija1(Datum(28, 10, 2018), 
		Datum(2, 11, 2018), gost1, apartman, 3);//Posljednji parametar konstruktora je broj osoba
	rezervacija1.RezervisiUslugu(*usluge[0]); //Parking
	rezervacija1.RezervisiUslugu(*usluge[1]); //Doručak za 3 osobe


	//Funkcija kojom se dodaje nova rezervacija pod uslovom da smjestaj nije zauzet u trazenom periodu 
	//i da kapacitet smještaja nije manji od broja osoba. Funkcija treba da ispiše sve uslove koje rezervacija
	//ne ispunjava.
	if (hotel1.DodajRezervaciju(rezervacija1))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;

	hotel1.PotvrdiRezervaciju(rezervacija1); //Prije nego se gosti prijave u hotel rezervacija mora biti potvrđena.
	hotel1.CheckIn(rezervacija1); //Mijenja status rezervacije na BoravakUToku, pod uslovom da je ista prethodno potvrđena.


	/*Vrši ispis računa sa svim stavkama rezervacije (posebno stavka za smještaj, a posebno za sve usluge sa
		pripadajućim cijenama, te ukupnim iznosom računa na kraju). Parametar tipa bool govori da li je potrebno obračunati
		PDV po utvrđenoj stopi na ukupan iznos računa te na sve stavke pojedinačno.*/
	hotel1.CheckOut(rezervacija1, true);

#pragma endregion

#pragma region RezervacijaGost2
	Gost gost2("Adijan Marić", "066/111-333");
	Rezervacija rezervacija2(Datum(29, 10, 2018), Datum(5, 11, 2018), gost2, apartman, 6);

	if (hotel1.DodajRezervaciju(rezervacija2))
		cout << "Uspjesno ste rezervisali smjestaj." << endl;
	else
		cout << "Rezervacija smjestaja nije uspjela." << endl;

#pragma endregion

	//Napomena: Za potrebe testiranje funkcija u nastavku dopuniti testni program.

	//Pronalazi i vraća podatke o najtraženijem smještaju hotela (onaj koji je najviše puta rezervisan u datom periodu)
	hotel1.GetNajTrazenijiSmjestaj(Datum(1,1,2018), Datum(24,1,2018)).Info();
	
	//Pronalazi i ispisuje podate o VIP gostu (onaj koji je u sumi utrošio najviše novca u hotelu u trenutnoj godini - 2018).
	hotel1.PronadjiVIPGosta().Info();

	for (size_t i = 0; i < brojUsluga; i++)
	{
		delete usluge[i];
	}

	system("pause");

	return 0;
}
