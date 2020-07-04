#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<thread>
#include<exception>
#include<mutex>
#include<chrono>
using namespace std;

const char* crt = "\n---------------------------------------\n";
char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}


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
	bool operator==(const DatumVrijeme& drugi)
	{
		return *_dan == *drugi._dan && *_mjesec == *drugi._mjesec && *_godina == *drugi._godina && *_sati == *drugi._sati && *_minuti == *drugi._minuti;
	}
	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << "-> " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
};

template<class T1, class T2 = int>
class FITKolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija& original) : _trenutno(original._trenutno)
	{
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	FITKolekcija& operator=(const FITKolekcija& drugi)
	{
		if (this != &drugi)
		{
			if (_trenutno != 0)
			{
				delete[] _elementi1;
				delete[] _elementi2;
			}
			_trenutno = drugi._trenutno;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = drugi._elementi1[i];
				_elementi2[i] = drugi._elementi2[i];
			}
		}
		return *this;
	}
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}

	T1* GetT1() { return _elementi1; }
	T2* GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }
	void Dodaj(T1 el1, T2 el2)
	{
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;
		temp1[_trenutno] = el1;
		temp2[_trenutno] = el2;
		_trenutno++;
		_elementi1 = temp1;temp1=nullptr;
		_elementi2 = temp2;temp2=nullptr;
	}
	void Sortiraj()
	{
		bool prolaz = true;
		while (prolaz)
		{
			prolaz = false;
			for (int i = 0; i < _trenutno-1; i++)
			{
				if (_elementi1[i] > _elementi1[i + 1])
				{
					T1 temp1 = _elementi1[i];
					_elementi1[i] = _elementi1[i + 1];
					_elementi1[i + 1] = temp1;

					T2 temp2 = _elementi2[i];
					_elementi2[i] = _elementi2[i + 1];
					_elementi2[i + 1] = temp2;
					prolaz = true;
				}
			}
		}
	}

	void DodajNaLokaciju(T1 el1, T2 el2, int lokacija)
	{
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			if (i == lokacija)
			{
				temp1[i] = el1;
				temp2[i] = el2;
			}
			else {
				temp1[i] = _elementi1[i];
				temp2[i] = _elementi2[i];
			}
		}
		delete[] _elementi1;
		delete[] _elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
	}
	FITKolekcija<T1, T2>* GetJedinstveni()
	{
		FITKolekcija<T1, T2>* nova = new FITKolekcija<T1, T2>;
		//pravimo novu kolekciju koja se vraca u funkciji
		for (int i = 0; i < _trenutno; i++)
		{
			bool ima = false;
			for (int j = 0; j < nova->GetTrenutno(); j++)
			{
				if (_elementi1[i] == nova->GetT1()[j] || _elementi2[i] == nova->GetT2()[j])//prodjemo kroz obe ako ne postoji element isti onda dodamo u novu 
					ima = true;
			}
			if (!ima)
				nova->Dodaj(_elementi1[i], _elementi2[i]);
		}
		return nova;
	}
	void Ukloni(int indeks)
	{
		for (int i = indeks; i < _trenutno-1; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;
	}
	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj) {
		for (int i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
const char* ispisVrsteDoc[] = { "PDF", "DOC", "TXT", "HTML" };

class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica(int broj) { _brojStranica+=broj; }
	int GetBrojStranica() { return _brojStranica; }
	friend ostream& operator<<(ostream& COUT, Dokument& obj) {
		COUT << "Dokument -> "<<obj._naziv << "." << ispisVrsteDoc[obj._vrsta] << " Broj stranica (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
	void DodajSadrzaj(string sadrzaj)
	{
		_sadrzaj += sadrzaj;
		int broj = _sadrzaj.length() / 30;//kad se doda na sadrzaj uzme se citav lenght i podijeli sa 30, dobijeni broj je onoliko koliko treba uvecati broj stranica
		UvecajBrojStranica(broj);
	}
	
};
class Uredjaj {
protected:
	char* _proizvodjac;
	char* _model;
public:
	Uredjaj(const char* proizvodjac, const char* model) {
		_proizvodjac = Alociraj(proizvodjac);
		_model = Alociraj(model);
	}
	Uredjaj(const Uredjaj& original) : _proizvodjac(Alociraj(original._proizvodjac)), _model(Alociraj(original._model)) {}
	Uredjaj& operator=(const Uredjaj& drugi)
	{
		if (this != &drugi)
		{
			delete[] _proizvodjac;
			delete[] _model;
			_proizvodjac = Alociraj(drugi._proizvodjac);
			_model = Alociraj(drugi._model);
		}
		return *this;
	}
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Uredjaj& obj) {
		COUT << obj._proizvodjac <<"." << obj._model << endl;
		return COUT;
	}
	virtual void info() = 0;
};

bool ValidanNaziv(string naziv)
{
	return regex_match(naziv, regex("[a-zA-Z]{5,15}\\.(pdf|doc|txt|html)"));
}

mutex mjuteks;
void ispisi(string sadrzaj)
{
	mjuteks.lock();
	cout << "::::::::::: Sadrzaj koji se printa ::::::::::::::" << crt;
	cout << sadrzaj << crt;
	this_thread::sleep_for(chrono::seconds(2));
	mjuteks.unlock();
}

class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	void info(){}
	Printer(const char* proizvodjac, const char* model) : Uredjaj(proizvodjac, model) {}
	Printer(const Printer& original) : Uredjaj(original), _printaniDokumenti(original._printaniDokumenti), _zabranjeneRijeci(original._zabranjeneRijeci) {}
	Printer& operator=(const Printer& drugi)
	{
		if (this != &drugi)
		{
			Uredjaj::operator=(drugi);
			_zabranjeneRijeci = drugi._zabranjeneRijeci;
			_printaniDokumenti = drugi._printaniDokumenti;
		}
		return *this;
	}
	FITKolekcija<DatumVrijeme, Dokument>& GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string>& GetZabranjeneRijeci() { return _zabranjeneRijeci; };
	char* GetProizvodjac() { return _proizvodjac; }
	char* GetModel() { return _model; }
	void DodajZabranjenuRijec(string rijec)
	{
		for (vector<string>::iterator i = _zabranjeneRijeci.begin(); i != _zabranjeneRijeci.end(); i++)
			if (*i == rijec) return;
		_zabranjeneRijeci.push_back(rijec);
	}
	bool ValidanNaziv(Dokument& dokument)
	{
		return regex_match(dokument.GetNaziv(), regex("[a-zA-z]{5,15}.(pdf|doc|txt|html)"));
	}

	bool ValidanSadrzaj(string sadrzaj)
	{
		bool imaRijec = false;
		for (vector<string>::iterator i = _zabranjeneRijeci.begin(); i != _zabranjeneRijeci.end(); i++)
		{
			if (regex_search(sadrzaj, regex(*i)))//regex pravilo je zapravo ta rijec,a prodjemo kroz citav proslijedjeni sadrzaj
				imaRijec = true;
		}
		if (imaRijec)
			return false;
		return true;
	}

	void Printaj(DatumVrijeme& datumPrinta,Dokument& dokument)
	{
		_printaniDokumenti.Dodaj(datumPrinta, dokument);//mora se dodati na pocetku bez obzira da li je validan
		if (ValidanNaziv(dokument) && ValidanSadrzaj(dokument.GetSadrzaj()))
		{
			cout << "--- Sadrzaj koji se printa-----\n";
			cout << dokument.GetSadrzaj() << endl;
			return;
		}
		throw exception("Dokument nije validan za printanje!");
	}
	
	string GetTopZabranjenuRijec()
	{
		int brojac_najvece = 0;
		int trenutna_iteracija = 0;
		vector<string>::iterator rijec = _zabranjeneRijeci.begin();

		for (vector<string>::iterator i = _zabranjeneRijeci.begin(); i != _zabranjeneRijeci.end(); i++)
		{
			trenutna_iteracija = 0;
			for (int j = 0; j < _printaniDokumenti.GetTrenutno(); j++)
			{
				if (regex_search(_printaniDokumenti.GetT2()[j].GetSadrzaj(), regex(*i)))
					trenutna_iteracija++;
			}

			if (trenutna_iteracija > brojac_najvece)
			{
				brojac_najvece = trenutna_iteracija;
				rijec = i;
			}

		}
		return *rijec;
	}
	void UkloniDokumente()
	{
		for (int i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (!ValidanNaziv(_printaniDokumenti.GetT2()[i]) || !ValidanSadrzaj(_printaniDokumenti.GetT2()[i].GetSadrzaj()))
			{
				_printaniDokumenti.Ukloni(i);
			}
		}
	}
	friend ostream& operator<<(ostream& COUT, Printer& obj)
	{
		COUT << "\nPrinter ->  " << obj.GetProizvodjac() << "." << obj.GetModel() << endl;
		COUT << "Zabranjene rijeci za ovaj printer: " << crt;
		for (vector<string>::iterator i = obj._zabranjeneRijeci.begin(); i != obj._zabranjeneRijeci.end(); i++)
		{
			COUT << *i << endl;
		}
		COUT << "Naziv dokumenata koji su isprintani: " << crt;

		for (int i = 0; i < obj._printaniDokumenti.GetTrenutno(); i++)
			COUT << obj._printaniDokumenti.GetT2()[i].GetNaziv() << endl;

		return COUT;
	}
};

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

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int>* jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;

	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	Printer hp3200("HP", "3200");
	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/*
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA
		*/
		hp3200.Printaj(danas, ispitBaze);
		hp3200.Printaj(danas, ispitBaze);
		hp3200.Printaj(danas, ispitPRIII); //zakomentarisano zato sto baci exception jer ima zabranjenu rijec

		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
		*/
		
	}
	catch (exception & err)
	{
		cout <<"\n"<< err.what() << endl;
	}

	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion
}