/*
	DISCLAIMER

	Ja nisam izlazio na ovaj rok, samo sam prikupio odredene informacije kroz pricu
	drugih studenata i slika koje su nekako uslikane tokom ispita. Moguce je da postoji
	mnogo vise razlicitih stvari nego sto sam naveo ovdje.
	Teoretska pitanja sam obrisao jer o njima nisam cuo nista.

	U slucaju da se ne podrazumijeva, na ispitu se ne daju (at least as of writing this)
	ikakvi dodatni bodovi za "optimizovan kod", takoder ne oduzimaju bodovi (u ovom ispitu)
	za memory leaks.
	Zbog cega u odredenim situacijama ja cu radi jednostavnosti pisati kod u kojem ne uzimam
	u obzir ista sem toga da se main moze pokrenut i nema ikakvih izuzetaka.
*/

#include <iostream>
using namespace std;
const char* PORUKA = "\n------------------------------------------------------------------------------ - \n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. "
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEÅ ENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";

// Headers I included below
#include<string>
#include<regex>
#include<chrono>
#include<sstream>
#include<thread>
#include<iomanip>
#include<numeric>
#include<algorithm>
// Headers I included above

enum Drzava { ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA };

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}

// Functions I added below
std::ostream& operator<<(std::ostream& os, Drzava drzava) {
	switch (drzava) {
	case ENGLESKA:
		os << "ENGLESKA";
		break;
	case SPANIJA:
		os << "SPANIJA";
		break;
	case HOLANDIJA:
		os << "HOLANDIJA";
		break;
	case FRANCUSKA:
		os << "FRANCUSKA";
		break;
	case BOSNA_I_HERCEGOVINA:
		os << "BOSNA_I_HERCEGOVINA";
		break;
	default:
		os << "Drzava ne postoji";
	}

	return os;
}

int ReverseNum(int num) {
	int reversedNum{ 0 };

	while (num != 0) {
		reversedNum = reversedNum * 10 + num % 10;
		num /= 10;
	}

	return reversedNum;
}

char* GenerisiID(const std::string& fullName, const int num) {
	std::string ID{};
	const int reverseNum = ReverseNum(num);

	const int nameLastLetterPos = fullName.find(' ') - 1;
	const int surnameInitialPos = fullName.find(' ') + 1;

	ID += std::toupper(fullName[nameLastLetterPos]);

	if (reverseNum < 10) {
		ID += "000";
	}
	else if (reverseNum < 100) {
		ID += "00";
	}
	else if (reverseNum < 1000) {
		ID += '0';
	}

	ID += std::to_string(num);
	ID += std::toupper(fullName[surnameInitialPos]);

	return GetNizKaraktera(ID.c_str());
}

bool ValidirajID(const std::string& id) {
	std::regex idValidation{ "[A-Z]\\d{4}[A-Z]" };

	return std::regex_match(id, idValidation);
}

std::string AddFrontAndBackPaddingToStr(const std::string& str, const int expectedWidth) {
	if (str.size() > expectedWidth) {
		return str;
	}

	const int difference = expectedWidth - str.size();
	const int leftPadding = difference / 2;
	const int rightPadding = difference - leftPadding;

	// Used for debugging
	// std::cout << "difference -> " << difference << '\n';
	// std::cout << "leftPadding -> " << leftPadding << '\n';
	// std::cout << "rightPadding -> " << rightPadding << '\n';

	return std::string(leftPadding, ' ') + str + std::string(rightPadding, ' ');
}

std::string GetDrzavaAsStr(const Drzava drzava) {
	std::ostringstream drzavaBuffer{};

	drzavaBuffer << drzava;

	return drzavaBuffer.str();
}
// Functions I added above

template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max]{};
	T2* _elementi2[max]{};
	int _trenutno{ 0 };
