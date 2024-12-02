#include <iostream>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
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
"-------------------------------------------------------------------------------\n";

// Headers I added below
#include<string>
#include<thread>
#include<numeric>
#include<vector>
// Headers I added above

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

// Functions I added below
std::ostream& operator<<(std::ostream& os, Karakteristike karakteristika) {
	switch (karakteristika) {
	case Karakteristike::NARUDZBA:
		os << "NARUDZBA";
		break;
	case Karakteristike::KVALITET:
		os << "KVALITET";
		break;
	case Karakteristike::PAKOVANJE:
		os << "PAKOVANJE";
		break;
	case Karakteristike::ISPORUKA:
		os << "ISPORUKA";
		break;
	default:
		os << "Karakteristika ne postoji";
	}

	return os;
}
// Functions I added above

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}
template<class T1, class T2>
class Parovi {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
	bool _omoguciDupliranje;
public:
	Parovi(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = new int{ 0 };
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}
	~Parovi() {
		clearArrays();
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	bool getOmoguciDupliranje() const { return _omoguciDupliranje; }
	friend ostream& operator<< (ostream& COUT, const Parovi& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Parovi(const Parovi& parovi)
		: _omoguciDupliranje{ parovi.getOmoguciDupliranje() }
		, _trenutno{ new int { parovi.getTrenutno() } }
		, _elementi1{ new T1[parovi.getTrenutno()] {} }
		, _elementi2{ new T2[parovi.getTrenutno()] {} }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = parovi.getElement1(i);
			_elementi2[i] = parovi.getElement2(i);
		}
	}

	Parovi& operator=(const Parovi& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearArrays();
		*_trenutno = rhs.getTrenutno();
		_omoguciDupliranje = rhs.getOmoguciDupliranje();

		_elementi1 = new T1[getTrenutno()]{};
		_elementi2 = new T2[getTrenutno()]{};

		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rhs.getElement1(i);
			_elementi2[i] = rhs.getElement2(i);
		}

		return *this;
	}

	bool daLiElementPostoji(const T1& element1, const T2& element2) const {
		for (int i = 0; i < getTrenutno(); ++i) {
			if (element1 == getElement1(i) || element2 == getElement2(i)) {
				return true;
			}
		}

		return false;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (!getOmoguciDupliranje() && daLiElementPostoji(element1, element2)) {
			throw std::exception("Dupliranje nije omoguceno");
		}

		T1* const temp1{ new T1[getTrenutno() + 1] {} };
		T2* const temp2{ new T2[getTrenutno() + 1] {} };

		for (int i = 0; i < getTrenutno(); ++i) {
			temp1[i] = getElement1(i);
			temp2[i] = getElement2(i);
		}

		temp1[getTrenutno()] = element1;
		temp2[getTrenutno()] = element2;

		clearArrays();

		_elementi1 = temp1;
		_elementi2 = temp2;

		++(*_trenutno);
	}

	Parovi operator()(int start, int end, const bool reverse = false) const {
		Parovi temp{};

		if (start < 0 || end >= getTrenutno()) {
			return temp;
		}

		int increment{ 1 };

		if (reverse) {
			std::swap(start, end);
			increment = -1;
		}

		end += increment;

		for (int i = start; i != end; i += increment) {
			temp.AddElement(getElement1(i), getElement2(i));
		}

		return temp;
	}

private:
	void clearArrays() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
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
	Datum(const Datum& datum)
		: _dan{ new int{ datum.getDan() } }
		, _mjesec{ new int{ datum.getMjesec() } }
		, _godina{ new int{ datum.getGodina() } }
	{}

	Datum& operator=(const Datum& rhs) {
		*_dan = rhs.getDan();
		*_mjesec = rhs.getMjesec();
		*_godina = rhs.getGodina();

		return *this;
	}

	int getDan() const {
		return *_dan;
	}

	int getMjesec() const {
		return *_mjesec;
	}

	int getGodina() const {
		return *_godina;
	}
};

