#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<regex>
#include<iterator>
#include<mutex>
using namespace std;



const char* crt = "\n---------------------------------------\n";
class Izuzetak :public exception {
	//Datum _datum;//KORISTITE DANASNJI DATUM
	string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
	int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:
	Izuzetak(string funkcija, int linija, const char* poruka) : exception(poruka)
	{
		_funkcija = funkcija;
		_linija = linija;
	}
	friend ostream& operator<<(ostream& COUT, Izuzetak& obj)
	{
		COUT << obj._linija << ":::" << obj._funkcija << ":::" << obj.what() << crt;
		return COUT;
	}
};


char* Alociraj(const char* sadrzaj)
{
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
	void ADD(T1 el1, T2 el2)
	{
		_elementi1[*_trenutno] = el1;
		_elementi2[*_trenutno] = el2;
		(*_trenutno)++;
	}
public:
	Kolekcija() : _trenutno(new int(0)) {}
	Kolekcija(const Kolekcija& original) : _trenutno(new int(*original._trenutno))
	{
		for (int i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = original._elementi1[i];
			_elementi2[i] = original._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& druga)
	{
		if (this != &druga)
		{
			*_trenutno = *druga._trenutno;
			for (int i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = druga._elementi1[i];
				_elementi2[i] = druga._elementi2[i];
			}
		}
		return *this;
	}
	~Kolekcija() { delete _trenutno; _trenutno = nullptr; }
	int GetMax()const { return max; }
	int GetTrenutno()const { return *_trenutno; }
	T1& GetElement1(int indeks)
	{
		if (indeks<0 || indeks>* _trenutno)
			throw exception("Indeks nije validan!");
		return _elementi1[indeks];
	}
	T2& GetElement2(int indeks)
	{
		if (indeks<0 || indeks>* _trenutno)
			throw exception("Indeks nije validan!");
		return _elementi2[indeks];
	}
	T1 GetEl1(int indeks)const { return _elementi1[indeks]; }
	T2 GetEl2(int indeks)const { return _elementi2[indeks]; }
	void Clear() { *_trenutno = 0; }
	void AddElement(T1 el1, T2 el2)
	{
		if (*_trenutno >= GetMax())
			throw Izuzetak( __FUNCTION__,__LINE__, "Dosegli ste maksimum kolekcije!");
		ADD(el1, el2);
	}
	friend ostream& operator<<(ostream& COUT, Kolekcija& obj)
	{
		for (int i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << "   " << obj.GetElement2(i) << endl;
		return COUT;
	}

};

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
	int toDane()const {
		return *_godina * 365 + *_mjesec * 30 + *_dan;
	}
	bool operator>(const Datum& drugi)
	{
		return this->toDane() > drugi.toDane();
	}
	friend ostream& operator<< (ostream& COUT, Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
};


enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char* ispisKurseva[] = { "HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity" };
class Kurs {
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char* _imePredavaca;
public:
	Kurs(enumKursevi kurs = MasteringSQL, const char* imePredavaca = "---", Datum pocetak = Datum(), Datum kraj = Datum()) : _kurs(kurs), _imePredavaca(Alociraj(imePredavaca)), _pocetak(pocetak), _kraj(kraj) {}
	Kurs(const Kurs& original) : _kurs(original._kurs), _imePredavaca(Alociraj(original._imePredavaca)), _pocetak(original._pocetak), _kraj(original._kraj) {}
	Kurs& operator=(const Kurs& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePredavaca;
			_kurs = drugi._kurs;
			_imePredavaca = Alociraj(drugi._imePredavaca);
			_pocetak = drugi._pocetak;
			_kraj = drugi._kraj;
		}
		return *this;
	}
	~Kurs() { delete[] _imePredavaca; _imePredavaca = nullptr; }
	enumKursevi GetKurs() { return _kurs; }
	char* GetImePredavaca() { return _imePredavaca; }
	Datum& GetPocetakKursa() { return _pocetak; }
	Datum& GetKrajKursa() { return _kraj; }
	bool operator==(const Kurs& drugi)
	{
		return _kurs == drugi._kurs && strcmp(_imePredavaca, drugi._imePredavaca) == 0;
	}
	friend  ostream& operator<<(ostream& COUT, Kurs& obj)
	{
		COUT << "Naziv kursa -> " << ispisKurseva[obj._kurs] << "   Kurs pocinje -> " << obj._pocetak << "    Kurs zavrsava -> " << obj._kraj << endl;
		COUT << "Predavac kursa -> " << obj._imePredavaca << crt;
		return COUT;
	}

};

bool ProvjeriFormatTelefona(string broj)
{
	return regex_match(broj, regex("\\([0-9]{3}\\)[0-9]{3}-[0-9]{3}"));
}

class Polaznik {
	static int ID;
	const int _polaznikID;
	//SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
	char* _imePrezime;
	string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (061)123-311 
	Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
	//INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
	Polaznik(const char* imePrezime, string telefon) :_polaznikID(ID++) {
		_imePrezime = Alociraj(imePrezime);
		if(ProvjeriFormatTelefona(telefon))
			_kontaktTelefon = telefon;
		else
			_kontaktTelefon = "not_set";
	}
	Polaznik(const Polaznik& original) : _polaznikID(original._polaznikID), _imePrezime(Alociraj(original._imePrezime)), _kontaktTelefon(original._kontaktTelefon)
	{
		//ako u destruktoru stoji da se kurs dealocira znaci da ga trebamo praviti pri konst. kopije i dodavanju bilo gdje pisati new Kurs...
		for (int i = 0; i < original._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*original._uspjesnoOkoncaniKursevi.GetEl1(i)), original._uspjesnoOkoncaniKursevi.GetEl2(i));
		}
	}
	Polaznik& operator=(const Polaznik& drugi)
	{
		if (this != &drugi)
		{
			delete[] _imePrezime;
			_imePrezime = Alociraj(drugi._imePrezime);
			_kontaktTelefon = drugi._kontaktTelefon;
			//prvo delete svaki 
			for (int i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
			{
				delete _uspjesnoOkoncaniKursevi.GetElement1(i);
			}
			//pozvati funkciju clear
			_uspjesnoOkoncaniKursevi.Clear();
			//opet alocirati za novi
			for (int i = 0; i < drugi._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
			{
				_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*drugi._uspjesnoOkoncaniKursevi.GetEl1(i)), drugi._uspjesnoOkoncaniKursevi.GetEl2(i));
			}
		}
		return *this;
	}
	~Polaznik() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (int i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			delete _uspjesnoOkoncaniKursevi.GetElement1(i);
			_uspjesnoOkoncaniKursevi.GetElement1(i) = nullptr;
		}
	}
	char* GetImePolaznika() { return _imePrezime; }
	Kolekcija<Kurs*, int, 10> GetUspjesnoOkonacni() { return _uspjesnoOkoncaniKursevi; }
	int GetID() { return _polaznikID; }
	bool operator==(const Polaznik& drugi)
	{
		return strcmp(_imePrezime, drugi._imePrezime) == 0 && _kontaktTelefon == drugi._kontaktTelefon && _polaznikID == drugi._polaznikID;
	}
	void AddUspjesanKurs(Kurs& kurs, int postotak)
	{
		_uspjesnoOkoncaniKursevi.AddElement(new Kurs(kurs), postotak);
	}
	friend  ostream& operator<<(ostream& COUT, Polaznik& obj)
	{
		COUT << "Polaznik -> " << obj._imePrezime << "   ID polaznika -> " << obj._polaznikID << "   Kontakt -> " << obj._kontaktTelefon << endl;
		COUT << ":::: USPJESNO OKONCANI KURSEVI POLAZNIKA ::::" << crt;
		for (int i = 0; i < obj._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			COUT <<"Kurs -> "<< ispisKurseva[obj._uspjesnoOkoncaniKursevi.GetElement1(i)->GetKurs()] << "    Ostvareni procenat -> " << obj._uspjesnoOkoncaniKursevi.GetElement2(i) << endl;
		}
		return COUT;
	}
};