public:
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija() = default;

	Kolekcija(const Kolekcija& kolekcija)
	{
		_trenutno = kolekcija.getTrenutno();
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ kolekcija.getElement1(i) };
			_elementi2[i] = new T2{ kolekcija.getElement2(i) };
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		_trenutno = rhs.getTrenutno();
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = new T1{ rhs.getElement1(i) };
			_elementi2[i] = new T2{ rhs.getElement2(i) };
		}

		return *this;
	}

	T1& getElement1(int lokacija) {
		return *_elementi1[lokacija];
	}

	T2& getElement2(int lokacija) {
		return *_elementi2[lokacija];
	}

	T1 getElement1(int lokacija) const {
		return *_elementi1[lokacija];
	}

	T2 getElement2(int lokacija) const {
		return *_elementi2[lokacija];
	}

	int getTrenutno() const {
		return _trenutno;
	}

	void AddElement(const T1& element1, const T2& element2) {
		_elementi1[getTrenutno()] = new T1{ element1 };
		_elementi2[getTrenutno()] = new T2{ element2 };

		++_trenutno;
	}

	Kolekcija& InsertAt(const int index, const T1& element1, const T2& element2) {
		Kolekcija kopijaSaDodanimElementom{};

		for (int i = 0; i < getTrenutno(); ++i) {
			if (i == index) {
				kopijaSaDodanimElementom.AddElement(element1, element2);
			}
			kopijaSaDodanimElementom.AddElement(getElement1(i), getElement2(i));
		}

		*this = kopijaSaDodanimElementom;

		return *this;
	}

	Kolekcija* RemoveRange(const int start, const int end) {
		if (start < 0 || end >= getTrenutno() || start >= end) {
			throw std::runtime_error("Interval nije validan");
		}

		Kolekcija* elementiZaIzbacit{ new Kolekcija {} };
		Kolekcija elementiZaZadrzat{};

		for (int i = 0; i < getTrenutno(); ++i) {
			if (i >= start && i <= end) {
				elementiZaIzbacit->AddElement(getElement1(i), getElement2(i));
			}
			else {
				elementiZaZadrzat.AddElement(getElement1(i), getElement2(i));
			}
		}

		*this = elementiZaZadrzat;

		return elementiZaIzbacit;
	}
};

class Vrijeme {
	int* _sat, * _minuta, * _sekunda;
public:
	Vrijeme(int sat = 10, int minuta = 0, int sekunda = 0) {
		_sat = new int(sat);
		_minuta = new int(minuta);
		_sekunda = new int(sekunda);
	}
	~Vrijeme() {
		delete _sat; _sat = nullptr;
		delete _minuta; _minuta = nullptr;
		delete _sekunda; _sekunda = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Vrijeme& obj) {
		COUT << *obj._sat << ":" << *obj._minuta << ":" << *obj._sekunda;
		return COUT;
	}

	// Methods I added below
	Vrijeme(const Vrijeme& vrijeme)
		: _sat{ new int{ vrijeme.getSat() } }
		, _minuta{ new int{ vrijeme.getMinuta() } }
		, _sekunda{ new int{ vrijeme.getSekunda() } }
	{
	}

	Vrijeme& operator=(const Vrijeme& rhs) {
		*_sat = rhs.getSat();
		*_minuta = rhs.getMinuta();
		*_sekunda = rhs.getSekunda();

		return *this;
	}

	int getSat() const {
		return *_sat;
	}

	int getMinuta() const {
		return *_minuta;
	}

	int getSekunda() const {
		return *_sekunda;
	}

	int toInt() const {
		return getSekunda() + getMinuta() * 60 + getSat() * 3600;
	}

	bool operator==(const Vrijeme& rhs) const {
		return getSat() == rhs.getSat()
			&& getMinuta() == rhs.getMinuta()
			&& getSekunda() == rhs.getSekunda();
	}

	bool operator!=(const Vrijeme& rhs) const {
		return !(*this == rhs);
	}

	bool operator>=(const Vrijeme& rhs) const {
		return toInt() >= rhs.toInt();
	}

	bool operator<=(const Vrijeme& rhs) const {
		return toInt() <= rhs.toInt();
	}
};

class Pogodak {
	Vrijeme* _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena) :
		_vrijemePogotka(new Vrijeme(vrijeme))
	{
		_napomena = GetNizKaraktera(napomena);
	}
	~Pogodak()
	{
		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;
	}
	Vrijeme GetVrijemePogotka() const { return *_vrijemePogotka; }
	char* GetNapomena() const { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}

	// Methods I added below
	Pogodak(const Pogodak& pogodak)
	{
		_vrijemePogotka = new Vrijeme{ pogodak.GetVrijemePogotka() };
		_napomena = GetNizKaraktera(pogodak.GetNapomena());
	}

	Pogodak& operator=(const Pogodak& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;

		_vrijemePogotka = new Vrijeme{ rhs.GetVrijemePogotka() };
		_napomena = GetNizKaraktera(rhs.GetNapomena());

		return *this;
	}

	bool operator==(const Pogodak& rhs) const {
		return GetVrijemePogotka() == rhs.GetVrijemePogotka()
			&& std::string(GetNapomena()) == rhs.GetNapomena();
	}

	bool operator!=(const Pogodak& rhs) const {
		return !(*this == rhs);
	}
};