class ZadovoljstvoKupca {
	int _ocjena; //za svaku kupovinu kupac moze ostaviti jednu ocjenu
	//uz ocjenu, kupci mogu komentarisati svaku od karakteristika proizvoda.
	//onemoguciti dupliranje karakteristika tj. svaka karakteristika se moze komentarisati samo jednom...u suprotnom baciti objekat tipa exception
	Parovi<Karakteristike*, const char*>* _komentariKarakteristika;
public:
	ZadovoljstvoKupca(int ocjena = 0) {
		_ocjena = ocjena;
		_komentariKarakteristika = new Parovi<Karakteristike*, const char*>{};
	}
	int GetOcjena() { return _ocjena; }
	Parovi<Karakteristike*, const char*>* GetKomentareKarakteristika() { return _komentariKarakteristika; }
	~ZadovoljstvoKupca() {
		clearKomentariKarakteristika();
	}

	// Methods I added below
	ZadovoljstvoKupca(const ZadovoljstvoKupca& zadovoljstvoKupca)
		: _ocjena{ zadovoljstvoKupca.getOcjena() }
		, _komentariKarakteristika{ getKomentareKarakteristikaCopy() }
	{}

	ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearKomentariKarakteristika();

		_ocjena = rhs.getOcjena();
		_komentariKarakteristika = rhs.getKomentareKarakteristikaCopy();

		return *this;
	}

	int getOcjena() const {
		return _ocjena;
	}

	const Parovi<Karakteristike*, const char*>& getKomentareKarakteristika() const {
		return *_komentariKarakteristika;
	}

	Parovi<Karakteristike*, const char*>* getKomentareKarakteristikaCopy() const {
		Parovi<Karakteristike*, const char*>* temp{ new Parovi<Karakteristike*, const char*>{} };

		for (int i = 0; i < getKomentareKarakteristika().getTrenutno(); ++i) {
			temp->AddElement(
				new Karakteristike{ *getKomentareKarakteristika().getElement1(i) },
				GetNizKaraktera(getKomentareKarakteristika().getElement2(i))
			);
		}

		return temp;
	}

	bool daLiJeKarakteristikaVecKomentarisana(const Karakteristike karakteristika) const {
		for (int i = 0; i < getKomentareKarakteristika().getTrenutno(); ++i) {
			if (karakteristika == *getKomentareKarakteristika().getElement1(i)) {
				return true;
			}
		}

		return false;
	}

	void DodajKomentarKarakteristike(
		const Karakteristike karakteristika, 
		const char* const komentar
	) {
		if (daLiJeKarakteristikaVecKomentarisana(karakteristika)) {
			throw std::runtime_error("Karakteristika je vec komentarisana");
		}

		_komentariKarakteristika->AddElement(
			new Karakteristike{ karakteristika },
			GetNizKaraktera(komentar)
		);
	}

	bool daLiSuKomentariKarakteristikaJednake(
		const Parovi<Karakteristike*, const char*>& komentariKarakteristika
	) const {
		if (komentariKarakteristika.getOmoguciDupliranje() != getKomentareKarakteristika().getOmoguciDupliranje()) {
			return false;
		}
		else if (komentariKarakteristika.getTrenutno() != getKomentareKarakteristika().getTrenutno()) {
			return false;
		}

		for (int i = 0; i < komentariKarakteristika.getTrenutno(); ++i) {
			const char* const komentar1{ komentariKarakteristika.getElement2(i) };
			const char* const komentar2{ getKomentareKarakteristika().getElement2(i) };

			if (*komentariKarakteristika.getElement1(i) != *getKomentareKarakteristika().getElement1(i)) {
				return false;
			}
			else if (std::strcmp(komentar1, komentar2) != 0) {
				return false;
			}
		}

		return true;
	}

	bool operator==(const ZadovoljstvoKupca& rhs) const {
		return getOcjena() == rhs.getOcjena()
			&& daLiSuKomentariKarakteristikaJednake(rhs.getKomentareKarakteristika());
	}

	bool operator!=(const ZadovoljstvoKupca& rhs) const {
		return !(*this == rhs);
	}

	friend std::ostream& operator<<(std::ostream& os, const ZadovoljstvoKupca& zadovoljstvoKupca) {
		os << zadovoljstvoKupca.getOcjena() << '\n';

		const auto& komentariKarakteristika{ zadovoljstvoKupca.getKomentareKarakteristika() };
		for (int i = 0; i < komentariKarakteristika.getTrenutno(); ++i) {
			os << '\t' << *komentariKarakteristika.getElement1(i) << '(';
			os << komentariKarakteristika.getElement2(i) << ')';

			if (i + 1 != komentariKarakteristika.getTrenutno()) {
				os << '\n';
			}
		}

		return os;
	}
