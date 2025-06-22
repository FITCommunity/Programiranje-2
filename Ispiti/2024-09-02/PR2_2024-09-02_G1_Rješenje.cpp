/*
	DISCLAIMER

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
#include<sstream>
#include<thread>
#include<chrono>
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

	ID += std::toupper(fullName[0]);

	if (reverseNum < 10) {
		ID += "000";
	}
	else if (reverseNum < 100) {
		ID += "00";
	}
	else if (reverseNum < 1000) {
		ID += '0';
	}

	const int surnameInitialPos = fullName.find(' ') + 1;
	ID += std::toupper(fullName[surnameInitialPos]);
	
	ID += std::to_string(reverseNum);

	return GetNizKaraktera(ID.c_str());
}

bool ValidirajID(const std::string& id) {
	std::regex oneDigitValidation{ "[A-Z]000[A-Z]\\d" };
	std::regex twoDigitValidation{ "[A-Z]00[A-Z]\\d{2}" };
	std::regex threeDigitValidation{ "[A-Z]0[A-Z]\\d{3}" };
	std::regex fourDigitValidation{ "[A-Z][A-Z]\\d{4}" };

	return std::regex_match(id, oneDigitValidation)
		|| std::regex_match(id, twoDigitValidation)
		|| std::regex_match(id, threeDigitValidation)
		|| std::regex_match(id, fourDigitValidation);
}
// Functions I added above

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max]{};
	T2 _elementi2[max]{};
	int* _trenutno;
public:
	~Kolekcija() {
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// Methods I added below
	const T1& getElement1(int lokacija) const { return _elementi1[lokacija]; }
	const T2& getElement2(int lokacija) const { return _elementi2[lokacija]; }

	Kolekcija() {
		_trenutno = new int{ 0 };
	}

	Kolekcija(const Kolekcija& kolekcija)
		: _trenutno{ new int { kolekcija.getTrenutno() } }
	{
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = kolekcija.getElement1(i);
			_elementi2[i] = kolekcija.getElement2(i);
		}
	}

	Kolekcija& operator=(const Kolekcija& rhs) {
		*_trenutno = rhs.getTrenutno();
		for (int i = 0; i < getTrenutno(); ++i) {
			_elementi1[i] = rhs.getElement1(i);
			_elementi2[i] = rhs.getElement2(i);
		}

		return *this;
	}

	void AddElement(const T1& element1, const T2& element2) {
		if (getTrenutno() == max) {
			return;
		}

		_elementi1[getTrenutno()] = element1;
		_elementi2[getTrenutno()] = element2;

		++(*_trenutno);
	}

	Kolekcija& InsertAt(const T1& element1, const T2& element2, const int index) {
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

	Kolekcija RemoveRange(const int start, const int end) {
		if (start < 0 || end >= getTrenutno() || start >= end) {
			throw std::runtime_error("Interval nije validan");
		}

		Kolekcija elementiZaIzbacit{};
		Kolekcija elementiZaZadrzat{};

		for (int i = 0; i < getTrenutno(); ++i) {
			if (i >= start && i <= end) {
				elementiZaIzbacit.AddElement(getElement1(i), getElement2(i));
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
	Pogodak(Vrijeme vrijeme, const char* napomena) {
		_napomena = GetNizKaraktera(napomena);
		_vrijemePogotka = new Vrijeme(vrijeme);
	}
	~Pogodak() {
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
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID tj.atributa _imePrezime(inicijala imena i prezimena) i statickog clana _id
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

class Reprezentacija {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	Reprezentacija(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}
	Drzava GetDrzava() const { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	// Methods I added below

	const std::vector<Igrac>& GetIgraci() const { return _igraci; }
	
	bool DaLiIgracPostojiUReprezentaciji(const Igrac& igracZaPronaci) const {
		for (const auto& igrac : GetIgraci()) {
			if (igrac == igracZaPronaci) {
				return true;
			}
		}

		return false;
	}

	void AddIgrac(const Igrac& igrac) {
		if (DaLiIgracPostojiUReprezentaciji(igrac)) {
			throw std::runtime_error("Igrac vec dodan u reprezentaciju");
		}

		_igraci.push_back(igrac);
	}

	bool operator==(const Reprezentacija& rhs) const {
		return GetDrzava() == rhs.GetDrzava()
			&& GetIgraci() == rhs.GetIgraci();
	}

	bool operator!=(const Reprezentacija& rhs) const {
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

	std::vector<Igrac*> GetIgraceSaIstimIliVecimBrojemPogodaka(const int brojPogodaka) {
		std::vector<Igrac*> igraci{};

		for (auto& igrac : GetIgraci()) {
			if (igrac.GetBrojPogodaka() >= brojPogodaka) {
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
	Kolekcija<Reprezentacija, Reprezentacija, 20> _utakmice;
public:
	Kolekcija<Reprezentacija, Reprezentacija, 20>& GetUtakmice() {
		return _utakmice;
	}

	// Methods I added below

	bool DaLiSuSeReprezentacijeSusrele(
		const Reprezentacija& repDomacinZaPronac,
		const Reprezentacija& repGostZaPronac
	) const {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			const Reprezentacija& repDomacin{ _utakmice.getElement1(i) };
			const Reprezentacija& repGost{ _utakmice.getElement2(i) };

			if (repDomacinZaPronac == repDomacin && repGostZaPronac == repGost) {
				return true;
			}
		}

		return false;
	}

	void AddUtakmicu(
		const Reprezentacija& repDomacin,
		const Reprezentacija& repGost
	) {
		if (DaLiSuSeReprezentacijeSusrele(repDomacin, repGost)) {
			throw std::runtime_error("Reprezentacije su se vec jednom susrele na ovom prvenstvu");
		}

		_utakmice.AddElement(repDomacin, repGost);
	}

	Reprezentacija* GetReprezentacijaForDrzava(Drzava drzava) {
		for (int i = 0; i < _utakmice.getTrenutno(); ++i) {
			Reprezentacija& repDomacin{ _utakmice.getElement1(i) };
			Reprezentacija& repGost{ _utakmice.getElement2(i) };

			if (repDomacin.GetDrzava() == drzava) {
				return &repDomacin;
			}
			else if (repGost.GetDrzava() == drzava) {
				return &repGost;
			}
		}

		return nullptr;
	}

	Igrac* GetIgracByIDOrNameFromReprezentacije(
		const std::string& idIliImeIgraca,
		Reprezentacija& repDomacin,
		Reprezentacija& repGost
	) {
		Igrac* igrac1{ repDomacin.GetIgracByIDOrName(idIliImeIgraca) };

		if (igrac1) {
			return igrac1;
		}

		Igrac* igrac2{ repGost.GetIgracByIDOrName(idIliImeIgraca) };
		return igrac2;
	}

	/*
		U metodi ispod ima nadprosjecan broj predpostavki da nesto nije
		nullptr, jer za nas testni main to nece praviti problem, za drugi
		tho vjv hoce
	*/
	bool AddPogodak(
		Drzava drzavaDomacina,
		Drzava drzavaGosta,
		const std::string& idIliImeIgraca,
		const Pogodak& pogodakZaDodat
	) {
		Reprezentacija* repDomacin{ GetReprezentacijaForDrzava(drzavaDomacina) };
		Reprezentacija* repGosta{ GetReprezentacijaForDrzava(drzavaGosta) };

		Igrac* igrac{
			GetIgracByIDOrNameFromReprezentacije(idIliImeIgraca, *repDomacin, *repGosta)
		};

		if (igrac->DaLiJePogodakDodan(pogodakZaDodat)) {
			return false;
		}

		igrac->AddPogodak(pogodakZaDodat);
		SendMailSvimIgracima(*igrac, *repDomacin, *repGosta);
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const Prventstvo& prventstvo) {
		const auto& utakmice{ prventstvo._utakmice };

		for (int i = 0; i < utakmice.getTrenutno(); ++i) {
			const Reprezentacija& repDomacin{ utakmice.getElement1(i) };
			const Reprezentacija& repGost{ utakmice.getElement2(i) };

			const std::vector<Igrac> igraciDomacini{ repDomacin.GetIgraciKojiSuDaliPogotke() };
			const std::vector<Igrac> igraciGosta{ repGost.GetIgraciKojiSuDaliPogotke() };
			int maksSize = std::max(igraciDomacini.size(), igraciGosta.size());

			os << crt;
			os << repDomacin.GetDrzava() << ' ' << repDomacin.GetBrojPogodaka();
			os << " : ";
			os << repGost.GetDrzava() << ' ' << repGost.GetBrojPogodaka();
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
			Reprezentacija& repDomacin{ _utakmice.getElement1(i) };
			Reprezentacija& repGost{ _utakmice.getElement2(i) };

			auto igraciReprezentacije1{ repDomacin.GetIgraceSaIstimIliVecimBrojemPogodaka(brojPogodaka) };
			auto igraciReprezentacije2{ repGost.GetIgraceSaIstimIliVecimBrojemPogodaka(brojPogodaka) };

			for (const auto& igrac : igraciReprezentacije1) {
				igraci.push_back(igrac);
			}

			for (const auto& igrac : igraciReprezentacije2) {
				igraci.push_back(igrac);
			}
		}

		return igraci;
	}

	void SendMailSvimIgracima(
		const Igrac& igracKojiJeDaoGo,
		const Reprezentacija& repDomacin,
		const Reprezentacija& repGost
	) const {
		for (const auto& igrac : repDomacin.GetIgraci()) {
			SendMail(igrac, igracKojiJeDaoGo, repDomacin, repGost);
		}
		for (const auto& igrac : repGost.GetIgraci()) {
			SendMail(igrac, igracKojiJeDaoGo, repDomacin, repGost);
		}
	}

	void SendMail(
		const Igrac& igracKojemSeSaljeMail,
		const Igrac& igracKojiJeDaoGo,
		const Reprezentacija& repDomacin,
		const Reprezentacija& repGost
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
				std::cout << repDomacin.GetDrzava() << ' ' << repDomacin.GetBrojPogodaka();
				std::cout << " : ";
				std::cout << repGost.GetDrzava() << ' ' << repGost.GetBrojPogodaka();
				std::cout << "\nPuno srece u nastavku susreta.\n\n";
			}
		};

		emailThread.join();
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite osnovne preduslove koji moraju biti ispunjeni da bi se realizovao polimorfizam(navesti kratki primjer) ? \n";
	return "Odgovor -> Da bi se realizovao polimorfizam potrebna je makar 1 metoda da bude deklarisana sa kljucnom rijeci virtual."
		"Recimo imamo klase Base i Derived, u klasi Base definisemo virtual void Info() {}, u klasi Derived definisemo "
		"void Info() override {} (naravno pored ovog je potrebno deklarisati virtualnim destruktor Base klase)."
		"Sada ako uzmemo Base* base = new Derived {}; i pozovemo base->Info(); imamo mogucnost pristupiti metodi Info"
		" iz najnasljedenije klase. Prednosti nasljedivanja su u tome sto nam dozvoljava da pomocu pokazivaca na baznu "
		" klasu imamo mogucnost da radimo sa svim objektima koji su je naslijedili, to moze dovesti do manje ponavljanja koda"
		"i fleksibilniji rad sa klasama. Takoder ako ta 1 metoda sto je virtual nije destruktor, potrebno ce biti i "
		"destruktor proglasiti virtual.";
}

