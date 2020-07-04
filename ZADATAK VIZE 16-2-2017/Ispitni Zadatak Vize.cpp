#include<iostream>
#include<string>
#include<vector>
#include<exception>
#include<thread>
#include<mutex>
#include<regex>
using namespace std;




//main je malo tricky postavljen pa treba paziti koje je vrijednosti poprimio odredjeni objekat i gdje se dodaje 


const char* crt = "\n-----------------------------------------------\n";

enum Sortiranje { RASTUCI, OPADAJUCI };
enum Status { ZAHTJEV_ZAPRIMLJEN, IZDATA, ODBIJENA, ODUSTAO, ISTEKLA, PONISTENA };
enum Drzava { SAD, AUSTRALIJA, ENGLESKA };
const char* ispisStatusa[] = { "ZAHTJEV_ZAPRIMLJEN"," ODUSTAO", "ODBIJENA", "IZDATA", "ISTEKLA", "PONISTENA" };
const char* ispisDrzava[] = { "SAD", "AUSTRALIJA", "ENGLESKA" };
char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& original)
	{
		_dan = new int(*original._dan);
		_mjesec = new int(*original._mjesec);
		_godina = new int(*original._godina);
	}
	Datum& operator=(const Datum& drugi)
	{
		if (this != &drugi)
		{
			*_dan = *drugi._dan;
			*_mjesec = *drugi._mjesec;
			*_godina = *drugi._godina;
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	bool operator==(const Datum& drugi)
	{
		return *_dan == *drugi._dan && *_mjesec == *drugi._mjesec && *_godina == *drugi._godina;
	}
	Datum& operator++()
	{
		(*_dan)++;
		return *this;
	}
	int GetYears()const {
		return *_godina;
	}
	bool operator>(const Datum& drugi)
	{
		return (*_godina * 365 + *_mjesec * 30 + *_dan) > (*drugi._godina * 365 + *drugi._mjesec * 30 + *drugi._dan);
	}
	friend ostream& operator<< (ostream& COUT, Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
};

template<class T1, class T2, int max>
class FITKolekcija {
	T1* _elementi1[max];
	T2* _elementi2[max];
	int _trenutno;
	bool Uslov(Sortiranje sort, int i)
	{
		if (sort == RASTUCI && *_elementi1[i] > * _elementi1[i + 1])
			return true;
		if (sort == OPADAJUCI && *_elementi1[i] < * _elementi1[i + 1])
			return true;
		return false;
	}
	void ADD(T1 el1, T2 el2)
	{
		_elementi1[_trenutno] = new T1(el1);
		_elementi2[_trenutno] = new T2(el2);
		_trenutno++;
	}
public:
	FITKolekcija() {
		for (size_t i = 0; i < max; i++) {
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija& original) : _trenutno(original._trenutno)
	{
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = new T1(*original._elementi1[i]);
			_elementi2[i] = new T2(*original._elementi2[i]);
		}

		for (int i = _trenutno; i < max; i++)
		{
			 _elementi1[i]=nullptr;
			 _elementi2[i]=nullptr;
		}	
	}
	FITKolekcija& operator=(const FITKolekcija& druga)
	{
		if (this != &druga)
		{
			if (_trenutno != 0)
			{
				for (int i = 0; i < _trenutno; i++)
				{
					delete _elementi1[i];
					delete _elementi2[i];
				}
			}
			_trenutno = druga._trenutno;
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = new T1(*druga._elementi1[i]);
				_elementi2[i] = new T2(*druga._elementi2[i]);
			}
		}
		return *this;
	}
	~FITKolekcija() {
		for (int i = 0; i < max; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	T1** GetT1() { return _elementi1; }
	T2** GetT2() { return _elementi2; }
	int GetTrenutno()const { return _trenutno; }
	void Dodaj(T1 el1, T2 el2)
	{
		if (_trenutno >= max)
			throw exception("Dosegli ste maksimum kolekcije!");
		ADD(el1, el2);
	}
	void Sortiraj(Sortiranje sort)
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < _trenutno-1; i++)
			{
				if (Uslov(sort, i))
				{
					T1 temp1 = *_elementi1[i];
					*_elementi1[i] = *_elementi1[i + 1];
					*_elementi1[i + 1] = temp1;

					T2 temp2 = *_elementi2[i];
					*_elementi2[i] = *_elementi2[i + 1];
					*_elementi2[i + 1] = temp2;
					prolaz = true;
				}
			}
		}
	}
	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj) {
		for (int i = 0; i < obj._trenutno; i++)
			COUT << *obj._elementi1[i] << "   " << *obj._elementi2[i] << endl;
		return COUT;
	}
};


