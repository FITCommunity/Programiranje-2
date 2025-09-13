#include <iostream> 
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include <regex>
#include <fstream>
using namespace std;
char* AlocirajTekst(const char* tekst) {
	if (!tekst) return nullptr;
	size_t vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}
string crt = "\n---------------------------------------------------------------------------------\n";
string PORUKA_TELEFON = crt + "TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN DOHVATA.\n"
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI ISKORISTENI ZA\n"
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI SANKCIONISANO." + crt;

string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN DESTRUKTOR\n"
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO KAO TM\n"
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ MAIN FUNKCIJI, "
"   OSIM AKO POSTOJI JASAN RAZLOG ZA MODIFIKACIJU\n"
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n"
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n"
"   AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILIVRATITE NEKU DEFAULT VRIJEDNOST\n"
"6. RJESENJE KOPIRAJTE U .DOCX DOKUMENT (NAZIV DOKUMENTA = BROJ INDEKSA, npr.IB150051.docx)\n"
"7. NA FTP SERVER POSTAVITE SAMO .DOCX DOKUMENT, A NE CIJELI PROJEKAT\n"
"8. SVE NEDOZVOLJENE RADNJE TOKOM ISPITA BIT CE SANKCIONISANE\n"
"9. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO VLASTITOM IZBORU\n"
"10. KORISTITE VISUAL STUDIO 2022 (C++17) I TESTIRAJTE PROGRAM U OBA MODA(F5 i Ctrl + F5)\n"
"11. NA KRAJU PROVJERITE DA LI STE RJESENJE ISPITA POSTAVILI U ODGOVARAJUCI FOLDER NA FTP SERVERU" + crt;

enum Kategorija { ELEKTRONIKA, KNJIGE, MODA, PREHRANA };
const char* KategorijaNazivi[] = { "ELEKTRONIKA", "KNJIGE", "MODA", "PREHRANA" };
ostream& operator<<(ostream& COUT, const Kategorija indeks) {
	COUT << KategorijaNazivi[indeks];
	return COUT;
}

char* GenerisiSifru(string imePrezime, int id) {
	time_t trenutnoVrijeme = time(0);
	tm lokalnoVrijeme{};
	localtime_s(&lokalnoVrijeme, &trenutnoVrijeme);
	int godina = lokalnoVrijeme.tm_year + 1900; //godina od 1900, moramo dodati 1900

	string sifra;

	sifra += toupper(imePrezime[0]);
	int lokacijaPrezime = imePrezime.find(' ') + 1;
	sifra += toupper(imePrezime[lokacijaPrezime]);
	sifra += ':';
	sifra += to_string(godina);
	sifra += "-";

	if (id < 10)
		sifra += "00";
	else if (id < 100)
		sifra += "0";
	sifra += to_string(id);

	return AlocirajTekst(sifra.c_str());
}

bool ValidirajSifru(string sifra) {
	regex jednaCifra{ "[A-Z]{2}:2025-00[1-9]" };
	regex dvijeCifre{ "[A-Z]{2}:2025-0[1-9]\\d" };
	regex triCifre{ "[A-Z]{2}:2025-[1-9]\\d{2}" };

	return regex_match(sifra, jednaCifra) || regex_match(sifra, dvijeCifre) || regex_match(sifra, triCifre);
}

template<class T1, class T2, int max>
class KolekcijaParova {
	T1* _prvi[max] = { nullptr };
	T2* _drugi[max] = { nullptr };
	int _trenutno = 0;
public:
	KolekcijaParova() = default;
	KolekcijaParova(const KolekcijaParova& obj) {
		_trenutno = obj._trenutno;
		for (size_t i = 0; i < GetTrenutno(); i++)
		{
			_prvi[i] = new T1(obj.GetPrvi(i));
			_drugi[i] = new T2(obj.GetDrugi(i));
		}
	}
	KolekcijaParova& operator=(const KolekcijaParova& obj) {
		if (this != &obj) {
			for (int i = 0; i < _trenutno; i++) {
				delete _prvi[i]; _prvi[i] = nullptr;
				delete _drugi[i]; _drugi[i] = nullptr;
			}
			_trenutno = obj._trenutno;
			for (size_t i = 0; i < GetTrenutno(); i++)
			{
				_prvi[i] = new T1(obj.GetPrvi(i));
				_drugi[i] = new T2(obj.GetDrugi(i));
			}
		}
		return *this;
	}
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

