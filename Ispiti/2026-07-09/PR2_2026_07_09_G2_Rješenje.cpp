#include <iostream>
#include <vector>
#include <regex>
#include <sstream>
#include <iomanip>
#include <thread>


using namespace std;

string crt = "\n-------------------------------------------------------------------------------- - \n";
string PORUKA_TELEFON = crt + "TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO.\n\n"
"SVI KOD KOJIH BUDE PRONADJEN TELEFON ILI NEKI DRUGI UREDJAJ KOJI MOZE SADRZAVATI\n"
"MATERIJAL ILI RJESENJA ISPITNIH ZADATAKA CE BITI UDALJENI SA ISPITA I BIT CE POKRENUT\n"
"POSTUPAK PROTIV NJIH" + crt;

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
	if (tekst == nullptr) return nullptr;
	size_t velicina = strlen(tekst) + 1;
	char* noviTekst = new char[velicina];
	strcpy_s(noviTekst, velicina, tekst);
	return noviTekst;
}

enum StatusZahtjeva { ZAPRIMLJEN, DIJAGNOSTIKA, POPRAVKA, ZAVRSEN };

const char* StatusZahtjevaNazivi[] = {
 "ZAPRIMLJEN", "DIJAGNOSTIKA", "POPRAVKA", "ZAVRSEN"
};


string GenerisiOznaku(const char* imePrezime, int redniBroj, int godina) {
	if (redniBroj < 1 || redniBroj > 999) {
		return "SRV-000/XX-0000";
	}

	if (godina < 2000 || godina > 2099) {
		return "SRV-000/XX-0000";
	}

	ostringstream buffer;

	string s_imePrezime = imePrezime;

	size_t lastSpace = s_imePrezime.find_last_of(' ');

	if (lastSpace == string::npos || lastSpace == s_imePrezime.size() - 1) {
		return "SRV-000/XX-0000";
	}

	buffer << "SRV-" << setfill('0') << setw(3) << redniBroj << "/" << imePrezime[0] << imePrezime[lastSpace + 1] << "-" << godina;

	return buffer.str();
}

/*
Koristeci regex, funkcija ValidirajOznaku provjerava prethodno
definisani
 format. Prefiks mora biti SRV, redni broj mora imati tri cifre i
ne moze
 biti 000, inicijali moraju biti velika slova, a godina je 2000-
2099.
 Potpis funkcije treba biti:
 bool ValidirajOznaku(const string& oznaka)
 */
bool ValidirajOznaku(const string& oznaka) {
	return regex_match(oznaka, regex("SRV-(?!000)[0-9]{3}/[A-Z]{2}-20([0-9]{2})"));
}

template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() : _trenutno(0) {
		_elementi1 = new T1[max];
		_elementi2 = new T2[max];
	}

	Kolekcija(const Kolekcija& other) : _trenutno(other._trenutno) {
		_elementi1 = new T1[max];
		_elementi2 = new T2[max];

		for (int i = 0; i < _trenutno; i++) {
			_elementi1[i] = other._elementi1[i];
			_elementi2[i] = other._elementi2[i];
		}
	}

	Kolekcija& operator=(const Kolekcija& other) {
		if (this == &other) return *this;
		_trenutno = other._trenutno;

		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = nullptr;
		_elementi2 = nullptr;

		_elementi1 = new T1[max];
		_elementi2 = new T2[max];

		for (int i = 0; i < _trenutno; i++) {
			_elementi1[i] = other._elementi1[i];
			_elementi2[i] = other._elementi2[i];
		}
		return *this;
	}

	T1& operator [] (int idx) {
		return _elementi1[idx];
	}

	int GetTrenutno() const { return _trenutno; }

	const T1& GetElement1(int indeks) const {
		return _elementi1[indeks];
	}

	const T2& GetElement2(int indeks) const {
		return _elementi2[indeks];
	}

	T2& GetElement2(int index) {
		return _elementi2[index];
	}

	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) <<
			endl;
		return COUT;
	}
	~Kolekcija() {
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}

	void Dodaj(T1 el1, T2 el2) {
		if (_trenutno >= max) {
			throw exception("collection full");
		};
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;

		_trenutno++;
	}

	Kolekcija<T1, T2, max> UkloniDuplikate() {
		Kolekcija<T1, T2, max> nova;

		for (int i = 0; i < _trenutno; i++) {
			int postoji = false;
			for (int j = 0; i < _trenutno; j++) {
				if (_elementi1[i] == nova.GetElement1(j) && _elementi2[i] == nova.GetElement2(j)) {
					postoji = true;
					break;
				}
			}

			if (!postoji) {
				nova.Dodaj(_elementi1[i], _elementi2[i]);
			}
		}

		return nova;
	}

};