class Viza {
protected:
	Drzava _drzava;
	Datum _vazenjeOD;
	Datum _vazenjeDO;
	char* _napomena;
	// string se odnosi na razlog promjene statusa, a moguće je samo 10 izmjena statusa
	FITKolekcija<Status, string, 10> _statusi;
public:
	Viza(Drzava drzava, Datum _OD, Datum _DO,const char* napomena = nullptr) :_vazenjeDO(_DO), _vazenjeOD(_OD)
	{
		if (napomena != nullptr) {
			_napomena = Alociraj(napomena);
		}
		else
			_napomena = nullptr;
		_drzava = drzava;
	}
	Viza(const Viza& original) : _drzava(original._drzava), _vazenjeOD(original._vazenjeOD), _vazenjeDO(original._vazenjeDO), _napomena(Alociraj(original._napomena)), _statusi(original._statusi) {}
	Viza& operator=(const Viza& druga)
	{
		if (this != &druga)
		{
			delete[] _napomena;
			_napomena = Alociraj(druga._napomena);
			_drzava = druga._drzava;
			_vazenjeOD = druga._vazenjeOD;
			_vazenjeDO = druga._vazenjeDO;
			_statusi = druga._statusi;
		}
		return *this;
	}
	~Viza() { delete[] _napomena; _napomena = nullptr; }
	Datum GetVazenjeOD() { return _vazenjeOD; }
	Datum GetVazenjeDO() { return _vazenjeDO; }
	char* GetNapomena() { return _napomena; }
	Drzava GetDrzavaVize() { return _drzava; }
	FITKolekcija<Status, string, 10>& GetStatuse() { return _statusi; }
	virtual void Info() = 0;
	friend ostream& operator<<(ostream& COUT, Viza& obj)
	{
		COUT << "Viza za drzavu -> " << ispisDrzava[obj._drzava] << "  Viza traje od -> " << obj._vazenjeOD << "   Viza traje do -> " << obj._vazenjeDO << endl;
		COUT <<"Napomena za vizu -> "<< ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "::: STATUSI VIZE :::" << crt;
		for (int i = 0; i < obj._statusi.GetTrenutno(); i++)
		{
			COUT << "Status vize -> " << ispisStatusa[*obj._statusi.GetT1()[i]] << "    Razlog promjene ->  " << *obj._statusi.GetT2()[i] << endl;
		}
		return COUT;
	}
};

class PoslovnaViza :public Viza {
	string _kompanija; //naziv kompanije koja potvrđuje da posluje sa aplikantom
public:
	void Info() {}
	PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija, char* napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
		_kompanija = kompanija;
	}
	PoslovnaViza(const PoslovnaViza& original) : Viza(original), _kompanija(original._kompanija){}
	PoslovnaViza& operator=(const PoslovnaViza& druga)
	{
		if (this != &druga)
		{
			Viza::operator=(druga);
			_kompanija = druga._kompanija;
		}
		return *this;
	}
	friend ostream& operator << (ostream& COUT, PoslovnaViza& obj) {
		COUT << "Viza za drzavu -> " << ispisDrzava[obj._drzava] << "  Viza traje od -> " << obj._vazenjeOD << "   Viza traje do -> " << obj._vazenjeDO << endl;
		COUT << "Napomena za vizu -> " << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "Viza za kompaniju -> " << obj._kompanija << endl;
		COUT << "::: STATUSI VIZE :::" << crt;
		for (int i = 0; i < obj._statusi.GetTrenutno(); i++)
		{
			COUT << "Status vize -> " << ispisStatusa[*obj._statusi.GetT1()[i]] << "    Razlog promjene ->  " << *obj._statusi.GetT2()[i] << endl;
		}
		return COUT;
	}

};
class TuristickaViza : public Viza {
	string _adresa; //adresa hotele ili drugog smještaja na kojoj će aplikant boraviti
public:
	void Info() {}
	TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa, char* napomena = nullptr) : Viza(drzava, _OD, _DO, napomena) {
		_adresa = adresa;
	}
	TuristickaViza(const TuristickaViza& original) : Viza(original), _adresa(original._adresa) {}
	TuristickaViza& operator=(const TuristickaViza& druga)
	{
		if (this != &druga)
		{
			Viza::operator=(druga);
			_adresa = druga._adresa;
		}
		return *this;
	}
	friend ostream& operator << (ostream& COUT, TuristickaViza& obj) 
	{
		COUT << "Viza za drzavu -> " << ispisDrzava[obj._drzava] << "  Viza traje od -> " << obj._vazenjeOD << "   Viza traje do -> " << obj._vazenjeDO << endl;
		COUT << "Napomena za vizu -> " << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "Adresa -> " << obj._adresa << endl;
		COUT << "::: STATUSI VIZE :::" << crt;
		for (int i = 0; i < obj._statusi.GetTrenutno(); i++)
		{
			COUT << "Status vize -> " << ispisStatusa[*obj._statusi.GetT1()[i]] << "    Razlog promjene ->  " << *obj._statusi.GetT2()[i] << endl;
		}
		return COUT;
	}
};


