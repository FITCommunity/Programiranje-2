//Napomena: U rješenju svaka klasa treba da posjeduje odgovarajući header i cpp file.

#include <iostream>
#include <iomanip>

using namespace std;

const char* str = "\n------------------------------------------------------------------\n";

class Vrijeme
{
	int _sati;
	int _minute;
	int _sekunde;
public:

	//Konstruktor bez parametara
	Vrijeme()
	{
		_sati = 0;
		_minute = 0;
		_sekunde = 0;
	}

	Vrijeme(int sati, int minute)
	{
		_sati = sati;
		_minute = minute;
		_sekunde = 0;
	}

	Vrijeme(int sati, int minute, int sekunde)
	{
		_sati = sati;
		_minute = minute;
		_sekunde = sekunde;
	}

	//Nisam siguran da li je bila poenta da se kreiraju 3 konstruktora ili da se prepozna da se moze uraditi sve sa jednim
	/*
	Vrijeme(int sati = 0, int minute = 0, int sekunde = 0)
	{
		_sati = sati;
		_minute = minute;
		_sekunde = sekunde;
	}
	*/

	//Funkciju Info sa neobaveznim parametrom tipa bool koji određuje da li će vrijeme biti ispisano u punom formatu
	//(hh:mm:ss) ili u skraćenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu.
	void Info(bool skraceniFormat = false)
	{
		skraceniFormat ? cout << setw(2) << setfill('0') << _sati << ":"
							  << setw(2) << setfill('0') << _minute << ":"
							  << setw(2) << setfill('0') << _sekunde << "\n"
					   : cout << setw(2) << setfill('0') << _sati << ":"
							  << setw(2) << setfill('0') << _minute << "\n";
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu vremena poslijeđenog kao parametar i instance this.
	Vrijeme Add(const Vrijeme& v)
	{
		int sekunde = this->_sekunde + v._sekunde;
		int minute = this->_minute + v._minute + sekunde / 60;
		int sati = this->_sati + v._sati + minute / 60;

		sekunde %= 60;
		minute %= 60;

		return { sati, minute, sekunde };
	}

	//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
	//sumu parametra izraženog u minutama i vremena instance this.
	Vrijeme Add(int minute)
	{
		int sati = this->_sati + minute / 60;
		minute %= 60;

		return { sati, minute, this->_sekunde };
	}


	//Funkciju CompareTo koja vraća vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, 
	//jednako ili poslije
	//vremena proslijeđenog kao parametar.
	//Moguće povratne vrijednosti:
	//-1 - vrijeme instance this nastupa prije vremena v2
	// 0 - vrijeme instance this je jednako vremenu v2
	// 1 - vrijeme instance this nastupa nakon vremena v2
	int CompareTo(const Vrijeme& v)
	{
		if (this->_sati != v._sati)
			return abs(this->_sati - v._sati) / (this->_sati - v._sati);
		else if (this->_minute != v._minute)
			return abs(this->_minute - v._minute) / (this->_minute - v._minute);
		else if (this->_sekunde != v._sekunde)
			return abs(this->_sekunde - v._sekunde) / (this->_sekunde - v._sekunde);
		return 0;
	}

};


/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene članaka među korisnicima.
Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima (Ime, Prezime, Email, DatumRegistracije,
KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) može sadržavati više tagova, ali pripada samo
jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar (Tekst, Datum, Popularnost) na određeni članak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima
i/ili funkcijama.
*/

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	//Potrebne konstruktor i destruktor funkcije
	Datum(int godina = 1970, int mjesec = 1, int dan = 1)
	{
		_godina = godina;
		_mjesec = mjesec;
		_dan = dan;
	}

    //Beskorisno
	~Datum()
	{
		_godina = 0;
		_mjesec = 0;
		_dan = 0;
	}
	//Funkciju Info
	void Info()
	{
		cout << setw(2) << setfill('0') << _dan << "/"
			 << setw(2) << setfill('0') << _mjesec << "/"
									    << _godina << "\n";
	}
};

enum TipKorisnika { Administrator, Guest };
const char* TipKorisnikaStr[]{ "Administrator", "Guest" };

