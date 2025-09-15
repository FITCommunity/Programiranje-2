/*
	DISCLAIMER

	Ja nisam izlazio na ovaj rok, samo sam prikupio odredene informacije kroz pricu
	drugih studenata i slika koje su nekako uslikane tokom ispita. Moguce je da postoji
	mnogo vise razlicitih stvari nego sto sam naveo ovdje.

	U slucaju da se ne podrazumijeva, na ispitu se ne daju (at least as of writing this)
	ikakvi dodatni bodovi za "optimizovan kod", takoder ne oduzimaju bodovi (u ovom ispitu)
	za memory leaks.
	Zbog cega u odredenim situacijama ja cu radi jednostavnosti pisati kod u kojem ne uzimam
	u obzir ista sem toga da se main moze pokrenut i nema ikakvih izuzetaka.

	Takoder receno mi je da za metodu DodajTransakciju recenica
	"oneomguciti dupliranje transakcija sa istim vremenom,"
	Se odnosi cisto na Kupovine, ne radi se isto sa Povratima.
	Ovo mi je rekao kolega jedan, jer je pitao profesora tokom ispita.
*/
#include <iostream>
// Headers I added below
#include<string>
#include<regex>
#include<iomanip>
#include<sstream>
#include<fstream>
// Headers I added above
using namespace std;
char* AlocirajTekst(const char* tekst) {
	if (!tekst) return nullptr;
	size_t vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}

string crt = "\n-------------------------------------------------------------------------------- - \n";

string PORUKA_TELEFON = crt +
"TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO." + crt;

string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO KAO TM\n"
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ MAIN FUNKCIJI, "
" OSIM AKO POSTOJI JASAN RAZLOG ZA MODIFIKACIJU\n"
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n"
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n"
" AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILI VRATITE NEKU DEFAULT VRIJEDNOST\n"
"6. RJESENJE KOPIRAJTE U .DOCX DOKUMENT (NAZIV DOKUMENTA = BROJ INDEKSA, npr.IB150051.docx)\n"
"7. NA FTP SERVER POSTAVITE SAMO .DOCX DOKUMENT, A NE CIJELI PROJEKAT\n"
"8. SVE NEDOZVOLJENE RADNJE TOKOM ISPITA BIT CE SANKCIONISANE\n"
"9. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO VLASTITOM IZBORU\n"
"10. KORISTITE VISUAL STUDIO 2022 (C++17) I TESTIRAJTE PROGRAM U OBA MODA(F5 i Ctrl + F5)\n"
"11. NA KRAJU PROVJERITE DA LI STE RJESENJE ISPITA POSTAVILI U ODGOVARAJUCI FOLDER NA FTP SERVERU" + crt;

enum Kategorija { ELEKTRONIKA, KNJIGE, MODA, PREHRANA };
const char* KategorijaNazivi[] = { "ELEKTRONIKA", "KNJIGE", "MODA", "PREHRANA" };

// Functions I added below

std::ostream& operator<<(std::ostream& os, Kategorija kategorija) {
	os << KategorijaNazivi[kategorija];

	return os;
}

std::string GenerisiSifru(std::string imePrezime, int broj) {
	std::string sifra;

	char prvoSlovoImena = std::toupper(imePrezime[0]);
	int prvoSlovoPrezimenaIndex = imePrezime.find(' ') + 1;
	char prvoSlovoPrezimena = std::toupper(imePrezime[prvoSlovoPrezimenaIndex]);

	sifra += prvoSlovoImena;
	sifra += prvoSlovoPrezimena;
	sifra += ':';

	std::time_t sekundeOdPocetka = std::time(nullptr);
	std::tm trenutniDatumVrijeme;
	localtime_s(&trenutniDatumVrijeme, &sekundeOdPocetka);
	int trenutnaGodina = trenutniDatumVrijeme.tm_year + 1900;

	sifra += std::to_string(trenutnaGodina);
	sifra += '-';

	if (broj < 10) {
		sifra += "00";
	}
	else if (broj < 100) {
		sifra += '0';
	}

	sifra += std::to_string(broj);

	return sifra;
}

bool ValidirajSifru(std::string sifra) {
	return std::regex_match(sifra, std::regex("[A-Z]{2}:2025-\\d{3}"));
}