int Polaznik::ID = 1;

class SkillsCentar {
	string _nazivCentra;
	vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
	Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
	SkillsCentar(string naziv) { _nazivCentra = naziv; }
	SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti) {
		_nazivCentra = obj._nazivCentra;
	}
	friend ostream& operator<<(ostream& COUT, SkillsCentar& obj)
	{
		COUT << "Naziv centra -> " << obj._nazivCentra << endl;
		COUT << ":::KURSEVI KOJE CENTAR NUDI:::" << crt;
		for (int i = 0; i < obj._kursevi.size(); i++)
			COUT << "Kurs-> " << ispisKurseva[obj._kursevi[i].GetKurs()] << "      Predavac->  " << obj._kursevi[i].GetImePredavaca() << endl;
		COUT << crt;
		COUT << "::: APLIKANTI :::" << crt;
		for (int i = 0; i < obj._aplikanti.GetTrenutno(); i++)
		{
			COUT << "Polaznik -> " << obj._aplikanti.GetElement2(i)->GetImePolaznika() << "     Aplicirao za -> " << ispisKurseva[obj._aplikanti.GetElement1(i).GetKurs()] << endl;
		}
		return COUT;
	}
	bool ProvjeriKoliziju(Kurs& kurs)
	{
		for (int i = 0; i < _kursevi.size(); i++)
		{
			//provjeri da li je ijedan kurs iz vektora mladji od proslijedjenog,tj da li idalje traje
			if ( _kursevi[i].GetKrajKursa()>kurs.GetPocetakKursa())
				throw Izuzetak(__FUNCTION__, __LINE__, "Pokusavate dodati kurs koji vec traje!");
		}
		return true;
	}
	bool AddKurs(Kurs& kurs)
	{
		for (int i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i] == kurs)
				throw Izuzetak(__FUNCTION__, __LINE__, "Pokusavate dodati isti kurs!");

		}
		_kursevi.push_back(kurs);
		return true;
	}
	bool AddAplikaciju(Kurs& kurs, Polaznik& polaznik)
	{
		bool imaKurs = false;
		for (int i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i] == kurs)
				imaKurs = true;
		}

		if (!imaKurs)
			throw Izuzetak(__FUNCTION__, __LINE__, "Kurs nije registrovan u centru!");

		for (int i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if(_aplikanti.GetElement1(i)==kurs && *_aplikanti.GetElement2(i)==polaznik)
				throw Izuzetak(__FUNCTION__, __LINE__, "Pokusavate opet aplicirati za isti kurs!");
		}
		_aplikanti.AddElement(kurs, &polaznik);
		return true;
	}

	//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR.
		//PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
	void DodajUspjesnoOkoncanKurs(int ID, Kurs& kurs, int postotak)
	{
		for (int i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement2(i)->GetID() == ID && postotak>=55)//ukoliko postoji proslijedjeni ID i postotak je veci od 55 dodaje se uspjesan kurs
			{
				_aplikanti.GetElement2(i)->AddUspjesanKurs(kurs, postotak);
				return;
			}
		}
		throw Izuzetak(__FUNCTION__, __LINE__, "Polaznik nije aplicirao za trazeni kurs ili nije dobar ID");
	}

	//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

	vector<Polaznik> GetPolazniciByPredavac(const char* imePredavaca, enumKursevi kurs)
	{
		vector<Polaznik> novi;
		for (int i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			for (int j = 0; j < _aplikanti.GetElement2(i)->GetUspjesnoOkonacni().GetTrenutno(); j++)
			{
				if (strcmp(_aplikanti.GetElement2(i)->GetUspjesnoOkonacni().GetElement1(j)->GetImePredavaca(), imePredavaca) == 0 && _aplikanti.GetElement2(i)->GetUspjesnoOkonacni().GetElement1(j)->GetKurs() == kurs)
				{
					novi.push_back(*_aplikanti.GetElement2(i));
				}
			}
		}
		return novi;
	}

	bool RemoveKurs(Kurs& kurs)
	{
		for (vector<Kurs>::iterator i= _kursevi.begin(); i != _kursevi.end(); i++)
		{
			if (*i == kurs)
			{
				_kursevi.erase(i);//prodje se preko iteratora kroz kurseve i ako je isti onda ima ugradjena funkcija erase da se ukloni
				return true;
			}
		}
		return false;
	}
};
void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int, 10> kolekcija1;
	try
	{
		for (size_t i = 0; i < kolekcija1.GetMax(); i++)
			kolekcija1.AddElement(i, i + 2);
		//FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
		cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
		//cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
		//FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
	}
	catch (Izuzetak & err)
	{
		cout << "Greska -> " << err << endl;
	}
	catch (exception & err)
	{
		cout << "Greska -> " << err.what() << endl;
	}

	cout << kolekcija1 << endl;
	Kolekcija<int, int, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeKursa
	Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
	cout << sef << endl;
	Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
	sef = msql;
	if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
		cout << "ISTI SU KURSEVI" << endl;
	Kurs msql2(msql);
	cout << msql2 << endl;