	void Dodaj(T1 el1, T2 el2) {
		if (_trenutno == max)
			return;
		_prvi[GetTrenutno()] = new T1(el1);
		_drugi[GetTrenutno()] = new T2(el2);
		_trenutno++;
	}

	KolekcijaParova DodajNaPoziciju(int lokacija, T1 el1, T2 el2) {
		if (_trenutno == max)
			return *this;
		for (size_t i = _trenutno; i > lokacija; i--)
		{
			_prvi[i] = new T1(GetPrvi(i - 1));
			_drugi[i] = new T2(GetDrugi(i - 1));
		}
		_prvi[lokacija] = new T1(el1);
		_drugi[lokacija] = new T2(el2);
		_trenutno++;
		return *this;
	}

	KolekcijaParova* UkloniRaspon(int pocetak, int brojElemenata) {
		KolekcijaParova* uklonjeniElementi = new KolekcijaParova();
		KolekcijaParova preostaliElementi;
		if (pocetak + brojElemenata - 1 >= GetTrenutno())
			throw exception("Nije validan range!\n");
		for (size_t i = 0; i < GetTrenutno(); i++)
		{
			if (i >= pocetak && i <= pocetak + brojElemenata - 1)
				uklonjeniElementi->Dodaj(GetPrvi(i), GetDrugi(i));
			else
				preostaliElementi.Dodaj(GetPrvi(i), GetDrugi(i));
		}
		*this = preostaliElementi;
		return uklonjeniElementi;
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
	DatumVrijeme(const DatumVrijeme& obj) {
		_godina = new int(*obj._godina);
		_mjesec = new int(*obj._mjesec);
		_dan = new int(*obj._dan);
		_sati = new int(*obj._sati);
		_minute = new int(*obj._minute);
		_sekunde = new int(*obj._sekunde);
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this != &obj) {
			delete _godina; delete _mjesec; delete _dan;
			delete _sati; delete _minute; delete _sekunde;
			_godina = new int(*obj._godina);
			_mjesec = new int(*obj._mjesec);
			_dan = new int(*obj._dan);
			_sati = new int(*obj._sati);
			_minute = new int(*obj._minute);
			_sekunde = new int(*obj._sekunde);
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _godina; delete _mjesec; delete _dan;
		delete _sati; delete _minute; delete _sekunde;
	}
	int getGodina() const { return *_godina; }
	int getMjesec() const { return *_mjesec; }
	int getDan() const { return *_dan; }
	int getSati() const { return *_sati; }
	int getMinute() const { return *_minute; }
	int getSekunde() const { return *_sekunde; }

	bool operator==(const DatumVrijeme& obj) const {
		if (getGodina() != obj.getGodina())
			return false;
		if (getMjesec() != obj.getMjesec())
			return false;
		if (getDan() != obj.getDan())
			return false;
		if (getSati() != obj.getSati())
			return false;
		if (getMinute() != obj.getMinute())
			return false;
		if (getSekunde() != obj.getSekunde())
			return false;
		return true;
	}
};

class Proizvod {
	char* _naziv;
	Kategorija _kategorija;
	int _cijena;
public:
	Proizvod(const char* naziv = "", Kategorija kategorija = ELEKTRONIKA, int cijena = 0)
		: _kategorija(kategorija), _cijena(cijena) {
		_naziv = AlocirajTekst(naziv);
	}
	Proizvod(const Proizvod& obj) {
		_naziv = AlocirajTekst(obj.GetNaziv());
		_kategorija = obj._kategorija;
		_cijena = obj._cijena;
	}
	Proizvod& operator=(const Proizvod& obj) {
		if (this != &obj) {
			delete[] _naziv;
			_naziv = AlocirajTekst(obj.GetNaziv());
			_kategorija = obj._kategorija;
			_cijena = obj._cijena;
		}
		return *this;
	}
	~Proizvod() {
		delete[] _naziv;
	}