// Functions I added above

template<class T1, class T2, int max>
class KolekcijaParova {
	T1* _prvi[max] = { nullptr };
	T2* _drugi[max] = { nullptr };
	int _trenutno = 0;
public:
	KolekcijaParova() = default;
	~KolekcijaParova() {
		for (int i = 0; i < _trenutno; i++) {
			delete _prvi[i]; _prvi[i] = nullptr;
			delete _drugi[i]; _drugi[i] = nullptr;
		}
	}
	int GetTrenutno() const { return _trenutno; }
	T1& GetPrvi(int indeks) const { return *_prvi[indeks]; }
	T2& GetDrugi(int indeks) const { return *_drugi[indeks]; }
	T1& operator[](int indeks) { return *_prvi[indeks]; }
	friend ostream& operator<<(ostream& COUT, KolekcijaParova& obj) {
		for (int i = 0; i < obj._trenutno; i++)
			COUT << obj.GetPrvi(i) << " " << obj.GetDrugi(i) << "\n";
		return COUT;
	}

	// Methods I added below

	KolekcijaParova(const KolekcijaParova& kolekcijaParova) {
		_trenutno = kolekcijaParova.GetTrenutno();
		for (int i = 0; i < GetTrenutno(); ++i) {
			_prvi[i] = new T1(kolekcijaParova.GetPrvi(i));
			_drugi[i] = new T2(kolekcijaParova.GetDrugi(i));
		}
	}

	KolekcijaParova& operator=(const KolekcijaParova& kolekcijaParova) {
		if (this == &kolekcijaParova) {
			return *this;
		}

		for (int i = 0; i < _trenutno; i++) {
			delete _prvi[i]; _prvi[i] = nullptr;
			delete _drugi[i]; _drugi[i] = nullptr;
		}

		_trenutno = kolekcijaParova.GetTrenutno();
		for (int i = 0; i < GetTrenutno(); ++i) {
			_prvi[i] = new T1(kolekcijaParova.GetPrvi(i));
			_drugi[i] = new T2(kolekcijaParova.GetDrugi(i));
		}

		return *this;
	}

	void Dodaj(T1 el1, T2 el2) {
		if (GetTrenutno() == max) {
			return;
		}

		_prvi[GetTrenutno()] = new T1(el1);
		_drugi[GetTrenutno()] = new T2(el2);

		++_trenutno;
	}

	KolekcijaParova& DodajNaPoziciju(int index, T1 el1, T2 el2) {
		if (index < 0 || index >= GetTrenutno() || GetTrenutno() == max) {
			return *this;
		}

		KolekcijaParova kolekcijaSaDodanimElementima;

		for (int i = 0; i < GetTrenutno(); i++)
		{
			if (index == i) {
				kolekcijaSaDodanimElementima.Dodaj(el1, el2);
			}
			kolekcijaSaDodanimElementima.Dodaj(GetPrvi(i), GetDrugi(i));
		}

		*this = kolekcijaSaDodanimElementima;

		return *this;
	}

