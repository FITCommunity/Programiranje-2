#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<mutex>
#include<thread>
#include<exception>
#include<sstream>
using namespace std;


const char* crt = "\n------------------------------\n";
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
	Datum(const Datum& dat) {
		_dan = new int(*dat._dan);
		_mjesec = new int(*dat._mjesec);
		_godina = new int(*dat._godina);
	}
	Datum& operator=(const Datum& drugi)
	{
		if (this != &drugi)
		{
			*_dan = *drugi._dan;
			*_mjesec = *drugi._mjesec;
			*_godina = *drugi._godina;
		}
		return  *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
	char* ToCharArray()
	{
		stringstream ss;
		ss << *_dan << "." << *_mjesec << "." << *_godina << endl;
		int vel = ss.str().length() + 1;
		char* temp = new char[vel];
		strcpy_s(temp, vel, ss.str().c_str());
		return temp;
	}
	bool operator==(const Datum& drugi)
	{
		return *_godina == *drugi._godina && *_mjesec == *drugi._mjesec && *_dan == *drugi._dan;
	}
	
	//nije potrebna dodatna provjera ako dan prelazi 31 da se uveca mjesec i tako za godine,dovoljno je ovo
	Datum& operator++(int)
	{
		(*_dan)++;
		return *this;
	}



};





class Izuzetak : public exception {
	string _funkcija;
public:
	Izuzetak(string funkcija, const char* poruka) : exception(poruka), _funkcija(funkcija){	}
	friend ostream& operator<<(ostream& cout, Izuzetak& obj)
	{
		cout << obj._funkcija << "         " << obj.what() << crt;
		return cout;
	}
};