	const char* GetNaziv() const { return _naziv; }
	Kategorija GetKategorija() const { return _kategorija; }
	int GetCijena() const { return _cijena; }

	friend ostream& operator<<(ostream& COUT, const Proizvod& p) {
		COUT << p._naziv << " " << p._kategorija << " " << p._cijena;
		return COUT;
	}
	bool operator==(const Proizvod& obj) const {
		if (strcmp(_naziv, obj.GetNaziv()) != 0)
			return false;
		if (_cijena != obj._cijena)
			return false;
		if (_kategorija != obj._kategorija)
			return false;
		return true;
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
	Transakcija(const Transakcija& obj) {
		_vrijemeRealizacije = obj._vrijemeRealizacije;
		_iznos = obj._iznos;
	}
	Transakcija& operator=(const Transakcija& obj) {
		if (this != &obj) {
			_vrijemeRealizacije = obj._vrijemeRealizacije;
			_iznos = obj._iznos;
		}
		return *this;
	}
	virtual ~Transakcija() {

	}
	virtual string Info() const = 0;

	const DatumVrijeme& GetVrijemeRealizacije() const { return _vrijemeRealizacije; }
	int GetIznos() const { return _iznos; }
};

class Kupovina : public Transakcija {
	vector<Proizvod> _kupljeniProizvodi;
public:
	Kupovina() : Transakcija(*this) {}
	Kupovina(DatumVrijeme vrijemeRealizacije) : Transakcija(vrijemeRealizacije, 0) {

	}
	Kupovina(const Kupovina& obj) : Transakcija(obj) {
		_kupljeniProizvodi = obj._kupljeniProizvodi;
	}
	Kupovina& operator=(const Kupovina& obj) {
		if (this != &obj) {
			Transakcija::operator=(obj);
			_kupljeniProizvodi = obj._kupljeniProizvodi;
		}
		return *this;
	}
	~Kupovina() {

	}

	//05.10.2025 09:30:00 KUPLJENO 1 PROIZVODA U UKUPNOM IZNOSU OD 1500KM
	string Info() const {
		ostringstream info;
		info << _vrijemeRealizacije.getDan() << "." << _vrijemeRealizacije.getMjesec() << "." << _vrijemeRealizacije.getGodina();
		info << " " << _vrijemeRealizacije.getSati() << ":" << _vrijemeRealizacije.getMinute() << ":" << _vrijemeRealizacije.getSekunde();
		info << " KUPLJENO " << _kupljeniProizvodi.size() << " PROIZVODA U UKUPNOM IZNOSU OD " << _iznos << "KM\n";
		return info.str();
	}
	const vector<Proizvod>& GetProizvodi() const { return _kupljeniProizvodi; }

	void DodajProizvod(const Proizvod& proizvod) {
		_kupljeniProizvodi.push_back(proizvod);
		_iznos += proizvod.GetCijena();
	}
};

class Povrat : public Transakcija {
	vector<Proizvod> _vraceniProizvodi;
public:
	Povrat() : Transakcija(*this) {

	}
	Povrat(DatumVrijeme vrijemeRealizacije) : Transakcija(vrijemeRealizacije, 0) {

	}
	Povrat(const Povrat& obj) : Transakcija(obj) {
		_vraceniProizvodi = obj._vraceniProizvodi;
	}
	Povrat& operator=(const Povrat& obj) {
		if (this != &obj) {
			Transakcija::operator=(obj);
			_vraceniProizvodi = obj._vraceniProizvodi;
		}
		return *this;
	}
	~Povrat() {

	}

