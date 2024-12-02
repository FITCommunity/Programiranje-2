/*
	BIG DISCLAIMER

	Ja nisam izlazio na ovaj rok, samo sam prikupio odredene informacije kroz pricu
	drugih studenata i slika koje su nekako uslikane tokom ispita. Moguce je da postoji
	mnogo vise razlicitih stvari nego sto sam naveo ovdje.
	Teoretska pitanja sam obrisao jer o njima nisam cuo nista.
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
	case Drzava::ENGLESKA:
		os << "ENGLESKA";
		break;
	case Drzava::SPANIJA:
		os << "SPANIJA";
		break;
	case Drzava::HOLANDIJA:
		os << "HOLANDIJA";
		break;
	case Drzava::FRANCUSKA:
		os << "FRANCUSKA";
		break;
	case Drzava::BOSNA_I_HERCEGOVINA:
		os << "BOSNA_I_HERCEGOVINA";
		break;
	default:
		os << "Drzava ne postoji";
	}

	return os;
}

int reverseNum(int num) {
	int reversedNum{ 0 };

	while (num != 0) {
		reversedNum = reversedNum * 10 + num % 10;
		num /= 10;
	}

	return reversedNum;
}

char* GenerisiID(const std::string& fullName, int num) {
	std::string ID{};
	num = reverseNum(num);

	const std::size_t nameLastLetterPos{ fullName.find(' ') - 1 };
	const std::size_t surnameInitialPos{ fullName.find(' ') + 1 };

	ID += std::toupper(fullName[nameLastLetterPos]);

	if (num < 10) {
		ID += "000";
	}
	else if (num < 100) {
		ID += "00";
	}
	else if (num < 1000) {
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

std::string addFrontBackPaddingToText(const std::string& str, const std::size_t width) {
	if (str.size() > width) {
		return str;
	}

	const std::size_t difference{ width - str.size() };
	const std::size_t leftPadding{ difference / 2 };
	const std::size_t rightPadding{ difference - leftPadding };

	// Used for debugging
	//std::cout << "difference -> " << difference << '\n';
	//std::cout << "leftPadding -> " << leftPadding << '\n';
	//std::cout << "rightPadding -> " << rightPadding << '\n';

	return std::string(leftPadding, ' ') + str + std::string(rightPadding, ' ');
}

std::string getDrzavaAsStr(const Drzava drzava) {
	std::ostringstream drzavaBuffer{};

	drzavaBuffer << drzava;

	return drzavaBuffer.str();
}
// Functions I added above

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max]{};
	T2 _elementi2[max]{};
	int _trenutno{ 0 };
public:
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	Kolekcija() = default;
	~Kolekcija() = default;

	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ kolekcija.getTrenutno() }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		_trenutno = rhs.getTrenutno();
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rhs.getElement1(i);
			_elementi2[i] = rhs.getElement2(i);
		}

		return *this;
	}

	T1& getElement1(int lokacija) {
		return _elementi1[lokacija];
	}

	T2& getElement2(int lokacija) {
		return _elementi2[lokacija];
	}

	T1 getElement1(int lokacija) const {
		return _elementi1[lokacija];
	}

	T2 getElement2(int lokacija) const {
		return _elementi2[lokacija];
	}

	int getTrenutno() const {
		return _trenutno;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (getTrenutno() == max) {
			return;
		}

		_elementi1[getTrenutno()] = element1;
		_elementi2[getTrenutno()] = element2;

		++_trenutno;
	}

	Kolekcija InsertAt(const int index, const T1& element1, const T2& element2) {
		if (getTrenutno() == max || index < 0 || index > getTrenutno()) {
			return *this;
		}

		for (int i = getTrenutno(); i > index; --i) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}

		_elementi1[index] = element1;
		_elementi2[index] = element2;

		++_trenutno;

		return *this;
	}

	void RemoveAt(const int index) {
		if (getTrenutno() == 0 || index < 0 || index >= getTrenutno()) {
			return;
		}

		--_trenutno;

		for (int i = index; i < getTrenutno(); ++i) {
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
	}

	Kolekcija* RemoveRange(const int start, const int end) {
		if (start < 0) {
			throw std::runtime_error("Start index nije u opsegu");
		}
		else if (end >= getTrenutno()) {
			throw std::runtime_error("End index nije u opsegu");
		}
		else if (start > end) {
			throw std::runtime_error("Start index je veci od end indexa");
			/*
				Posto komentar ima dio koji kaze "U slucaju da zahtijevani opseg ne postoji u kolekciji metoda treba baciti izuzetak"
				vjerujem da je naglaseno da se uzme u obzir da ne bude da se ide od 6 do 1
				Iako da se ovo proslijedi nece se nista desiti jer uslov for petlje ispod nece se ispuniti, so yeah
			*/
		}

		Kolekcija* temp{ new Kolekcija{} };

		for (int i = start; i <= end; ++i) {
			temp->AddElement(getElement1(start), getElement2(start));
			RemoveAt(start);
		}

		return temp;
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
	{}

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
	Vrijeme GetVrijemePogotka() { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}

	// Methods I added below
	Pogodak(const Pogodak& pogodak)
		: _vrijemePogotka{ new Vrijeme{ pogodak.getVrijemePogotka() } }
		, _napomena{ GetNizKaraktera(pogodak.getNapomena()) }
	{}

	Pogodak& operator=(const Pogodak& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _napomena;

		*_vrijemePogotka = rhs.getVrijemePogotka();
		_napomena = GetNizKaraktera(rhs.getNapomena());

		return *this;
	}

	const Vrijeme& getVrijemePogotka() const {
		return *_vrijemePogotka;
	}

	const char* getNapomena() const {
		return _napomena;
	}

	bool operator==(const Pogodak& rhs) const {
		return getVrijemePogotka() == rhs.getVrijemePogotka()
			&& std::strcmp(getNapomena(), rhs.getNapomena()) == 0;
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
		clearResources();
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			COUT << *obj._pogoci[i] << endl;
		return COUT;
	}

	// Methods I added below

	Igrac(const Igrac& igrac)
		: _ID{ GetNizKaraktera(igrac.getID()) }
		, _imePrezime{ GetNizKaraktera(igrac.getImePrezime()) }
		, _pogoci{ igrac.getPogociCopy() }
	{}

	Igrac& operator=(const Igrac& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clearResources();

		_ID = GetNizKaraktera(rhs.getID());
		_imePrezime = GetNizKaraktera(rhs.getImePrezime());
		_pogoci = rhs.getPogociCopy();

		return *this;
	}

	const char* getImePrezime() const {
		return _imePrezime;
	}

	const char* getID() const {
		return _ID;
	}

	const std::vector<Pogodak*>& getPogoci() const {
		return _pogoci;
	}

	std::vector<Pogodak*> getPogociCopy() const {
		std::vector<Pogodak*> temp{};

		for (const auto& pogodak : _pogoci) {
			temp.push_back(new Pogodak(*pogodak));
		}

		return temp;
	}

	bool operator==(const Igrac& rhs) const {
		return std::strcmp(getID(), rhs.getID()) == 0;
	}

	bool operator!=(const Igrac& rhs) const {
		return !(*this == rhs);
	}

	bool operator==(const std::string& idIliImeIgraca) const {
		return getID() == idIliImeIgraca || getImePrezime() == idIliImeIgraca;
	}

	bool operator!=(const std::string& idIliImeIgraca) const {
		return !(*this == idIliImeIgraca);
	}

	bool daLiJePogodakDodan(const Pogodak& pogodakZaPronaci) {
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

	const Pogodak& getZadnjiPogodak() const {
		return *_pogoci.back();
	}

	std::size_t getBrojPogodaka() const {
		return _pogoci.size();
	}

private:
	void clearResources() {
		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
		for (auto& pogodak : _pogoci) {
			delete pogodak;
			pogodak = nullptr;
		}
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
	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	// Methods I added below
	DrzavaTim(const DrzavaTim& reprezentacija) = default;
	~DrzavaTim() = default;

	DrzavaTim& operator=(const DrzavaTim& rhs) {
		if (this == &rhs) {
			return *this;
		}

		_drzava = rhs.getDrzava();
		_igraci = rhs.getIgraci();

		return *this;
	}

	Drzava getDrzava() const {
		return _drzava;
	}

	const std::vector<Igrac>& getIgraci() const {
		return _igraci;
	}

	bool daLiIgracPostojiUDrzavaTim(const Igrac& igracZaPronaci) const {
		for (const auto& igrac : _igraci) {
			if (igrac == igracZaPronaci) {
				return true;
			}
		}

		return false;
	}

	void AddIgrac(const Igrac& igrac) {
		if (daLiIgracPostojiUDrzavaTim(igrac)) {
			throw std::runtime_error("Igrac vec dodan u reprezentaciju");
		}

		_igraci.push_back(igrac);
	}

	bool operator==(const DrzavaTim& rhs) const {
		return getDrzava() == rhs.getDrzava()
			&& getIgraci() == rhs.getIgraci();
	}

	bool operator!=(const DrzavaTim& rhs) const {
		return !(*this == rhs);
	}

	std::size_t getBrojPogodaka() const {
		std::size_t sum{ 0 };

		for (const auto& igrac : _igraci) {
			sum += igrac.getBrojPogodaka();
		}

		return sum;
	}

	Igrac* getIgracByIDOrName(const std::string& idIliImeIgraca) {
		for (auto& igrac : _igraci) {
			if (igrac == idIliImeIgraca) {
				return &igrac;
			}
		}

		return nullptr;
	}

	std::vector<Igrac*> operator()(const std::size_t brojPogodaka) {
		std::vector<Igrac*> temp{};

		for (auto& igrac : _igraci) {
			if (igrac.getBrojPogodaka() == brojPogodaka) {
				temp.push_back(&igrac);
			}
		}

		return temp;
	}

	std::vector<Igrac> getIgraciThatScores() const {
		std::vector<Igrac> igraci{};

		for (auto& igrac : _igraci) {
			for (std::size_t i = 0; i < igrac.getBrojPogodaka(); ++i) {
				igraci.push_back(igrac);
			}
		}

		return igraci;
	}
};

class Prventstvo {
	Kolekcija<DrzavaTim, DrzavaTim, 20> _utakmice;
public:
	Kolekcija<DrzavaTim, DrzavaTim, 20>& GetUtakmice() {
		return _utakmice;
	}

	// Methods I added below
	Prventstvo() = default;
	Prventstvo(const Prventstvo& prventstvo) = default;
	Prventstvo& operator=(const Prventstvo& rhs) = default;
	~Prventstvo() = default;

	const Kolekcija<DrzavaTim, DrzavaTim, 20>& getUtakmice() const {
		return _utakmice;
	}

	bool daLiSuSeDrzaveTimoviVecSusreli(
		const DrzavaTim& drzavaTim1ZaPronaci,
		const DrzavaTim& drzavaTim2ZaPronaci
	) const {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			const DrzavaTim& drzavaTim1{ _utakmice.getElement1(i) };
			const DrzavaTim& drzavaTim2{ _utakmice.getElement2(i) };

			if (drzavaTim1ZaPronaci == drzavaTim1 && drzavaTim2ZaPronaci == drzavaTim2) {
				return true;
			}
			else if (drzavaTim1ZaPronaci == drzavaTim2 && drzavaTim2ZaPronaci == drzavaTim1) {
				return true;
			}
		}

		return false;
	}

	void AddUtakmicu(
		const DrzavaTim& drzavaTim1,
		const DrzavaTim& drzavaTim2
	) {
		if (daLiSuSeDrzaveTimoviVecSusreli(drzavaTim1, drzavaTim2)) {
			throw std::runtime_error("Drzave tim su se vec jednom susrele na ovom prvenstvu");
		}
		else if (drzavaTim1.getDrzava() == drzavaTim2.getDrzava()) {
			// No point in setting a match if the countries are the same
			return;
		}

		_utakmice.AddElement(drzavaTim1, drzavaTim2);
	}

	DrzavaTim* getDrzavaTimForDrzava(Drzava drzava) {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			DrzavaTim& drzavaTim1{ _utakmice.getElement1(i) };
			DrzavaTim& drzavaTim2{ _utakmice.getElement2(i) };

			if (drzavaTim1.getDrzava() == drzava) {
				return &drzavaTim1;
			}
			else if (drzavaTim2.getDrzava() == drzava) {
				return &drzavaTim2;
			}
		}

		return nullptr;
	}

	Igrac* getIgracByIDOrNameFromDrzaveTimovi(
		const std::string& idIliImeIgraca,
		DrzavaTim& drzavaTim1,
		DrzavaTim& drzavaTim2
	) {
		Igrac* igrac1{ drzavaTim1.getIgracByIDOrName(idIliImeIgraca) };

		if (igrac1) {
			return igrac1;
		}

		Igrac* igrac2{ drzavaTim2.getIgracByIDOrName(idIliImeIgraca) };
		return igrac2;
	}

	bool AddPogodak(
		Drzava drzava1,
		Drzava drzava2,
		const std::string& idIliImeIgraca,
		const Pogodak& pogodak
	) {
		DrzavaTim* drzavaTim1{ getDrzavaTimForDrzava(drzava1) };
		DrzavaTim* drzavaTim2{ getDrzavaTimForDrzava(drzava2) };

		if (!drzavaTim1 || !drzavaTim2) {
			return false;
		}
		else if (!daLiSuSeDrzaveTimoviVecSusreli(*drzavaTim1, *drzavaTim2)) {
			return false;
		}

		Igrac* igrac{
			getIgracByIDOrNameFromDrzaveTimovi(idIliImeIgraca, *drzavaTim1, *drzavaTim2)
		};

		if (!igrac || igrac->daLiJePogodakDodan(pogodak)) {
			return false;
		}

		igrac->AddPogodak(pogodak);
		sendMail(*igrac, *drzavaTim1, *drzavaTim2);
		return true;
	}

	static std::string getFormattedResultStrForDrzaveTimovi(
		const DrzavaTim& drzavaTim1,
		const DrzavaTim& drzavaTim2
	) {
		std::string formattedResult{};

		std::string drzava1Str{ getDrzavaAsStr(drzavaTim1.getDrzava()) };
		std::string drzava1Pogoci{ '(' + std::to_string(drzavaTim1.getBrojPogodaka()) + ')' };

		std::string drzava2Str{ getDrzavaAsStr(drzavaTim2.getDrzava()) };
		std::string drzava2Pogoci{ '(' + std::to_string(drzavaTim2.getBrojPogodaka()) + ')' };

		formattedResult += drzava1Str;
		formattedResult += " : ";
		formattedResult += drzava2Str;
		formattedResult += '\n';

		formattedResult += addFrontBackPaddingToText(drzava1Pogoci, drzava1Str.size());
		formattedResult += "   ";
		formattedResult += addFrontBackPaddingToText(drzava2Pogoci, drzava2Str.size());

		return formattedResult;
	}

	static std::string getPlayersWhoScoredGoalsSideBySide(
		const std::vector<Igrac>& igraci1,
		const std::vector<Igrac>& igraci2
	) {
		std::string playerNamesSideBySide{};

		std::size_t igrac1Index{ 0 };
		std::size_t igrac2Index{ 0 };
		bool anyIgraci1Left{ igrac1Index < igraci1.size() };
		bool anyIgraci2Left{ igrac2Index < igraci2.size() };

		while (anyIgraci1Left || anyIgraci2Left) {
			if (anyIgraci1Left) {
				playerNamesSideBySide += igraci1[igrac1Index].getImePrezime();
				++igrac1Index;
			}

			if (anyIgraci2Left) {
				playerNamesSideBySide += ((anyIgraci1Left) ? "\t" : "\t\t");
				playerNamesSideBySide += igraci2[igrac2Index].getImePrezime();
				++igrac2Index;
			}

			playerNamesSideBySide += '\n';

			anyIgraci1Left = igrac1Index < igraci1.size();
			anyIgraci2Left = igrac2Index < igraci2.size();
		}

		if (!playerNamesSideBySide.empty()) {
			playerNamesSideBySide.pop_back();
		}

		return playerNamesSideBySide;
	}

	friend std::ostream& operator<<(std::ostream& os, const Prventstvo& prventstvo) {
		const auto& utakmice{ prventstvo.getUtakmice() };

		for (int i = 0; i < utakmice.getTrenutno(); ++i) {
			const DrzavaTim& drzavaTim1{ utakmice.getElement1(i) };
			const DrzavaTim& drzavaTim2{ utakmice.getElement2(i) };

			os << crt;
			os << Prventstvo::getFormattedResultStrForDrzaveTimovi(drzavaTim1, drzavaTim2);
			os << crt;

			os << Prventstvo::getPlayersWhoScoredGoalsSideBySide(drzavaTim1.getIgraciThatScores(), drzavaTim2.getIgraciThatScores());
			os << crt;
		}

		return os;
	}

	std::vector<Igrac*> operator()(const std::size_t brojPogodaka) {
		std::vector<Igrac*> temp{};

		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			DrzavaTim& drzavaTim1{ _utakmice.getElement1(i) };
			DrzavaTim& drzavaTim2{ _utakmice.getElement2(i) };

			auto igraciDrzaveTim1{ drzavaTim1(brojPogodaka) };
			auto igraciDrzaveTim2{ drzavaTim2(brojPogodaka) };

			for (const auto& igrac : igraciDrzaveTim1) {
				temp.push_back(igrac);
			}

			for (const auto& igrac : igraciDrzaveTim2) {
				temp.push_back(igrac);
			}
		}

		return temp;
	}

private:
	void sendMail(
		const Igrac& igrac,
		const DrzavaTim& drzavaTim1,
		const DrzavaTim& drzavaTim2
	) const {
		std::thread emailThread{
			[&]() {
				// DON'T FORGET TO UNCOMMENT THIS LINE BELOW
				std::this_thread::sleep_for(2s);
				std::cout << "\nTo: " << igrac.getID() << "@euro2024.com\n";
				std::cout << "From: info@euro2024.com\n";
				std::cout << "Subject: Informacija\n";
				std::cout << "Postovani,\n";
				std::cout << "U " << igrac.getZadnjiPogodak().getVrijemePogotka() << " sati igrac " << igrac.getImePrezime();
				std::cout << " je zabiljezio svoj " << igrac.getBrojPogodaka() << '\n';
				std::cout << "pogodak na ovoj utakmici.\n";
				std::cout << "Trenutni rezultat je:\n";
				std::cout << Prventstvo::getFormattedResultStrForDrzaveTimovi(drzavaTim1, drzavaTim2);
				std::cout << "\nPuno srece u nastavku susreta.\n\n";
			}
		};

		emailThread.join();
	}
};

void main() {
	cout << PORUKA;
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