class Igrac {
	static int _id;
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID i vrijednost statickog clana _id
	char* _imePrezime;
	vector<Pogodak*> _pogoci;
public:
	Igrac(const char* imePrezime)
		: _ID{ GenerisiID(imePrezime, _id++) }
	{
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	~Igrac() {
		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); i++) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
	}
	char* GetImePrezime() const { return _imePrezime; }
	char* GetID() const { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			COUT << *obj._pogoci[i] << endl;
		return COUT;
	}

	// Methods I added below

	Igrac(const Igrac& igrac)
	{
		_ID = GetNizKaraktera(igrac.GetID());
		_imePrezime = GetNizKaraktera(igrac.GetImePrezime());
		for (const Pogodak* const pogodak : igrac._pogoci) {
			_pogoci.push_back(new Pogodak{ *pogodak });
		}
	}

	Igrac& operator=(const Igrac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); i++) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
		_pogoci.clear();

		_ID = GetNizKaraktera(rhs.GetID());
		_imePrezime = GetNizKaraktera(rhs.GetImePrezime());
		for (const Pogodak* const pogodak : rhs._pogoci) {
			_pogoci.push_back(new Pogodak{ *pogodak });
		}

		return *this;
	}

	bool operator==(const Igrac& rhs) const {
		return std::string(GetID()) == rhs.GetID();
	}

	bool operator!=(const Igrac& rhs) const {
		return !(*this == rhs);
	}

	bool operator==(const std::string& idIliImeIgraca) const {
		return GetID() == idIliImeIgraca || GetImePrezime() == idIliImeIgraca;
	}

	bool operator!=(const std::string& idIliImeIgraca) const {
		return !(*this == idIliImeIgraca);
	}

	bool DaLiJePogodakDodan(const Pogodak& pogodakZaPronaci) const {
		for (const auto& pogodak : _pogoci) {
			if (*pogodak == pogodakZaPronaci) {
				return true;
			}
		}

		return false;
	}

	void AddPogodak(const Pogodak& pogodak) {
		_pogoci.push_back(new Pogodak{ pogodak });
	}

	const Pogodak& GetZadnjiPogodak() const {
		return *_pogoci.back();
	}

	int GetBrojPogodaka() const {
		return _pogoci.size();
	}
};
int Igrac::_id = 1;

class DrzavaTim {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	DrzavaTim(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}
	Drzava GetDrzava() const { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	// Methods I added below

	const std::vector<Igrac>& GetIgraci() const {
		return _igraci;
	}

	bool DaLiIgracPostojiUDrzavaTim(const Igrac& igracZaPronaci) const {
		for (const auto& igrac : GetIgraci()) {
			if (igrac == igracZaPronaci) {
				return true;
			}
		}

		return false;
	}

	void AddIgrac(const Igrac& igrac) {
		if (DaLiIgracPostojiUDrzavaTim(igrac)) {
			throw std::runtime_error("Igrac vec dodan u drzava timu");
		}

		_igraci.push_back(igrac);
	}

	bool operator==(const DrzavaTim& rhs) const {
		return GetDrzava() == rhs.GetDrzava()
			&& GetIgraci() == rhs.GetIgraci();
	}

	bool operator!=(const DrzavaTim& rhs) const {
		return !(*this == rhs);
	}

	int GetBrojPogodaka() const {
		int sum{ 0 };

		for (const auto& igrac : GetIgraci()) {
			sum += igrac.GetBrojPogodaka();
		}

		return sum;
	}

	Igrac* GetIgracByIDOrName(const std::string& idIliImeIgraca) {
		for (auto& igrac : GetIgraci()) {
			if (igrac == idIliImeIgraca) {
				return &igrac;
			}
		}

		return nullptr;
	}

	std::vector<Igrac*> GetIgraceSaIstimBrojemPogodaka(const int brojPogodaka) {
		std::vector<Igrac*> igraci{};

		for (auto& igrac : GetIgraci()) {
			if (igrac.GetBrojPogodaka() == brojPogodaka) {
				igraci.push_back(&igrac);
			}
		}

		return igraci;
	}

	std::vector<Igrac> GetIgraciKojiSuDaliPogotke() const {
		std::vector<Igrac> igraci{};

		for (auto& igrac : GetIgraci()) {
			for (std::size_t i = 0; i < igrac.GetBrojPogodaka(); ++i) {
				igraci.push_back(igrac);
			}
		}

		return igraci;
	}
};

class Prventstvo {
	Kolekcija<DrzavaTim*, DrzavaTim*, 20> _utakmice;
public:
	Kolekcija<DrzavaTim*, DrzavaTim*, 20>& GetUtakmice() {
		return _utakmice;
	}

