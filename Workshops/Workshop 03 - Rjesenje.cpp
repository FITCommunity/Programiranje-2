#include <iostream>
using namespace std;


char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

int sifraBrojac = 0;

class Uposlenik {

	const int _sifra; //Automatski uvecavati za 1 za svakog novog uposlenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;
public:
	Uposlenik() : _sifra(++sifraBrojac), _radnoMjesto(nullptr)
	{}

	//Implementirati potrebne konstruktor i destruktor funkcije
	Uposlenik(const char* ime, const char* prezime, const char* radnoMjesto) : _sifra(++sifraBrojac)
	{
		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);

		_radnoMjesto = AlocirajNizKaraktera(radnoMjesto);
	}

	Uposlenik(const Uposlenik& uposlenik) :
		_sifra(uposlenik._sifra)
	{
		strncpy_s(_ime, uposlenik._ime, _TRUNCATE);
		strncpy_s(_prezime, uposlenik._prezime, _TRUNCATE);

		//delete[] _radnoMjesto;
		_radnoMjesto = AlocirajNizKaraktera(uposlenik._radnoMjesto);
	}


	~Uposlenik()
	{
		delete[] _radnoMjesto;
		_radnoMjesto = NULL;
	}

	//Ostale funkcije dodati po potrebi

	void Info()
	{
		cout << "Sifra: " << _sifra << endl;
		cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
		cout << "Radno mjesto: " << _radnoMjesto << endl;

	}

	const char* GetIme() const { return _ime; }
	const char* GetPrezime() const { return _prezime; }
	const int GetSifra() const { return _sifra; }

};


class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima
	Uposlenik* _uposlenici[5];
public:
	//Implementirati potrebne konstruktor i destruktor funkcije
	Aktivnost() : _naziv(nullptr), _zavrsena(false), _trajanje(nullptr)
	{
		for (int i = 0; i < 5; i++)
			_uposlenici[i] = nullptr;
	}

	Aktivnost(const char* naziv, int trajanje) :
		_naziv(AlocirajNizKaraktera(naziv)), _trajanje(new int(trajanje)), _zavrsena(false)
	{

		for (int i = 0; i < 5; i++)
			_uposlenici[i] = nullptr;
	}

	Aktivnost(const Aktivnost& aktivnost)
	{
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(aktivnost._naziv);

		delete _trajanje;
		_trajanje = new int(*aktivnost._trajanje);

		_zavrsena = aktivnost._trajanje;

		for (int i = 0; i < 5; i++)
		{
			if (aktivnost._uposlenici[i])
			{
				delete[] _uposlenici[i];
				_uposlenici[i] = new Uposlenik(*aktivnost._uposlenici[i]);
			}
		}
	}

	Aktivnost& operator=(const Aktivnost& aktivnost)
	{
		if (this != &aktivnost)
		{
			delete[] _naziv;
			_naziv = AlocirajNizKaraktera(aktivnost._naziv);

			delete _trajanje;
			_trajanje = new int(*aktivnost._trajanje);

			_zavrsena = aktivnost._trajanje;

			for (int i = 0; i < 5; i++)
			{
				if (aktivnost._uposlenici[i])
				{
					delete[] _uposlenici[i];
					_uposlenici[i] = new Uposlenik(*aktivnost._uposlenici[i]);
				}
			}
		}
		return *this;
	}
	~Aktivnost()
	{
		delete[] _naziv; _naziv = nullptr;
		delete _trajanje; _trajanje = nullptr;
		for (int i = 0; i < 5; i++)
		{
			delete _uposlenici[i];
			_uposlenici[i] = nullptr;
		}
	}


	const char* GetNaziv() const { return _naziv; }
	Uposlenik *const *GetUposlenike() const { return _uposlenici; }
	int GetTrajanje() const { return *_trajanje; }
	void SetZavrsena(bool status) { _zavrsena = status; }
	bool GetZavrsena() const { return _zavrsena; }

	void Zavrsi()
	{
		SetZavrsena(true);
	}
	//Funkciju koja omogucava angazovanje uposlenika na projektnoj aktivnosti. Funkcija treba da vrati vrijednost tipa
	//bool za uspjesno, odnosno neuspjesno dodavanje uposlenika. Nije moguce dodati istog uposlenika vise puta. 
	//Nije moguce
	//angazovati uposlenike na vec zavrsenoj aktivnosti.
	bool DodajUposlenika(const Uposlenik& uposlenik)
	{
		if (_zavrsena) return false;

		for (int i = 0; i < 5; i++)
		{
			if (_uposlenici[i] && _uposlenici[i]->GetSifra() == uposlenik.GetSifra())
			{
				return false;
			}
			else if (!_uposlenici[i])
			{
				_uposlenici[i] = new Uposlenik(uposlenik);
				return true;
			}
		}

		return false;
	}
	//Funkciju koja uklanja uposlenika na aktivnosti sa sifrom proslijedjenom kao parametar.
	bool UkloniUposlenika(int sifra)
	{
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i] && _uposlenici[i]->GetSifra() == sifra)
			{
				delete _uposlenici[i];
				_uposlenici[i] = nullptr;
				return true;
			}

		return false;
	}

	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti.
	void UkloniUposlenike()
	{
		for (int i = 0; i < 5; i++)
		{
			delete _uposlenici[i];
			_uposlenici[i] = nullptr;
		}
	}

	bool CompareTo(const Aktivnost& aktivnost)
	{
		return _naziv && aktivnost._naziv && strcmp(_naziv, aktivnost._naziv) == 0;
	}

	void Info()
	{
		cout << "Naziv: " << _naziv << " | Trajanje: " << *_trajanje << "\nUposlenici:  \n";
		for (int i = 0; i < 5; i++)
			if (_uposlenici[i])
				_uposlenici[i]->Info();
	}
};