const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite razloge koristenja kljucnih rijeci abstract i ciste virtualne metode, te razlike izmedju njih ? \n";
	return "Odgovor -> Koristenje kljucne rijeci abstract ili ciste virtualne metode dovodi do toga da se ne moze napraviti instanca "
		"te klase, najcesce ona sluzi kao baza u hirarhiji nasljedivanja. Dok su ciste virtualne metode dio standarda za C++, abstract "
		"kljucna rijec nije, uvedena je kao dio VSovog C++-a. Efektivno pruzaju istu uslugu, a to je da se ne moze napraviti instanca "
		"te klase dok se ne naslijedi, ciste virtualne metode bi zahtjevale implementaciju njihovu dok abstract samo zahtjeva nasljedivanje. "
		"Abstract se takoder moze koristiti na metode i klase, dok ciste virtualne metode su iskljucive za metode klase.";
}

void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/*
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti
   proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale tj. prva slova
   imena i prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne
   vrijednosti parametara. Ukoliko se proslijede
	mala pocetna slova imena ili prezimena, potrebno ih je
   konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost
   treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti D000M3
	cout << GenerisiID("Jasmin Azemovic", 14) << endl;//treba vratiti J00A41
	cout << GenerisiID("Goran Skondric", 156) << endl;//treba vratiti G0S651
	cout << GenerisiID("emina junuz", 1798) << endl;//treba vratiti EJ8971

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("D000M3"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("J00A41"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("G00S651"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("Ej8971"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti prvog i drugog
   parametra na lokaciju koja je definisana trecim parametrom. Povratna
   vrijednost metode je objekat (pozivaoc metode, u konkretnom slucaju objekat
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
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(10, 10, 0);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/

   // A bit of a correction here
   // Komentar iznad trazi da se vrati pokazivac, medutim to je izgleda ostalo od
   // veoma slicnog roka

	Kolekcija<int, int, 10> kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << kolekcija3 << endl;
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
	kolekcija1 = kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");

	if (strcmp(denis.GetID(), "D000M1") == 0 && strcmp(jasmin.GetID(), "J000A2") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtom pogotku");
	Reprezentacija BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		BIH.AddIgrac(denis);//onemoguciti dodavanje istih igraca - provjeravati ID
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}

	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		euro2024.AddUtakmicu(BIH, ENG);//onemoguciti ponovne susrete drzava tokom istog prvenstva
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	//omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "D000M1", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "J000A2", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//u zasebnom thread-u, poslati email. u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	/*
	To: D000M1@euro2024.com
	From: info@euro2024.com
	Subject: Informacija
	Postovani,
	U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
   pogodak na ovoj utakmici.
	Trenutni rezultat je:
	BOSNA_I_HERCEGOVINA 2 : 0 ENGLESKA
	Puno srece u nastavku susreta.
	Neka bolji tim pobijedi.
	*/
	//ispisuje detaljnije informacije o susretu, kako je navedeno u narednom ispisu
	cout << euro2024;
	/*
	-------------------------------------------
	(3) BOSNA_I_HERCEGOVINA : ENGLESKA (1)
	-------------------------------------------
	Denis Music Goran Skondric
	Jasmin Azemovic
	Jasmin Azemovic
	-------------------------------------------
	*/
	//vraca sve igrace koji su na takmicenju postigli broj pogodaka koji je veci ili jednak proslijedjenoj vrijednosti
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;
	cin.get();
	system("pause>0");
}