	KolekcijaParova* UkloniRaspon(int pocetak, int kolicina) {
		int kraj = pocetak + kolicina - 1;

		if (pocetak < 0 || kraj >= GetTrenutno() || pocetak >= kraj) {
			throw std::exception("Raspon za ukloniti ne postoji");
		}

		KolekcijaParova* obrisaniElementi = new KolekcijaParova;
		KolekcijaParova zadrzaniElementi;

		for (int i = 0; i < GetTrenutno(); i++)
		{
			if (i >= pocetak && i <= kraj) {
				obrisaniElementi->Dodaj(GetPrvi(i), GetDrugi(i));
			}
			else {
				zadrzaniElementi.Dodaj(GetPrvi(i), GetDrugi(i));
			}
		}

		*this = zadrzaniElementi;

		return obrisaniElementi;
	}
};
class DatumVrijeme {
	int* _godina, * _mjesec, * _dan, * _sati, * _minute, * _sekunde;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int
		sati = 0, int minute = 0, int sekunde = 0) {
		_godina = new int(godina);
		_mjesec = new int(mjesec);
		_dan = new int(dan);
		_sati = new int(sati);
		_minute = new int(minute);
		_sekunde = new int(sekunde);
	}
	~DatumVrijeme() {
		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute; delete _sekunde;
	}

	// Methods I added below

	DatumVrijeme(const DatumVrijeme& datumVrijeme) {
		_godina = new int(*datumVrijeme._godina);
		_mjesec = new int(*datumVrijeme._mjesec);
		_dan = new int(*datumVrijeme._dan);
		_sati = new int(*datumVrijeme._sati);
		_minute = new int(*datumVrijeme._minute);
		_sekunde = new int(*datumVrijeme._sekunde);
	}

	DatumVrijeme& operator=(const DatumVrijeme& datumVrijeme) {
		if (this == &datumVrijeme) {
			return *this;
		}

		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute; delete _sekunde;

		_godina = new int(*datumVrijeme._godina);
		_mjesec = new int(*datumVrijeme._mjesec);
		_dan = new int(*datumVrijeme._dan);
		_sati = new int(*datumVrijeme._sati);
		_minute = new int(*datumVrijeme._minute);
		_sekunde = new int(*datumVrijeme._sekunde);

		return *this;
	}

	static std::ostream& formatirajDioDatumaVrijeme(std::ostream& os, int data) {
		os << std::setfill('0');
		os << std::setw(2);
		os << data;

		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, const DatumVrijeme& datumVrijeme) {
		DatumVrijeme::formatirajDioDatumaVrijeme(os, *datumVrijeme._dan) << '.';
		DatumVrijeme::formatirajDioDatumaVrijeme(os, *datumVrijeme._mjesec) << '.';

		os << *datumVrijeme._godina << ' ';

		DatumVrijeme::formatirajDioDatumaVrijeme(os, *datumVrijeme._sati) << ':';
		DatumVrijeme::formatirajDioDatumaVrijeme(os, *datumVrijeme._minute) << ':';
		DatumVrijeme::formatirajDioDatumaVrijeme(os, *datumVrijeme._sekunde);

		return os;
	}

	bool operator==(const DatumVrijeme& datumVrijeme) const {
		return *_dan == *datumVrijeme._dan
			&& *_mjesec == *datumVrijeme._mjesec
			&& *_godina == *datumVrijeme._godina
			&& *_sati == *datumVrijeme._sati
			&& *_minute == *datumVrijeme._minute
			&& *_sekunde == *datumVrijeme._sekunde;
	}

	bool operator!=(const DatumVrijeme& datumVrijeme) const {
		return !(*this == datumVrijeme);
	}
};
class Artikal {
	char* _naziv;
	Kategorija _kategorija;
	int _cijena;
public:
	Artikal(const char* naziv = "", Kategorija kategorija =
		ELEKTRONIKA, int cijena = 0)
		: _kategorija(kategorija), _cijena(cijena) {
		_naziv = AlocirajTekst(naziv);
	}
	~Artikal() { delete[] _naziv; }
	const char* GetNaziv() const { return _naziv; }
	Kategorija GetKategorija() const { return _kategorija; }
	int GetCijena() const { return _cijena; }
	friend ostream& operator<<(ostream& COUT, const Artikal& p) {
		COUT << p._naziv << " " << KategorijaNazivi[(int)p._kategorija] << " " << p._cijena;
		return COUT;
	}

	// Methods I added below

	Artikal(const Artikal& artikal) {
		_naziv = AlocirajTekst(artikal._naziv);
		_kategorija = artikal._kategorija;
		_cijena = artikal._cijena;
	}

	Artikal& operator=(const Artikal& artikal) {
		if (this == &artikal) {
			return *this;
		}

		delete[] _naziv;

		_naziv = AlocirajTekst(artikal._naziv);
		_kategorija = artikal._kategorija;
		_cijena = artikal._cijena;

		return *this;
	}

	bool operator==(const Artikal& artikal) const {
		return string(_naziv) == artikal._naziv
			&& _kategorija == artikal._kategorija
			&& _cijena == artikal._cijena;
	}