//Pomocni struct
struct UposlenikAngazovanja
{
	Uposlenik* uposlenik;
	int brojAngazovanja = 0;
	int ukupnaDuzinaAktivnosti = 0;
	UposlenikAngazovanja() :
		uposlenik(new Uposlenik())
	{}
	UposlenikAngazovanja(const Uposlenik u, int angazovanja = 0, int duzina = 0) :
		brojAngazovanja(angazovanja), ukupnaDuzinaAktivnosti(duzina)
	{
		uposlenik = new Uposlenik(u);
	}
};

class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;
public:
	Projekat():
		_naziv(nullptr), _oblast(nullptr), _trajanje(0), 
		_aktivnosti(nullptr), _brojAktivnosti(0)
	{}

	//Implementirati potrebne konstruktor i destruktor funkcije.
	Projekat(const char* naziv, const char* oblast, int trajanje) :
		_naziv(AlocirajNizKaraktera(naziv)), _oblast(AlocirajNizKaraktera(oblast)), _trajanje(trajanje), 
		_aktivnosti(nullptr), _brojAktivnosti(0)
	{}

	Projekat(const Projekat& projekat) :
		_trajanje(projekat._trajanje), _brojAktivnosti(projekat._brojAktivnosti)
	{
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(projekat._naziv);
		delete[] _oblast;
		_oblast = AlocirajNizKaraktera(projekat._oblast);
		delete[] _aktivnosti;
		_aktivnosti = new Aktivnost[_brojAktivnosti];
		for (int i = 0; i < _brojAktivnosti; i++)
			_aktivnosti[i] = projekat._aktivnosti[i];
	}

	Projekat& operator=(const Projekat& projekat)
	{
		if (this != &projekat)
		{
			delete[] _naziv;
			_naziv = AlocirajNizKaraktera(projekat._naziv);
			delete[] _oblast;
			_oblast = AlocirajNizKaraktera(projekat._oblast);

			_brojAktivnosti = projekat._brojAktivnosti;
			delete[] _aktivnosti;
			_aktivnosti = new Aktivnost[_brojAktivnosti];
			for (int i = 0; i < _brojAktivnosti; i++)
				_aktivnosti[i] = projekat._aktivnosti[i];
		}

		return *this;
	}

	~Projekat()
	{
		
		delete[] _naziv; _naziv = nullptr;
		delete[] _oblast; _oblast = nullptr;
		delete[] _aktivnosti; _aktivnosti = nullptr;
	}

	Aktivnost* GetAktivnosti() const { return _aktivnosti; }
	int GetBrojAktivnosti() const { return _brojAktivnosti; }

	//Funkciju za dodavanje projektnih aktivnosti. Sprijeciti dodavanje vise aktivnosti sa istim nazivom.
	//Za potrebe poredjenja aktivnosti kreirati funkciju unutar klase Aktivnosti.
	void DodajAktivnost(const Aktivnost& aktivnost)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (_aktivnosti[i].CompareTo(aktivnost))
				return;

		Aktivnost* temp = new Aktivnost[_brojAktivnosti + 1];
		for (int i = 0; i < _brojAktivnosti; i++)
			temp[i] = _aktivnosti[i];
		temp[_brojAktivnosti] = aktivnost;
		
		_aktivnosti = temp;
		_brojAktivnosti++;
	}

	//Funkciju koja oznacava aktivnost kao zavrsenu. Funkcija kao parametar prima naziv aktivnosti.
	void ZavrsiAktivnost(const char* naziv)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
			{
				_aktivnosti[i].Zavrsi();
				return;
			}
	}

	//Funkciju koja treba da aktivnosti sa proslijedjenim nazivom dodijeli novog uposlenika.
	void DodajUposlenikaNaAktivnost(const char* naziv, const Uposlenik& uposlenik)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
			{
				_aktivnosti[i].DodajUposlenika(uposlenik);
				return;
			}
	}

	//Funkciju koja treba da vrati sve uposlenike angazovane na odredjenoj aktivnosti. 
	//Ulazni parametar je naziv aktivnosti.
	const Uposlenik* const *GetUposlenikeNaAktivnosti(const char* naziv)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
				return _aktivnosti[i].GetUposlenike();
		return nullptr;
	}

	//Funkciju koja uklanja odredjenog uposlenika na aktivnosti. 
	//Ulazni parametri funkcije su naziv aktivnosti i sifra uposlenika.
	bool UkloniUposlenikaSaAktivnosti(const char* naziv, int sifra)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
				return _aktivnosti[i].UkloniUposlenika(sifra);
		return false;
	}

	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti sa nazivom proslijedjenim kao parametar.
	void UkloniUposlenikeSaAktivnosti(const char* naziv)
	{
		for (int i = 0; i < _brojAktivnosti; i++)
			if (strcmp(_aktivnosti[i].GetNaziv(), naziv) == 0)
			{
				_aktivnosti[i].UkloniUposlenike();
				return;
			}
	}


	Uposlenik** GetTopNAngazovani(int top)
	{
		UposlenikAngazovanja* niz = nullptr;
		int brojAngazovanih = 0;
		for (int i = 0; i < _brojAktivnosti; i++)
		{
			const Uposlenik* const* angazovani = _aktivnosti[i].GetUposlenike();
			for (int j = 0; j < 5; j++)
			{
				if (angazovani[j])
				{
					bool nijeAngazovan = true;
					for (int k = 0; k < brojAngazovanih; k++)
					{
						if (niz[k].uposlenik->GetSifra() == angazovani[j]->GetSifra())
						{
							niz[k].brojAngazovanja++;
							nijeAngazovan = false;
							break;
						}
					}

					if (nijeAngazovan)
					{
						UposlenikAngazovanja* temp = new UposlenikAngazovanja[brojAngazovanih + 1]{};
						for (int l = 0; l < brojAngazovanih; l++)
							temp[l] = niz[l];
						temp[brojAngazovanih] = UposlenikAngazovanja(*angazovani[j], 1);
						niz = temp;
						brojAngazovanih++;
					}
				}
			}
		}

		for (int i = 0; i < brojAngazovanih; i++)
			if (niz[i].brojAngazovanja < niz[i + 1].brojAngazovanja)
			{
				swap(niz[i], niz[i + 1]);
			}

		Uposlenik** topN = new Uposlenik*[top];

		if (niz)
		{
			for (int i = 0; i < top && i < brojAngazovanih; i++)
				topN[i] = new Uposlenik(*niz[i].uposlenik);
			return topN;
		}

		return nullptr;
	}

	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.
	Uposlenik** GetTop1Angazovan()
	{
		return GetTopNAngazovani(1);
	}

	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.
	Uposlenik** GetTop3Angazovani()
	{
		return GetTopNAngazovani(3);
	}

	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.
	void Info()
	{
		cout << "Naziv: " << _naziv << "\nOblast: " << _oblast << "\nTrajanje: " << _trajanje
			<< "\nZavrsene aktivnosti: \n";
		for (int i = 0; i < _brojAktivnosti; i++)
			if (_aktivnosti[i].GetZavrsena())
				_aktivnosti[i].Info();
	}
};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg uposlenika na projektima (vise projekata)
proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/

