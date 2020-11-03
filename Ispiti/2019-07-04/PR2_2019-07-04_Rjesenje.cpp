#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <exception>
#include <thread>
#include <mutex>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ?E BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJE?ILO GUBLJENJE URA?ENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI?NI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLU?AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO?NE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA?ENO.
****************************************************************************/

const char* crt = "\n-------------------------------------------\n";
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;

mutex m;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }

	void AddElement(const T1& elem1, const T2& elem2) {

		for (int i = 0; i < _trenutno; i++)
			if (_elementi1[i] == elem1 || _elementi2[i] == elem2)
				throw exception(nedozvoljena_operacija);

		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[_trenutno] = elem1;
		_elementi2[_trenutno++] = elem2;

	}

	T1* getElementi1Pok() { return _elementi1; }
	T2* getElementi2Pok() { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)

			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class Poglavlje {
	char* _naslov;
	char* _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	Poglavlje(const Poglavlje& p) :Poglavlje(p._naslov, p._sadrzaj) {
		OcijeniPoglavlje(p._ocjena);
	}
	~Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, const Poglavlje& obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	Poglavlje& operator = (const Poglavlje& p) {
		if (this != &p) {
			delete[] _naslov; delete[] _sadrzaj;
			_naslov = AlocirajNizKaraktera(p._naslov);
			_sadrzaj = AlocirajNizKaraktera(p._sadrzaj);
			OcijeniPoglavlje(p._ocjena);
		}
		return *this;
	}
	char* GetNaslov() { return _naslov; }
	char* GetSadrzaj() { return _sadrzaj; }
	bool GetPrihvaceno() { return _prihvaceno; }
	int GetOcjena() { return _ocjena; }

	void OcijeniPoglavlje(int ocjena) {
		_ocjena = ocjena;
		if (_ocjena > 5 && ocjena <= 10)
			_prihvaceno = true;
	}
	void SetSadrzaj(string sadrzaj) {
		char* temp = AlocirajNizKaraktera((sadrzaj + string(_sadrzaj)).c_str());
		delete[] _sadrzaj;
		_sadrzaj = temp;
	}
};

class ZavrsniRad {
	char* _tema;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}

	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}

	ZavrsniRad& operator= (const ZavrsniRad& z) {
		if (this != &z) {
			delete[] _tema;
			_tema = AlocirajNizKaraktera(z._tema);
			_poglavljaRada = z._poglavljaRada;
			_datumOdbrane = z._datumOdbrane;
			_konacnaOcjena = z._konacnaOcjena;
		}
		return *this;
	}

	bool operator == (const ZavrsniRad& r) {
		return strcmp(_tema, r._tema) == 0;
	}

	void DodajPoglavlje(string naslov, string sadrzaj) {
		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i != _poglavljaRada.end(); i++)
		{
			if (strcmp(i->GetNaslov(), naslov.c_str()) == 0) {
				i->SetSadrzaj(sadrzaj);
				return;
			}
		}
		_poglavljaRada.push_back(Poglavlje(naslov.c_str(), sadrzaj.c_str()));
	}

	void OcijeniPoglavlje(string naslov, int ocjena) {
		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i != _poglavljaRada.end(); i++)
		{
			if (strcmp(i->GetNaslov(), naslov.c_str()) == 0) i->OcijeniPoglavlje(ocjena);
		}
	}

	char* GetNazivTeme()const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane()const { return _datumOdbrane; }
	float GetOcjena() { return _konacnaOcjena; }
	float GetKonacnaOcjena() { return _konacnaOcjena; }
	friend ostream& operator<<(ostream& COUT, const ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}
	void SetDatumOdbrane(string datum) {
		_datumOdbrane = datum;
	}
	void SetKonacnaOcjena(float ocjena) {
		_konacnaOcjena = ocjena;
	}
};

class Osoba {
protected:
	string _imePrezime;
public:
	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
	string GetImePrezime() { return _imePrezime; }
	virtual void Info() = 0;

	friend ostream& operator << (ostream& o, const Osoba& os) {
		o << os._imePrezime;
		return o;
	}
};

class Nastavnik : public Osoba {
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
	Kolekcija<string, ZavrsniRad> _teme;
public:
	Nastavnik(string imeprezime) :Osoba(imeprezime) {}

	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
	friend ostream& operator << (ostream& o, Nastavnik& n) {
		o << dynamic_cast<Osoba&>(n) << endl;
		o << "Teme: " << endl << n._teme;
		return o;
	}
	void Info() {
		cout << *this << endl;
	}