private:
	void clearKomentariKarakteristika() {
		for (int i = 0; i < getKomentareKarakteristika().getTrenutno(); ++i) {
			delete getKomentareKarakteristika().getElement1(i);
			delete[] getKomentareKarakteristika().getElement2(i);
		}
		delete _komentariKarakteristika; _komentariKarakteristika = nullptr;
	}
};

class Osoba {
protected:
	char* _imePrezime;
	Datum _datumRodjenja;
public:
	Osoba(const char* imePrezime = "", Datum datumRodjenja = Datum()) : _datumRodjenja(datumRodjenja) {
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	virtual ~Osoba() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	char* GetImePrezime() { return _imePrezime; }
	Datum& GetDatumRodjenja() { return _datumRodjenja; }

	virtual void Info() = 0;
	friend ostream& operator<< (ostream& COUT, const Osoba& obj) {
		COUT << obj._imePrezime << " " << obj._datumRodjenja << endl;
		return COUT;
	}

	// Methods I added below
	Osoba(const Osoba& osoba)
		: _imePrezime{ GetNizKaraktera(osoba.getImePrezime()) }
		, _datumRodjenja{ osoba.getDatumRodjenja() }
	{}

	Osoba& operator=(const Osoba& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _imePrezime;

		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_datumRodjenja = rhs.getDatumRodjenja();

		return *this;
	}

	const char* getImePrezime() const {
		return _imePrezime;
	}

	const Datum& getDatumRodjenja() const {
		return _datumRodjenja;
	}
};

class Kupac : public Osoba {
	char* _emailAdresa;
	//float se odnosi na iznos racuna za odredjenu kupovinu
	Parovi<float, ZadovoljstvoKupca>* _kupovine;
	vector<int> _bodovi; // bodovi sakupljeni tokom kupovine, svakih potrosenih 10KM donosi po 1 bod.
public:
	Kupac(const char* imePrezime = "", Datum datumRodjenja = Datum(), const char* emailAdresa = "")
		: Osoba(imePrezime, datumRodjenja)
	{
		_emailAdresa = GetNizKaraktera(emailAdresa);
		_kupovine = new Parovi<float, ZadovoljstvoKupca>{};
	}
	~Kupac()
	{
		delete[] _emailAdresa; _emailAdresa = nullptr;
		delete _kupovine; _kupovine = nullptr;
	}
	char* GetEmail() { return _emailAdresa; }
	Parovi<float, ZadovoljstvoKupca>& GetKupovine() { return *_kupovine; }
	vector<int> GetBodovi() { return _bodovi; }
	int GetBodoviUkupno() {
		int ukupno = 0;
		for (size_t i = 0; i < _bodovi.size(); i++) ukupno += _bodovi[i];
		return ukupno;
	}

	friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
		COUT << crt << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._emailAdresa << " " << endl;
		COUT << "KUPOVINE -> " << crt;
		for (size_t i = 0; i < obj._kupovine->getTrenutno(); i++)
			COUT << "Iznos racuna: " << obj._kupovine->getElement1(i) << "KM, zadovoljstvo kupca: " << obj._kupovine->getElement2(i) << crt;
		COUT << "BODOVI -> ";
		for (size_t i = 0; i < obj._bodovi.size(); i++)
			COUT << obj._bodovi[i] << ", ";
		COUT << crt;
		return COUT;
	}

	// Methods I added below
	Kupac(const Kupac& kupac)
		: Osoba(kupac)
		, _emailAdresa{ GetNizKaraktera(kupac.getEmail()) }
		, _bodovi{ kupac.getBodovi() }
		, _kupovine{ new Parovi<float, ZadovoljstvoKupca>{ kupac.getKupovine() } }
	{}

