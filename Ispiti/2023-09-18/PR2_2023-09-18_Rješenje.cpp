/*
	DISCLAIMER

	U slucaju da se ne podrazumijeva, na ispitu se ne daju (at least as of writing this)
	ikakvi dodatni bodovi za "optimizovan kod", takoder ne oduzimaju bodovi (u ovom ispitu)
	za memory leaks.
	Zbog cega u odredenim situacijama ja cu radi jednostavnosti pisati kod u kojem ne uzimam
	u obzir ista sem toga da se main moze pokrenut i nema ikakvih izuzetaka.
*/
#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <chrono>
using namespace std;

const char* PORUKA = "\n-----------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. METODE KOJE NISU VOID, MORAJU VRACATI NEKU VRIJEDNOST!\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"13. RJESENJE TESTIRAJTE U OBA MODA (F5 i Ctrl+F5)\n"
"------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
const int MaxBrojRjesenja = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

char* GetNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

// Stuff I added below

std::ostream& operator<<(std::ostream& os, Predmet predmet) {
	switch (predmet)
	{
	case UIT:
		os << "UIT";
		break;
	case PRI:
		os << "PRI";
		break;
	case PRII:
		os << "PRII";
		break;
	case PRIII:
		os << "PRIII";
		break;
	case RSI:
		os << "RSI";
		break;
	case RSII:
		os << "RSII";
		break;
	default:
		os << "Predmet ne postoji";
		break;
	}

	return os;
}

const std::string NEVALIDNA_LOZINKA { "<VRIJEDNOST_NIJE_VALIDNA>" };

bool ValidirajLozinku(const std::string& lozinka) {
	std::regex minimalno7Karaktera{ ".{7,}" };
	std::regex jednoMaloSlovo{ "[a-z]" };
	std::regex jednoVelikoSlovo{ "[A-Z]" };
	std::regex jedanBroj{ "\\d" };
	std::regex jedanSpecijalniZnak{ "\\W" };

	return std::regex_search(lozinka, minimalno7Karaktera)
		&& std::regex_search(lozinka, jednoMaloSlovo)
		&& std::regex_search(lozinka, jednoVelikoSlovo)
		&& std::regex_search(lozinka, jedanBroj)
		&& std::regex_search(lozinka, jedanSpecijalniZnak);
}

// Stuff I added above

