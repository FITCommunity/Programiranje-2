#include<iostream>
#include<string>
#include<vector>
#include<exception>
#include<regex>
#include<sstream>
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum stringFormat { DDMMGG, DDMMGGGG, DDMMGGSSMM, DDMMGGGGSSMM };
enum prikazPoruka { SVE_PORUKE, SAKRIJ_POBRISANE, PRIKAZI_SAMO_POBRISANE };
vector<string> nedozvoljeneRijeci;
/*
DDMMGG - 29.8.17
DDMMGGGG - 29.8.2017
DDMMGGGGSSMM - 29.8.2017 10:15
*/
bool ValidSadrzaj(string sadrzaj)
{
	for (int i = 0; i < nedozvoljeneRijeci.size(); i++)
		if (regex_search(sadrzaj, regex(nedozvoljeneRijeci[i])))
			return false;
	return true;
}

char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}

	Kolekcija(const Kolekcija& original) : _trenutno(new int(*original._trenutno))
	{
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (int i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}

	Kolekcija& operator=(const Kolekcija& orig)
	{
		if (this != &orig)
		{
			delete[]_elementi1;
			delete[]_elementi2;

			_elementi1 = new T1[*orig._trenutno];
			_elementi2 = new T2[*orig._trenutno];
			*_trenutno = *orig._trenutno;

			for (int i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = orig._elementi1[i];
				_elementi2[i] = orig._elementi2[i];
			}
		}
		return *this;
	}

	bool AddElement(T1 elem1, T2 elem2)
	{
		T1* temp1 = new T1[*_trenutno + 1];
		T2* temp2 = new T2[*_trenutno + 1];

		for (int i = 0; i < *_trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[*_trenutno] = elem1;
		_elementi2[*_trenutno] = elem2;
		(*_trenutno)++;
		return true;
	}
	~Kolekcija()
	{
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}

	T1* getElementi1Pok() { return _elementi1; }
	T2* getElementi2Pok() { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija& obj)
	{
		for (int i = 0; i < obj.getTrenutno(); i++)
		{
			COUT << obj.getElement1(i) << "   " << obj.getElement2(i) << endl;
		}
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
	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << "->  " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
	int GetMinute()
	{
		return *_godina * 365 * 24 * 60 + *_mjesec * 30 * 24 * 60 + *_dan * 24 * 60 + *_sati * 60 + *_minuti;
	}
	string ToString(stringFormat format)
	{
		stringstream ss;
		switch (format)
		{
		case DDMMGG:
			ss << *_dan << "." << *_mjesec << "." << *_godina % 100 << endl;
			return ss.str();
			break;
		case DDMMGGGG:
			ss << *_dan << "." << *_mjesec << "." << *_godina<< endl;
			return ss.str();
			break;
		case DDMMGGSSMM:
			ss << *_dan << "." << *_mjesec << "." << *_godina % 100 <<"-> "<<*_sati<<":"<<*_dan<< endl;
			return ss.str();
			break;
		case DDMMGGGGSSMM:
			ss << *_dan << "." << *_mjesec << "." << *_godina<< "-> " << *_sati << ":" << *_dan << endl;
			return ss.str();
			break;
		default:
			break;
		}
	}
};



class Poruka {
	string _posiljalac;
	string _primalac;
	string _sadrzaj;
	DatumVrijeme _vrijeme;
public:
	Poruka(string posiljalac="---", string primalac="---", string sadrzaj="---", DatumVrijeme vrijeme=DatumVrijeme()) :_vrijeme(vrijeme)
	{
		_posiljalac = posiljalac;
		_primalac = primalac;
		_sadrzaj = sadrzaj;
	}
	friend ostream& operator<< (ostream& COUT, Poruka& obj) {
		COUT  << obj._vrijeme <<"  " << "Od->  "<< obj._posiljalac << "   za ->  "<<obj._primalac<<endl;
		COUT << obj._sadrzaj;
		return COUT;
	}
	string getPrimalac() { return _primalac; }
	string getPosiljalac() { return _posiljalac; }
	string getSadrzaj() { return _sadrzaj; }
	DatumVrijeme& getDatumSlanja() { return _vrijeme; }
};
class Komunikacija {
	string _naslov;
	int _ocjena; //ocjena komunikacije 1 - 5 se automatski izracunava
	Kolekcija<Poruka, bool> _poruke;//bool se odnosi na podatak da li je poruka pobrisana tj. nece biti vidljiva u prikazu ukoliko se drugacije ne navede
public:
	Komunikacija(string naslov="---") {
		_naslov = naslov;
		_ocjena = -1;
	}
	Komunikacija(const Komunikacija& original) : _naslov(original._naslov), _ocjena(original._ocjena), _poruke(original._poruke) {}
	Komunikacija& operator=(const Komunikacija& druga)
	{
		if (this != &druga)
		{
			_naslov = druga._naslov;
			_ocjena = druga._ocjena;
			_poruke = druga._poruke;
		}
		return *this;
	}
	Kolekcija<Poruka, bool>* getPoruke() { return &_poruke; }
	int getOcjena() { return _ocjena; }
	string getNaslov() { return _naslov; }
	float ProsjekOdgovora()
	{
		float prosjek = 0;
		for (int i = 0; i < _poruke.getTrenutno() - 1; i++)
			prosjek += abs(_poruke.getElement1(i).getDatumSlanja().GetMinute() - _poruke.getElement1(i + 1).getDatumSlanja().GetMinute());

		return prosjek / _poruke.getTrenutno();
	}
	void SetOcjena(int ocjena)
	{
		if (ocjena > 0 && ocjena < 6)
			_ocjena = ocjena;
	}
	friend ostream& operator<< (ostream& COUT, Komunikacija& obj) {
		COUT << "Naslov poruke->  " << obj._naslov << "     ocjena ( " << obj._ocjena << " ) " << endl;
		for (int i = 0; i < obj._poruke.getTrenutno(); i++)
		{
			COUT << obj._poruke.getElement1(i) << endl;
			if (obj._poruke.getElement2(i))
				COUT << "OBRISANA" << crt;
			else
				COUT << "NIJE OBRISANA" << crt;
		}
		return COUT;
	}
};

class Korisnik {
	string _korisnickoIme;
	char* _imePrezime;
	//char * - se odnosi na naziv predmeta ili tema gdje će se čuvati kompletna komunikacija sa nastavnim osobljem ili korisnikom na određenom predmetu/temi
	Kolekcija<const char*, Komunikacija> _komunikacija;
public:
	Korisnik(const char* korisnickoIme,const char* imePrezime)
	{
		_imePrezime = Alociraj(imePrezime);
		_korisnickoIme = korisnickoIme;
	}
	Korisnik(Korisnik& original) :_komunikacija(original._komunikacija)
	{
		_imePrezime = Alociraj(original._imePrezime);
		_korisnickoIme = original._korisnickoIme;
		_komunikacija = original._komunikacija;
	}

	Korisnik& operator=(const Korisnik& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(drugi._imePrezime);
			_korisnickoIme = drugi._korisnickoIme;
			_komunikacija = drugi._komunikacija;
		}
		return *this;
	}

	~Korisnik()
	{
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	Kolekcija<const char*, Komunikacija>* GetKomunikacija() { return &_komunikacija; }
	string getKorisnickoIme() { return _korisnickoIme; }
	friend ostream& operator<< (ostream& COUT, Korisnik& obj)
	{
		COUT << "Korisnik->  " << obj._imePrezime << "     Username->  " << obj._korisnickoIme << endl;
		COUT<<"KOMUNIKACIJA: "<< crt;
		for (int i = 0; i < obj._komunikacija.getTrenutno(); i++)
		{
			COUT << "Naziv teme komunikacije->   " << obj._komunikacija.getElement1(i) << crt;
			COUT << obj._komunikacija.getElement2(i);
		}
		return COUT;
	}

	void PrikaziKomunikacijuPoNaslovu(const char* naslov, prikazPoruka prikaz)
	{
		switch (prikaz)
		{
		case SVE_PORUKE:
			for (int i = 0; i < _komunikacija.getTrenutno(); i++)
			{
				if (strcmp(_komunikacija.getElement1(i), naslov) == 0)
				{
					cout << "Razmjenjene poruke pod naslovom  ->  " << naslov << endl;
					for (int j = 0; j < _komunikacija.getElement2(i).getPoruke()->getTrenutno(); j++)
						cout <<_komunikacija.getElement2(i).getPoruke()->getElement1(j).getDatumSlanja()<<"     "<< _komunikacija.getElement2(i).getPoruke()->getElement1(j).getSadrzaj() << crt;
				}
			}
			break;
		case SAKRIJ_POBRISANE:
			for (int i = 0; i < _komunikacija.getTrenutno(); i++)
			{
				if (strcmp(_komunikacija.getElement1(i), naslov) == 0)
				{
					cout << "Razmjenjene poruke pod naslovom  ->  " << naslov << endl;
					for (int j = 0; j < _komunikacija.getElement2(i).getPoruke()->getTrenutno(); j++)
					{
						if (_komunikacija.getElement2(i).getPoruke()->getElement2(j))
							cout << "****PORUKA IZBRISANA****" << endl;
						else
							cout << _komunikacija.getElement2(i).getPoruke()->getElement1(j).getDatumSlanja() << "     " << _komunikacija.getElement2(i).getPoruke()->getElement1(j).getSadrzaj() << crt;
					}
				}
			}
			break;
		case PRIKAZI_SAMO_POBRISANE:
			for (int i = 0; i < _komunikacija.getTrenutno(); i++)
			{
				if (strcmp(_komunikacija.getElement1(i), naslov) == 0)
				{
					cout << "Razmjenjene poruke pod naslovom  ->  " << naslov << endl;
					for (int j = 0; j < _komunikacija.getElement2(i).getPoruke()->getTrenutno(); j++)
					{
						if (_komunikacija.getElement2(i).getPoruke()->getElement2(j))
							cout << _komunikacija.getElement2(i).getPoruke()->getElement1(j).getDatumSlanja() << "     " << _komunikacija.getElement2(i).getPoruke()->getElement1(j).getSadrzaj() << crt;
					}
				}
			}
			break;
		default:
			break;
		}
	}

	int PrikaziKomunikacijuSaKorisnikom(string korisnickoIme)
	{
		int brojacPoruka = 0;
		for (int i = 0; i < _komunikacija.getTrenutno(); i++)
		{
			for (int j = 0; j < _komunikacija.getElement2(i).getPoruke()->getTrenutno(); j++)
			{
				if (_komunikacija.getElement2(i).getPoruke()->getElement1(j).getPosiljalac() == korisnickoIme || _komunikacija.getElement2(i).getPoruke()->getElement1(j).getPrimalac() == korisnickoIme)
				{
					cout << _komunikacija.getElement2(i).getPoruke()->getElement1(j).getSadrzaj() << endl;
					brojacPoruka++;
				}
			}
		}
		cout << crt;
		return brojacPoruka;
	}

	void OcijeniKomunikaciju(const char* nazivTeme)
	{
		for (int i = 0; i < _komunikacija.getTrenutno(); i++)
		{
			if (strcmp(_komunikacija.getElement1(i), nazivTeme) == 0)
			{
				for (int j = 0; j < _komunikacija.getElement2(i).getPoruke()->getTrenutno(); j++)
				{
					float prosjek = _komunikacija.getElement2(i).ProsjekOdgovora();
					if (prosjek > 20)
						_komunikacija.getElement2(i).SetOcjena(1);
					else if(prosjek > 15) 
						_komunikacija.getElement2(i).SetOcjena(2);
					else if (prosjek > 10)
						_komunikacija.getElement2(i).SetOcjena(3);
					else if (prosjek > 5)
						_komunikacija.getElement2(i).SetOcjena(4);
					else if (prosjek <= 5)
						_komunikacija.getElement2(i).SetOcjena(5);

				}
				cout << "Ocjena za komunikaciju sa naslovom -> " << _komunikacija.getElement2(i).getNaslov() << "   je->   " << _komunikacija.getElement2(i).getOcjena() << crt;
			}
		}
	}
};


void PosaljiPoruku(Korisnik** korisnici, int max, const char* nazivTeme, string posiljalac, string primalac, string sadrzajPoruke, DatumVrijeme& datumSlanja)
{
	bool imaPosiljalac = false;
	bool imaPrimalac = false;
	//provjeravamo da li postoji ili posiljalac ili primalac unutar korisnika
	for (int i = 0; i < max; i++)
	{
		if (korisnici[i]->getKorisnickoIme() == posiljalac) imaPosiljalac = true;
		if (korisnici[i]->getKorisnickoIme() == primalac) imaPrimalac = true;
	}
//ukoliko nema ili jednog ili drugog funkcija se zavrsava
	if (!imaPrimalac && !imaPosiljalac)
		throw exception("Primalac ili posiljalac ne postoje!");

	if (!ValidSadrzaj(sadrzajPoruke))
		throw exception("Sadrzaj koji ste poslali ima u sebi zabranjenu rijec!");

//u suprotnom prodjemo kroz sve korisnike i provjerimo je li proslijedjeno ime ista od navedenog
	for (int i = 0; i < max; i++)
	{
		bool imaNaslov = false;
		if (korisnici[i]->getKorisnickoIme() == posiljalac || korisnici[i]->getKorisnickoIme() == primalac)
		{
			//ukoliko jest prodjemo kroz njegovu komunikaicju i gledamo da li postoji isti naslov kao proslijedjena
			for (int j = 0; j < korisnici[i]->GetKomunikacija()->getTrenutno(); j++)
			{
				if (strcmp(korisnici[i]->GetKomunikacija()->getElement1(j), nazivTeme) == 0)
				{
					//ukoliko postoji dodajemo mu samo poruku unutar te komunikacije
					imaNaslov = true;
					korisnici[i]->GetKomunikacija()->getElement2(j).getPoruke()->AddElement(Poruka(posiljalac,primalac,sadrzajPoruke,datumSlanja),false);
				}
			}

//ukoliko nema naslova prvo dodajemo komunikaicju sa tim naslovom pa onda na zadnji clan dodajemo poruku
			if (!imaNaslov)
			{
				korisnici[i]->GetKomunikacija()->AddElement(nazivTeme, Komunikacija(nazivTeme));
				int trenutno = korisnici[i]->GetKomunikacija()->getTrenutno();
				korisnici[i]->GetKomunikacija()->getElement2(trenutno - 1).getPoruke()->AddElement(Poruka(posiljalac, primalac, sadrzajPoruke, datumSlanja), false);
			}

		}
	}
}



void main()
{

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/


	/*riječi koje su zabranjene u komunikaciji*/
	nedozvoljeneRijeci.push_back("ubiti");
	nedozvoljeneRijeci.push_back("mrzim");
	nedozvoljeneRijeci.push_back("rat");

	DatumVrijeme temp,
		datum19062017_1015(19, 6, 2017, 10, 15),
		datum19062017_1020(19, 6, 2017, 10, 20),
		datum19062017_1021(19, 6, 2017, 10, 21),
		datum19062017_1030(19, 6, 2017, 10, 30);

	cout << datum19062017_1015.ToString(DDMMGGGG) << endl;//vraca string: 19.6.2017
	cout << datum19062017_1015.ToString(DDMMGGGGSSMM) << endl;//vraca string: 19.6.2017 10:15


	const int max = 3;
	Korisnik* korisnici[max];
	korisnici[0] = new Korisnik("jasmin", "Jasmin Azemovic");
	korisnici[1] = new Korisnik("adel", "Adel Handzic");
	korisnici[2] = new Korisnik("denis", "Denis Music");

	///*
	//sve poruke se cuvaju u komunikaciji posiljaoca i primaoca tako da u svakom momentu oba ucesnika u komunikaciji posjeduju kompletnu historiju poruka.
	//poruke se grupisu na osnovu naslova, pa ce poruke pod naslovom "Sastanak" izmedju dva korisnika sadrzavati sve poruke koje su razmijenjene na tu temu
	//u slucaju da posiljalac ili primalac ne postoje funkcija treba baciti izuzetak sa odgovarajucom porukom. 
	//takodjer, koristeci regex sve poruke koje sadrze neku od zabranjenih rijeci trebaju biti oznacene kao
	//*/
	PosaljiPoruku(korisnici, max, "Sastanak",korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),"Danas imamo sastanak u 10h!", datum19062017_1015);

	PosaljiPoruku(korisnici, max, "Sastanak",korisnici[1]->getKorisnickoIme(), korisnici[0]->getKorisnickoIme(),"Naravno, vidimo se u sali za sastanke!", datum19062017_1020);

	PosaljiPoruku(korisnici, max, "Sastanak",korisnici[0]->getKorisnickoIme(), korisnici[1]->getKorisnickoIme(),"Sa sobom ponesi radni materijal!", datum19062017_1021);

	///*ispisuje sve poruke koje je korisnik razmijenio pod naslovom definisanim parametrom. ispis komunikacije
	//treba biti organizovan po datumu na nacin da se prvo prikaze datum, a nakon toga sve poruke koje su razmijenjene tog datuma.
	//Na mjestima pobrisanih poruka prikazati tekst "PORUKA IZBRISANA"
	//*/
	korisnici[0]->PrikaziKomunikacijuPoNaslovu("Sastanak", SAKRIJ_POBRISANE);

	///*funkcija prikazuje sve poruke sa korisnikom cije korisnicko ime je definisano parametrom, te vraca ukupan broj (razmijenjenih poruka sa tim korisnikom)*/
	int ukupnoPoruka = korisnici[0]->PrikaziKomunikacijuSaKorisnikom("adel");

	///*formira ocjenu na nivou komunikacije na nacin da izracunava prosjecno vrijeme odgovora drugog ucesnika izrazeno u minutama i to prema sljedecoj skali
	//prosjek > 20 minuta = ocjena 1
	//prosjek > 15 minuta = ocjena 2
	//prosjek > 10 minuta = ocjena 3
	//prosjek > 5 minuta = ocjena 4
	//prosjek <=5 minuta = ocjena 5
	//*/
	korisnici[0]->OcijeniKomunikaciju("Sastanak");


	 cout << *korisnici[0];

	for (size_t i = 0; i < max; i++)
	{
		delete korisnici[i];
		korisnici[i] = nullptr;
	}

	system("PAUSE");
}