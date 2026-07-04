#include <iostream>
#include <vector>
#include <regex>
#include <time.h>

// za ostringstream
#include <sstream>

// za setfill i setw funkcije
#include <iomanip>

// za ifstream
#include <fstream>

using namespace std;


string crt = "\n------------------------------------------------------ -------------------------- - \n";

string PORUKA_TELEFON = crt +
"TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO." + crt;

string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO KAO TM\n"
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ MAIN FUNKCIJI, \n"
" OSIM AKO POSTOJI JASNO OPISAN RAZLOG ZA MODIFIKACIJU\n"
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n"
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n"
" AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILI VRATITE DEFAULT VRIJEDNOST\n"
"6. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO VLASTITOM IZBORU\n"
"7. TESTIRAJTE PROGRAM U OBA MODA (F5 i Ctrl+F5)" + crt;

char* AlocirajTekst(const char* tekst) {
	if (!tekst) return nullptr;
	size_t vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}


string GenerisiSifru(const char* imePrezime, int redniBroj) {
	time_t vrijeme = time(NULL);
	struct tm vrijeme_info;
	localtime_s(&vrijeme_info, &vrijeme);

	ostringstream buffer;

	// pretvaram da dobijem .find() metodu
	string s_imePrezime = imePrezime;

	buffer << "CW-" << imePrezime[0] << imePrezime[s_imePrezime.find(" ", 1) + 1] << "-" << setfill('0') << setw(3) << redniBroj << "/" << (vrijeme_info.tm_year + 1900);

	return buffer.str();
}

bool ValidirajSifru(const string& sifra) {
	return regex_match(sifra, regex("CW-([A-Z]{2})-([0-9]{3})/([0-9]{4})"));
}

enum TipProstora { RADNO_MJESTO, SALA, STUDIO, LABORATORIJA };

const char* TipProstoraNazivi[] = { "RADNO MJESTO", "SALA", "STUDIO", "LABORATORIJA" };

const char* GetTipProstoraCStr(TipProstora prostor) {
	return TipProstoraNazivi[prostor];
}


template<class T1, class T2, int max>
class Kolekcija {
	T1 _prvi[max];
	T2 _drugi[max];
	int* _trenutno;
public:
	Kolekcija() { _trenutno = new int(0); }
	~Kolekcija() { delete _trenutno; _trenutno = nullptr; }
	int GetTrenutno() const { return *_trenutno; }
	T1& GetPrvi(int indeks) { return _prvi[indeks]; }
	T2& GetDrugi(int indeks) { return _drugi[indeks]; }
	T1& operator[](int indeks) { return _prvi[indeks]; }
	friend ostream& operator<<(ostream& COUT, Kolekcija& obj) {
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetPrvi(i) << " " << obj.GetDrugi(i) << endl;
		return COUT;
	}

	// method i added below

	Kolekcija(const Kolekcija& other) {
		_trenutno = new int(other.GetTrenutno());

		for (int i = 0; i < GetTrenutno(); i++) {
			_prvi[i] = other._prvi[i];
			_drugi[i] = other._drugi[i];
		}
	}

	Kolekcija& operator=(const Kolekcija& other) {
		if (this == &other) return *this;
		// nema potrebe brisat i ponovo pravit new int nek samo preuzme value (ako sam negdje to uradio zapravo, idk bro 4 ujutro je)
		*_trenutno = other.GetTrenutno();

		for (int i = 0; i < GetTrenutno(); i++) {
			_prvi[i] = other._prvi[i];
			_drugi[i] = other._drugi[i];
		}

		return *this;
	}

	void Dodaj(T1 el1, T2 el2) {
		if (*_trenutno >= max) return;

		_prvi[*_trenutno] = el1;
		_drugi[*_trenutno] = el2;

		*_trenutno += 1;
	}

	Kolekcija<T1, T2, max> DodajNaPoziciju(int pos, T1 el1, T2 el2) {
		Kolekcija<T1, T2, max> nova;

		for (int i = 0; i < GetTrenutno(); i++) {
			if (i == pos) {
				nova.Dodaj(el1, el2);
			}

			nova.Dodaj(_prvi[i], _drugi[i]);
		}
		*this = nova;
		return nova;
	}