class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minute;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000,
		int sati = 0, int minute = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minute = new int(minute);
	}

	DatumVrijeme(const DatumVrijeme& other) {
		_dan = new int(*other._dan);
		_mjesec = new int(*other._mjesec);
		_godina = new int(*other._godina);
		_sati = new int(*other._sati);
		_minute = new int(*other._minute);
	}
	DatumVrijeme& operator=(const DatumVrijeme& other) {
		if (this == &other) return *this;
		delete _dan;
		delete _mjesec;
		delete _godina;
		delete _sati;
		delete _minute;
		_dan = _mjesec = _godina = _sati = _minute = nullptr;

		_dan = new int(*other._dan);
		_mjesec = new int(*other._mjesec);
		_godina = new int(*other._godina);
		_sati = new int(*other._sati);
		_minute = new int(*other._minute);
		return *this;
	}
	int GetGodina() const { return *_godina; }
	friend ostream& operator<<(ostream& COUT, const DatumVrijeme& obj)
	{
		// ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM
		COUT << obj.ToString();
		return COUT;
	}

	string ToString() const {
		ostringstream buffer;

		buffer << setfill('0') << setw(2) << *_dan << ".";
		buffer << setfill('0') << setw(2) << *_mjesec << ".";
		buffer << setfill('0') << setw(4) << *_godina << " ";
		buffer << setfill('0') << setw(2) << *_sati << ":";
		buffer << setfill('0') << setw(2) << *_minute << endl;


		return buffer.str();
	}

	~DatumVrijeme() {
		delete _dan;
		delete _mjesec;
		delete _godina;
		delete _sati;
		delete _minute;
		_dan = _mjesec = _godina = _sati = _minute = nullptr;
	}

	bool operator > (const DatumVrijeme& other) const {
		if (*_godina != *other._godina) return *_godina > *other._godina;
		if (*_mjesec != *other._mjesec) return *_mjesec > *other._mjesec;
		if (*_dan != *other._dan) return *_dan > *other._dan;

		if (*_sati != *other._sati) return *_sati > *other._sati;


		return *_minute > *other._minute;
	}

	bool operator == (const DatumVrijeme& other) const {
		return *_godina == *other._godina &&
			*_mjesec == *other._mjesec &&
			*_dan == *other._dan &&
			*_sati == *other._sati &&
			*_minute == *other._minute;
	}

};

class Intervencija {
	string _opis;
	string _tehnicar;
	double _cijena;
	int _trajanjeMinuta;
public:
	const string& GetOpis() const { return _opis; }
	const string& GetTehnicar() const { return _tehnicar; }
	double GetCijena() const { return _cijena; }
	int GetTrajanjeMinuta() const { return _trajanjeMinuta; }
	friend ostream& operator<<(ostream& COUT, const Intervencija& obj)
	{
		/*
		ToString vraca podatke u formatu :
		opis | tehnicar | cijena KM | trajanje min
		Zamjena diska | Haris Hadzic | 85.50 KM | 45 min
		*/
		COUT << obj.ToString();
		return COUT;
	}
	Intervencija(const char* opis, const char* tehnicar, double cijena, int trajanje) : _opis(opis), _tehnicar(tehnicar), _cijena(cijena), _trajanjeMinuta(trajanje) {}