	// Methods I added below

	bool DaLiSuSeDrzaveTimoviVecSusreli(
		const DrzavaTim& drzavaDomacegTimaZaPronaci,
		const DrzavaTim& drzavaGostTimaZaPronaci
	) const {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			const DrzavaTim& drzavaDomacegTima{ *_utakmice.getElement1(i) };
			const DrzavaTim& drzavaGostTima{ *_utakmice.getElement2(i) };

			if (drzavaDomacegTimaZaPronaci == drzavaDomacegTima
				&& drzavaGostTimaZaPronaci == drzavaGostTima) {
				return true;
			}
		}

		return false;
	}

	void AddUtakmicu(
		const DrzavaTim& drzavaTim1,
		const DrzavaTim& drzavaTim2
	) {
		if (DaLiSuSeDrzaveTimoviVecSusreli(drzavaTim1, drzavaTim2)) {
			throw std::runtime_error("Drzave tim su se vec jednom susrele na ovom prvenstvu");
		}

		_utakmice.AddElement(new DrzavaTim{ drzavaTim1 }, new DrzavaTim{ drzavaTim2 });
	}

	DrzavaTim* GetDrzavaTimForDrzava(Drzava drzava) {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			DrzavaTim& drzavaTimDomacina{ *_utakmice.getElement1(i) };
			DrzavaTim& drzavaTimGosta{ *_utakmice.getElement2(i) };

			if (drzavaTimDomacina.GetDrzava() == drzava) {
				return &drzavaTimDomacina;
			}
			else if (drzavaTimGosta.GetDrzava() == drzava) {
				return &drzavaTimGosta;
			}
		}

