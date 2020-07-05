#include<iostream>
#include<string>
#include<vector>
#include<mutex>
#include<thread>
#include<regex>
#include<iterator>
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum GodinaStudija { PRVA, DRUGA, TRECA };
const char* ispisGodine[] = { "PRVA" ," DRUGA", "TRECA" };


char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Dictionary {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Dictionary() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	Dictionary(const Dictionary& original) : _trenutno(new int(*original._trenutno))
	{
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (int i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	Dictionary& operator=(const Dictionary& druga)
	{
		if (this != &druga)
		{
			if (*_trenutno != 0)
			{
				delete[]_elementi1;
				delete[]_elementi2;
			}
			*_trenutno = *druga._trenutno;
			_elementi1 = new T1[*_trenutno];
			_elementi2 = new T2[*_trenutno];
			for (int i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = druga._elementi1[i];
				_elementi2[i] = druga._elementi2[i];
			}
		}
		return *this;
	}
	~Dictionary() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno()const { return *_trenutno; }
	void AddElement(T1 el1, T2 el2)
	{
		T1* temp1 = new T1[*_trenutno + 1];
		T2* temp2 = new T2[*_trenutno + 1];
		for (int i = 0; i < *_trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;
		temp1[*_trenutno] = el1;
		temp2[*_trenutno] = el2;
		(*_trenutno)++;
		_elementi1 = temp1; temp1 = nullptr;
		_elementi2 = temp2; temp2 = nullptr;
	}
	Dictionary<T1, T2> getRange(int pocetak, int kraj)
	{
		if (pocetak<0 || pocetak>* _trenutno || kraj > * _trenutno || kraj<0 || pocetak>kraj)
			throw exception("Niste unijeli validan range");

		Dictionary<T1, T2> nova;
		for (pocetak; pocetak < kraj; pocetak++)
		{
			nova.AddElement(_elementi1[pocetak], _elementi2[pocetak]);
		}
		return nova;
	}
	friend ostream& operator<< (ostream& COUT, const Dictionary& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << "    " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& original)
	{
		_dan = new int(*original._dan);
		_mjesec = new int(*original._mjesec);
		_godina = new int(*original._godina);
		_sati = new int(*original._sati);
		_minuti = new int(*original._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& drugi)
	{
		if (this != &drugi)
		{
			*_dan = *drugi._dan;
			*_mjesec = *drugi._mjesec;
			*_godina = *drugi._godina;
			*_sati = *drugi._sati;
			*_minuti = *drugi._minuti;
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	char* ToCharArray()
	{
		string sve = to_string(*_dan) + "." + to_string(*_mjesec) + "." + to_string(*_godina) + "-> " + to_string(*_sati) + ":" + to_string(*_minuti);
		int vel = sve.length() + 1;
		char* temp = new char[vel];
		strcpy_s(temp, vel, sve.c_str());
		return temp;
	}
	int toMinute()const {
		return *_godina * 365 * 24 * 60 + *_mjesec * 30 * 24 * 60 + *_dan * 24 * 60 + *_sati * 60 + *_minuti;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << "-> " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
};

int GetRazlika(DatumVrijeme& prvi, DatumVrijeme& drugi)
{
	return abs(prvi.toMinute() - drugi.toMinute());
}

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& original) : _naziv(Alociraj(original._naziv)), _ocjena(original._ocjena), _napomena(original._napomena) {}
	Predmet& operator=(const Predmet& drugi)
	{
		if (this != &drugi)
		{
			delete[] _naziv;
			_naziv = Alociraj(drugi._naziv);
			_napomena = drugi._napomena;
			_ocjena = drugi._ocjena;
		}
		return *this;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }
	void SetOcjena(int ocjena) { _ocjena = ocjena; }
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
	bool operator==(const Predmet& drugi)
	{
		return strcmp(_naziv, drugi._naziv) == 0 && _ocjena == drugi._ocjena && _napomena == drugi._napomena;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << "Predmet -> " << obj._naziv << "   Ocjena (" << obj._ocjena << ")    Napomena -> " << obj._napomena << endl;
		return COUT;
	}
};
class Uspjeh {
	GodinaStudija* _godina;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Dictionary<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(GodinaStudija godina) {
		_godina = new GodinaStudija(godina);
	}
	Uspjeh(const Uspjeh& original) : _godina(new GodinaStudija(*original._godina)), _predmeti(original._predmeti) {}
	Uspjeh& operator=(const Uspjeh& drugi)
	{
		if (this != &drugi)
		{
			delete _godina;
			_godina = new GodinaStudija(*drugi._godina);
			_predmeti = drugi._predmeti;
		}
		return *this;
	}
	~Uspjeh() { delete _godina; _godina = nullptr; }
	Dictionary<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	GodinaStudija* GetGodinaStudija() { return _godina; }
	float GetProsjek()
	{
		float prosjek = 0;
		for (int i = 0; i < _predmeti.getTrenutno(); i++)
		{
			prosjek += _predmeti.getElement1(i).GetOcjena();
		}
		return prosjek / _predmeti.getTrenutno();
	}
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << "Godina studija -> " << ispisGodine[*obj._godina] << endl;
		COUT << "::: PREDMETI ::: " << crt;
		for (int i = 0; i < obj._predmeti.getTrenutno(); i++)
		{
			COUT << "Predmet -> " << obj._predmeti.getElement1(i) << "    Datum evidentiranja -> " << obj._predmeti.getElement2(i) << endl;
		}
		return COUT;
	}
};

mutex mjutegz;
class Student {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
	bool ValidanEmail(string mail)
	{
		return regex_match(mail, regex("[a-zA-Z]{4,15}.[a-zA-Z]{4,15}@(hotmail.com|outlook.com|fit.ba)"));
	}
	void PosaljiMail(GodinaStudija godina)
	{
		mjutegz.lock();

		cout << "FROM: info@fit.ba\n";
		cout << "TO: " << _emailAdresa << endl;
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << ispisGodine[godina] << " studija" << endl;
		cout << "Pozdrav." << crt;

		mjutegz.unlock();
	}
	void PosaljiSMS(GodinaStudija godina, float prosjek)
	{
		mjutegz.lock();

		if (prosjek > 8.0)
		{
			cout << "Saljem SMS -> " << _brojTelefona << endl;
			cout << "Cestitamo na uspjehu " << prosjek << " ostvaren u " << ispisGodine[godina] << " godini studija" << crt;
		}

		mjutegz.unlock();
	}
public:
	Student(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		if (ValidanEmail(emailAdresa))
			_emailAdresa = emailAdresa;
		else
			_emailAdresa = "not_set@fit.ba";
		_brojTelefona = brojTelefona;
	}
	Student(const Student& original) : _imePrezime(Alociraj(original._imePrezime)), _emailAdresa(original._emailAdresa), _brojTelefona(original._brojTelefona), _uspjeh(original._uspjeh) {}
	Student& operator=(const Student& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(drugi._imePrezime);
			_emailAdresa = drugi._emailAdresa;
			_brojTelefona = drugi._brojTelefona;
			_uspjeh = drugi._uspjeh;
		}
		return *this;
	}
	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
	friend ostream& operator<< (ostream& COUT, Student& obj) {
		COUT << "Student -> " << obj._imePrezime << "    Email -> " << obj._emailAdresa << "    Kontakt -> " << obj._brojTelefona << endl;
		COUT << "::: USPJEH STUDENTA :::" << crt;
		ostream_iterator<Uspjeh> out_iterator(COUT, "\n");
		copy(obj._uspjeh.begin(), obj._uspjeh.end(), out_iterator);
		return COUT;
	}


	bool AddPredmet(Predmet& p, GodinaStudija godina, DatumVrijeme& d)
	{
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetGodinaStudija() == godina)
			{
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					if (_uspjeh[i].GetPredmeti()->getElement1(j) == p)
						return false;
				}

				int trenutno = _uspjeh[i].GetPredmeti()->getTrenutno();
				if (GetRazlika(_uspjeh[i].GetPredmeti()->getElement2(trenutno - 1), d) < 60)
					return false;

				_uspjeh[i].GetPredmeti()->AddElement(p, d);
				{
					thread t1(&Student::PosaljiMail, this, godina);
					t1.join();
					this_thread::sleep_for(chrono::seconds(2));
					float prosjek = _uspjeh[i].GetProsjek();
					thread t2(&Student::PosaljiSMS, this, godina, prosjek);
					t2.join();
				}
				return true;
			}
		}

		Uspjeh u(godina);
		u.GetPredmeti()->AddElement(p, d);
		_uspjeh.push_back(u);
		{
			thread t1(&Student::PosaljiMail, this, godina);
			t1.join();
			this_thread::sleep_for(chrono::seconds(2));
			float prosjek = u.GetProsjek();
			thread t2(&Student::PosaljiSMS, this, godina, prosjek);
			t2.join();
		}
		return true;
	}

	int BrojPonavljanjaRijeci(string rijec)
	{
		regex pravilo(rijec);
		int brojPonavljanja = 0;
		{
			for (int i = 0; i < _uspjeh.size(); i++)
			{
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					string tekst = _uspjeh[i].GetPredmeti()->getElement1(j).GetNapomena();
					sregex_iterator it_poc(tekst.begin(), tekst.end(), pravilo);
					sregex_iterator it_kraj;
					while (it_poc != it_kraj)
					{
						it_poc++;
						brojPonavljanja++;
					}
				}
			}
		}
		return brojPonavljanja;
	}

	vector<Predmet> operator()(DatumVrijeme* pocetak, DatumVrijeme* kraj)
	{
		vector<Predmet> novi;
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				if (_uspjeh[i].GetPredmeti()->getElement2(j).toMinute() > pocetak->toMinute() && kraj->toMinute() > _uspjeh[i].GetPredmeti()->getElement2(j).toMinute())
					novi.push_back(_uspjeh[i].GetPredmeti()->getElement1(i));
			}
		}
		return novi;
	}

	Uspjeh* operator[](const char* godina)
	{
		Uspjeh* u = nullptr;
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (strcmp(ispisGodine[*_uspjeh[i].GetGodinaStudija()], godina) == 0)
				u = &_uspjeh[i];
		}
		return u;
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
	cout << "NA KRAJU ISPITA, RAD PREDAJTE U ODGOVARAJUCI FOLDER NA FTP SERVERU (INTEGRALNI)!" << endl;
	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);
	//funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
	//voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca iskazane kao dvije cifre
	cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
	temp = datum05072019_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31

	const int DictionaryTestSize = 9;
	Dictionary<int, int> Dictionary1;
	for (size_t i = 0; i < DictionaryTestSize; i++)
		Dictionary1.AddElement(i + 1, i * i);

	try {
		//vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
		//funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
		Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
		cout << opseg << endl;
		Dictionary1.getRange(7, 11);
	}
	catch (exception & err) {
		cout << err.what() << endl;
	}
	cout << Dictionary1 << endl;

	Dictionary<int, int> Dictionary2 = Dictionary1;
	cout << Dictionary2 << crt;

	Dictionary<int, int> Dictionary3;
	Dictionary3 = Dictionary1;
	cout << Dictionary3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet MAT("Matematika", 7, "Ucesce na takmicenju takmicenju takmicenju"),
		UIT("Uvod u informacijske tehnologije", 9),
		RM("Racunarske mreze", 8),
		EN("Engleski jezik", 6);
	UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << MAT << endl;

	/*
	email adresa mora biti u formatu: texte-texte@hotmail.com nakon cega slijedi neka od sljedecih domena: hotmail.com ili outlook.com ili fit.ba.
	Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
	za provjeru koristiti regex
	*/
	Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
	Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
	Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");



	/*
	uspjeh se dodaje za svaki predmet na nivou godine studija.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jedne godine,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 1 sat).
	godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu godinu, pa onda za prvu godinu i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati MAT jer je vec dodana u prvoj godini
	if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231)) //ne doda jer je iznad dodao MAT
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115)) //ne doda jer nije prosao minut od MAT GORNJE
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu se salje email sa sadrzajem:
	FROM:info@fit.ba
	TO: emailStudenta
	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
	Pozdrav.
	FIT Team.
	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS sa sadrzajem: "Svaka cast za uspjeh X.X ostvaren u X godini studija".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	cout << "USPJEH ISPISATI KORISTEĆI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
	for (Predmet u : jasminUspjeh)
		cout << u << endl;

	Uspjeh* uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
	if (uspjeh_I_godina != nullptr)
		cout << *uspjeh_I_godina << endl;

	system("pause>0");
}