	bool operator!=(const Artikal& artikal) const {
		return !(*this == artikal);
	}
};
class Transakcija {
protected:
	DatumVrijeme _vrijemeRealizacije;
	int _iznos;
public:
	Transakcija(DatumVrijeme vrijemeRealizacije, int iznos = 0)
		: _vrijemeRealizacije(vrijemeRealizacije), _iznos(iznos) {
	}
	virtual ~Transakcija() {}
	virtual string Info() const = 0;
	const DatumVrijeme& GetVrijemeRealizacije() const {
		return
			_vrijemeRealizacije;
	}
	int GetIznos() const { return _iznos; }

	// Methods I added below

	virtual Transakcija* GetClone() = 0;
};
class Kupovina : public Transakcija {
	vector<Artikal> _kupljeniArtikli;
public:
	Kupovina(DatumVrijeme vrijemeRealizacije) :
		Transakcija(vrijemeRealizacije, 0) {
	}
	const vector<Artikal>& GetArtikli() const {
		return
			_kupljeniArtikli;
	}

	// Methods I added below

	Transakcija* GetClone() {
		return new Kupovina(*this);
	}

	void DodajArtikal(Artikal artikal) {
		_kupljeniArtikli.push_back(artikal);
		_iznos += artikal.GetCijena();
	}

	string Info() const {
		std::ostringstream buffer;

		buffer << _vrijemeRealizacije << " KUPLJENO " << _kupljeniArtikli.size();
		buffer << " ARTIKALA U UKUPNOM IZNOSU OD " << _iznos << "KM";

		return buffer.str();
	}

	bool DaLiPostojiArtikal(Artikal artikal) {
		for (auto& kupljeniArtikal : _kupljeniArtikli) {
			if (kupljeniArtikal == artikal) {
				return true;
			}
		}

		return false;
	}

	bool DaLiPostojiArtikalUKategoriji(Kategorija kategorija) {
		for (auto& kupljeniArtikal : _kupljeniArtikli) {
			if (kupljeniArtikal.GetKategorija() == kategorija) {
				return true;
			}
		}

		return false;
	}
};
class Povrat : public Transakcija {
	vector<Artikal> _vraceniArtikli;
public:
	Povrat(DatumVrijeme vrijemeRealizacije) :
		Transakcija(vrijemeRealizacije, 0) {
	}
	const vector<Artikal>& GetArtikli() const {
		return
			_vraceniArtikli;
	}

	// Methods I added below

	Transakcija* GetClone() {
		return new Povrat(*this);
	}

	void DodajArtikal(Artikal artikal) {
		_vraceniArtikli.push_back(artikal);
		_iznos += artikal.GetCijena();
	}

	string Info() const {
		std::ostringstream buffer;

		buffer << _vrijemeRealizacije << " VRACENO " << _vraceniArtikli.size();
		buffer << " ARTIKALA U UKUPNOM IZNOSU OD " << _iznos << "KM";

		return buffer.str();
	}

	bool DaLiPostojiArtikalUKategoriji(Kategorija kategorija) {
		for (auto& vraceniArtikal : _vraceniArtikli) {
			if (vraceniArtikal.GetKategorija() == kategorija) {
				return true;
			}
		}

		return false;
	}
};
class Kupac {
	static int _id;
	char* _sifra;
	char* _imePrezime;
	vector<Transakcija*> _transakcije;
public:
	Kupac(const char* imePrezime) {
		_imePrezime = AlocirajTekst(imePrezime);
		_sifra = AlocirajTekst(GenerisiSifru(imePrezime, _id).c_str());
		_id++;
	}
	~Kupac() {
		delete[] _sifra;
		delete[] _imePrezime;
		for (auto* transakcija : _transakcije) delete transakcija;
		_transakcije.clear();
	}
	const char* GetSifra() const { return _sifra; }
	const char* GetImePrezime() const { return _imePrezime; }
	vector<Transakcija*>& GetTransakcije() { return _transakcije; }
	friend ostream& operator<<(ostream& COUT, Kupac& kupac) {
		COUT << crt << kupac._imePrezime << " [" << kupac._sifra <<
			"]\n";
		for (int i = 0; i < kupac._transakcije.size(); i++)
			COUT << " - " << kupac._transakcije[i]->Info() << "\n";
		COUT << crt;
		return COUT;
	}

	// Methods I added below