	Kolekcija<T1, T2, max>* UkloniRaspon(int from, int elements) {
		if (from < 0 || elements >= *_trenutno || from + elements >= *_trenutno) {
			throw exception("invalid range - UkloniRaspon()");
		}

		Kolekcija<T1, T2, max>* removed = new Kolekcija<T1, T2, max>();

		for (int i = from; i < from + elements; i++) {
			removed->Dodaj(_prvi[i], _drugi[i]);
		}

		for (int i = from + elements; i < *_trenutno; i++) {
			_prvi[i - elements] = _prvi[i];
			_drugi[i - elements] = _drugi[i];
		}

		*_trenutno -= elements;

		return removed;
	}
};

class DatumVrijeme {
	int* _godina, * _mjesec, * _dan, * _sati, * _minute;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int
		sati = 0, int minute = 0) {
		_godina = new int(godina);
		_mjesec = new int(mjesec);
		_dan = new int(dan);
		_sati = new int(sati);
		_minute = new int(minute);
	}
	~DatumVrijeme() {
		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute;
	}
	friend ostream& operator<<(ostream& COUT, DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." <<
			*obj._godina << " " << *obj._sati << ":" << *obj._minute;
		return COUT;
	}

	// methods i added below


	// bez copy constructora i copy assignmenta se pravi shallow copy ovog objekta pa se ovi brojevi sjebu, ugl dodaj u svaku klasu ovo 2 i neces imat problema
	DatumVrijeme(const DatumVrijeme& other) {
		_godina = new int(other.GetGodina());
		_mjesec = new int(other.GetMjesec());
		_dan = new int(other.GetDan());
		_sati = new int(other.GetSati());
		_minute = new int(other.GetMinute());
	}

	DatumVrijeme& operator=(const DatumVrijeme& other) {
		if (this == &other) return *this;
		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute;

		_godina = new int(other.GetGodina());
		_mjesec = new int(other.GetMjesec());
		_dan = new int(other.GetDan());
		_sati = new int(other.GetSati());
		_minute = new int(other.GetMinute());

		return *this;
	}

	int GetGodina() const {
		return *_godina;
	}

	int GetMjesec() const {
		return *_mjesec;
	}
	int GetDan() const {
		return *_dan;
	}

	int GetSati() const {
		return *_sati;
	}

	int GetMinute() const {
		return *_minute;
	}

	bool operator==(const DatumVrijeme& other) const {
		return (GetGodina() == other.GetGodina() && GetMjesec() == other.GetMjesec() && GetDan() == other.GetDan() && GetSati() == other.GetSati() && GetMinute() == other.GetMinute());
	}

};
class Rezervacija {
	char* _oznaka;
	TipProstora _tipProstora;
	DatumVrijeme _pocetak;
	int _trajanjeMinuta;
public:
	Rezervacija(const char* oznaka, TipProstora tipProstora,
		DatumVrijeme pocetak, int trajanjeMinuta)
		: _tipProstora(tipProstora), _pocetak(pocetak),
		_trajanjeMinuta(trajanjeMinuta) {
		_oznaka = AlocirajTekst(oznaka);
	}
	~Rezervacija() { delete[] _oznaka; _oznaka = nullptr; }
	const char* GetOznaka() const { return _oznaka; }
	TipProstora GetTipProstora() const { return _tipProstora; }
	DatumVrijeme& GetPocetak() { return _pocetak; }
	int GetTrajanjeMinuta() const { return _trajanjeMinuta; }

	// methods i added below

	Rezervacija(const Rezervacija& other) {
		_oznaka = AlocirajTekst(other._oznaka);
		_tipProstora = other._tipProstora;
		_pocetak = other._pocetak;
		_trajanjeMinuta = other._trajanjeMinuta;
	}

	Rezervacija& operator=(const Rezervacija& other) {
		if (this == &other) return *this;
		delete[] _oznaka; _oznaka = nullptr;

		_oznaka = AlocirajTekst(other._oznaka);
		_tipProstora = other._tipProstora;
		_pocetak = other._pocetak;
		_trajanjeMinuta = other._trajanjeMinuta;

		return *this;
	}