	string ToString() const {
		ostringstream buffer;

		buffer << GetOpis() << " | " << GetTehnicar() << " | " << GetCijena() << " | " << GetTrajanjeMinuta() << endl;

		return buffer.str();
	}

};



class Klijent {
	string _imePrezime;
	string _email;
	string _telefon;
public:
	Klijent(const char* imePrezime, const char* email, const char* telefon) {
		_imePrezime = imePrezime;
		_email = email;
		_telefon = telefon;
	}
	// ovdje inace nisu potrebni copy constructori, oni se inace prave kada imas pointer u klasi, npr da je bilo char* _imePrezime, ovako ga obicno ne moras pravit jer nema brige hocel se desit shallow copy
	Klijent(const Klijent& other) {
		_imePrezime = other.GetImePrezime();
		_email = other.GetEmail();
		_telefon = other.GetTelefon();
	}

	Klijent& operator=(const Klijent& other) {
		if (this == &other) return *this;
		_imePrezime = other.GetImePrezime();
		_email = other.GetEmail();
		_telefon = other.GetTelefon();
		return *this;
	}
	const string& GetImePrezime() const { return _imePrezime; }
	const string& GetEmail() const { return _email; }
	const string& GetTelefon() const { return _telefon; }
	friend ostream& operator<<(ostream& COUT, const Klijent& obj) {
		COUT << obj.GetImePrezime() << " | " << obj.GetEmail()
			<< " | " << obj.GetTelefon();
		return COUT;
	}
};



class ServisniZahtjev {
	char* _oznaka;
	char* _uredjaj;
	char* _opisKvara;
	int _redniBroj;
	Klijent _klijent;
	Kolekcija<StatusZahtjeva, DatumVrijeme, 10> _statusi;
	vector<Intervencija> _intervencije;
public:
	const char* GetOznaka() const { return _oznaka; }
	const char* GetUredjaj() const { return _uredjaj; }
	const char* GetOpisKvara() const { return _opisKvara; }
	int GetRedniBroj() const { return _redniBroj; }
	Klijent& GetKlijent() { return _klijent; }
	const Klijent& GetKlijent() const { return _klijent; }
	Kolekcija<StatusZahtjeva, DatumVrijeme, 10>& GetStatusi() {
		return _statusi;
	}
	const Kolekcija<StatusZahtjeva, DatumVrijeme, 10>& GetStatusi()
		const {
		return _statusi;
	}
	vector<Intervencija>& GetIntervencije() { return _intervencije; }
	const vector<Intervencija>& GetIntervencije() const {
		return
			_intervencije;
	}
	StatusZahtjeva GetTrenutniStatus() const {
		return
			_statusi.GetElement1(_statusi.GetTrenutno() - 1);
	}
	friend ostream& operator<<(ostream& COUT, const ServisniZahtjev& obj) {
		// ToString vraca:
		// oznaka | ime i prezime klijenta | uredjaj | trenutni status
		COUT << obj.ToString();
		return COUT;
	}

	string ToString() const {
		ostringstream buffer;

		buffer << GetOznaka() << " | " << GetKlijent().GetImePrezime() << " | " << GetUredjaj() << " | " << StatusZahtjevaNazivi[GetTrenutniStatus()] << endl;

		return buffer.str();
	}
	~ServisniZahtjev() {
		delete[] _oznaka;
		delete[] _uredjaj;
		delete[] _opisKvara;
		_oznaka = _uredjaj = _opisKvara = nullptr;
	}
	// : _klijent(klijent) se mora dodat ako ne zelis da se peglas sa jednom greskom vec 20 minuta :D
	ServisniZahtjev(const char* uredjaj, const char* opisKvara, const Klijent& klijent, int redniBroj, const DatumVrijeme& vrijeme) : _klijent(klijent) {
		_oznaka = AlocirajTekst(GenerisiOznaku(klijent.GetImePrezime().c_str(), redniBroj, vrijeme.GetGodina()).c_str());
		_uredjaj = AlocirajTekst(uredjaj);
		_opisKvara = AlocirajTekst(opisKvara);
		_redniBroj = redniBroj;

		_statusi.Dodaj(ZAPRIMLJEN, vrijeme);
	}