Uposlenik* NajuspjesnijiUposlenik(Projekat* projekti, int brojProjekata)
{
	UposlenikAngazovanja* niz = nullptr;
	int brojAngazovanih = 0;
	for (int i = 0; i < brojProjekata; i++)
	{
		Aktivnost* aktivnosti = projekti[i].GetAktivnosti();
		for (int j = 0; j < projekti[i].GetBrojAktivnosti(); i++)
		{
			if (aktivnosti[j].GetZavrsena())
			{
				const Uposlenik* const *angazovani = aktivnosti[j].GetUposlenike();
				for (int k = 0; k < 5; k++)
				{
					if (angazovani[k])
					{
						bool nijeAngazovan = true;
						for (int l = 0; l < brojAngazovanih; l++)
						{
							if (niz[l].uposlenik->GetSifra() == angazovani[k]->GetSifra())
							{
								niz[l].brojAngazovanja++;
								niz[l].ukupnaDuzinaAktivnosti += aktivnosti[j].GetTrajanje();
								nijeAngazovan = false;
								break;
							}
						}

						if (nijeAngazovan)
						{
							UposlenikAngazovanja* temp = new UposlenikAngazovanja[brojAngazovanih + 1];
							for (int m = 0; m < brojAngazovanih; m++)
								temp[m] = niz[m];
							temp[brojAngazovanih] = UposlenikAngazovanja(*angazovani[k], 1, aktivnosti[j].GetTrajanje());
							niz = temp;
							brojAngazovanih++;
						}
					}
				}
			}
			
		}
	}

	int max = 0;
	for (int i = 1; i < brojAngazovanih; i++)
	{
		if (niz[i].brojAngazovanja > niz[max].brojAngazovanja)
		{
			max = i;
		}
		else if (niz[i].brojAngazovanja == niz[max].brojAngazovanja && niz[i].ukupnaDuzinaAktivnosti > niz[i].ukupnaDuzinaAktivnosti)
		{
			max = i;
		}
	}


	return niz ? niz[max].uposlenik : nullptr;
}