	Kupac(const Kupac& kupac) {
		_imePrezime = AlocirajTekst(kupac._imePrezime);
		_sifra = AlocirajTekst(kupac._sifra);
		for (auto* transakcija : kupac._transakcije) {
			_transakcije.push_back(transakcija->GetClone());
		}
	}

	Kupac& operator=(const Kupac& kupac) {
		if (this == &kupac) {
			return *this;
		}

		delete[] _sifra;
		delete[] _imePrezime;
		for (auto* transakcija : _transakcije) delete transakcija;
		_transakcije.clear();

		_imePrezime = AlocirajTekst(kupac._imePrezime);
		_sifra = AlocirajTekst(kupac._sifra);
		for (auto* transakcija : kupac._transakcije) {
			_transakcije.push_back(transakcija->GetClone());
		}

		return *this;
	}

	bool DaLiTransakcijaSaIstimVremenomPostoji(Transakcija* transakcijaZaDodat) {
		for (auto* transakcija : _transakcije) {
			if (transakcija->GetVrijemeRealizacije() == transakcijaZaDodat->GetVrijemeRealizacije()) {
				return true;
			}
		}

		return false;
	}

	std::vector<Kupovina> GetTransakcijeKojeSuKupovine() {
		std::vector<Kupovina> kupovineZaVratit;

		for (auto* transakcija : _transakcije) {
			Kupovina* kupovina = dynamic_cast<Kupovina*>(transakcija);

			if (kupovina) {
				kupovineZaVratit.push_back(*kupovina);
			}
		}

		return kupovineZaVratit;
	}

	bool DaLiKupovinaZaDodatImaPostojeciArtikal(Kupovina kupovinaZaDodat) {
		auto kupovine = GetTransakcijeKojeSuKupovine();

		for (auto& kupovina : kupovine) {
			for (auto& artikal : kupovina.GetArtikli()) {
				if (kupovinaZaDodat.DaLiPostojiArtikal(artikal)) {
					return true;
				}
			}
		}

		return false;
	}

	bool DodajTransakciju(Kupovina kupovinaZaDodat) {
		if (DaLiTransakcijaSaIstimVremenomPostoji(&kupovinaZaDodat)
			|| DaLiKupovinaZaDodatImaPostojeciArtikal(kupovinaZaDodat)) {
			return false;
		}

		_transakcije.push_back(new Kupovina(kupovinaZaDodat));
		return true;
	}

	bool DaLiSviProizvodiZaPovratPostoje(Povrat povratZaDodat) {
		auto kupovine = GetTransakcijeKojeSuKupovine();
		auto& povrati = povratZaDodat.GetArtikli();
		int pronaceniArtikli = 0;

		for (auto& artikal : povrati) {
			for (auto& kupovina : kupovine) {
				if (kupovina.DaLiPostojiArtikal(artikal)) {
					++pronaceniArtikli;
				}
			}
		}

		return pronaceniArtikli == povrati.size();
	}

	bool DodajTransakciju(Povrat povratZaDodat) {
		if (!DaLiSviProizvodiZaPovratPostoje(povratZaDodat)) {
			return false;
		}

		_transakcije.push_back(new Povrat(povratZaDodat));
		return true;
	}
};

int Kupac::_id = 1;

class WebShop {
	char* _naziv;
	vector<Kupac> _kupci;
public:
	WebShop(const char* naziv) { _naziv = AlocirajTekst(naziv); }
	~WebShop() { delete[] _naziv; }
	WebShop(const WebShop& obj) {
		_naziv =
			AlocirajTekst(obj._naziv); _kupci = obj._kupci;
	}
	const char* GetNaziv() const { return _naziv; }
	vector<Kupac>& GetKupci() { return _kupci; }

	// Methods I added below

	WebShop& operator=(const WebShop& webShop) {
		if (this == &webShop) {
			return *this;
		}

		delete[] _naziv;

		_naziv = AlocirajTekst(webShop._naziv);
		_kupci = webShop._kupci;

		return *this;
	}

	bool DaLiJeKupacDodan(Kupac kupacZaDodat) {
		for (auto& kupac : _kupci) {
			if (string(kupac.GetSifra()) == kupacZaDodat.GetSifra()) {
				return true;
			}
		}

		return false;
	}