	ServisniZahtjev(const ServisniZahtjev& other) : _klijent(other._klijent) {
		_oznaka = AlocirajTekst(other.GetOznaka());
		_uredjaj = AlocirajTekst(other.GetUredjaj());
		_opisKvara = AlocirajTekst(other.GetOpisKvara());
		_redniBroj = other.GetRedniBroj();
		_intervencije = other.GetIntervencije();
		_statusi = other.GetStatusi();
	}

	bool DodajStatus(StatusZahtjeva status, const DatumVrijeme& vrijeme) {
		DatumVrijeme posljednjeVrijeme = _statusi.GetElement2(_statusi.GetTrenutno() - 1);
		StatusZahtjeva posljednjiStatus = GetTrenutniStatus();
		if (vrijeme > posljednjeVrijeme) {
			if(posljednjiStatus == ZAVRSEN) {
				return false;
			}
			else if ((int)status == (int)(posljednjiStatus + 1)) {
				_statusi.Dodaj(status, vrijeme);
				return true;
			}
		}

		return false;
	}

	double UkupnaCijena() {
		double sum = 0.0;

		for (const Intervencija& i : _intervencije) {
			sum += i.GetCijena();
		}

		return sum;
	}

	int UkupnoTrajanje() {
		int sum = 0.0;

		for (const Intervencija& i : _intervencije) {
			sum += i.GetTrajanjeMinuta();
		}

		return sum;
	}


	bool DodajIntervenciju(Intervencija intervencija) {
		StatusZahtjeva trenutni = GetTrenutniStatus();
		if (trenutni == DIJAGNOSTIKA || trenutni == POPRAVKA) {
			if (intervencija.GetCijena() > 0 && intervencija.GetTrajanjeMinuta() > 0) {
				_intervencije.push_back(intervencija);
				return true;
			}
		}
		return false;
	}


};



class Servis {
	char* _naziv;
	vector<ServisniZahtjev> _zahtjevi;
public:
	Servis(const char* naziv = "") {
		_naziv = AlocirajTekst(naziv);
	}
	const char* GetNaziv() const { return _naziv; }
	vector<ServisniZahtjev>& GetZahtjevi() { return _zahtjevi; }
	const vector<ServisniZahtjev>& GetZahtjevi() const {
		return
			_zahtjevi;
	}
	~Servis() {
		delete[] _naziv; _naziv = nullptr;
	}

	bool ZahtjevExist(int redniBroj) {
		return any_of(_zahtjevi.begin(), _zahtjevi.end(), [&](const ServisniZahtjev& z) {
			return z.GetRedniBroj() == redniBroj;
		});
	}
	bool ZahtjevExist(const char* oznaka) {
		return any_of(_zahtjevi.begin(), _zahtjevi.end(), [&](const ServisniZahtjev& z) {
			return strcmp(oznaka, z.GetOznaka()) == 0;
		});
	}

	void DodajZahtjev(const ServisniZahtjev& zahtjev) {
		if (ZahtjevExist(zahtjev.GetRedniBroj())) {
			throw exception("zahtjev already exists");
		};
		if (ZahtjevExist(zahtjev.GetOznaka())) {
			throw exception("zahtjev already exists");
		};
		_zahtjevi.push_back(zahtjev);
	}
	ServisniZahtjev* PronadjiZahtjev(string oznaka) {

		for (ServisniZahtjev& z : _zahtjevi) {
			if (oznaka == z.GetOznaka()) {
				return &z;
			}
		}
		return nullptr;
	}