class Korisnik
{
	char _ime[30];
	char _prezime[50];
	char _korisnickoIme[20];
	char _email[20];
	char* _lozinka = nullptr;
	Datum _datumRegistracije;
	TipKorisnika _tipKorisnika; //Administrator, Guest
public:
	//Potrebne konstruktor i destruktor funkcije
	Korisnik(const char* ime, const char *prezime, const char* korisnickoIme, const char *email, const char* lozinka, Datum d, TipKorisnika tipKorisnika = Guest)
	{
		strcpy_s(_ime, ime);
		strcpy_s(_prezime, prezime);
		strcpy_s(_korisnickoIme, korisnickoIme);
		strcpy_s(_email, email);
		
		_datumRegistracije = d;

		int velicina = strlen(lozinka) + 1;
		_lozinka = new char[velicina];
		strcpy_s(_lozinka, velicina, lozinka);

		_tipKorisnika = tipKorisnika;
	}

	Korisnik(const Korisnik& korisnik)
	{
		strcpy_s(_ime, korisnik._ime);
		strcpy_s(_korisnickoIme, korisnik._korisnickoIme);
		strcpy_s(_korisnickoIme, korisnik._korisnickoIme);
		strcpy_s(_email, korisnik._email);
		_datumRegistracije = korisnik._datumRegistracije;

		delete[] _lozinka;
		int velicina = strlen(korisnik._lozinka) + 1;
		_lozinka = new char[velicina];
		strcpy_s(_lozinka, velicina, korisnik._lozinka);

		_tipKorisnika = korisnik._tipKorisnika;
	}

	~Korisnik()
	{
		delete[] _lozinka; _lozinka = nullptr;
	}
	//Funkciju za promjenu korisničke lozinke
	bool PromjeniLozinku(const char* staraLozinka, const char* novaLozinka)
	{
		if (strcmp(_lozinka, staraLozinka) == 0)
		{
			delete[] _lozinka;

			int velicina = strlen(novaLozinka) + 1;
			_lozinka = new char[velicina];
			strcpy_s(_lozinka, velicina, novaLozinka);
			return true;
		}

		return false;
	}
	//Funkciju Info
	void Info()
	{
		cout << "Ime: " << _ime << endl
			<< "Korisnicko ime: " << _korisnickoIme << endl
			<< "Tip korisnika: " << TipKorisnikaStr[_tipKorisnika] << endl;
		/*cout << _lozinka << endl;*/
	}

	const char* GetPassword() { return _lozinka; }
	const char* GetKorisnikoIme() { return _korisnickoIme; }

};

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	//Potrebne konstruktor i destruktor funkcije
	Komentar()
	{
		_tekst = nullptr;
		_popularnost = 0;
		_autor = nullptr;
	}
	Komentar(const char* tekst, Datum datum, Vrijeme vrijeme, Korisnik autor)
	{
		int velicina = strlen(tekst) + 1;
		_tekst = new char[velicina];
		strcpy_s(_tekst, velicina, tekst);

		_datum = datum;
		_satnica = vrijeme;
		_autor = new Korisnik(autor);
		_popularnost = 0;
	}

	Komentar(const Komentar& komentar)
	{
		//delete[] _tekst;
		int velicina = strlen(komentar._tekst) + 1;
		_tekst = new char[velicina];
		strcpy_s(_tekst, velicina, komentar._tekst);

		_datum = komentar._datum;
		_satnica = komentar._satnica;
		_autor = new Korisnik(*komentar._autor);
		_popularnost = komentar._popularnost;
	}

	~Komentar()
	{
		delete[] _tekst; 
		cout << _autor->GetPassword();
		delete _autor;
	}
	//Funkciju za izmjenu popularnosti komentara
	void Like()
	{
		_popularnost++;
	}
	//Funkciju Info
	void Info()
	{
		cout << str << _tekst << str << "Popularnost: " << _popularnost << str;

		_datum.Info();
		_satnica.Info();
		_autor->Info();

		cout << str;
	}

	Korisnik *GetAutor() { return _autor; }
};

class Clanak
{
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;
public:
	Clanak()
	{
		_sadrzaj = nullptr;
		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;
		_autor = nullptr;
		_komentari = nullptr;
		_brojKomentara = 0;
	}