mutex mjuteks;
class Aplikant {
	char* _imePrezime;
	Datum* _datumRodjenja;
	char* _brojPasosa;
	vector<Viza*> _vize;
	void Print(Viza* viza)
	{
		mjuteks.lock();
		PoslovnaViza* poslovna = dynamic_cast<PoslovnaViza*>(viza);//cast koristimo da bi vidjeli je li poslovna ili turisticka
		if (poslovna != nullptr)
			cout << *poslovna << crt;

		TuristickaViza* turisticka = dynamic_cast<TuristickaViza*>(viza);
		if (turisticka != nullptr)
			cout << *turisticka << crt;
		
		mjuteks.unlock();
	}
public:
	Aplikant(const char* imePrezime, Datum datumRodjenja, const char* brPasosa) {
		_imePrezime = Alociraj(imePrezime);
		_brojPasosa = Alociraj(brPasosa);
		_datumRodjenja = new Datum(datumRodjenja);
	}
	Aplikant(const Aplikant& original) : _imePrezime(Alociraj(original._imePrezime)), _datumRodjenja(new Datum(*original._datumRodjenja)), _brojPasosa(Alociraj(original._brojPasosa))
	{
		for (int i = 0; i < original._vize.size(); i++)
		{
			PoslovnaViza* poslovna = dynamic_cast<PoslovnaViza*>(original._vize[i]);
			if (poslovna != nullptr)
				_vize.push_back(new PoslovnaViza(*poslovna));

			TuristickaViza* turisticka = dynamic_cast<TuristickaViza*>(original._vize[i]);
			if (turisticka != nullptr)
				_vize.push_back(new TuristickaViza(*turisticka));
		}
	}
	Aplikant& operator=(const Aplikant& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			delete _datumRodjenja;
			delete[] _brojPasosa;
			_brojPasosa = Alociraj(drugi._brojPasosa);
			_imePrezime = Alociraj(drugi._imePrezime);
			_datumRodjenja = new Datum(*drugi._datumRodjenja);
			for (int i = 0; i < _vize.size(); i++)
			{
				delete _vize[i];
			}
			_vize.clear();
			for (int i = 0; i < drugi._vize.size(); i++)
			{
				PoslovnaViza* poslovna = dynamic_cast<PoslovnaViza*>(drugi._vize[i]);
				if (poslovna != nullptr)
					_vize.push_back(new PoslovnaViza(*poslovna));

				TuristickaViza* turisticka = dynamic_cast<TuristickaViza*>(drugi._vize[i]);
				if (turisticka != nullptr)
					_vize.push_back(new TuristickaViza(*turisticka));
			}
		}
		return *this;
	}
	~Aplikant() {
		delete[]_imePrezime; _imePrezime = nullptr;
		delete[]_brojPasosa; _brojPasosa = nullptr;
		delete _datumRodjenja; _datumRodjenja = nullptr;
		for (size_t i = 0; i < _vize.size(); i++)
		{
			delete _vize[i]; _vize[i] = nullptr;
		}
	}
	char* GetImePrezime() { return _imePrezime; }
	Datum& GetDatumRodjenja() { return *_datumRodjenja; }
	vector<Viza* > GetVize() { return _vize; }
	friend ostream& operator << (ostream& COUT, Aplikant& obj) {
		COUT << "Aplikant -> " << obj._imePrezime << "   Datum rodjenja -> " << *obj._datumRodjenja << "   Broj pasosa -> " << obj._brojPasosa << endl;
		COUT << "::: VIZE APLIKANTA ::: " << crt;
		for (int i = 0; i < obj._vize.size(); i++)
		{
			COUT << *obj._vize[i] << crt;
		}
		return COUT;
	}
	
	bool DodajVizu(Viza* viza)
	{
		if (_datumRodjenja->GetYears() >= 2010)//ako je osoba ta mladja od 10 godina
			return false;
		for (int i = 0; i < _vize.size(); i++)
		{
			if (viza->GetVazenjeOD() > _vize[i]->GetVazenjeOD() && _vize[i]->GetVazenjeDO() > viza->GetVazenjeDO())//provjera da li traje tokom neke druge
			{
				int trenutno = _vize[i]->GetStatuse().GetTrenutno();
				if (*_vize[i]->GetStatuse().GetT1()[trenutno - 1] == IZDATA)
					return false;
			}

			if (viza->GetDrzavaVize() == SAD)//ako je proslijedjena viza SAD onda se izvrsavaju provjere ispod
			{
				for (int j = 0; j < viza->GetStatuse().GetTrenutno(); j++)
				{
					if (*viza->GetStatuse().GetT1()[j] == PONISTENA)
						return false;
				}
			}
		}

//ukoliko sve provjere prodje uspjesno onda opet koristimo cast da bi dodali onu koju zapravo i treba
		PoslovnaViza* poslovna = dynamic_cast<PoslovnaViza*>(viza);
		if (poslovna != nullptr)
		{
			_vize.push_back(new PoslovnaViza(*poslovna));
			return true;
		}

		TuristickaViza* turisticka = dynamic_cast<TuristickaViza*>(viza);
		if (turisticka != nullptr)
		{
			_vize.push_back(new TuristickaViza(*turisticka));
			return true;
		}
		return false;
	}

	bool DodajStatus(Viza* viza, Status status, string razlogPromjene="nije navedeno")
	{
		for (int i = 0; i < _vize.size(); i++)
		{
			int trenutno = _vize[i]->GetStatuse().GetTrenutno();
			
			if (_vize[i]->GetDrzavaVize() == viza->GetDrzavaVize() && trenutno == 0 && status == ZAHTJEV_ZAPRIMLJEN)//ako je ista drzava i nema statusa  a status koji se dodaje je prvi po redu onda doda
			{
				_vize[i]->GetStatuse().Dodaj(status, razlogPromjene);
				viza->GetStatuse().Dodaj(status, razlogPromjene);
				return true;
			}

			if (*_vize[i]->GetStatuse().GetT1()[trenutno - 1] < status && _vize[i]->GetDrzavaVize() == viza->GetDrzavaVize())// ako je ista viza i status koji se dodaje veci od zadnjeg dodanog
			{
				_vize[i]->GetStatuse().Dodaj(status, razlogPromjene);
				viza->GetStatuse().Dodaj(status, razlogPromjene);
				return true;
			}
		}
		return false;
	}

	void PrintajVizu(Viza* viza)
	{
		for (int i = 0; i < _vize.size(); i++)
		{
			if (_vize[i]->GetDrzavaVize() == viza->GetDrzavaVize())
			{
				thread t1(&Aplikant::Print, this, viza);
				this_thread::sleep_for(chrono::seconds(3));
				t1.join();
			}
		}
	}

	vector<Viza*> GetVizeByDrzava(Drzava drzava, Status status)
	{
		vector<Viza*> novi;
		for (int i = 0; i < _vize.size(); i++)
		{
			if (_vize[i]->GetDrzavaVize() == drzava)
			{
				for (int j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == status)
					{
						novi.push_back(_vize[i]);
					}
				}
			}
		}
		return novi;
	}
	void ZamijeniRijec(string trazena, string nova)
	{
		regex pravilo(trazena);
		for (int i = 0; i < _vize.size(); i++)
		{
			for (int j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
			{
				*_vize[i]->GetStatuse().GetT2()[j] = regex_replace(*_vize[i]->GetStatuse().GetT2()[j], pravilo, nova);
			}
		}

	}
};