	bool EvidentirajStatus(string oznaka, StatusZahtjeva status, const DatumVrijeme& vrijeme) {

		ServisniZahtjev* zahtjev = PronadjiZahtjev(oznaka);

		if (!zahtjev) return false;

		if (zahtjev->DodajStatus(status, vrijeme)) {
			thread t([&]() {
				ostringstream buffer;

				buffer << " ---------------------------------------------------------------------------------" <<endl;

				buffer << "To: " << zahtjev->GetKlijent().GetEmail() << endl;
				buffer << "From: racuni@servis.ba" << endl;
				buffer << "Subject: Servisni zahtjev zavrsen - racun" << endl;
				buffer << "Postovani " << zahtjev->GetKlijent().GetImePrezime() << endl;
				buffer << "Servisni zahtjev " << zahtjev->GetOznaka() << " za uredjaj " << zahtjev->GetUredjaj() << " je zavrsen." << endl;
				buffer << "Ukupan iznos: " << zahtjev->UkupnaCijena() << " KM" << endl;
				buffer << "Hvala na povjerenju." << endl;

				buffer << " ---------------------------------------------------------------------------------" << endl;

				cout << buffer.str();
				});
			t.join();
			return true;
		}

		return false;
	}
	vector<ServisniZahtjev*> IzdvojiNezavrsene() {
		vector<ServisniZahtjev*> nezavrseni;

		for (ServisniZahtjev& z : _zahtjevi) {
			if (z.GetTrenutniStatus() != ZAVRSEN) {
				nezavrseni.push_back(&z);
			}
		}

		return nezavrseni;
	}
	/*
	IzracunajPrihod vraca zbir cijena svih intervencija evidentiranih
   na
	zahtjevima koji imaju status ZAVRSEN. Intervencije na nezavrsenim
	zahtjevima ne ulaze u prihod.
	*/
	double IzracunajPrihod() {
		double sum = 0.0;

		for (ServisniZahtjev& z : _zahtjevi) {
			if (z.GetTrenutniStatus() == ZAVRSEN) {
				sum += z.UkupnaCijena();
			}
		}
		return sum;
	}

};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite zbog cega se operator<< implementira kao globalna a ne funkcija clanica, te na koji nacin se implementiraju prefiksalni i postfiksalni oblik operatora inkrementiranja ? \n";
	return "Odgovor -> operator<< se implementira kao globalna funkcija jer lijevi operand nije objekat naše klase, a prefiksni i postfiksni ++ razlikuju se po parametru int kod postfiksnog oblika.";
}

const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite nacin na koji biste, koristeci obradjene klase i metode, mogli saznati velicinu nekog tekstualnog fajla.\n";
	return "Odgovor -> Veličinu tekstualnog fajla možemo saznati otvaranjem fajla, pozicioniranjem na njegov kraj pomoću seekg() i očitavanjem pozicije pomoću tellg()";
}