	Clanak(const char* naslov, const char* sadrzaj, const char* oblast, Datum datum, Vrijeme vrijeme, Korisnik autor)
	{
		strcpy_s(_naslov, naslov);

		int velicina = strlen(sadrzaj) + 1;
		_sadrzaj = new char[velicina];
		strcpy_s(_sadrzaj, velicina, sadrzaj);

		_datum = datum;
		_satnica = vrijeme;

		_brojPregleda = 0;
		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;

		strcpy_s(_oblast, oblast);
		_autor = new Korisnik(autor);

		_komentari = nullptr;
		_brojKomentara = 0;
	}
	//Funkciju za dodavanje tagova za članak
	bool DodajTag(const char* tag)
	{
		for(int i = 0; i < 10; i++)
			if (_tagovi[i] == nullptr)
			{
				int velicina = strlen(tag) + 1;
				_tagovi[i] = new char[velicina];
				strcpy_s(_tagovi[i], velicina, tag);

				return true;
			}

		return false;
	}

	/*Funkciju za promjenu sadržaja i vremena promjene članka. Kao verifikaciju dozvole potrebno je
	proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/
	bool PromijeniSadrzaj(const char* sadrzaj, Vrijeme vrijeme, const char* autorKorisnickoIme)
	{
		bool SadrzajNotNull = sadrzaj != nullptr;
		bool AutorIsCorrect = strcmp(_autor->GetKorisnikoIme(), autorKorisnickoIme) == 0;
		bool VrijemeLaterFromOriginal = _satnica.CompareTo(vrijeme) == 1;
		if (SadrzajNotNull && AutorIsCorrect && VrijemeLaterFromOriginal)
		{
			delete[] _sadrzaj;
			int velicina = strlen(sadrzaj) + 1;
			_sadrzaj = new char[velicina];
			strcpy_s(_sadrzaj, velicina, sadrzaj);

			_satnica = vrijeme;
		}
	}

	//Funkciju za dodavanje komentara
	void DodajKomentar(const Komentar& komentar)
	{
		Komentar* temp = new Komentar[_brojKomentara + 1];
		for (int i = 0; i < _brojKomentara; i++)
			temp[i] = _komentari[i];
		temp[_brojKomentara] = komentar;
		_komentari = temp;
		_brojKomentara++;

		
		//delete[] temp;
	}

	//Funkciju Info
	void Info()
	{
		cout << str << _naslov 
			 << str << _oblast 
			 << str << _sadrzaj 
			 << str << _brojPregleda << str;

		for(int i = 0; i < 10; i++)
			if (_tagovi[i] != nullptr)
				cout << _tagovi[i] << " ";

		_autor->Info();
		cout << str << "Komentari: " << str;
		for (int i = 0; i < _brojKomentara; i++)
		{
			cout << str;
			_komentari[i].Info();
			cout << str;
		}

		_brojPregleda++;
	}
};

int main()
{
	// ------------------------------------------------------------------------
	// ToDo
	// ------------------------------------------------------------------------
	// [] Testovi sa assert
	// [] GET/SET funkcije
	// [] Doraditi ispis u konzoli
	// ------------------------------------------------------------------------

	//Kreirati testni program koji demonstrira implementirane funckionalnosti
	Vrijeme v1, v2(5, 2), v3(5, 24, 5);
	v1.Info();
	v2.Info();
	v3.Info(true);

	Datum d1, d2(2020, 3), d3(2020, 3, 5);
	d1.Info();
	d2.Info();
	d3.Info();

	Korisnik korisnik1("Ime", "Prezime", "KorisnickoIme", "Email", "Password", Datum(2020, 1, 1), Administrator), 
			 korisnik2("Ime_", "Prezime_", "Ime_", "Email@gmail.com", "12345678", Datum(2020, 2, 1));

	korisnik1.Info();
	korisnik1.PromjeniLozinku("Password", "Password1");
	korisnik1.Info();
	
	Komentar komentar("Tekst komentara", d3, v3, korisnik2);
	komentar.Info();
	komentar.Like();
	komentar.Info();

	Clanak clanak("Naslov", "Sadrzaj", "Oblast", d2, v2, korisnik1);
	clanak.DodajKomentar(komentar);
	clanak.Info();

	return 0;
}