	string ToString() {
		ostringstream buffer;

		buffer << setfill('0') << setw(2) << _pocetak.GetDan() << ".";
		buffer << setfill('0') << setw(2) << _pocetak.GetMjesec() << ".";
		buffer << _pocetak.GetGodina() << " ";
		buffer << setfill('0') << setw(2) << _pocetak.GetSati() << ":";
		buffer << setfill('0') << setw(2) << _pocetak.GetMinute();


		buffer << " " << _oznaka << " " << GetTipProstoraCStr(_tipProstora) << " " << _trajanjeMinuta << " min";

		return buffer.str();
	}
	// ako sam dobro skonto ovo je false samo ako rezervacija A zavrsi prije nego sto rezervacija B pocne i obrnuto
	bool ImaKonfliktSa(Rezervacija rezervacijaB) {
		if (_pocetak.GetDan() != rezervacijaB._pocetak.GetDan() ||
			_pocetak.GetMjesec() != rezervacijaB._pocetak.GetMjesec() ||
			_pocetak.GetGodina() != rezervacijaB._pocetak.GetGodina())
			return false;

		int a_Start = _pocetak.GetSati() * 60 + _pocetak.GetMinute();
		int a_End = a_Start + _trajanjeMinuta;

		int b_Start = rezervacijaB._pocetak.GetSati() * 60 + _pocetak.GetMinute();
		int b_End = b_Start + rezervacijaB._trajanjeMinuta;

		return !(a_End <= b_Start || b_End <= a_Start);
	}
};

class Korisnik {
	static int _id;
	char* _sifra;
	char* _imePrezime;
	vector<Rezervacija> _rezervacije;
public:
	Korisnik(const char* imePrezime = "") {
		_imePrezime = AlocirajTekst(imePrezime);
		_sifra = AlocirajTekst(GenerisiSifru(imePrezime,
			_id).c_str());
		_id++;
	}
	~Korisnik() {
		delete[] _sifra; _sifra = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
	}

	Korisnik(const Korisnik& other) {
		_imePrezime = AlocirajTekst(other._imePrezime);
		_sifra = AlocirajTekst(other._sifra);
		_rezervacije = other._rezervacije;
	}

	Korisnik& operator=(const Korisnik& other) {
		if (this == &other) return *this;
		delete[] _sifra; _sifra = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;

		_imePrezime = AlocirajTekst(other._imePrezime);
		_sifra = AlocirajTekst(other._sifra);
		_rezervacije = other._rezervacije;
		return *this;
	}

	const char* GetSifra() const { return _sifra; }
	const char* GetImePrezime() const { return _imePrezime; }
	vector<Rezervacija>& GetRezervacije() { return _rezervacije; }
	friend ostream& operator<<(ostream& COUT, Korisnik& obj) {
		COUT << obj._imePrezime << " [" << obj._sifra << "]" << endl;
		for (auto& rezervacija : obj._rezervacije)
			//ToString metoda klase Rezervacija vraca podatke o rezervaciji u formatu :
			//10.09.2026 09:00 SALA-A SALA 60 min
			COUT << " - " << rezervacija.ToString() << endl;
		return COUT;
	}

	// methods i added below

	bool DodajRezervaciju(Rezervacija rezervacijaZaDodat) {

		int minute = rezervacijaZaDodat.GetTrajanjeMinuta();

		for (auto& rezervacija : _rezervacije) {
			if (rezervacijaZaDodat.ImaKonfliktSa(rezervacija)) return false;

			// provjera da li je u istom danu
			if (rezervacija.GetPocetak().GetDan() ==
				rezervacijaZaDodat.GetPocetak().GetDan() &&
				rezervacija.GetPocetak().GetMjesec() ==
				rezervacijaZaDodat.GetPocetak().GetMjesec() &&
				rezervacija.GetPocetak().GetGodina() ==
				rezervacijaZaDodat.GetPocetak().GetGodina())
			{
				minute += rezervacija.GetTrajanjeMinuta();
			}
		}
		if (minute > 480) return false;

		_rezervacije.push_back(rezervacijaZaDodat);
		return true;
	}

};