	bool DodajZavrsniRad(string brojIndexa, ZavrsniRad z) {
		try
		{
			_teme.AddElement(brojIndexa, z);
			return true;
		}
		catch (const std::exception& e)
		{
			return false;
		}
		return false;
	}

	ZavrsniRad* ZakaziOdbranuRada(string brojIndexa, string datum) {
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (_teme.getElement1(i) == brojIndexa) {
				if (_teme.getElement2(i).GetPoglavlja().size() < min_polgavlja) return nullptr;
				float suma = 0;
				for (vector<Poglavlje>::iterator j = _teme.getElement2(i).GetPoglavlja().begin(); j != _teme.getElement2(i).GetPoglavlja().end(); j++)
				{
					if (strlen(j->GetSadrzaj()) < min_karaktera_po_poglavlju || !j->GetPrihvaceno()) 
						return nullptr;
					suma += j->GetOcjena();
				}
				suma /= _teme.getElement2(i).GetPoglavlja().size();
				_teme.getElement2(i).SetDatumOdbrane(datum);
				_teme.getElement2(i).SetKonacnaOcjena(suma);
				return &_teme.getElement2(i);
			}
		}
		return nullptr;
	}
};

string PosaljiPozivZaDodjeluNagrada(Nastavnik** nastavnici, int max, float ocjena) {
	string poruka = not_set;
	Nastavnik* n = nullptr;
	float prosjek = 0;
	for (size_t i = 0; i < max; i++)
	{
		float trenutniProsjek = 0;
		int brojac = 0;
		for (size_t j = 0; j < nastavnici[i]->GetTeme().getTrenutno(); j++)
		{
			if (nastavnici[i]->GetTeme().getElement2(j).GetOcjena() > 5) {
				trenutniProsjek += nastavnici[i]->GetTeme().getElement2(j).GetOcjena();
				brojac++;
			}
		}
		if (brojac != 0) {
			trenutniProsjek /= brojac;
			if (prosjek > trenutniProsjek) {
				prosjek = trenutniProsjek;
				n = nastavnici[i];
			}
		}
	}
	if (n != nullptr) {
		for (size_t i = 0; i < n->GetTeme().getTrenutno(); i++)
		{
			if (n->GetTeme().getElement2(i).GetKonacnaOcjena() >= ocjena) {
				string temp = "Postovani" + n->GetTeme().getElement1(i) + ", uzimajuci u obzir cinjenicu da ste kod mentora " + n->GetImePrezime() + " uspjesno odbranili rad sa ocjenom " + to_string(n->GetTeme().getElement2(i).GetKonacnaOcjena()) + " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT - u 20.09.2018.godine.";
				poruka += "\n" + temp + "\n";
				thread t([temp](string email) {
					m.lock();
					cout << "Saljem mail -> " << email << endl;
					cout << temp << endl;
					m.unlock();
					}, n->GetTeme().getElement1(i) + "@edu.fit.ba");
				t.join();
			}
		}
	}
	return poruka;
}

int main() {

	cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;

	const int max = 4;
	Nastavnik* nastavnici[max];

	nastavnici[0] = new Nastavnik("Denis Music");
	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
	nastavnici[3] = new Nastavnik("Emina Junuz");
	//parametri: naziv zavrsnog rada
	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti beži?nih ra?unarskih mreža");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih klju?eva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");

	try {
		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

		multimedijalni.OcijeniPoglavlje("Uvod", 8);
		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
	}
	catch (exception& err) {
		cout << "Greska -> " << err.what() << endl;
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri: brojIndeksa, zavrsniRad
	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
		cout << "Zavrsni rad nije dodat!" << endl;
	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
		cout << "Zavrsni rad uspjesno dodat!" << endl;

	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
		1. zavrsni rad ima broj poglavlja veci od minimalnog
		2. svako poglavlje ima broj karaktera veci od minimalnog
		3. svako poglavlje je prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//parametri: brojIndeksa, datumOdbrane
	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	nastavnici[0]->Info();

	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;

	for (int i = 0; i < max; i++) {
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
	system("pause>0");
	return 0;
}