		return nullptr;
	}

	Igrac* GetIgracByIDOrNameFromDrzaveTimovi(
		const std::string& idIliImeIgraca,
		DrzavaTim& drzavaTimDomacina,
		DrzavaTim& drzavaTimGosta
	) {
		Igrac* igracDomacin{ drzavaTimDomacina.GetIgracByIDOrName(idIliImeIgraca) };

		if (igracDomacin) {
			return igracDomacin;
		}

		Igrac* igracGost{ drzavaTimGosta.GetIgracByIDOrName(idIliImeIgraca) };

		return igracGost;
	}

	/*
		U metodi ispod ima nadprosjecan broj predpostavki da nesto nije
		nullptr, jer za nas testni main to nece praviti problem, za drugi
		tho vjv hoce
	*/
	bool AddPogodak(
		Drzava drzavaDomacegTima,
		Drzava drzavaGostTima,
		const std::string& idIliImeIgraca,
		const Pogodak& pogodakZaDodat
	) {
		DrzavaTim* drzavaTimDomacina{ GetDrzavaTimForDrzava(drzavaDomacegTima) };
		DrzavaTim* drzavaTimGosta{ GetDrzavaTimForDrzava(drzavaGostTima) };

		Igrac* igracKojiJeDaoGo{
			GetIgracByIDOrNameFromDrzaveTimovi(idIliImeIgraca, *drzavaTimDomacina, *drzavaTimGosta)
		};

		if (igracKojiJeDaoGo->DaLiJePogodakDodan(pogodakZaDodat)) {
			return false;
		}

		igracKojiJeDaoGo->AddPogodak(pogodakZaDodat);
		SendMailSvimIgracima(*igracKojiJeDaoGo, *drzavaTimDomacina, *drzavaTimGosta);
		return true;
	}

	std::string GetFormattedResultStrForDrzaveTimovi(
		const DrzavaTim& drzavaTimDomacina,
		const DrzavaTim& drzavaTimGosta
	) const {
		std::string formattedResult{};

		const std::string drzava1Str{ GetDrzavaAsStr(drzavaTimDomacina.GetDrzava()) };
		const std::string drzava1Pogoci{ '(' + std::to_string(drzavaTimDomacina.GetBrojPogodaka()) + ')' };

		const std::string drzava2Str{ GetDrzavaAsStr(drzavaTimGosta.GetDrzava()) };
		const std::string drzava2Pogoci{ '(' + std::to_string(drzavaTimGosta.GetBrojPogodaka()) + ')' };

		formattedResult += drzava1Str;
		formattedResult += " : ";
		formattedResult += drzava2Str;
		formattedResult += '\n';

		formattedResult += AddFrontAndBackPaddingToStr(drzava1Pogoci, drzava1Str.size());
		formattedResult += "   ";
		formattedResult += AddFrontAndBackPaddingToStr(drzava2Pogoci, drzava2Str.size());

		return formattedResult;
	}

	friend std::ostream& operator<<(std::ostream& os, const Prventstvo& prventstvo) {
		const auto& utakmice{ prventstvo._utakmice };

		for (int i = 0; i < utakmice.getTrenutno(); ++i) {
			const DrzavaTim& drzavaTimDomacina{ *utakmice.getElement1(i) };
			const DrzavaTim& drzavaTimGosta{ *utakmice.getElement2(i) };

			const std::vector<Igrac> igraciDomacini{ drzavaTimDomacina.GetIgraciKojiSuDaliPogotke() };
			const std::vector<Igrac> igraciGosta{ drzavaTimGosta.GetIgraciKojiSuDaliPogotke() };
			int maksSize = std::max(igraciDomacini.size(), igraciGosta.size());

			os << crt;
			os << prventstvo.GetFormattedResultStrForDrzaveTimovi(drzavaTimDomacina, drzavaTimGosta);
			os << crt;

			for (int i = 0; i < maksSize; ++i) {
				if (i < igraciDomacini.size()) {
					os << igraciDomacini[i].GetImePrezime();
				}
				os << ' ';
				if (i < igraciGosta.size()) {
					os << igraciGosta[i].GetImePrezime();
				}
				if (i + 1 != maksSize) {
					os << '\n';
				}
			}

			os << crt;
		}

		return os;
	}

	std::vector<Igrac*> operator()(const int brojPogodaka) {
		std::vector<Igrac*> igraci{};

		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			DrzavaTim& drzavaTimDomacina{ *_utakmice.getElement1(i) };
			DrzavaTim& drzavaTimGosta{ *_utakmice.getElement2(i) };

			auto igraciDrzaveTimDomacina{
				drzavaTimDomacina.GetIgraceSaIstimBrojemPogodaka(brojPogodaka)
			};
			auto igraciDrzaveGosta{
				drzavaTimGosta.GetIgraceSaIstimBrojemPogodaka(brojPogodaka)
			};

			for (const auto& igracDomacin : igraciDrzaveTimDomacina) {
				igraci.push_back(igracDomacin);
			}

			for (const auto& igracGost : igraciDrzaveGosta) {
				igraci.push_back(igracGost);
			}
		}

		return igraci;
	}

	void SendMailSvimIgracima(
		const Igrac& igracKojiJeDaoGo,
		const DrzavaTim& drzavaTimDomacina,
		const DrzavaTim& drzavaTimGosta
	) const {
		for (const auto& igracDomacin : drzavaTimDomacina.GetIgraci()) {
			SendMail(
				igracDomacin,
				igracKojiJeDaoGo,
				drzavaTimDomacina,
				drzavaTimGosta
			);
		}
		for (const auto& igracGost : drzavaTimGosta.GetIgraci()) {
			SendMail(
				igracGost,
				igracKojiJeDaoGo,
				drzavaTimDomacina,
				drzavaTimGosta
			);
		}
	}

	void SendMail(
		const Igrac& igracKojemSeSaljeMail,
		const Igrac& igracKojiJeDaoGo,
		const DrzavaTim& drzavaTimDomacina,
		const DrzavaTim& drzavaTimGosta
	) const {
		std::thread emailThread{
			[&]() {
				std::this_thread::sleep_for(2s);
				std::cout << "\nTo: " << igracKojemSeSaljeMail.GetID() << "@euro2024.com\n";
				std::cout << "From: info@euro2024.com\n";
				std::cout << "Subject: Informacija\n";
				std::cout << "Postovani,\n";
				std::cout << "U " << igracKojiJeDaoGo.GetZadnjiPogodak().GetVrijemePogotka();
				std::cout << " sati igrac " << igracKojiJeDaoGo.GetImePrezime();
				std::cout << " je zabiljezio svoj " << igracKojiJeDaoGo.GetBrojPogodaka() << '\n';
				std::cout << "pogodak na ovoj utakmici.\n";
				std::cout << "Trenutni rezultat je:\n";
				std::cout << GetFormattedResultStrForDrzaveTimovi(drzavaTimDomacina, drzavaTimGosta);
				std::cout << "\nPuno srece u nastavku susreta.\n\n";
			}
		};

		emailThread.join();
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite kljucnu rijec virtual? \n";
	return "Odgovor -> virtual kljucna rijec se moze koristiti u dvije svrhe, jedna je za kreiranje virtualnih metoda, metode cije ponasanje se odreduje u run-time sto nam omogucava da imamo polimorfizam, druga svrha je da prilikom nasljedivanja koristeci virtual mozemo naglasiti da zelimo da klasa u sebi sadrzi maksimalno 1 instancu nekog objekta sto je naslijedila";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite function tip podatka? \n";
	return "Odgovor -> function tip podatka predstavlja tip koji u sebi ima preklopljen operator () na nacin da njegove instance se mogu pozivati kao sto bi funkcije. Takoder ima ugradene konstruktore i operatore jednakosti da primi funkcije, lambde i druge objekte tip function";
}
void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/*
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale, tj. zadnje slovo imena i prvo slovo prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne vrijednosti parametara. Ukoliko se proslijede
	mala slova imena ili prezimena, potrebno ih je konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti S0003M
	cout << GenerisiID("jasmin azemovic", 14) << endl;//treba vratiti N0041A
	cout << GenerisiID("Goran skondric", 156) << endl;//treba vratiti N0651S
	cout << GenerisiID("emina Junuz", 1798) << endl;//treba vratiti A8971J

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//Vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("S0003M"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("N0041A"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("N00651S"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("a8971j"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti drugog i treceg
   parametra na lokaciju koja je definisana prvim parametrom. Povratna
   vrijednost metode je pokazivac na pozivaoca metode (u konkretnom slucaju objekat
   kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
   zahtijevani parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
   kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	10 10
	0 0
	1 1
	2 2
	* ....
	*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(0, 10, 10);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji
	metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/
	Kolekcija<int, int, 10>* kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << *kolekcija3 << endl;
	cout << kolekcija1 << crt;
	/*kolekcija3 bi trebala sadrzavati sljedece elemente:
	0 0
	1 1
	2 2
	dok bi kolekcija1 trebala sadrzavati sljedece elemente:
	10 10
	3 3
	4 4
	......
	*/
	kolekcija1 = *kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");
	if (strcmp(denis.GetID(), "S0001M") == 0 && strcmp(jasmin.GetID(), "N0002A") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtom pogotku");
	DrzavaTim BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		//onemoguciti dodavanje istih igraca - provjeravati ID, baciti izuzetak
		BIH.AddIgrac(denis);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		//onemoguciti ponovne susrete drzave tokom istog prvenstva, baciti izuzetak
		euro2024.AddUtakmicu(BIH, ENG);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	//omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "S0001M", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "N0002A", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//u zasebnom thread-u, poslati email, u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	/*
	To: S0001M@euro2024.com
	From: info@euro2024.com
	Subject: Informacija
	Postovani,
	U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
   pogodak na ovoj utakmici.
	Trenutni rezultat je:
	BOSNA_I_HERCEGOVINA : ENGLESKA
		  (2)			    (0)
	Puno srece u nastavku susreta.
	Neka bolji tim pobijedi.
	*/
	//ispisuje detaljnije informacije o susretu, kako je navedeno u narednom ispisu
	cout << euro2024;
	/*
	-------------------------------------------
	BOSNA_I_HERCEGOVINA : ENGLESKA
		  (3)			    (1)
	-------------------------------------------
	Denis Music Goran Skondric
	Jasmin Azemovic
	Jasmin Azemovic
	-------------------------------------------
	*/
	//vraca sve igrace koji su na takmicenju postigli broj pogodaka proslijeden
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;
	cin.get();
	system("pause>0");
}