int main()
{
	//Testirati sve dostupne funkcionalnosti
	Uposlenik u1("Ime1", "Prezime1", "RadnoMjesto1");
	Uposlenik u2("Ime2", "Prezime2", "RadnoMjesto2");
	Uposlenik u3("Ime3", "Prezime3", "RadnoMjesto3");
	Uposlenik u4("Ime4", "Prezime4", "RadnoMjesto4");
	Uposlenik u5("Ime5", "Prezime5", "RadnoMjesto5");
	Uposlenik u6("Ime6", "Prezime6", "RadnoMjesto6");
	Uposlenik u7("Ime7", "Prezime7", "RadnoMjesto7");
	Uposlenik u8("Ime8", "Prezime8", "RadnoMjesto8");


	Aktivnost a1("Aktivnost 1", 12);
	Aktivnost a2("Aktivnost 2", 12);
	Aktivnost a3("Aktivnost 3", 10);
	Aktivnost a4("Aktivnost 4", 5);
	Aktivnost a5("Aktivnost 5", 7);

	
	a1.DodajUposlenika(u1);
	a1.DodajUposlenika(u2);
	a1.DodajUposlenika(u3);

	a2.DodajUposlenika(u1);
	a2.DodajUposlenika(u4);
	a2.DodajUposlenika(u5);

	a3.DodajUposlenika(u1);
	a3.DodajUposlenika(u2);
	a3.DodajUposlenika(u6);

	a4.DodajUposlenika(u2);
	a4.DodajUposlenika(u3);
	a4.DodajUposlenika(u7);

	a5.DodajUposlenika(u3);
	a5.DodajUposlenika(u8);
	
	Projekat projekti[3]{ Projekat("Projekat1", "Oblast1", 12) };
	
	projekti[0].DodajAktivnost(a1);
	projekti[0].DodajAktivnost(a1);
	projekti[0].DodajAktivnost(a2);
	projekti[0].DodajAktivnost(a3);
	projekti[0].DodajAktivnost(a4);
	projekti[0].DodajAktivnost(a5);

	
	
	Uposlenik** temp1 = projekti[0].GetTop1Angazovan();
	cout << endl << endl << temp1[0]->GetIme() << endl << endl;
	Uposlenik** temp2 = projekti[0].GetTop3Angazovani();
	for (int i = 0; i < 3; i++)
		cout << temp2[i]->GetIme() << endl;
	

	projekti[1] = projekti[0];
	projekti[2] = projekti[0];

	Uposlenik* temp3 = NajuspjesnijiUposlenik(projekti, 1);
	cout << endl << temp3->GetIme() << endl;


	system("pause");
	return 0;
}