void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/



	Datum danas(15, 2, 2017);
	Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
	Datum prekosutra;
	Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);


	prekosutra = danas;
	if (prekosutra == danas)
		cout << "Datumi su jednaki" << endl;
	cout << danas << endl << sutra << endl << prekosutra << crt;

	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int, 7> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//NA KOJI NAČIN ĆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
	brojevi.Sortiraj(RASTUCI);
	cout << brojevi << crt;
	brojevi.Sortiraj(OPADAJUCI);
	cout << brojevi << crt;

	try
	{
		//U SLUČAJU PREKORAČENJA DEFINISANE VELIČINE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
		brojevi.Dodaj(v13, v196);
	}
	catch (exception & err)
	{
		cout << "Error -> " << err.what() << endl;
	}

	Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
	PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft");
	TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");

	/*
	NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
	- JE APLIKANT MLAĐI OD 10 GODINA
	- U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEĆA (POJAM VAŽEĆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.
	- JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)
	*/
	if (jasmin.DodajVizu(&poslovna))
		cout << "Podaci o vizi uspjesno zaprimljeni" << endl;

	if (jasmin.DodajVizu(&turisticka))
		cout << "Podaci o vizi uspjesno zaprimljeni" << endl;
	/*
	STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
	- NIJE MOGUĆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
	- NIJE MOGUĆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA
	*/
	if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin.GetImePrezime() << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


	if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


	if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	if (jasmin.DodajStatus(&turisticka, IZDATA)) {
		cout << "Status vize uspijesno promijenjen" << endl;
		//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
		jasmin.PrintajVizu(&turisticka);
	}
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
	////VRAĆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREĐENU DRŽAVU, A KOJE SU IMALE ODREĐENI STATUS
	vector<Viza*> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);

	/*for (int i = 0; i < jasminVize.size(); i++) //dodano zbog testiranja 
	{
		cout << *jasminVize[i] << crt;
	}*/

	////UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
	jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");

	Aplikant denis(jasmin);
	cout << denis;

	system("pause>0");

}