	//05.10.2025 10:15 : 00 VRACENO 1 PROIZVODA U UKUPNOM IZNOSU OD 55KM
	string Info() const {
		ostringstream info;
		info << _vrijemeRealizacije.getDan() << "." << _vrijemeRealizacije.getMjesec() << "." << _vrijemeRealizacije.getGodina();
		info << " " << _vrijemeRealizacije.getSati() << ":" << _vrijemeRealizacije.getMinute() << ":" << _vrijemeRealizacije.getSekunde();
		info << " VRACENO " << _vraceniProizvodi.size() << " PROIZVODA U UKUPNOM IZNOSU OD " << _iznos << "KM\n";
		return info.str();
	}
	void DodajProizvod(const Proizvod& proizvod) {
		_vraceniProizvodi.push_back(proizvod);
		_iznos += proizvod.GetCijena();
	}
	const vector<Proizvod>& GetProizvodi() const { return _vraceniProizvodi; }
};

class Kupac {
	static int _id;
	char* _sifra;
	char* _imePrezime;
	vector<Transakcija*> _transakcije;
public:
	Kupac(const char* imePrezime) {
		_imePrezime = AlocirajTekst(imePrezime);
		_sifra = AlocirajTekst(GenerisiSifru(imePrezime, _id++));
	}
	Kupac(const Kupac& obj) {
		_imePrezime = AlocirajTekst(obj._imePrezime);
		_sifra = AlocirajTekst(obj._sifra);
		for (size_t i = 0; i < obj._transakcije.size(); i++)
		{
			Kupovina* kupovina = dynamic_cast<Kupovina*>(obj._transakcije[i]);
			if (kupovina != nullptr)
				_transakcije.push_back(new Kupovina(*kupovina));
			Povrat* povrat = dynamic_cast<Povrat*>(obj._transakcije[i]);
			if (povrat != nullptr)
				_transakcije.push_back(new Povrat(*povrat));
		}
	}
	Kupac& operator=(const Kupac& obj) {
		if (this != &obj) {
			delete[] _sifra;
			delete[] _imePrezime;
			for (auto* transakcija : _transakcije) delete transakcija;
			_transakcije.clear();
			_imePrezime = AlocirajTekst(obj._imePrezime);
			_sifra = AlocirajTekst(obj._sifra);
			for (size_t i = 0; i < obj._transakcije.size(); i++)
			{
				Kupovina* kupovina = dynamic_cast<Kupovina*>(obj._transakcije[i]);
				if (kupovina != nullptr)
					_transakcije.push_back(new Kupovina(*kupovina));
				Povrat* povrat = dynamic_cast<Povrat*>(obj._transakcije[i]);
				if (povrat != nullptr)
					_transakcije.push_back(new Povrat(*povrat));
			}
		}
		return *this;
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
		COUT << crt << kupac._imePrezime << " [" << kupac._sifra << "]\n";
		for (int i = 0; i < kupac._transakcije.size(); i++)
			COUT << " - " << kupac._transakcije[i]->Info() << "\n";
		COUT << crt;
		return COUT;
	}

	// DodajTransakciju - oneomguciti dupliranje transakcija sa istim vremenom, kod kupovine onemoguciti
	// dupliranje proizvoda, a povrat omoguciti samo ako je proizvod kupljen.
	// U zavisnosti od rezultata izvrsenja metoda vraca true ili false 
	bool DodajTransakciju(Transakcija& transakcija) {
		Kupovina* kupovina = dynamic_cast<Kupovina*>(&transakcija);
		Povrat* povrat = dynamic_cast<Povrat*>(&transakcija);
		bool zastavicaPovrat = false;
		for (size_t i = 0; i < _transakcije.size(); i++)
		{
			//1. Provjera istog vremena za transakcije
			if (transakcija.GetVrijemeRealizacije() == _transakcije[i]->GetVrijemeRealizacije())
				return false;
		}
		for (size_t j = 0; j < _transakcije.size(); j++)
		{
			Kupovina* kupovinaVectora = dynamic_cast<Kupovina*>(_transakcije[j]);

			if (kupovinaVectora != nullptr && kupovina != nullptr) {
				//2. Provjera dupliranja proizvoda za kupovine
				if (kupovina->GetProizvodi() == kupovinaVectora->GetProizvodi())
					return false;
			}

			//3. Provjera ima li proizvoda za povrat
			if (kupovinaVectora != nullptr && povrat != nullptr) {
				for (size_t k = 0; k < kupovinaVectora->GetProizvodi().size(); k++)
				{
					//.back() je koristeno sa pretpostavkom da za jednu transakciju tipa povrat ima samo jedan proizvod (kako je u mainu),
					//u suprotnom, potrebna je druga implementacija
					if (povrat->GetProizvodi().back() == kupovinaVectora->GetProizvodi()[k]) {
						_transakcije.push_back(new Povrat(*povrat));
						return true;
					}
				}
			}
		}
		if (kupovina != nullptr) {
			_transakcije.push_back(new Kupovina(*kupovina));
			return true;
		}
		return false;
	}