class CentarZaRad {
	char* _naziv;
	vector<Korisnik> _korisnici;
public:
	CentarZaRad(const char* naziv) { _naziv = AlocirajTekst(naziv); }
	~CentarZaRad() { delete[] _naziv; _naziv = nullptr; }
	CentarZaRad(const CentarZaRad& obj) {
		_naziv = AlocirajTekst(obj._naziv);
		_korisnici = obj._korisnici;
	}
	const char* GetNaziv() const { return _naziv; }
	vector<Korisnik>& GetKorisnici() { return _korisnici; }

	void DodajKorisnika(Korisnik korisnik) {
		for (auto& k : _korisnici) {
			if (strcmp(k.GetSifra(), korisnik.GetSifra()) == 0) {
				throw exception("korisnik sa istom sifrom vec postoji");
			}
		}
		_korisnici.push_back(korisnik);
	}

	bool RegistrujRezervaciju(const char* sifra, Rezervacija rezervacija) {
		for (auto& korisnik : _korisnici) {
			if (strcmp(korisnik.GetSifra(), sifra) == 0) {
				korisnik.DodajRezervaciju(rezervacija);
				return true;
			}
		}

		return false;
	}

	vector<Korisnik*> AktivniKorisnici(int min) {
		vector<Korisnik*> aktivniKorisnici;

		for (auto& k : _korisnici) {
			if (k.GetRezervacije().size() >= min) {
				aktivniKorisnici.push_back(new Korisnik(k));
			}
		}

		return aktivniKorisnici;
	}

	Kolekcija<Korisnik, int, 50> KoristenjePoTipu(TipProstora prostor) {
		Kolekcija<Korisnik, int, 50> korisnici;

		for (auto& k : _korisnici) {
			for (auto& r : k.GetRezervacije()) {
				if (r.GetTipProstora() == prostor && k.GetRezervacije().size() >= 1) {
					korisnici.Dodaj(k, r.GetTrajanjeMinuta());
				}
			}
		}

		return korisnici;
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite razliku izmedju koristenja kljucne rijeci abstract i cistih virtualnih metoda ? \n";
	return "abstract klasa je klasa koja ima bar jednu cistu virtualnu metodu i ne moze se instancirat, cista virtualna metoda je samo deklaracija funkcije bez implementacije u baznoj klasi i prisiljava child klase da se implementiraju";
}
// ne znam ni sta pita lik xd
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite korelaciju izmedju polimorfizma i virtualnih metoda, te zbog cega se javlja potreba za virtualnim destruktorom ? \n";
	return "Polimorfizam omogućava da se preko pokazivača ili reference na baznu klasu pozivaju metode izvedene klase, a to se postiže virtualnim funkcijama koje omogućavaju runtime binding. Virtualni destruktor je potreban da bi se pri brisanju objekta preko baznog pokazivača pravilno pozvao destruktor izvedene klase i spriječilo curenje resursa.";
}
int Korisnik::_id = 1;


CentarZaRad* GetCentar(const char* naziv, vector<CentarZaRad> centri) {
	for (auto& centar : centri) {
		if (strcmp(naziv, centar.GetNaziv()) == 0) return &centar;
	}
	return nullptr;
}

bool UcitajPodatke(const char* nazivFajla, vector<CentarZaRad>& centri) {
	ifstream file(nazivFajla);

	if (!file.is_open()) {
		return false;
	}

	string s_centar;
	string s_korisnik;
	bool dodano = false;
	while (getline(file, s_centar, '|') && getline(file, s_korisnik)) {
		CentarZaRad* centar = GetCentar(s_centar.c_str(), centri);
		if (!centar) {
			centri.push_back(CentarZaRad(s_centar.c_str()));
			centar = &centri.back();
			dodano = true;
		}

		Korisnik korisnik(s_korisnik.c_str());
		bool duplikat = false;
		for (auto& k : centar->GetKorisnici()) {
			if (strcmp(k.GetImePrezime(), korisnik.GetImePrezime()) == 0) duplikat = true;
		}
		if (!duplikat) {
			centar->DodajKorisnika(korisnik);
			dodano = true;
		}
	}
	return dodano;
}