	bool DaLiPostojiKupacZaDatiNaziv(std::string nazivKupca) {
		for (auto& kupac : _kupci) {
			if (kupac.GetImePrezime() == nazivKupca) {
				return true;
			}
		}

		return false;
	}

	void DodajKupca(Kupac kupac) {
		if (DaLiJeKupacDodan(kupac)) {
			throw std::exception("Kupac je vec dodan");
		}

		_kupci.push_back(kupac);
	}

	Kupac* GetKupacForSifra(string sifraKupca) {
		for (auto& kupac : _kupci) {
			if (kupac.GetSifra() == sifraKupca) {
				return &kupac;
			}
		}

		return nullptr;
	}

	bool RegistrujTransakcijuKupcu(string sifraKupca, Kupovina kupovina) {
		Kupac* kupac = GetKupacForSifra(sifraKupca);

		if (!kupac) {
			return false;
		}

		return kupac->DodajTransakciju(kupovina);
	}

	bool RegistrujTransakcijuKupcu(string sifraKupca, Povrat povrat) {
		Kupac* kupac = GetKupacForSifra(sifraKupca);

		if (!kupac) {
			return false;
		}

		return kupac->DodajTransakciju(povrat);
	}

	KolekcijaParova<Kupac, int, 50> PotrosnjaPoKategoriji(Kategorija kategorija) {
		KolekcijaParova<Kupac, int, 50> potrosnjaKupcaPoKategoriji;

		for (auto& kupac : _kupci) {
			int ukupnaPotrosnjaZaKupca = 0;

			for (auto& transakcija : kupac.GetTransakcije()) {
				Kupovina* kupovina = dynamic_cast<Kupovina*>(transakcija);
				Povrat* povrat = dynamic_cast<Povrat*>(transakcija);

				if (kupovina && kupovina->DaLiPostojiArtikalUKategoriji(kategorija)) {
					ukupnaPotrosnjaZaKupca += kupovina->GetIznos();
				}
				else if (povrat && povrat->DaLiPostojiArtikalUKategoriji(kategorija)) {
					ukupnaPotrosnjaZaKupca -= povrat->GetIznos();
				}
			}

			if (ukupnaPotrosnjaZaKupca != 0) {
				potrosnjaKupcaPoKategoriji.Dodaj(kupac, ukupnaPotrosnjaZaKupca);
			}
		}

		return potrosnjaKupcaPoKategoriji;
	}
};

WebShop* GetWebShopForNaziv(std::string nazivWebShopa, std::vector<WebShop>& webShopovi) {
	for (auto& webShop : webShopovi) {
		if (webShop.GetNaziv() == nazivWebShopa) {
			return &webShop;
		}
	}

	return nullptr;
}

bool UcitajPodatke(std::string filePath, std::vector<WebShop>& webShopovi) {
	std::ifstream file(filePath);

	if (!file.is_open()) {
		return false;
	}

	std::string nazivKupca;
	std::string nazivWebShopa;

	while (std::getline(file, nazivKupca, '|')
		&& std::getline(file, nazivWebShopa)) {

		WebShop* webShop = GetWebShopForNaziv(nazivWebShopa, webShopovi);

		if (!webShop) {
			webShopovi.push_back(WebShop(nazivWebShopa.c_str()));
			webShop = &webShopovi.back();
		}

		if (!webShop->DaLiPostojiKupacZaDatiNaziv(nazivKupca)) {
			webShop->DodajKupca(Kupac(nazivKupca.c_str()));
		}
	}

	return true;
}