	bool operator==(const Kupac& obj) {
		if (strcmp(_sifra, obj._sifra) != 0)
			return false;
		return true;
	}
};
int Kupac::_id = 1;

class Prodavnica {
	char* _naziv;
	vector<Kupac> _kupci;
public:
	Prodavnica(const char* naziv) {
		_naziv = AlocirajTekst(naziv);
	}
	Prodavnica(const Prodavnica& obj) {
		_naziv = AlocirajTekst(obj._naziv);
		_kupci = obj._kupci;
	}
	Prodavnica& operator=(const Prodavnica& obj) {
		if (this != &obj) {
			delete[] _naziv;
			_naziv = AlocirajTekst(obj._naziv);
			_kupci = obj._kupci;
		}
		return *this;
	}
	~Prodavnica() {
		delete[] _naziv;
	}

	const char* GetNaziv() const { return _naziv; }
	vector<Kupac>& GetKupci() { return _kupci; }

	void DodajKupca(Kupac k) {
	for (int i = 0; i < _kupci.size(); i++)
	{
		if (strcmp(_kupci.at(i).GetImePrezime(), k.GetImePrezime() )==0)
		{
			throw exception("Kupac je vec dodan");
		}
	}
	_kupci.push_back(k);
}

	bool RegistrujTransakcijuKupcu(const char* sifra, Transakcija& transakcija) {
		for (size_t i = 0; i < _kupci.size(); i++)
		{
			if (strcmp(_kupci[i].GetSifra(), sifra) == 0) {
				_kupci[i].DodajTransakciju(transakcija);
				return true;
			}
		}
		return false;
	}