	Kupac& operator=(const Kupac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _emailAdresa;

		Osoba::operator=(rhs);
		_emailAdresa = GetNizKaraktera(rhs.getEmail());
		_bodovi = rhs.getBodovi();
		*_kupovine = rhs.getKupovine();

		return *this;
	}

	const char* getEmail() const {
		return _emailAdresa;
	}

	const Parovi<float, ZadovoljstvoKupca>& getKupovine() const {
		return *_kupovine;
	}

	const vector<int> getBodovi() const {
		return _bodovi;
	}

	int getBodoviUkupno() const {
		int sum{ 0 };

		for (const int bod : _bodovi) {
			sum += bod;
		}

		return sum;
	}

	void Info() {
		std::cout << *this;
	}

	void DodajKupovinu(const float cijena, const ZadovoljstvoKupca& zadovoljstvoKupca) {
		if (cijena <= 0) {
			return;
		}

		_kupovine->AddElement(cijena, zadovoljstvoKupca);

		const int bodovi = cijena / 10;

		if (!bodovi) {
			return;
		}

		_bodovi.push_back(bodovi);

		if (bodovi <= 5) {
			return;
		}

		sendMail();
	}

	Parovi<Karakteristike, const char*> GetKupovineByKomentar(const char* const dioKomentara) {
		Parovi<Karakteristike, const char*> temp{};

		for (int i = 0; i < _kupovine->getTrenutno(); ++i) {
			const auto& zadovoljstvoKupca{ _kupovine->getElement2(i) };
			const auto& komentariKarakteristike{ zadovoljstvoKupca.getKomentareKarakteristika() };

			for (int j = 0; j < komentariKarakteristike.getTrenutno(); ++j) {
				const std::string komentarStr{ komentariKarakteristike.getElement2(j) };

				if (komentarStr.find(dioKomentara) != std::string::npos) {
					temp.AddElement(*komentariKarakteristike.getElement1(j), komentariKarakteristike.getElement2(j));
				}
			}
		}

		return temp;
	}

private:
	void sendMail() const {
		std::thread emailThread{
			[&]() {
				std::this_thread::sleep_for(3s);
				std::cout << "To: " << getEmail() << '\n';
				std::cout << "Subject: Osvareni bodovi\n\n";
				std::cout << "Postovani,\n\n";
				std::cout << "Prilikom posljednje kupovine ste ostvarili " << getBodovi().back();
				std::cout << " bodova, tako da trenutno vas ukupan broj bodova iznosi " << getBodoviUkupno() << ".\n\n";
				std::cout << "Zahvaljujemo vam na kupovini.\n";
				std::cout << "Puno pozdrava\n";
			}
		};

		emailThread.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite pojam reprezentacije tipa podatka?\n";
	return  "Odgovor -> Reprezentacija tipa predstavlja nacin njihove pohrane cime se "
		"omogucava izvrsenje aplikacije na racunaru.";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Navedite i ukratko opisite ulogu ios modova koji se koriste pri rada sa fajlovima?\n";
	return "Odgovor -> ios::out - otvara fajl za citanje\n"
		"ios::in - otvara fajl za pisanje\n"
		"ios::app - prije svakog pisanja u fajl odlazi na kraj njega\n"
		"ios::ate - kada otvori fajl odlazi na kraj njega\n"
		"ios::trunc - otvara fajl, sve sto je bilo u fajlu prijasnje se brise\n"
		"ios::binary - otvara fajl u binarnom modu, podatci su spaseni onako kako su u memoriji\n";
	"ios::noreplace - slicno ios::app, samo sto nece uspjeti otvoriti fajl ako ne postoji i fail-ovat ce\n";
}

void main() {

	cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();

	const int ParoviTestSize = 9;

	Parovi<int, int> Parovi1(false);
	for (int i = 0; i < ParoviTestSize - 1; i++)
		Parovi1.AddElement(i, i);//dodaje vrijednosti u Parovi

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 ili T2), metoda AddElement treba baciti izuzetak tipa exception
		Parovi1.AddElement(3, 3);
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}
	Parovi1.AddElement(9, 9);

	cout << Parovi1 << crt;

	/*
	metoda prihvata indekse lokacije, te vraća elemente koji se u kolekciji parova nalaze
	na proslijedjenim lokacijama (ukljucujuci i te lokacije)
	*/
	Parovi<int, int> Parovi2 = Parovi1(2, 5);
	/*clanovi objekta Parovi2 bi trebali biti:
	2 2
	3 3
	4 4
	5 5
	*/
	cout << Parovi2 << crt;
	Parovi<int, int> Parovi3 = Parovi1(2, 5, true);
	/*ukoliko se posalje treci parametar koji oznacava potrebu
	za obrnutim redoslijedom vracenih parova, clanovi objekta Parovi3 bi trebali biti:
	5 5
	4 4
	3 3
	2 2
	*/
	cout << Parovi3 << crt;

	Parovi3 = Parovi2;
	cout << Parovi3 << crt;


	const int maxKupaca = 3;
	Osoba* kupci[maxKupaca];
	kupci[0] = new Kupac("Denis Music", Datum(12, 1, 1980), "denis@fit.ba");
	kupci[1] = new Kupac("Jasmin Azemovic", Datum(12, 2, 1980), "jasmin@fit.ba");
	kupci[2] = new Kupac("Adel Handzic", Datum(12, 3, 1980), "adel@edu.fit.ba");

	ZadovoljstvoKupca zadovoljstvoKupca(7);
	zadovoljstvoKupca.DodajKomentarKarakteristike(NARUDZBA, "Nismo mogli odabrati sve potrebne opcije");
	zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");

	try {
		//karakteristika kvaliteta je vec komentarisana, pa je potrebno baciti izuzetak
		zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}

	zadovoljstvoKupca.DodajKomentarKarakteristike(PAKOVANJE, "Pakovanje je bilo osteceno");
	zadovoljstvoKupca.DodajKomentarKarakteristike(ISPORUKA, "Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana");


	Kupac* denis = dynamic_cast<Kupac*>(kupci[0]);
	/*za svakih 10KM kupcu se dodaje 1 bod, pa ce tako kupovina od 128KM kupcu donijeti 12 bodova*/
	denis->DodajKupovinu(128, zadovoljstvoKupca);
	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno() << '\n';//12 bodova


	ZadovoljstvoKupca zadovoljstvoKupca2(4);
	zadovoljstvoKupca2.DodajKomentarKarakteristike(KVALITET, "Jako lose, proizvod ostecen");
	denis->DodajKupovinu(81, zadovoljstvoKupca2);

	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno() << '\n';//20 bodova

	/*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

	  To: denis@fit.ba;
	  Subject: Osvareni bodovi

	  Postovani,

	  Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

	  Zahvaljujemo vam na kupovini.
	  Puno pozdrava
 */


 //ispisuje sve podatke o kupcu i njegovim kupovinama.

	denis->Info();
	/* Primjer ispisa:
		 -------------------------------------------
		 Denis Music 12.1.1980 denis@fit.ba
		 KUPOVINE ->
		 -------------------------------------------
		 Iznos racuna: 128KM, zadovoljstvo kupca: 7
				   NARUDZBA - Nismo mogli odabrati sve potrebne opcije
				   KVALITET - Kvalitet je ocekivan
				   PAKOVANJE - Pakovanje je bilo osteceno
				   ISPORUKA - Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana
		 -------------------------------------------
		 Iznos racuna: 81KM, zadovoljstvo kupca: 4
				   KVALITET - Jako lose, proizvod ostecen
		 -------------------------------------------
		 BODOVI -> 12, 8,
		 -------------------------------------------
  */

  //metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
	Parovi<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
	cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

	/*Ocekivani ispis:
		 -------------------------------------------
		 Rezultat pretrage ->
		 -------------------------------------------
		 PAKOVANJE Pakovanje je bio osteceno
		 KVALITET Jako lose, proizvod ostecen
		 -------------------------------------------
	*/

	for (size_t i = 0; i < maxKupaca; i++)
		delete kupci[i], kupci[i] = nullptr;

	cin.get();
	system("pause>0");
}