int main() {
	//funkcija za generisanje sifre kupca na osnovu imena i prezimena i rednog broja.
	//sifra je u formatu INICIJALI:TRENUTNA_GODINA-ID_KUPCA, npr. AB:2025 - 003.
	//koristiti trenutnu godinu, dobijenu iz sistema na kome se program izvrsava
	//funkciju koristiti prilikom kreiranja objekta klase Kupac za inicijalizaciju atributa _sifra
	cout << GenerisiSifru("Amina Buric", 3) << endl; // AB:2025-003
	cout << GenerisiSifru("Amar Macic", 15) << endl; // AM:2025-015
	cout << GenerisiSifru("Maid Ramic", 156) << endl; // MR:2025-156

	//za validaciju sifre koristiti funkciju ValidirajSifru koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajSifru("AB:2025-003"))
		cout << "SIFRA VALIDNA\n";
	if (!ValidirajSifru("Ab:2025-003") && !ValidirajSifru("AB2025/003") && !ValidirajSifru("AB-003:2025"))
		cout << "SIFRA NIJE VALIDNA\n";
	KolekcijaParova<int, string, 20> listaProizvoda;
	for (int i = 0; i < 10; i++)
		listaProizvoda.Dodaj(i, "Proizvod_" + to_string(i));
	cout << listaProizvoda << crt;
	//DodajNaPoziciju - dodaje par (99, Proizdovi_99) na lokaciju 1 tj.lokaciju definisanu vrijednoscu prvog parametra,
	// a vraca novo stanje kolekcije tj. kolekciju zajedno sa novododatim elementom
	KolekcijaParova<int, string, 20> prosirenaLista =
		listaProizvoda.DodajNaPoziciju(1, 99, "Proizvod_99");
	cout << prosirenaLista << crt;
	// UkloniRaspon - od lokacije definisane prvim parametrom uklanja broj elemenata definisanih drugi parametrom
	// (pocevsi od lokacije 2 ukloni 3 elementa), a vraca pokazivac na kolekciju parova s uklonjenim elementima
	KolekcijaParova<int, string, 20>* uklonjeniProizvodi =
		prosirenaLista.UkloniRaspon(2, 3);
	cout << "Uklonjeni:\n" << *uklonjeniProizvodi << crt;
	/*
	Uklonjeni:
	1 Proizvod_1
	2 Proizvod_2
	3 Proizvod_3
	*/
	cout << "Preostali:\n" << prosirenaLista << crt;
	/*
	Preostali:
	0 Proizvod_0
	99 Proizvod_99
	4 Proizvod_4
	5 Proizvod_5
	6 Proizvod_6
	7 Proizvod_7
	8 Proizvod_8
	9 Proizvod_9
	*/
	*uklonjeniProizvodi = prosirenaLista;
	cout << "Proizvodi:\n" << *uklonjeniProizvodi << crt;
	try
	{
		//baciti izuzetak u slucaju nepostojeceg opsega
		listaProizvoda.UkloniRaspon(3, 10); // izuzetak - neispravan opseg
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	DatumVrijeme vrijeme1(5, 10, 2025, 9, 30, 0), vrijeme2(5, 10,
		2025, 10, 15, 0), vrijeme3(5, 10, 2025, 12, 36, 0), vrijeme4(55, 10, 2025, 12, 36, 0);
	Artikal telefon("Telefon FITPhone", ELEKTRONIKA, 1500),
		knjiga("Napredno C++ programiranje", KNJIGE, 55),
		slusalice("Slusalice FSX", ELEKTRONIKA, 129), laptop("Laptop FITLx", ELEKTRONIKA, 1499);
	Kupovina kupovina1(vrijeme1), kupovinaDuplikatVremena(vrijeme1),
		kupovina2(vrijeme2), kupovinaSlusalice(vrijeme2),
		kupovinaDuplikatProizvoda(vrijeme3);
	//dodaje artikal u listu kupljenih proizvoda i azurira iznos kupovine
	kupovina1.DodajArtikal(telefon);
	kupovina2.DodajArtikal(knjiga);
	//format povratne vrijednosti info metode
	cout << kupovina1.Info() << endl; //05.10.2025 09:30:00 KUPLJENO 1 PROIZVODA U UKUPNOM IZNOSU OD 1500KM
	Kupac amina("Amina Buric"), goran("Goran Skondric"), berun("Berun Agic");
	// DodajTransakciju - oneomguciti dupliranje transakcija sa istim vremenom, kod kupovine onemoguciti
	// dupliranje proizvoda, a povrat omoguciti samo ako je proizvod kupljen.U zavisnosti od rezultata izvrsenja
	// metoda vraca true ili false
	amina.DodajTransakciju(kupovina1);
	amina.DodajTransakciju(kupovina2);
	kupovinaDuplikatProizvoda.DodajArtikal(knjiga);
	//amina je u kupovina2 vec kupila knjigu, duplikat proizvoda, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatProizvoda))
		cout << "Duplikat proizvoda\n";
	kupovinaDuplikatVremena.DodajArtikal(laptop);
	//amina je u kupovina1 vec imala transakciju u vrijeme1, duplikat vremena, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatVremena))
		cout << "Duplikat vremena\n";
	Povrat povratKnjige(vrijeme2);
	povratKnjige.DodajArtikal(knjiga);
	//format povratne vrijednosti Info metode
	cout << povratKnjige.Info() << endl; // 05.10.2025 10:15:00 VRACENO 1 PROIZVODA U UKUPNOM IZNOSU OD 55KM
	//povrat dozvoljen samo ako je proizvod ranije kupljen
	if (amina.DodajTransakciju(povratKnjige))
		cout << "Povrat uspjesno izvrsen\n";
	WebShop tehnika("Tehnika"), knjizara("Knjizara");
	tehnika.DodajKupca(amina);
	tehnika.DodajKupca(goran);
	knjizara.DodajKupca(berun);
	try {
		tehnika.DodajKupca(amina); // amina je vec dodata kao kupac
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}
	kupovinaSlusalice.DodajArtikal(slusalice);
	//registraciju transakcije, pored direktnog nacina - preko kupca,
	//je moguce realizovati i u okviru odredjene prodavnice koja ce pronaci kupca
	//po sifri i dodati mu transakciju proslijedjenu kao parametar.u zavisnosti od rezultata
	//izvrsenja metoda vraca true ili false (i dalje vaze pravila vezana za dodavanje transakcije)
	if (!tehnika.RegistrujTransakcijuKupcu(amina.GetSifra(), kupovinaSlusalice))
		cout << "Transakcija registrovana\n";
	vector<WebShop> prodavnice;
	prodavnice.push_back(tehnika);
	prodavnice.push_back(knjizara);
	/*
	Funkcija UcitajPodatke ima zadatak ucitati podatke o prodavnicama
   i njihovim kupcima iz fajla cije ime se proslijedjuje kao parametar
	(fajl mozete pronaci zajedno sa ispitnim zadatkom). Svaka linija u
   fajlu treba biti u formatu "ime i prezime kupca|naziv prodavnice".
   Funkcija za
	svaki red u fajlu:
	- unutar vector-a, po nazivu, pronadje ranije dodatu ili
   kreira novu prodavnicu,
	- kreira novog kupca ukoliko vec nije registrovan u naznacenoj
   prodavnici,
	- dodaje kupca u naznacenu prodavnicu (onemoguciti
   dupliciranje kupaca u istoj prodavnici).
	Na kraju, sve prodavnice sa svojim kupcima se trebaju nalaziti u
   proslijedjenom vektoru prodavnice.
	Funkcija vraca true ako je ucitavanje podataka bilo uspjesno (u
   vector ucitan najmanje jedan podatak
	o prodavnici ili kupcu), a false ako se desilo nesto neocekivano
   ili niti jedan podatak nije ucitan.
	Primjer sadrzaja fajla:
	Emina Junuz|Tehnika";
	Jasmin Azemovic|Tehnika";
	Zanin Vejzovic|Knjizara";
	*/
	string nazivFajla = "podaci.txt";
	if (UcitajPodatke(nazivFajla, prodavnice)) cout << "Ucitavanje uspjesno" << crt;

	for (auto& prodavnica : prodavnice)
		cout << prodavnica.GetNaziv() << " sa " << prodavnica.GetKupci().size() << " kupaca" << crt;

	//vraca listu svih kupaca iz prodavnice koji su imali najmanje jednu transakciju u proslijedjenoj kategoriji,
	//te koliko su ukupno potrosili na proizvode iz te kategorije (ukupna potrosnja za kategoriju se
	// izracunava: kupovina - povrat)
	KolekcijaParova<Kupac, int, 50> potrosnja = tehnika.PotrosnjaPoKategoriji(ELEKTRONIKA);
	for (int i = 0; i < potrosnja.GetTrenutno(); i++)
		cout << potrosnja.GetPrvi(i).GetImePrezime() << " [" << potrosnja.GetPrvi(i).GetSifra() << "] " << " potrosio/la " << potrosnja.GetDrugi(i) << " KM na proizvode iz kategorije ELEKTRONIKA" << crt;

	return 0;
}