	KolekcijaParova<Kupac, int, 50> PotrosnjaPoKategoriji(Kategorija kategorija) {
		KolekcijaParova<Kupac, int, 50> rezultat;

		for (size_t i = 0; i < _kupci.size(); i++) {
			int suma = 0;
			// prolazimo kroz sve transakcije datog kupca
			vector<Transakcija*>& transakcije = _kupci[i].GetTransakcije();

			for (size_t j = 0; j < transakcije.size(); j++) {
				Kupovina* kupovina = dynamic_cast<Kupovina*>(transakcije[j]);
				Povrat* povrat = dynamic_cast<Povrat*>(transakcije[j]);

				if (kupovina != nullptr) {
					const vector<Proizvod>& proizvodi = kupovina->GetProizvodi();
					for (size_t k = 0; k < proizvodi.size(); k++) {
						if (proizvodi[k].GetKategorija() == kategorija)
							suma += proizvodi[k].GetCijena();
					}
				}
				else if (povrat != nullptr) {
					const vector<Proizvod>& proizvodi = povrat->GetProizvodi();
					for (size_t k = 0; k < proizvodi.size(); k++) {
						if (proizvodi[k].GetKategorija() == kategorija)
							suma -= proizvodi[k].GetCijena();
					}
				}
			}

			// dodaj u rezultat ako je kupac potrosio ista u toj kategoriji
			if (suma > 0)
				rezultat.Dodaj(_kupci[i], suma);
		}

		return rezultat;
	}
};

bool UcitajPodatke(const string& putanja, vector<Prodavnica>& prodavnice) {
	ifstream fajl{ putanja };

	if (!fajl.is_open()) {
		return false;
	}

	string nazivKupca;
	string nazivProdavnice;

	while (getline(fajl, nazivKupca, '|') 
		&& getline(fajl, nazivProdavnice)) {
		
		Prodavnica* trenutnaProdavnica = nullptr;

		for (Prodavnica& prodavnica : prodavnice) {
			if (prodavnica.GetNaziv() == nazivProdavnice) {
				trenutnaProdavnica = &prodavnica;
				break;
			}
		}

		if (trenutnaProdavnica == nullptr) {
			prodavnice.push_back(Prodavnica(nazivProdavnice.c_str()));
			trenutnaProdavnica = &prodavnice.back();
		}

		bool daLiKupacPostoji = false;
		
		for (Kupac kupac : trenutnaProdavnica->GetKupci()) {
			if (kupac.GetImePrezime() == nazivKupca) {
				daLiKupacPostoji = true;
				break;
			}
		}

		if (!daLiKupacPostoji) {
			trenutnaProdavnica->DodajKupca(Kupac(nazivKupca.c_str()));
		}
	}

	return true;
}

// Teorija ponovljena sa roka 10.07.2025.

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite razliku između virtualnih i cistih virtualnih metoda, te korelaciju virtualnih metoda sa polimorfizmom (navesti kratki primjer) ? \n";
	return "Odgovor -> Razlike su u tome sto virtualne metode sadrze implementaciju,\ndok ciste virtualne metode ne sadrze, zbog cega cine klasu apstraktnom, \ntj. onemoguci instanciranje date klase,\ntakve klase se koriste u hijerarhiji nasljedivanja sa drugim klasama.\nSintaksicke razlike:\n"
		"\tvirtual NekaMetoda() {} // virtualna metoda\n"
		"\tvirtual NekaMetoda() = 0; // cista virtualna metoda\n"
		"Korelacija izmedu polimorfizma i virtualnih metoda je ta da nam one dozvoljavaju\nda dadnemo drugacije implementacije metodi u klasama koje nasljede tu metodu.\n"
		"Primjer:\n"
		"class Base { \npublic: \n\tvirtual void PrintClassName() { \n\t\tstd::cout << \"Base\"; \n\t} \n};\n"
		"class Derived : public Base { \npublic: \n\tvoid PrintClassName() override { \n\t\tstd::cout << \"Derived\"; \n\t} \n};\n"
		"Kao sto se vidi u primjer metoda PrintClassName ima drugaciju implementaciju\nu klasi sto je nasljedi.\n";
}

const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasniti razliku izmedju konstruktora kopije i move konstruktora, razlike u implementaciji, te navesti primjere implicitnog i eksplicitnog poziva ? \n";
	return "Odgovor -> Kontruktor kopije se koristi da napravi kopiju objekta,\ndok move konstruktor se koristi da resurse iz jednog objekta prebaci u drugi,\nostavljajuci prvi objekat u validnom stanju,\ntj. objekat se moze nastaviti koristiti bez izazivanja nedefinisanog ponasanja.\nPrimjer prototipa:\n"
		"Foo(const Foo& foo) { /* logika kopiranja */ }\n"
		"Foo(Foo&& foo) { /* logika micanja (move) */ }\n"
		"Primjer implicitnog poziva:\n"
		"Foo foo;\n"
		"Foo foo2 = foo; // Konstruktor kopije  \n"
		"Foo foo3 = std::move(foo); // Move konstruktor  \n"
		"Primjer eksplicitnog poziva:\n"
		"Foo foo;\n"
		"Foo foo2(foo); // Konstruktor kopije  \n"
		"Foo foo3(std::move(foo)); // Move konstruktor  \n";
}