int main() {

	cout << PORUKA_TELEFON; cin.get();
	cout << PORUKA_ISPIT; cin.get(); system("cls");
	cout << GetOdgovorNaPrvoPitanje() << crt;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << crt;
	cin.get();

	//funkcija generise sifru korisnika na osnovu imena i prezimena, rednog broja i trenutne godine.
	//sifra je u formatu CW-IN-BBB/GGGG, gdje IN predstavlja inicijale, BBB redni broj korisnika
	//popunjen nulama na slobodnim mjestima, a GGGG trenutnu godinu dobijenu iz sistema.
	//funkciju koristiti u konstruktoru klase Korisnik za inicijalizaciju atributa _sifra.
	if (GenerisiSifru("Amina Buric", 3) == "CW-AB-003/2026")
		cout << "Sifra OK" << crt;
	if (GenerisiSifru("Amar Macic", 15) == "CW-AM-015/2026")
		cout << "Sifra OK" << crt;
	if (GenerisiSifru("Maid Ramic", 156) == "CW-MR-156/2026")
		cout << "Sifra OK" << crt;
	//koristeci regex, funkcija ValidirajSifru provjerava da li je sifra zapisana u prethodno
	//definisanom formatu. funkcija vraca true ako je sifra validna, u suprotnom vraca false.
	if (ValidirajSifru("CW-AB-003/2026"))
		cout << "SIFRA VALIDNA" << crt;
	if (!ValidirajSifru("CW-Ab-003/2026") && !ValidirajSifru("CW-AB03/2026") &&
		!ValidirajSifru("CW/AB-003-2026"))
		cout << "SIFRA NIJE VALIDNA" << crt;
	Kolekcija<int, string, 20> termini;
	for (int i = 0; i < 8; i++)
		termini.Dodaj(i, "Termin_" + to_string(i));
	cout << termini << crt;
	//DodajNaPoziciju dodaje novi par na lokaciju definisanu prvim parametrom, pomjera postojece
	//elemente udesno i vraca trenutno stanje kolekcije. u slucaju popunjene kolekcije ili
	//neispravne lokacije potrebno je baciti izuzetak.
	Kolekcija<int, string, 20> prosireniTermini = termini.DodajNaPoziciju(2, 99, "Poseban termin");
	cout << prosireniTermini << crt;
	//UkloniRaspon od lokacije definisane prvim parametrom uklanja broj elemenata definisan
	//drugim parametrom, a vraca pokazivac na novu kolekciju koja sadrzi uklonjene elemente.
	//pozivalac je odgovoran za dealokaciju vracene kolekcije.
	Kolekcija<int, string, 20>* uklonjeniTermini = prosireniTermini.UkloniRaspon(3, 2);

	cout << "Uklonjeni elementi:" << crt << *uklonjeniTermini;
	cout << "Preostali elementi:" << crt << prosireniTermini;
	delete uklonjeniTermini;

	try {
		//za neispravan raspon potrebno je baciti izuzetak
		termini.UkloniRaspon(6, 5);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	DatumVrijeme vrijeme1(10, 9, 2026, 9, 0), vrijeme2(10, 9, 2026, 9, 30),
		vrijeme3(10, 9, 2026, 10, 0), vrijeme4(10, 9, 2026, 12, 0);
	Rezervacija salaA("SALA-A", SALA, vrijeme1, 60);
	Rezervacija studio1("STUDIO-1", STUDIO, vrijeme2, 90);
	Rezervacija radnoMjesto("RM-12", RADNO_MJESTO, vrijeme3, 60);
	Rezervacija laboratorija("LAB-1", LABORATORIJA, vrijeme4, 400);
	//ToString metoda vraca podatke o rezervaciji u formatu prikazanom u nastavku.
	//voditi racuna o prikazu jednocifrenih vrijednosti datuma i vremena(npr. 9 -> 09).
	cout << salaA.ToString() << crt;
	//10.09.2026 09:00 SALA-A SALA 60 min
	//ImaKonfliktSa vraca true ako su rezervacije istog datuma i njihovi vremenski intervali
	//se preklapaju. rezervacija koja pocinje u trenutku kada prethodna zavrsava nije konfliktna.
	if (salaA.ImaKonfliktSa(studio1))
		cout << "Termini se preklapaju" << crt;
	if (!salaA.ImaKonfliktSa(radnoMjesto))
		cout << "Termini se ne preklapaju" << crt;
	Korisnik amina("Amina Buric"), goran("Goran Skondric"), berun("Berun Agic");
	//DodajRezervaciju dodaje rezervaciju korisniku ako se ona ne preklapa sa nekom od ranije
	//dodanih rezervacija i ako ukupno trajanje svih rezervacija korisnika u jednom danu ne
	//prelazi 480 minuta. metoda vraca true ako je rezervacija dodana, u suprotnom vraca false.
	if (amina.DodajRezervaciju(salaA))
		cout << "Rezervacija dodana" << crt;
	if (!amina.DodajRezervaciju(studio1))
		cout << "Rezervacija nije dodana - preklapanje termina" <<
		crt;
	if (amina.DodajRezervaciju(radnoMjesto))
		cout << "Rezervacija dodana" << crt;
	if (!amina.DodajRezervaciju(laboratorija))
		cout << "Rezervacija nije dodana - prekoracen dnevni limit"
		<< crt;
	CentarZaRad radniKutak("Radni kutak"), poslovnaZona("Poslovna zona");
	radniKutak.DodajKorisnika(amina);
	radniKutak.DodajKorisnika(goran);
	poslovnaZona.DodajKorisnika(berun);
	try {
		//DodajKorisnika onemogucava dodavanje korisnika sa istom sifrom i baca izuzetak
		radniKutak.DodajKorisnika(amina);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	Rezervacija goranovaSala("SALA-B", SALA, vrijeme4, 120);
	//RegistrujRezervaciju pronalazi korisnika na osnovu sifre i dodaje mu rezervaciju.
	//i dalje vaze pravila definisana u metodi DodajRezervaciju. metoda vraca true ili false.
	if (radniKutak.RegistrujRezervaciju(goran.GetSifra(), goranovaSala))
		cout << "Rezervacija registrovana" << crt;
	//AktivniKorisnici vraca pokazivace na korisnike koji imaju najmanje onoliko rezervacija
	//koliko je definisano vrijednoscu proslijedjenog parametra.
	vector<Korisnik*> aktivni = radniKutak.AktivniKorisnici(1);
	for (auto korisnik : aktivni)
		cout << korisnik->GetImePrezime() << " ima " << korisnik->GetRezervacije().size() << " rezervacija" << crt;
	//KoristenjePoTipu vraca kolekciju parova (korisnik, broj minuta) za sve korisnike koji
	//imaju najmanje jednu rezervaciju prostora proslijedjenog tipa.
	Kolekcija<Korisnik, int, 50> koristenjeSala = radniKutak.KoristenjePoTipu(SALA);
	for (int i = 0; i < koristenjeSala.GetTrenutno(); i++)
		cout << koristenjeSala.GetPrvi(i).GetImePrezime() << " -> " << koristenjeSala.GetDrugi(i) << " minuta" << crt;

	vector<CentarZaRad> centri;
	centri.push_back(radniKutak);
	centri.push_back(poslovnaZona);
	/*
	Funkcija UcitajPodatke ucitava podatke o centrima za rad i
   njihovim korisnicima iz
	datoteke cije ime se prosljedjuje kao prvi parametar. Svaka linija
   je zapisana u formatu:
	naziv centra|ime i prezime korisnika
	Za svaki ispravan red potrebno je:
	- pronaci postojeci ili kreirati novi centar za rad,
	- kreirati i dodati korisnika u odgovarajuci centar,
	- onemoguciti dupliranje centara i korisnika unutar istog
   centra.
	Funkcija vraca true ako je ucitan najmanje jedan novi podatak, a
   false ako datoteka ne
	postoji ili nije ucitan nijedan novi podatak.
	Primjer sadrzaja datoteke:
   Fakultet informacijskih tehnologija
   Pismeni dio ispita iz predmeta Programiranje II – 25.06.2026
   7
	Radni kutak|Emina Junuz
	Radni kutak|Jasmin Azemovic
	Poslovna zona|Zanin Vejzovic
	*/

	if (UcitajPodatke("korisnici.txt", centri))
		cout << "Ucitavanje uspjesno" << crt;
	for (auto& centar : centri)
		cout << centar.GetNaziv() << " sa " <<
		centar.GetKorisnici().size() << " korisnika" << crt;
	cin.get();
	return 0;
}