#pragma endregion
#pragma region TestiranjePolaznika
	string telefon1 = "(061)111-111";
	string telefon2 = "(061)111222";
	string telefon3 = "(061)111-333";

	if (!ProvjeriFormatTelefona(telefon1))
		cout << "Broj " << telefon1 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon2))
		cout << "Broj " << telefon2 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon3))
		cout << "Broj " << telefon3 << " nije validan" << endl;


	Polaznik denis("Denis Music", telefon1);
	Polaznik denis2("Denis2 Music2", telefon3);

	cout << denis;

#pragma endregion

#pragma region TestiranjeCentra
	try {
		SkillsCentar mostar("Skills Center Mostar");
		if (mostar.ProvjeriKoliziju(sef))
			//JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA KURSA SE NE SMIJE POKLAPATI
		//ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
			mostar.AddKurs(sef);
		/*if (mostar.ProvjeriKoliziju(msql))
			mostar.AddKurs(msql);
		if (mostar.ProvjeriKoliziju(msql2))
			mostar.AddKurs(msql2);*/

		//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
//		//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
		mostar.AddAplikaciju(sef, denis);
		/*mostar.AddAplikaciju(msql, denis);
		mostar.AddAplikaciju(msql, denis);*/
		cout << denis2 << crt;
		denis2 = denis;
		if (denis == denis2)
			//POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
			cout << "ISTI SU" << endl;

		mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);
		mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);

		//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR.
		//PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%

		vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Adel Handzic", MasteringSQL);
		
		//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

		if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
			cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

		SkillsCentar sarajevo = mostar;
		cout << sarajevo << endl;
	}
	catch (Izuzetak & err) {
		cout << err << endl;
	}
#pragma endregion
	system("pause");
}