int main() {
	cout << PORUKA_TELEFON; cin.get();
	cout << PORUKA_TELEFON; cin.get();
	cout << PORUKA_ISPIT; cin.get();
	system("cls");
	cout << GetOdgovorNaPrvoPitanje() << crt;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << crt;
	cin.get();
	/*
 Funkcija GenerisiOznaku generise oznaku servisnog zahtjeva u
formatu:
 SRV-BBB/IN-GGGG
 Potpis funkcije treba biti:
 string GenerisiOznaku(const char* imePrezime, int redniBroj, int
godina)
 SRV -> fiksni prefiks,
 BBB -> redni broj zahtjeva popunjen nulama na slobodnim mjestima,
 IN -> inicijali imena i prezimena klijenta,
 GGGG -> godina zaprimanja zahtjeva.
 Kod imena koje sadrzi vise rijeci koriste se inicijal prve i
posljednje
 rijeci. Redni broj mora biti u rasponu 1-999, a godina 2000-2099.
 Za neispravne podatke funkcija vraca "SRV-000/XX-0000".
 */
	if (GenerisiOznaku("Amina Buric", 42, 2026) == "SRV-042/AB-2026")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Goran Skondric", 7, 2026) == "SRV-007/GS2026")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Ana Marija Kovac", 156, 2027) ==
		"SRV-156/AK-2027")
		cout << "Oznaka OK" << crt;
	if (GenerisiOznaku("Amina", 42, 2026) == "SRV-000/XX-0000" &&
		GenerisiOznaku("Amina Buric", 0, 2026) == "SRV-000/XX-0000" &&
		GenerisiOznaku("Amina Buric", 1000, 2026) == "SRV-000/XX-0000"
		&&
		GenerisiOznaku("Amina Buric", 42, 1999) == "SRV-000/XX-0000")
		cout << "Neispravni podaci za oznaku OK" << crt;
	/*
	Koristeci regex, funkcija ValidirajOznaku provjerava prethodno
   definisani
	format. Prefiks mora biti SRV, redni broj mora imati tri cifre i
   ne moze
	biti 000, inicijali moraju biti velika slova, a godina je 2000-
   2099.
	Potpis funkcije treba biti:
	bool ValidirajOznaku(const string& oznaka)
	*/
	if (ValidirajOznaku("SRV-042/AB-2026"))
		cout << "OZNAKA VALIDNA" << crt;
	if (!ValidirajOznaku("SRV/042-AB-2026") &&
		!ValidirajOznaku("SRV-42/AB-2026") &&
		!ValidirajOznaku("SRV-042/Ab-2026") &&
		!ValidirajOznaku("SRV-000/AB-2026") &&
		!ValidirajOznaku("2026-SRV-042/AB"))
		cout << "OZNAKA NIJE VALIDNA" << crt;
	Kolekcija<int, string, 6> brojevi;
	brojevi.Dodaj(10, "Deset");
	brojevi.Dodaj(20, "Dvadeset");
	brojevi.Dodaj(10, "Deset");
	brojevi.Dodaj(30, "Trideset");
	brojevi.Dodaj(20, "Dvadeset");
	cout << brojevi << crt;
	/*
	UkloniDuplikate vraca novu kolekciju u kojoj je zadrzano samo prvo
	pojavljivanje svakog para. Par predstavlja duplikat iskljucivo ako
   su
	jednaki i prvi i drugi element. Originalna kolekcija ostaje
   nepromijenjena.
	*/
	Kolekcija<int, string, 6> bezDuplikata =
		brojevi.UkloniDuplikate();
	cout << "Bez duplikata:" << crt << bezDuplikata;
	cout << "Original:" << crt << brojevi;
	try {
		Kolekcija<int, string, 2> puna;
		puna.Dodaj(1, "Jedan");
		puna.Dodaj(2, "Dva");
		puna.Dodaj(3, "Tri");
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	Kolekcija<int, string, 6> kopijaBrojeva = brojevi;
	kopijaBrojeva[0] = 100;
	Kolekcija<int, string, 6> dodijeljeniBrojevi;
	dodijeljeniBrojevi = brojevi;
	dodijeljeniBrojevi.GetElement2(0) = "Izmijenjeno";
	cout << "Original:" << crt << brojevi;
	cout << "Kopija:" << crt << kopijaBrojeva;
	cout << "Dodijeljeni objekat:" << crt << dodijeljeniBrojevi;
	DatumVrijeme zaprimljen(9, 7, 2026, 8, 0);
	DatumVrijeme dijagnostika(9, 7, 2026, 9, 0);
	DatumVrijeme popravka(9, 7, 2026, 10, 0);
	DatumVrijeme zavrsen(9, 7, 2026, 11, 0);
	/*
	ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM,
   ukljucujuci
	pocetne nule.
	*/
	cout << zaprimljen.ToString() << crt; // 09.07.2026 08:00
	if (dijagnostika > zaprimljen)
		cout << "Vrijeme dijagnostike je nakon zaprimanja" << crt;
	DatumVrijeme kopijaDatuma(dijagnostika);
	if (kopijaDatuma == dijagnostika && !(zaprimljen == dijagnostika))
		cout << "Provjera vremena, OK." << crt;
	Klijent amina("Amina Buric", "amina@fit.ba", "061-111-222");
	Klijent goran("Goran Skondric", "goran@fit.ba", "062-222-333");
	Klijent kopijaKlijenta = amina;
	cout << kopijaKlijenta << crt;
	/*
   Intervencija sadrzi opis, ime tehnicara, cijenu i trajanje u
   minutama.
	*/
	Intervencija pregled("Dijagnostika uredjaja", "Haris Hadzic", 20,
		30);
	Intervencija zamjenaDiska("Zamjena diska", "Haris Hadzic", 85.5,
		45);
	Intervencija instalacija("Instalacija sistema", "Maja Majic", 35,
		60);
	/* ToString vraca podatke u formatu:
	opis | tehnicar | cijena KM | trajanje min
	Zamjena diska | Haris Hadzic | 85.50 KM | 45 min
	*/
	cout << zamjenaDiska.ToString() << crt;
	/*
	Konstruktor ServisnogZahtjeva generise oznaku na osnovu klijenta,
	rednog broja i godine zaprimanja, te evidentira pocetni status
   ZAPRIMLJEN
	sa proslijedjenim vremenom.
	*/
	ServisniZahtjev laptop("Laptop", "Ne pokrece se", amina, 42,
		zaprimljen);
	ServisniZahtjev telefon("Telefon", "Razbijen ekran", goran, 7,
		zaprimljen);
	/*
	ToString vraca podatke u formatu:
	oznaka | ime i prezime klijenta | uredjaj | trenutni status
	SRV-042/AB-2026 | Amina Buric | Laptop | ZAPRIMLJEN
	*/
	cout << laptop.ToString() << crt;
	if (laptop.ToString() ==
		"SRV-042/AB-2026 | Amina Buric | Laptop | ZAPRIMLJEN")
		cout << "ServisniZahtjev ToString OK" << crt;
	/*
	DodajStatus dodaje status samo ako je vrijeme vece od vremena
   posljednjeg
	statusa i ako status predstavlja neposredno sljedecu fazu.
	Dozvoljen slijed je: ZAPRIMLJEN -> DIJAGNOSTIKA -> POPRAVKA ->
   ZAVRSEN
	Preskakanje ili ponavljanje statusa nije dozvoljeno. Nakon statusa
	ZAVRSEN nisu dozvoljene nove promjene. Neuspjesan pokusaj vraca
   false
	bez izmjene kolekcije statusa.
	*/
	if (!laptop.DodajStatus(POPRAVKA, dijagnostika))
		cout << "Preskakanje statusa nije dozvoljeno" << crt;
	if (laptop.DodajStatus(DIJAGNOSTIKA, dijagnostika))
		cout << "Status DIJAGNOSTIKA dodan" << crt;
	if (!laptop.DodajStatus(DIJAGNOSTIKA, popravka))
		cout << "Ponavljanje statusa nije dozvoljeno" << crt;
	/*DodajIntervenciju dodaje intervenciju samo dok je zahtjev u
   statusu
	DIJAGNOSTIKA ili POPRAVKA, uz cijenu i trajanje vece od nule.
	Metoda vraca true ako je intervencija dodana, u suprotnom false.
	UkupnaCijena vraca zbir cijena svih intervencija, a UkupnoTrajanje
   zbir
	njihovih trajanja u minutama.
	*/
	if (laptop.DodajIntervenciju(pregled))
		cout << "Intervencija dodana" << crt;
	if (laptop.DodajStatus(POPRAVKA, popravka))
		cout << "Status POPRAVKA dodan" << crt;
	laptop.DodajIntervenciju(zamjenaDiska);
	laptop.DodajIntervenciju(instalacija);
	cout << "Ukupna cijena: " << laptop.UkupnaCijena() << " KM" <<
		crt;
	cout << "Ukupno trajanje: " << laptop.UkupnoTrajanje() << " min"
		<< crt;
	ServisniZahtjev kopijaLaptopa = laptop;
	cout << kopijaLaptopa << crt;
	Servis fitServis("FIT Servis");
	/*
	DodajZahtjev dodaje zahtjev u servis. Nije dozvoljeno dodati dva
   zahtjeva
	sa istim rednim brojem ili istom oznakom. U slucaju duplikata
   metoda
	baca izuzetak.
	*/
	fitServis.DodajZahtjev(laptop);
	fitServis.DodajZahtjev(telefon);
	try {
		fitServis.DodajZahtjev(telefon);
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	/*
	PronadjiZahtjev vraca pokazivac na zahtjev sa proslijedjenom
   oznakom.
	Ako zahtjev nije pronadjen, metoda vraca nullptr.
	*/
	string oznakaLaptopa = laptop.GetOznaka();
	ServisniZahtjev* pronadjen =
		fitServis.PronadjiZahtjev(oznakaLaptopa);
	if (pronadjen != nullptr)
		cout << "Pronadjen zahtjev: " << pronadjen->GetOznaka() <<
		crt;
	if (fitServis.PronadjiZahtjev("SRV-999/XX-2026") == nullptr)
		cout << "Zahtjev nije pronadjen" << crt;
	/*
	EvidentirajStatus pronalazi zahtjev i pokusava dodati status
   koristeci
   pravila metode DodajStatus.
   Racun se salje u zasebnom threadu iskljucivo nakon uspjesnog
   evidentiranja
	statusa ZAVRSEN. Za ostale statuse se ne salju obavijesti. Ako
   zahtjev ne
	postoji ili status nije dodan, metoda vraca false.
	Primjer sadrzaja racuna:
	------------------------------------------------------------------
   ---------------
	To: amina@fit.ba
	From: racuni@servis.ba
	Subject: Servisni zahtjev zavrsen - racun
	Postovani Amina Buric,
	Servisni zahtjev SRV-042/AB-2026 za uredjaj Laptop je zavrsen.
	Ukupan iznos: 140.50 KM
	Hvala na povjerenju.
	------------------------------------------------------------------
   ---------------
	*/
	if (fitServis.EvidentirajStatus(oznakaLaptopa, ZAVRSEN, zavrsen))
		cout << "Zahtjev zavrsen i racun poslan" << crt;
	if (!fitServis.EvidentirajStatus(
		oznakaLaptopa, ZAVRSEN, DatumVrijeme(9, 7, 2026, 12, 0)))
		cout << "Ponavljanje zavrsnog statusa nije dozvoljeno" << crt;
	if (!fitServis.EvidentirajStatus(
		"NEPOSTOJECI", DIJAGNOSTIKA, dijagnostika))
		cout << "Status nije evidentiran za nepostojeci zahtjev" <<
		crt;

	/*
	IzdvojiNezavrsene vraca vector pokazivaca na sve zahtjeve ciji
   trenutni
	status nije ZAVRSEN.
	*/
	vector<ServisniZahtjev*> nezavrseni =
		fitServis.IzdvojiNezavrsene();
	for (auto zahtjev : nezavrseni)
		cout << zahtjev->GetOznaka() << " -> "
		<< StatusZahtjevaNazivi[(int)zahtjev->GetTrenutniStatus()] <<
		crt;
	/*
	IzracunajPrihod vraca zbir cijena svih intervencija evidentiranih
   na
	zahtjevima koji imaju status ZAVRSEN. Intervencije na nezavrsenim
	zahtjevima ne ulaze u prihod.
	*/
	cout << "Ostvareni prihod: " << fitServis.IzracunajPrihod()
		<< " KM" << crt;
	Servis kopijaServisa = fitServis;
	cout << kopijaServisa.GetNaziv() << " ima "
		<< kopijaServisa.GetZahtjevi().size() << " zahtjeva" << crt;
	cin.get();
	return 0;
}