template <class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutnoElemenata;
	bool _omoguciDupliranjeElemenata;
	void Alociraj(const Kolekcija& nova)
	{
		_elementi1 = new T1[_trenutnoElemenata];
		_elementi2 = new T2[_trenutnoElemenata];
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = nova._elementi1[i];
			_elementi2[i] = nova._elementi2[i];
		}
	}
	void Dealociraj()
	{
		delete[]_elementi2;
		delete[]_elementi1;
	}
	bool ProsiriNiz(T1 el1, T2 el2)
	{
		T1* temp1 = new T1[_trenutnoElemenata + 1];
		T2* temp2 = new T2[_trenutnoElemenata + 1];
		for (int i = 0; i < _trenutnoElemenata; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		Dealociraj();
		temp1[_trenutnoElemenata] = el1;
		temp2[_trenutnoElemenata] = el2;
		_trenutnoElemenata++;
		_elementi1 = temp1; temp1 = nullptr;
		_elementi2 = temp2; temp2 = nullptr;
		return true;
	}
public:
	Kolekcija(bool omoguciDupliranjeElemenata = false) {
		_trenutnoElemenata = 0;
		_omoguciDupliranjeElemenata = omoguciDupliranjeElemenata;
		_elementi1 = nullptr;
		_elementi2 = nullptr;
	}
	Kolekcija(const Kolekcija& original) : _trenutnoElemenata(original._trenutnoElemenata)
	{
		_omoguciDupliranjeElemenata = original._omoguciDupliranjeElemenata;
		Alociraj(original);
	}
	Kolekcija& operator=(const Kolekcija& drugi)
	{
		if (this != &drugi)
		{
			_trenutnoElemenata = drugi._trenutnoElemenata;
			if (_trenutnoElemenata != 0)
			{
				Dealociraj();
				Alociraj(drugi);
			}
		}
		return *this;
	}
	~Kolekcija()
	{
		delete[]_elementi2; _elementi2 = nullptr;
		delete[]_elementi1; _elementi1 = nullptr;
		_trenutnoElemenata = 0;
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	T1& GetElement1(int lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) const
	{
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw Izuzetak("Nepostojeca lokacija", __FUNCTION__);
		return _elementi2[lokacija];
	}
	void SetElement2(int lokacija,bool zavrsena){ _elementi2[lokacija] = zavrsena;}
	bool AddElement(T1 el1, T2 el2)
	{
		for (int i = 0; i < _trenutnoElemenata; i++)
			if (!_omoguciDupliranjeElemenata && (_elementi1[i] == el1 && _elementi2[i] == el2))
				return false;
		ProsiriNiz(el1, el2);
	}
	void RemoveElement(int lokacija)
	{
		for (int i = lokacija; i < _trenutnoElemenata; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutnoElemenata--;
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};



class Dogadjaj
{
	Datum _datumOdrzavanja;
	Kolekcija<string, bool>* _obaveze; //cuva informaciju o obavezama koje je potrebno ispuniti prije samog dogadjaja, string se odnosi na opis, a bool na izvrsenje te obaveze (da li je zavrsena ili ne)

	char* _naziv;
	int _notificirajPrije; //oznacava broj dana prije samog dogadjaja kada ce krenuti notifikacija/podsjetnik
	bool _rekurzivnaNotifikacija; //ako je vrijednost true onda se korisnik notificira svaki dan do _datumaOdrzavanja dogadjaja, a pocevsi prije dogadjaja za _brojDanaZaNotifikaciju
	bool ValidanFormat(string obaveza)
	{
		return !regex_search(obaveza, regex("(ustipak|mutekz|rat)"));
	}
public:
	Dogadjaj(Datum datumOdrzavanja, const char* naziv, int brojDana = 1,
		bool rekurzivnaNotifikacija = false) : _datumOdrzavanja(datumOdrzavanja)
	{
		_naziv = Alociraj(naziv);
		_notificirajPrije = brojDana;
		_rekurzivnaNotifikacija = rekurzivnaNotifikacija;
		_obaveze = new Kolekcija<string,bool>;
	}
	Dogadjaj(const Dogadjaj& obj) : _datumOdrzavanja(obj._datumOdrzavanja), _naziv(Alociraj(obj._naziv)), _notificirajPrije(obj._notificirajPrije), _rekurzivnaNotifikacija(obj._rekurzivnaNotifikacija)
	{
		_obaveze = new Kolekcija<string, bool>(*obj._obaveze);
	}
	Dogadjaj& operator=(const Dogadjaj& drugi)
	{
		if (this != &drugi)
		{
			_datumOdrzavanja = drugi._datumOdrzavanja;
			*_obaveze = *drugi._obaveze;
			_naziv = Alociraj(drugi._naziv);
			_notificirajPrije = drugi._notificirajPrije;
			_rekurzivnaNotifikacija = drugi._rekurzivnaNotifikacija;
		}
		return *this;
	}
	~Dogadjaj()
	{
		delete[] _naziv;_naziv = nullptr;
		delete _obaveze;_obaveze = nullptr;
	}
	char* GetNaziv() { return _naziv; }
	Datum GetDatumOdrzavanja() const { return _datumOdrzavanja; }
	bool GetRekurzivnaNotifikacija()
	{
		return _rekurzivnaNotifikacija;
	}
	Kolekcija<string, bool>* GetObaveze() { return _obaveze; }
	bool AddObavezu(string obaveza)
	{
		//ako je validan format proslijedjene obaveze prodje se kroz obaveze i provjeri ima li ista, ako nema onda je dodamo 
		if (ValidanFormat(obaveza))
		{
			for (int i = 0; i < _obaveze->GetTrenutno(); i++)
				if (_obaveze->GetElement1(i) == obaveza)
					return false;
			return _obaveze->AddElement(obaveza, false);
		}
		return false;
	}
	float PostotakObavljenih()
	{
		float ukupno = _obaveze->GetTrenutno();
		int brojac = 0;
		for (int i = 0; i < _obaveze->GetTrenutno(); i++)
			if (_obaveze->GetElement2(i))
				brojac++;
		return brojac / ukupno * 100;
	}
	void IspisPreostalihObaveza() 
	{
		for (int i = 0; i < _obaveze->GetTrenutno(); i++)
			if (!_obaveze->GetElement2(i))
				cout << _obaveze->GetElement1(i) << endl;
		cout << crt;
	}
	friend ostream& operator<<(ostream& cout, Dogadjaj& obj)
	{
		cout << "Naziv dogadjaja->   " << obj.GetNaziv() << crt;
		cout << "Datum odrzavanja->  " << obj._datumOdrzavanja << "        Dogadjaj krece za ->  " << obj._rekurzivnaNotifikacija << endl;
		for (int i = 0; i < obj.GetObaveze()->GetTrenutno(); i++)
			cout << "Obaveza -> " << obj.GetObaveze()->GetElement1(i) << crt;
		return cout;
	}
};

class Student
{
	int _indeks;
	string _imePrezime;
	vector<Dogadjaj> _dogadjaji;
public:

	Student(int indeks, string imePrezime) : _indeks(indeks), _imePrezime(imePrezime) {}
	int GetIndeks() const { return _indeks; }
	vector<Dogadjaj>& GetDogadjaji()  { return _dogadjaji; }
	string GetImePrezime() { return _imePrezime; }
	bool AddDogadjaj(Dogadjaj& dogadjaj)
	{
		for (int i = 0; i < _dogadjaji.size(); i++)
			if (strcmp(_dogadjaji[i].GetNaziv(), dogadjaj.GetNaziv()) == 0)
				return false;
		_dogadjaji.push_back(dogadjaj);
		return true;
	}
	friend ostream& operator<<(ostream& COUT, const Student& obj)
	{
		COUT <<"Student-> "<< obj._imePrezime << " (" << obj._indeks << ")" << endl;
		return COUT;
	}
};


mutex mutegz;

class DLWMSReminder
{
	vector<Student> _reminiderList;
	//pogledati na youtube prof. Larisa je uradila ovu funkciju koja je dosta jednostavnija da posalje samo jednu obavijest,u ovoj funkciji sam je ja shvatio kako bi trebalo svaki dan slati kao u pravom zivotu
	void PosaljiPoruku(Datum& Maindatum,int & brojac)
	{
		for (int i = 0; i < _reminiderList.size(); i++)
		{
			for (int j = 0; j < _reminiderList[i].GetDogadjaji().size(); j++)
			{
				for (int k = 0; k < _reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetTrenutno(); k++)
				{

					Datum temp= Datum(Maindatum);
					if (_reminiderList[i].GetDogadjaji()[j].GetRekurzivnaNotifikacija())
					{


						while (!(temp==_reminiderList[i].GetDogadjaji()[j].GetDatumOdrzavanja()))/*&& !_reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetElement2(k)*/
						{
							mutegz.lock();


							cout << "Postovani " << _reminiderList[i].GetImePrezime()<<"," << endl;
							cout << "Dogadjaj "<<_reminiderList[i].GetDogadjaji()[j].GetNaziv()<<" je za "<<_reminiderList[i].GetDogadjaji()[j].GetDatumOdrzavanja().getRazlikaUDanima(temp) << " dana,a do sada ste obavili ";
							cout << "a vi ste do sada obavili " << _reminiderList[i].GetDogadjaji()[j].PostotakObavljenih() << "% obaveza vezanih za ovaj dogadjaj."<<endl;
							cout << "Neispunjene obaveze su: " << crt;
							_reminiderList[i].GetDogadjaji()[j].IspisPreostalihObaveza();
							cout << "Predlazemo Vam da ispunite i ostale planirane obaveze." << endl;
							cout << "FIT Reminder" << crt;
							mutegz.unlock();


							brojac++;
							temp++;
						}


					}else {
						mutegz.lock();


						cout << "Poštovani " << _reminiderList[i].GetImePrezime() << "," << endl;
						cout << _reminiderList[i].GetDogadjaji()[j].GetDatumOdrzavanja().getRazlikaUDanima(temp) << " dana,a do sada ste obavili ";
						cout << "a vi ste do sada obavili " << _reminiderList[i].GetDogadjaji()[j].PostotakObavljenih() << "% obaveza vezanih za ovaj dogadjaj.";
						cout << "Neispunjene obaveze su: " << endl;
						_reminiderList[i].GetDogadjaji()[j].IspisPreostalihObaveza();
						cout << "Predlazemo Vam da ispunite i ostale planirane obaveze." << endl;
						cout << "FIT Reminder" << crt;


						mutegz.unlock();
						brojac++;
					}



				}
			}
		}
	}
	
public:
	bool AddStudent(Student& student)
	{
		for (int i = 0; i < _reminiderList.size(); i++)
			if (_reminiderList[i].GetImePrezime() == student.GetImePrezime())
				throw Izuzetak(__FUNCTION__, "Nije moguce dodati istog studenta....");
		_reminiderList.push_back(student);
		return true;
	}
	bool OznaciObavezuKaoZavrsenu(int indeks, const char* nazivDogadjaja, string obaveza)
	{
		for (int i = 0; i < _reminiderList.size(); i++)
		{
			if (_reminiderList[i].GetIndeks() == indeks)
			{
				for (int j = 0; j < _reminiderList[i].GetDogadjaji().size(); j++)
				{
					if (strcmp(_reminiderList[i].GetDogadjaji()[j].GetNaziv(), nazivDogadjaja) == 0)
					{
						for (int k = 0; k < _reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetTrenutno(); k++)
						{
							if (_reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetElement1(k) == obaveza && !_reminiderList[i].GetDogadjaji()[j].GetObaveze()->GetElement2(k))
							{
								_reminiderList[i].GetDogadjaji()[j].GetObaveze()->SetElement2(k, true);
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}
	int PosaljiNotifikacije(Datum& datum)
	{
		int poslano = 0;
		thread t1(&DLWMSReminder::PosaljiPoruku, this, ref(datum), ref(poslano));
		t1.join();
		return poslano;
	}
};

void main() {

	/**************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_ParcijalniII.TXT
	5. NAZIVI FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI PO ŽELJI.
	****************************************************************************/

#pragma region Datum

	Datum danas(28, 1, 2018), sutra(29, 1, 2018);
	Datum datumIspitaPRIII(30, 1, 2018), datumIspitBPII(31, 1, 2018);
	Datum prekosutra(danas);
	prekosutra = danas;
	cout << danas << endl
		<< sutra << endl
		<< prekosutra << crt;

#pragma endregion

#pragma region Kolekcija

	/*
	AddElement :: omogucava dodavanje novog elementa u kolekciju. Ukoliko je moguce, osigurati automatsko prosiranje kolekcije prilikom dodavanja svakog novog elementa, te onemoguciti ponavljanje elemenata
	RemoveElement :: na osnovu parametra tipa T1 uklanja elemente iz kolekcije i ukoliko je moguce smanjuje velicinu niza/kolekcije. Prilikom uklanjanja elemenata ocuvati redoslijed njihovog dodavanja
	*/
	const int brElemenata = 10;
	Kolekcija<int, float> kolekcija1;
	for (size_t i = 0; i < brElemenata; i++)
		if (!kolekcija1.AddElement(i, i + (0.6 * i)))
			cout << "Elementi " << i << " i " << i + (0.6 * i) << " nisu dodati u kolekciju" << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;

	kolekcija1.RemoveElement(1);

	Kolekcija<int, float> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;

	Kolekcija<int, float> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;

#pragma endregion

#pragma region Dogadjaj

	Dogadjaj ispitPRIII(datumIspitaPRIII, "Ispit iz PRIII", 5, true),
		ispitBPII(datumIspitBPII, "Ispit iz BPII", 7, true);
//	/*po vlasitom izboru definisati listu zabranjenih rijeci koje ce onemoguciti dodavanje odredjene obaveze. Prilikom provjere koristiti regex*/
	if (ispitPRIII.AddObavezu("Preraditi pdf materijale"))cout << "Obaveza dodana!" << endl;
	//onemoguciti dupliranje obaveza
	//if (!ispitPRIII.AddObavezu("Preraditi pdf materijale role"))cout << "Obaveza nije dodana!" << endl;
	if (ispitPRIII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Preraditi ispitne zadatke"))cout << "Obaveza dodana!" << endl;
	if (ispitPRIII.AddObavezu("Samostalno vjezbati"))cout << "Obaveza dodana!" << endl;

	if (ispitBPII.AddObavezu("Preraditi knjigu SQL za 24 h"))cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Pregledati video materijale"))cout << "Obaveza dodana!" << endl;
	if (ispitBPII.AddObavezu("Napraviti bazu za konkretnu aplikaciju"))cout << "Obaveza dodana!" << endl;

	Student jasmin(150051, "Jasmin Azemovic"), adel(160061, "Adel Handzic");
	
	if (jasmin.AddDogadjaj(ispitPRIII) && jasmin.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;

	if (adel.AddDogadjaj(ispitPRIII) && adel.AddDogadjaj(ispitBPII))
		cout << "Dogadjaj uspjesno dodan!" << endl;
	//onemoguciti dupliranje dogadjaja
	if (!adel.AddDogadjaj(ispitPRIII))
		cout << "Dogadjaj nije uspjesno dodan!" << crt;

	DLWMSReminder reminder;

	try
	{
		reminder.AddStudent(jasmin);
		reminder.AddStudent(adel);
		//u slucaju dupliranja studenata funkcija baca izuzetak tipa Izuzetak
		//reminder.AddStudent(jasmin);
	}
	catch (Izuzetak & err)
	{
		//ispisati sve informacije o nastalom izuzetku
		cout << err << crt;
	}
	catch (exception & err)
	{
		//ispisati sve informacije o nastalom izuzetku
		cout << err.what() << crt;
	}

	//da bi bila oznacena kao zavrsena, obaveza mora postojati i mora biti oznacena kao nezavrsena (false)
	//salje se indeks, naziv Dogadjaja,string obaveza
	if (reminder.OznaciObavezuKaoZavrsenu(150051, "Ispit iz PRIII", "Pregledati video materijale"))
		cout << "Obaveza oznacena kao zavrsena" << endl;

	/*metodi PosaljiNotifikacije se salje trenutni datum na osnovu cega ona pretrazuje sve studente koje treba podsjetiti/notoficirati o dogadjajima koji se priblizavaju.
	Koristeci multithread-ing, svim studentima se salju notifikacije sa sljedecim sadrzajem:
	-------------------------------------------------------------------------
	Postovani Jasmin Azemovic,
	Dogadjaj Ispit iz PRIII je zakazan za 3 dana, a do sada ste obavili 56% obaveza vezanih za ovaj dogadjaj. Neispunjene obaveze su:
	1.Preraditi ispitne zadatke
	2.Samostalno vjezbati
	Predlazemo Vam da ispunite i ostale planirane obaveze.
	FIT Reminder
	-------------------------------------------------------------------------
	Dakle, notifikacije ce biti poslane svim studentima koji su dodali dogadjaj za 30.01.2018. godine i oznacili da zele da budu podsjecani ponovo/rekurzivno najmanje 2 dana prije samog dogadjaja (podaci se odnose na konkretan dogadjaj: Ispit iz PRIII)
	*/
	int poslato = 0;
	//funkcija vraca broj poslatih podsjetnika/notifikacija
	poslato = reminder.PosaljiNotifikacije(danas);
	cout << "Za " << danas << " poslato ukupno " << poslato << " podsjetnika!" << crt;
	poslato = reminder.PosaljiNotifikacije(sutra);
	cout << "Za " << sutra << " poslato ukupno " << poslato << " podsjetnika!" << endl;

#pragma endregion

}