int main() {
	cout << PORUKA_TELEFON; cin.get(); system("cls");
	cout << PORUKA_ISPIT; cin.get(); system("cls");
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	//funkcija za generisanje sifre kupca na osnovu imena i prezimena i rednog broja.
	//sifra je u formatu INICIJALI:TRENUTNA_GODINA-ID_KUPCA, npr.AB:2025 - 003.
	//koristiti trenutnu godinu, dobijenu iz sistema na kome se program izvrsava
	//funkciju koristiti prilikom kreiranja objekta klase Kupac za inicijalizaciju atributa _sifra
	cout << GenerisiSifru("Amina Buric", 3) << endl; // AB:2025-003 
	cout << GenerisiSifru("Amar Macic", 15) << endl; // AM:2025-015
	cout << GenerisiSifru("Maid Ramic", 156) << endl; // MR:2025-156

	//za validaciju sifre koristiti funkciju ValidirajSifru koja treba, koristeci regex, 
	//osigurati postivanje osnovnih pravila vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajSifru("AB:2025-003"))
		cout << "SIFRA VALIDNA\n";
	if (!ValidirajSifru("Ab:2025-003") && !ValidirajSifru("AB- 2025/003") && !ValidirajSifru("AB-003:2025"))
		cout << "SIFRA NIJE VALIDNA\n";

	KolekcijaParova<int, string, 20> listaProizvoda;
	for (int i = 0; i < 10; i++)
		listaProizvoda.Dodaj(i, "Proizvod_" + to_string(i));
	cout << listaProizvoda << crt;

	//DodajNaPoziciju - dodaje par (99, Proizdovi_99) na lokaciju 1 tj.
	// lokaciju definisanu vrijednoscu prvog parametra a vraca novo stanje kolekcije
	// tj. kolekciju zajedno sa novododatim elementom
	KolekcijaParova<int, string, 20> prosirenaLista = listaProizvoda.DodajNaPoziciju(1, 99, "Proizvod_99");
	cout << prosirenaLista << crt;

	// UkloniRaspon - od lokacije definisane prvim parametrom uklanja broj elemenata definisanih drugi parametrom
	// (pocevsi od lokacije 2 ukloni 3 elementa), a vraca pokazivac na kolekciju parova s uklonjenim elementima
	KolekcijaParova<int, string, 20>* uklonjeniProizvodi = prosirenaLista.UkloniRaspon(2, 3);
	cout << "Uklonjeni:\n" << *uklonjeniProizvodi << crt;
	/* Uklonjeni:
	1	Proizvod_1
	2	Proizvod_2
	3	Proizvod_3
	*/
	cout << "Preostali:\n" << prosirenaLista << crt;
	/* Preostali:
	0 Proizvod_0
	99 Proizvod_99
	4	Proizvod_4
	5	Proizvod_5
	6	Proizvod_6
	7	Proizvod_7
	8	Proizvod_8
	9	Proizvod_9
	*/
	*uklonjeniProizvodi = prosirenaLista;
	cout << "Proizvodi:\n" << *uklonjeniProizvodi << crt;
	try
	{
		//baciti izuzetak u slucaju nepostojeceg opsega 
		listaProizvoda.UkloniRaspon(3, 10); //izuzetak - neispravan opseg
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}

	DatumVrijeme
		vrijeme1(5, 10, 2025, 9, 30, 0),
		vrijeme2(5, 10, 2025, 10, 15, 0),
		vrijeme3(5, 10, 2025, 12, 36, 0);

	Proizvod telefon("Telefon FITPhone", ELEKTRONIKA, 1500),
		knjiga("Napredno C++ programiranje", KNJIGE, 55),
		slusalice("Slusalice FSX", ELEKTRONIKA, 129),
		laptop("Laptop FITLx", ELEKTRONIKA, 1499);

	Kupovina kupovina1(vrijeme1),
		kupovinaDuplikatVremena(vrijeme1),
		kupovina2(vrijeme2),
		kupovinaSlusalice(vrijeme2),
		kupovinaDuplikatProizvoda(vrijeme3);

	//dodaje proizvod u listu kupljenih proizvoda i azurira iznos kupovine
	kupovina1.DodajProizvod(telefon);
	kupovina2.DodajProizvod(knjiga);

	////format povratne vrijednosti info metode
	cout << kupovina1.Info() << endl; //05.10.2025 09:30:00 KUPLJENO 1 PROIZVODA U UKUPNOM IZNOSU OD 1500KM

	Kupac amina("Amina Buric"), goran("Goran Skondric"), berun("Berun Agic");

	// DodajTransakciju - oneomguciti dupliranje transakcija sa istim vremenom, kod kupovine onemoguciti
	// dupliranje proizvoda, a povrat omoguciti samo ako je proizvod kupljen.
	// U zavisnosti od rezultata izvrsenja metoda vraca true ili false 
	amina.DodajTransakciju(kupovina1);
	amina.DodajTransakciju(kupovina2);

	kupovinaDuplikatProizvoda.DodajProizvod(knjiga);
	//amina je u kupovina2 vec kupila knjigu, duplikat proizvoda, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatProizvoda)) cout << "Duplikat proizvoda\n";

	kupovinaDuplikatVremena.DodajProizvod(laptop);
	//amina je u kupovina1 vec imala transakciju u vrijeme1, duplikat vremena, onemoguciti dodavanje
	if (!amina.DodajTransakciju(kupovinaDuplikatVremena)) cout << "Duplikat vremena\n";

	Povrat povratKnjige(vrijeme2);
	povratKnjige.DodajProizvod(knjiga);
	//format povratne vrijednosti Info metode
	cout << povratKnjige.Info() << endl; // 05.10.2025 10:15:00 VRACENO 1 PROIZVODA U UKUPNOM IZNOSU OD 55KM
	//povrat dozvoljen samo ako je proizvod ranije kupljen
	if (amina.DodajTransakciju(povratKnjige))
		cout << "Povrat uspjesno izvrsen\n";

	Prodavnica tehnika("Tehnika"), knjizara("Knjizara");
	tehnika.DodajKupca(amina);
	tehnika.DodajKupca(goran);
	knjizara.DodajKupca(berun);
	try {
		tehnika.DodajKupca(amina); // amina je vec dodata kao kupac
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << crt;
	}

	kupovinaSlusalice.DodajProizvod(slusalice);

	/*registraciju transakcije, pored direktnog nacina - preko kupca,
	je moguce realizovati i u okviru odredjene prodavnice koja ce pronaci kupca
	po sifri i dodati mu transakciju proslijedjenu kao parametar.u zavisnosti od rezultata
	izvrsenja metoda vraca true ili false (i dalje vaze pravila vezana za dodavanje transakcije)*/
	if (!tehnika.RegistrujTransakcijuKupcu(amina.GetSifra(), kupovinaSlusalice))
		cout << "Transakcija registrovana\n";

	vector<Prodavnica> prodavnice;
	prodavnice.push_back(tehnika);
	prodavnice.push_back(knjizara);

	/*
	Funkcija UcitajPodatke ima zadatak ucitati podatke o prodavnicama i njihovim kupcima
	iz fajla cije ime se proslijedjuje kao parametar (fajl mozete pronaci zajedno sa ispitnim zadatkom).
	Svaka linija u fajlu treba biti u formatu "ime i prezime kupca|naziv prodavnice". Funkcija za svaki red u fajlu:
	- unutar vector-a, po nazivu, pronadje ranije dodatu ili kreira novu prodavnicu,
	- kreira novog kupca ukoliko vec nije registrovan u naznacenoj prodavnici,
	-dodaje kupca u naznacenu prodavnicu (onemoguciti dupliciranje kupaca u istoj prodavnici).

	Na kraju, sve prodavnice sa svojim kupcima se trebaju nalaziti u proslijedjenom vektoru prodavnice.
	Funkcija vraca true ako je ucitavanje podataka bilo uspjesno (u vector ucitan najmanje jedan podatak
	o prodavnici ili kupcu), a false ako se desilo nesto neocekivano ili niti jedan podatak nije ucitan.
		Primjer sadrzaja fajla:
		Emina Junuz|Tehnika";
		Jasmin Azemovic|Tehnika";
		Zanin Vejzovic|Knjizara";
	*/
	string nazivFajla = "podaci.txt";
	if (UcitajPodatke(nazivFajla, prodavnice)) cout << "Ucitavanje uspjesno" << crt;

	for (auto& prodavnica : prodavnice)
		cout<< prodavnica.GetNaziv()<<" sa " << prodavnica.GetKupci().size() << " kupaca" << crt;

	//vraca listu svih kupaca iz prodavnice koji su imali najmanje jednu transakciju u proslijedjenoj kategoriji,
	//te koliko su ukupno potrosili na proizvode iz te kategorije 
	//(ukupna potrosnja za kategoriju se izracunava: kupovina - povrat) 

	KolekcijaParova <Kupac, int, 50> potrosnja = tehnika.PotrosnjaPoKategoriji(ELEKTRONIKA);

	for (int i = 0; i < potrosnja.GetTrenutno(); i++)
		cout << potrosnja.GetPrvi(i).GetImePrezime() << " [" << potrosnja.GetPrvi(i).GetSifra() << "] " << " potrosio/la " << potrosnja.GetDrugi(i) << " KM na proizvode iz kategorije ELEKTRONIKA" << crt;

	cin.get();
	return 0;

}