template<class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1[max]{ nullptr };
	T2* _elementi2[max]{ nullptr };
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int{ 0 };
	}
	~Kolekcija() {
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
		delete _trenutno; _trenutno = nullptr;
	}
	T1 getElement1(int lokacija)const { return *_elementi1[lokacija]; }
	T2 getElement2(int lokacija)const { return *_elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below

	Kolekcija(const Kolekcija& kolekcija) {
		_trenutno = new int{ kolekcija.getTrenutno() };

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ kolekcija.getElement1(i) };
			_elementi2[i] = new T2{ kolekcija.getElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		if (this == &rhs) {
			return *this;
		}
		
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
		delete _trenutno; _trenutno = nullptr;
		
	_trenutno = new int{ rhs.getTrenutno() };
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.getElement1(i) };
			_elementi2[i] = new T2{ rhs.getElement2(i) };
		}

		return *this;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (getTrenutno() == max) {
			throw exception("Maksimalni broj elemenata dostignut");
		}

		_elementi1[getTrenutno()] = new T1{ element1 };
		_elementi2[getTrenutno()] = new T2{ element2 };

		++(*_trenutno);
	}

	void AddElement(const T1& element1, const T2& element2, int index) {
		if (getTrenutno() == max) {
			throw exception("Maksimalni broj elemenata dostignut");
		}

		Kolekcija kopijaSaDodanimElementom{};

		for (int i = 0; i < getTrenutno(); ++i) {
			if (i == index) {
				kopijaSaDodanimElementom.AddElement(element1, element2);
			}
			kopijaSaDodanimElementom.AddElement(getElement1(i), getElement2(i));
		}

		*this = kopijaSaDodanimElementom;
	}

	T2& operator[](const T1& element1) const {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (element1 == getElement1(i)) {
				return *_elementi2[i];
			}
		}
	}

	Kolekcija* operator()(const int start, const int end) const {
		Kolekcija* elementiUOpsegu{ new Kolekcija{} };

		for (int i = start; i <= end; ++i) {
			elementiUOpsegu->AddElement(getElement1(i), getElement2(i));
		}

		return elementiUOpsegu;
	}
};
class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}

	// Methods I added below

	int getDan() const {
		return *_dan;
	}

	int getMjesec() const {
		return *_mjesec;
	}

	int getGodina() const {
		return *_godina;
	}

	Datum(const Datum& datum) {
		_dan = new int(datum.getDan());
		_mjesec = new int(datum.getMjesec());
		_godina = new int(datum.getGodina());
	}

	Datum& operator=(const Datum& rhs) {
		*_dan = rhs.getDan();
		*_mjesec = rhs.getMjesec();
		*_godina = rhs.getGodina();

		return *this;
	}

	int toInt() const {
		return getDan() + getMjesec() * 31 + getGodina() * 365;
	}

	int operator-(const Datum& rhs) const {
		return toInt() - rhs.toInt();
	}

	bool operator>=(const Datum& rhs) const {
		return toInt() >= rhs.toInt();
	}

	bool operator<=(const Datum& rhs) const {
		return toInt() <= rhs.toInt();
	}
};
/*na odredjeno pitanje kandidat je duzan postaviti vise odgovora/rjesenja od kojih ce svako biti ocijenjeno*/
class Pitanje {
	char* _sadrzaj;
	//int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
	Kolekcija<int, Datum*, MaxBrojRjesenja> _ocjeneRjesenja;
public:
	Pitanje(const char* sadrzaj = "") {
		_sadrzaj = GetNizKaraktera(sadrzaj);
	}
	~Pitanje() {
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	char* GetSadrzaj() const { return _sadrzaj; }
	Kolekcija<int, Datum*, MaxBrojRjesenja> GetOcjene() const { return _ocjeneRjesenja; }

	// Methods I added below

	Pitanje(const Pitanje& pitanje) {
		_sadrzaj = GetNizKaraktera(pitanje.GetSadrzaj());

		for (int i = 0; i < pitanje.GetOcjene().getTrenutno(); ++i) {
			const int ocjena = pitanje.GetOcjene().getElement1(i);
			const Datum& datumOcjene = *pitanje.GetOcjene().getElement2(i);

			_ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });
		}
	}

	Pitanje& operator=(const Pitanje& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _sadrzaj; _sadrzaj = nullptr;

		_sadrzaj = GetNizKaraktera(rhs.GetSadrzaj());
		for (int i = 0; i < rhs.GetOcjene().getTrenutno(); ++i) {
			const int ocjena = rhs.GetOcjene().getElement1(i);
			const Datum& datumOcjene = *rhs.GetOcjene().getElement2(i);

			_ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });
		}

		return *this;
	}

	bool DaLiJeDatumOcjeneValidan(const Datum& datumOcjene) {
		const int ocjeneRjesenjaSize = GetOcjene().getTrenutno();

		if (ocjeneRjesenjaSize == 0) {
			return true;
		}

		const Datum& zadnjiDatumOcjene = *GetOcjene().getElement2(ocjeneRjesenjaSize - 1);

		return datumOcjene - zadnjiDatumOcjene >= 3;
	}

	bool AddOcjena(const Datum& datumOcjene, const int ocjena) {
		if (!DaLiJeDatumOcjeneValidan(datumOcjene)) {
			return false;
		}

		_ocjeneRjesenja.AddElement(ocjena, new Datum{ datumOcjene });
		return true;
	}

	float GetProsjekOcjena() const {
		const int ocjeneRjesenjaSize = GetOcjene().getTrenutno();
		float sumaOcjena{ 0.0f };

		if (ocjeneRjesenjaSize == 0) {
			return sumaOcjena;
		}

		for (int i = 0; i < ocjeneRjesenjaSize; ++i) {
			const int ocjena = GetOcjene().getElement1(i);
			sumaOcjena += ocjena;
		}

		return sumaOcjena / ocjeneRjesenjaSize;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pitanje& pitanje) {
		os << "Sadrzaj/tekst pitanja: " << pitanje.GetSadrzaj() << '\n';
		os << "Datum ocjene - ocjena:\n";

		for (int i = 0; i < pitanje.GetOcjene().getTrenutno(); ++i) {
			const int ocjena = pitanje.GetOcjene().getElement1(i);
			const Datum& datumOcjene = *pitanje.GetOcjene().getElement2(i);

			os << '\t' << datumOcjene << " - " << ocjena << '\n';
		}
		os << "Prosjek ocjena: " << pitanje.GetProsjekOcjena() << '\n';

		return os;
	}

	/*
		Posto nije nigdje naglaseno sta cini dva pitanja jednaka
		for the sake of simplicty uzet cu da je samo sadrzaj, to
		ce biti dovoljno da testni main radi
	*/
	bool operator==(const Pitanje& rhs) const {
		return std::string(GetSadrzaj()) == rhs.GetSadrzaj();
	}

	bool operator!=(const Pitanje& rhs) const {
		return !(*this == rhs);
	}

	bool DaLiPostojiOcjenaUIntervalu(const Datum& startDate, const Datum& endDate) const {
		for (int i = 0; i < GetOcjene().getTrenutno(); ++i) {
			const Datum& datumOcjene = *GetOcjene().getElement2(i);

			if (startDate >= datumOcjene && datumOcjene <= endDate) {
				return true;
			}
		}
		return false;
	}
};
class Ispit {
	Predmet* _predmet;
	vector<Pitanje> _pitanjaOdgovori;
public:
	Ispit(Predmet predmet = UIT) {
		_predmet = new Predmet{ predmet };
	}
	~Ispit() {
		delete _predmet; _predmet = nullptr;
	}
	vector<Pitanje>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
	Predmet GetPredmet() const { return *_predmet; }
	friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
		COUT << *obj._predmet << endl;
		for (size_t i = 0; i < obj._pitanjaOdgovori.size(); i++)
			COUT << obj._pitanjaOdgovori[i];
		return COUT;
	}

	// Methods I added below

	const std::vector<Pitanje>& GetPitanjaOdgovore() const { return _pitanjaOdgovori; }

	Ispit(const Ispit& ispit) {
		_predmet = new Predmet{ ispit.GetPredmet() };
		_pitanjaOdgovori = ispit.GetPitanjaOdgovore();
	}

	Ispit& operator=(const Ispit& ispit) {
		if (this == &ispit) {
			return *this;
		}

		delete _predmet; _predmet = nullptr;

		_predmet = new Predmet{ ispit.GetPredmet() };
		_pitanjaOdgovori = ispit.GetPitanjaOdgovore();

		return *this;
	}

	bool DaLiJePitanjeVecDodato(const Pitanje& pitanjeZaProvjerit) const {
		for (const auto& pitanje : GetPitanjaOdgovore()) {
			if (pitanje == pitanjeZaProvjerit) {
				return true;
			}
		}

		return false;
	}

	void DodajPitanje(const Pitanje& pitanjeZaDodat) {
		_pitanjaOdgovori.push_back(pitanjeZaDodat);
	}

	float GetProsjekPitanja() const {
		const int pitanjaSize = GetPitanjaOdgovore().size();
		float sumaProsjekaOcjena{ 0.0f };

		if (pitanjaSize == 0) {
			return sumaProsjekaOcjena;
		}

		for (const auto& pitanje : GetPitanjaOdgovore()) {
			sumaProsjekaOcjena += pitanje.GetProsjekOcjena();
		}

		return sumaProsjekaOcjena / pitanjaSize;
	}

	int GetBrojPitanja() const {
		return GetPitanjaOdgovore().size();
	}
};

class Korisnik {
protected:
	char* _imePrezime;
	string _emailAdresa;
	string _lozinka;
	bool _aktivan;
public:
	Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
	{
		_imePrezime = GetNizKaraktera(imePrezime);
		_emailAdresa = emailAdresa;
		_lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
		_aktivan = true;
	}
	virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
	string GetEmail() const { return _emailAdresa; }
	string GetLozinka() const { return _lozinka; }
	char* GetImePrezime() const { return _imePrezime; }
	bool GetAktivan() const { return _aktivan; }
	void SetAktivan(bool aktivan) { _aktivan = aktivan; }
	virtual void Info() = 0;

	// Methods I added below

	friend std::ostream& operator<<(std::ostream& os, const Korisnik& korisnik) {
		os << "Ime i prezime: " << korisnik.GetImePrezime() << '\n';
		os << "Email: " << korisnik.GetEmail() << '\n';
		os << "Lozinka: " << korisnik.GetLozinka() << '\n';
		os << "Aktivan: " << (korisnik.GetAktivan() ? "DA" : "NE") << '\n';

		return os;
	}
};

class Kandidat : public Korisnik {
	vector<Ispit*> _polozeniPredmeti;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string lozinka)
		: Korisnik(imePrezime, emailAdresa, lozinka)
	{}
	~Kandidat() {
		for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
			delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
		cout << crt << "KANDIDAT :: DESTRUKTOR" << crt;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << (Korisnik&)obj << endl;
		for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
			COUT << *obj._polozeniPredmeti[i];
		return COUT;
	}
	vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

	// Methods I added below

	void Info() override {
		std::cout << *this;
	}

	Ispit* GetIspitForPredmet(const Predmet predmet) const {
		for (Ispit* const ispit : _polozeniPredmeti) {
			if (ispit->GetPredmet() == predmet) {
				return ispit;
			}
		}

		return nullptr;
	}

	bool DaLiJeIspunjenUslovZaVisiPredmet() const {
		if (_polozeniPredmeti.empty()) {
			return true;
		}

		const Ispit& ispit = *_polozeniPredmeti.back();

		return ispit.GetBrojPitanja() >= 3
			&& ispit.GetProsjekPitanja() > 3.5f;
	}

	bool AddPitanje(const Predmet predmet, const Pitanje& pitanje) {
		if (!GetAktivan()) {
			return false;
		}

		Ispit* const postojeciIspit{ GetIspitForPredmet(predmet) };

		if (postojeciIspit) {
			if (postojeciIspit->DaLiJePitanjeVecDodato(pitanje)) {
				return false;
			}

			postojeciIspit->DodajPitanje(pitanje);
			SendMail(predmet, pitanje);

			return true;
		}
		else if (!DaLiJeIspunjenUslovZaVisiPredmet()) {
			return false;
		}

		Ispit* const noviIspit{ new Ispit{ predmet} };
		noviIspit->DodajPitanje(pitanje);
		
		_polozeniPredmeti.push_back(noviIspit);
		SendMail(predmet, pitanje);

		return true;
	}

	void SendMail(const Predmet predmet, const Pitanje& pitanje) {
		std::thread emailThread{
			[&]() {
				std::this_thread::sleep_for(2s);

				std::cout << "FROM:info@kursevi.ba\n";
				std::cout << "TO:" << GetEmail() << "\n\n";
				std::cout << "Postovani " << GetImePrezime() << ", evidentirana vam je pitanje ";
				std::cout << "\"" << pitanje.GetSadrzaj() << "\" za odgovor na predmet " << predmet;
				std::cout << ".Dosadasnji uspjeh(prosjek ocjena) za pitanje iznosi ";
				std::cout << pitanje.GetProsjekOcjena() << ", a ukupni uspjeh(prosjek ocjena) na ";
				std::cout << "svim predmetima iznosi " << GetProsjekPolozeniPredmeta() << ".\n";
				std::cout << "Pozdrav.\n";
				std::cout << "EDUTeam.\n";
			}
		};
		emailThread.join();
	}

	float GetProsjekPolozeniPredmeta() const {
		const int polozeniPredmetiSize = _polozeniPredmeti.size();
		float sumaProsjekaPolozeniPredmeta{ 0.0f };

		if (polozeniPredmetiSize == 0) {
			return sumaProsjekaPolozeniPredmeta;
		}

		for (const Ispit* const ispit : _polozeniPredmeti) {
			sumaProsjekaPolozeniPredmeta += ispit->GetProsjekPitanja();
		}

		return sumaProsjekaPolozeniPredmeta / polozeniPredmetiSize;
	}

	Kolekcija<Pitanje, float> operator()(const Datum& startDate, const Datum& endDate) {
		Kolekcija<Pitanje, float> pitanjaOcjenjenaUIntervalu{};

		for (const Ispit* const ispit : _polozeniPredmeti) {
			for (const Pitanje& pitanje : ispit->GetPitanjaOdgovore()) {
				if (pitanje.DaLiPostojiOcjenaUIntervalu(startDate, endDate)) {
					pitanjaOcjenjenaUIntervalu.AddElement(
						pitanje, 
						pitanje.GetProsjekOcjena()
					);
				}
			}
		}

		return pitanjaOcjenjenaUIntervalu;
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite STACK i HEAP dio memorije, za šta su namijenjeni, te na koji način se trebaju koristiti (prednosti i nedostaci pojedinih slučajeva).\n";
	return "Odgovor -> STACK je dio memorije namjenjen za automatsu alokaciju i dealokaciju"
		", gdje se najcesce cuvaju lokalne varijable i stack frames funkcija.\n"
		"Prednost je to sto je brza i automatski alocira i dealocira podatke, dok je mana ogranicen "
		"kapacitet memorije na raspolaganju, pa se tu ne bi trebale spasavati vece kolicine podataka.\n"
		"HEAP je dio memorije namjenjen za dinamicku alokaciju i dealokaciju, koristeci new i delete"
		"u C++-u\n"
		"Prednost je to sto imamo vise memorije na raspolaganju, pa je moguce alocirati vece objekte,"
		" dok je mana sporije alokacije i dealokacije od STACK-a, potrebno je rucno alocirati i dealocirati"
		" memorije sto moze dovesti do memory leak-a i fragmentacije (sto moze dodatno usporit program)\n";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite preduslove za realizaciju polimorfizma, te koje su prednosti njegovog korištenja?\n";
	return "Odgovor -> Preduslov za realizaciju polimorfizma (u kontekstu OOP-a) je uspostavljanje "
		"nasljedivanja izmedu 2 ili vise klasa i osigurati da bazna i izvedena klasa imaju metodu sa"
		" istim prototipom gdje je makar bazna metoda oznacena sa virtual.\n"
		"Prednosti su te da polimorfizam omogucava pisanje fleksibilnijeg koda koji se moze lahko"
		" prosiriti (ako je sve uradeno kako treba) i izmjeniti, takoder smanjuje ponavljanje koda.\n"
		"Primjer: Recimo da pravimo neku UI aplikaciju, gdje bismo imali vise "
		" komponenti (button, text box, etc) i zelimo da nacrtamo na ekran svaki frame ove komponent, "
		" ovjde jedan pristupi bi bio da generalizujemo sve ove komponente pod jednu klasu kao sto je "
		" \"Widget\" ili \"Component\" i naslijedimo u ostale klase \"Button\", \"TextBox\", i osiguramo"
		" da sve metode imaju Draw() metodu, sada mozemo svim komponentama pristupiti preko zajednicke"
		" klase (bazne) i sve ih mozemo nacrtat pomocu Draw() metode, gdje logika za crtanje bi se mogla"
		" promjeniti u klasama koje naslijede baznu. Da nema polimorfizma ovaj postupak bi zahtjevao"
		" mnogo vise jedno te istog koda u svim klasama.";
}
void main() {

	cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	Datum   datum19062023(19, 6, 2023),
		datum20062023(20, 6, 2023),
		datum30062023(30, 6, 2023),
		datum05072023(5, 7, 2023);

	int kolekcijaTestSize = 10;

	Kolekcija<int, int> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize - 2; i++)
		kolekcija1.AddElement(i, i);

	cout << kolekcija1 << endl;

	try {
		/*metoda AddElement baca izuzetak u slucaju da se pokusa
		dodati vise od maksimalnog broja elemenata. Ako zelite da testirate
izuzetak, uklonite -2 iz prethodne for petlje*/
		kolekcija1.AddElement(11, 11);
	}
	catch (exception& err) {
		cout << crt << "Greska -> " << err.what() << crt;
	}
	cout << kolekcija1 << crt;

	kolekcija1.AddElement(9, 9, 2);
	/*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
	nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
	u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
	0 0
	1 1
	2 2
	3 3
	nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
	0 0
	9 9
	1 1
	2 2
	3 3
	*/

	cout << kolekcija1 << crt;

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija1 << crt;

	//na osnovu vrijednosti T1 mijenja vrijednost T2. 
	kolekcija1[9] = 2;
	/* npr.ako unutar kolekcije postoje elementi:
	0 0
	9 9
	1 1
	2 2
	3 3
	nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
	0 0
	9 2
	1 1
	2 2
	3 3
	*/

	Kolekcija<int, int>* kolekcija3 = kolekcija1(1, 3);
	/*kolekcija3 treba sadrzavati sve elemente koji se u kolekciji1 nalaze na lokacijama sa proslijedjenim indeksima,
	u ovom primjeru na lokacijama sa indeksom od 1 do 3, npr.ako unutar kolekcije1 postoje elementi:
	   0 0
	   9 9
	   1 1
	   2 2
	   3 3
	   sadrzaj kolekcije3 ce biti sljedeci
	   9 9
	   1 1
	   2 2

	   u slucaju da se zahtijevaju lokacije koje ne postoje u kolekciji, funkcija vraca samo one elemente koje postoje
	   u zahtijevanom opsegu (bez bacanja izuzetaka).
   */
	cout << *kolekcija3 << endl;
	delete kolekcija3;

	Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza?"),
		dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom?"),
		visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa?"),
		regex("Navedite par primjera regex validacije podataka?"),
		polimorfizam("Na koji nacin se realizuje polimorfizam?");

	/*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
		-   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
		-   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
	*/
	if (sortiranjeNiza.AddOcjena(datum19062023, 1))
		cout << "Ocjena evidentirana!" << endl;
	if (!sortiranjeNiza.AddOcjena(datum20062023, 5))
		cout << "Ocjena NIJE evidentirana!" << endl;
	if (sortiranjeNiza.AddOcjena(datum30062023, 5))
		cout << "Ocjena evidentirana!" << endl;

	if (polimorfizam.AddOcjena(datum19062023, 5))
		cout << "Ocjena evidentirana!" << endl;

	// ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
	// ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
	cout << sortiranjeNiza << endl;

	if (ValidirajLozinku("john4Do*e"))
		cout << "Lozinka :: OK :)" << crt;
	if (!ValidirajLozinku("john4Doe"))
		cout << "Lozinka :: Specijalni znak?" << crt;
	if (!ValidirajLozinku("jo*4Da"))
		cout << "Lozinka :: 7 znakova?" << crt;
	if (!ValidirajLozinku("4jo-hnoe"))
		cout << "Lozinka :: Veliko slovo?" << crt;
	if (ValidirajLozinku("@john2Doe"))
		cout << "Lozinka :: OK :)" << crt;

	/*
	za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
	-   najmanje 7 znakova
	-   velika i mala slova
	-   najmanje jedan broj
	-   najmanje jedan specijalni znak

	za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
	validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
	postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
	*/

	Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "j@sm1N*");
	Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "4Ade1*H");
	Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

	/*
	svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
	tom prilikom onemoguciti:
	- dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
	- dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
	(onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
	funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/

	//doraditi klase da nacin da omoguce izvrsenje naredne linije koda
	Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

	if (jasminPolaznik != nullptr) {
		if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija))
			cout << "Pitanje uspjesno dodano!" << crt;
		//ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
		if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
			cout << "Pitanje NIJE uspjesno dodano!" << crt;
		if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
			cout << "Pitanje uspjesno dodano!" << crt;
		if (jasminPolaznik->AddPitanje(PRI, regex))
			cout << "Pitanje uspjesno dodano!" << crt;
		if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
			cout << "Pitanje uspjesno dodano!" << crt;
		//ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
		if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
			cout << "Pitanje NIJE uspjesno dodano!" << crt;

		//onemoguciti dodavanje pitanja korisnicima koji nisu aktivni
		jasmin->SetAktivan(false);
		if (!jasminPolaznik->AddPitanje(PRII, polimorfizam))
			cout << "Pitanje NIJE uspjesno dodano!" << crt;

		//ispisuje sve dostupne podatke o kandidatu
		cout << *jasminPolaznik << crt;
	}

	/*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

	FROM:info@kursevi.ba
	TO: emailKorisnika

	Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
	za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
	Pozdrav.

	EDUTeam.

	slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
	*/

	//osigurati da se u narednim linijama poziva i destruktor klase Kandidat

	Datum ocijenjenOD(19, 6, 2023), ocijenjenDO(1, 7, 2023);
	/*
	koristeci adekvatan operator osigurati pretragu pozitivno ocijenjeni odgovora u okviru pitanja u proslijedjenom vremenskom opsegu OD - DO.
	rezultat pretrage trebaju biti ona pitanja kojima je, u definisanom periodu, najmanje jedan odgovor ocijenjen pozitivno. drugi formalni
	argument tipa float predstavlja prosjecnu ocjenu odgovora na pronadjenom pitanju
	*/
	Kolekcija<Pitanje, float> pretraga = (*jasminPolaznik)(ocijenjenOD, ocijenjenDO);
	cout << "U periodu od " << ocijenjenOD << " - " << ocijenjenDO << " ocijenjeno " << pretraga.getTrenutno() << " pitanja." << endl;
	for (size_t i = 0; i < pretraga.getTrenutno(); i++)
		cout << pretraga.getElement1(i) << endl << pretraga.getElement2(i) << crt;

	delete jasmin;
	delete adel;
	delete lozinkaNijeValidna;

	cin.get();
	system("pause>0");
}