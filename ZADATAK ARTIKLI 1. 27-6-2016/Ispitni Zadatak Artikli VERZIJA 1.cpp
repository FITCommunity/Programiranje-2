#include <iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

const char* crt = "\n----------------------------------------------------\n";
int brojacRacuna = 0;
char* Alociraj(const char* sadrzaj)
{
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
template<class T1, class T2>
class Kolekcija
{
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
    Kolekcija& operator=(const Kolekcija& druga)
    {
        if (this != &druga)
        {
            if (*_trenutno != 0)
            {
                delete[] _elementi1;
                delete[] _elementi2;
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
    //1. potrebne funkcije	
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int indeks)
    {
        if (indeks<0 || indeks>* _trenutno)
            throw exception("Indeks nije validan!");
        return _elementi1[indeks];
    }  
    T2& getElement2(int indeks)
    {
        if (indeks<0 || indeks>* _trenutno)
            throw exception("Indeks nije validan!");
        return _elementi2[indeks];
    }
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
        _elementi1 = temp1;temp1=nullptr;
        _elementi2 = temp2;temp2=nullptr;
    }
    friend ostream& operator<<(ostream& COUT, Kolekcija& obj)
    {
        for (int i = 0; i < obj.getTrenutno(); i++)
        {
            COUT << obj.getElement1(i) << "    " << obj.getElement2(i) << endl;
        }
        return COUT;
    }
};


class Datum
{
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000)
    {
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
    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
    //1. potrebne funkcije
};
class Osoba
{
protected:
    char* _imePrezime;
    Datum* _datumRodjenja;
public:
    Osoba(const char* imePrezime, Datum datum)
    {
        _imePrezime = Alociraj(imePrezime);
        _datumRodjenja = new Datum(datum);
    }
    Osoba(const Osoba& obj)
    {
        _imePrezime = Alociraj(obj._imePrezime);
        _datumRodjenja = new Datum(*obj._datumRodjenja);
    }
    Osoba& operator=(const Osoba& druga)
    {
        if (this != &druga)
        {
            delete[] _imePrezime;
            delete _datumRodjenja;
            _imePrezime = Alociraj(druga._imePrezime);
            _datumRodjenja = new Datum(*druga._datumRodjenja);
        }
        return *this;
    }
    ~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
    virtual void info() = 0;
    //1. potrebne funkcije
};


class Kupac : public Osoba
{
    //svaki kupac ima popust koji mu se zaracunava prilikom svake kupovine
    //pocetni popust je 0.10%
    //svaka kupovina u iznosu 100 - 500KM povecava iznos popusta za 0.15%
    //svaka kupovina u iznosu 500 - 1000KM povecava iznos popusta za 0.25%
    //svaka kupovina u iznosu vecem od 1000KM povecava iznos popusta za 0.30%
    float _odobreniPopust;
public:
    void info() {}
    //1. potrebne funkcije
    Kupac(const char* imePrezime, Datum datum) : Osoba(imePrezime, datum)
    {
        _odobreniPopust = 0.10;
    }
    Kupac(const Kupac& original) : Osoba(original)
    {
        _odobreniPopust = original._odobreniPopust;
    }
    Kupac& operator=(const Kupac& drugi)
    {
        if (this != &drugi)
        {
            Osoba::operator=(drugi);
            _odobreniPopust = drugi._odobreniPopust;
        }
        return *this;
    }
   /* ~Kupac()  //ne treba destruktor izvedenoj klasi ako ona nema nikakav doticaj sa dinamickom memorijom
    {
        delete[] _imePrezime; delete _datumRodjenja;
    }*/
    char* GetImeKupca() { return _imePrezime; }
    float GetPopust() { return _odobreniPopust; }
    Datum& GetDatumRodjenja() { return *_datumRodjenja; }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj)
    {
        COUT << "Kupac:  " << obj._imePrezime << "     Datum rodjenja->  " << *obj._datumRodjenja << endl;
        COUT << "Kupac ima odobren popust ->  " << obj._odobreniPopust << "%" << crt;
        return COUT;
    }
};
class Artikal
{
    string _barCode;
    char* _naziv;
    float _cijena;
public:
    Artikal(const char* naziv, float cijena, string barCode)
    {
        _naziv = Alociraj(naziv);
        _cijena = cijena;
        _barCode = barCode;
    }
    Artikal(const Artikal& original) : _naziv(Alociraj(original._naziv)), _barCode(original._barCode), _cijena(original._cijena) {}
    Artikal& operator=(const Artikal& drugi)
    {
        if (this != &drugi)
        {
            delete[] _naziv;
            _naziv = Alociraj(drugi._naziv);
            _barCode = drugi._barCode;
            _cijena = drugi._cijena;
        }
        return *this;
    }
    ~Artikal() { delete[]_naziv; _naziv = nullptr; }
    char* GetNaziv()
    {
        return _naziv;
    }
    float GetCijena()
    {
        return _cijena;
    }
    friend ostream& operator<< (ostream& COUT, const Artikal& obj)
    {
        COUT << obj._naziv << " " << obj._cijena << " KM" << endl;
        return COUT;
    }
    bool operator==(const Artikal& drugi)
    {
        return _barCode == drugi._barCode && strcmp(_naziv, drugi._naziv) == 0 && _cijena == drugi._cijena;
    }
    //1. potrebne funkcije
};
class Racun
{
    //format broja racuna: RN6005491
    //osigurati automatsko generisanje broja racuna pocevsi od RN0000001
    char _brojRacuna[10];
    Datum _datumKreiranja;
    //prvi argument je Artikal, a drugi kolicina/broj artikala koju je kupac uzeo
    Kolekcija<Artikal*, int>* _stavkeRacuna;
    Kupac* _kupac;
public:
    // 1. potrebne (de)konstruktor i druge funkcije
    // 2. DodajArtikal - dodaje novi artikal u listu artikala zajedno sa njegovom kolicinom. Onemoguciti ponavljanje 
    //    artikala na nacin da se uvecava samo kolicina ukoliko korisnik vise puta pokusa dodati isti artikal.
    // 3. operator<< - ispisuje racun u formatu prikazanom na slici(nije obavezno da bude identican, ali je svakako pozeljno).
    //    Nakon ispisa svakog racuna, ukoliko su ispunjeni definisani uslovi, kupcu se uvecava popust.
    // 4. Sortiraj - sortira artikle (rastuci) po kolicini novca kojom ucestvuju u ukupnom iznosu racuna
    Racun(string brojRacuna , Datum datumKreiranja, Kupac* kupac)
    {
        strcpy_s(_brojRacuna, 10, brojRacuna.c_str());
        _datumKreiranja = datumKreiranja;
        _stavkeRacuna = new  Kolekcija<Artikal*, int>;
        _kupac = new Kupac(*kupac);
    }
    
    Racun(const Racun& original) : _datumKreiranja(original._datumKreiranja)
    {
        strcpy_s(_brojRacuna, 10, original._brojRacuna);
        _stavkeRacuna = new  Kolekcija<Artikal*, int>(*original._stavkeRacuna);
        _kupac = new Kupac(*original._kupac);
    }

    Racun& operator=(const Racun& drugi)
    {
        if (this != &drugi)
        {
            delete _stavkeRacuna;
            delete _kupac;
            _kupac = new Kupac(*drugi._kupac);
            _stavkeRacuna=new  Kolekcija<Artikal*, int>(*drugi._stavkeRacuna);
            _datumKreiranja = drugi._datumKreiranja;
        }
        return *this;
    }

    ~Racun()
    {
        delete _stavkeRacuna; _stavkeRacuna = nullptr;
        delete _kupac; _kupac = nullptr;
    }

    void DodajArtikal(Artikal& artikal, int kolicina)
    {
        _stavkeRacuna->AddElement(&artikal, kolicina);
    }


    friend ostream& operator<<(ostream& COUT, Racun& obj)
    {
    	//moze se malo optimalnije uraditi ovaj razmak sa setw(vrijednost)
        float sumaArtikala = 0; 
        COUT << "FITStore::Racun::" << obj._brojRacuna << endl;
        COUT << "|  RB   Artikal         Cijena  Kolicina   Ukupno   |" << endl;
        for (int i = 0; i < obj._stavkeRacuna->getTrenutno(); i++)
        {
            int kolicina = obj._stavkeRacuna->getElement2(i);
            float cijena = obj._stavkeRacuna->getElement1(i)->GetCijena();
            COUT << "|  " << i + 1 << ".   " << obj._stavkeRacuna->getElement1(i)->GetNaziv() << "    " << cijena << "      " << kolicina << "      ";
            COUT << cijena * kolicina << "   |" << endl;
            sumaArtikala += cijena * kolicina;
        }
        COUT << "|  Suma : " << sumaArtikala << "KM" << endl;
        COUT << "|  Popust : "  << "KM" << endl;
        COUT << "|  Za platiti : " << sumaArtikala << "KM" << endl;
        return COUT;
    }
};


string GenerisiSljedeciBrojRacuna()
{
    string broj = "RN" + to_string(brojacRacuna++);
    return broj;
}

void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE.
    ****************************************************************************/
#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeKolekcije
    Kolekcija<int, int> kolekcija1;
    int brojElemenata = 15;
    for (size_t i = 0; i < brojElemenata; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1.getElement1(0) << " " << kolekcija1.getElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;

    cout << kolekcija2 << crt;
    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKupca
    Kupac jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Kupac adel("Adel Handzic", Datum(15, 10, 1981));

    Kupac jasmin2 = jasmin;
    cout << jasmin << endl << jasmin2 << endl;
    jasmin = jasmin2;
    cout << jasmin << endl << jasmin2 << endl;
#pragma endregion

#pragma region TestiranjeArtikla
    Artikal sokCppyNarandza("Cappy narandza", 2.1, "699511236545");
    Artikal cokoladaMilkaMilkins("Milka Milkins", 2.55, "622445875463");
    Artikal jogurtMeggle("Meggle jogurt", 2.55, "155338774458");

    cout << sokCppyNarandza << cokoladaMilkaMilkins << jogurtMeggle << endl;
   // sokCppyNarandza = cokoladaMilkaMilkins;
    cout << sokCppyNarandza << endl;

    if (sokCppyNarandza == cokoladaMilkaMilkins)
        cout << "Artikli su isti" << endl;
#pragma endregion

#pragma region TestiranjeRacuna
    /*GenerisiSljedeciBrojRacuna - globalna funkcija koja generise i vraca naredni broj racuna u
    prethodno definisanom formatu*/
    Racun racun1(GenerisiSljedeciBrojRacuna(), danas, &jasmin);

    racun1.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun1.DodajArtikal(sokCppyNarandza, 20);
    racun1.DodajArtikal(jogurtMeggle, 20);

    cout << racun1 << endl;

    Racun racun2(GenerisiSljedeciBrojRacuna(), sutra, &jasmin);
    racun2.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun2.DodajArtikal(sokCppyNarandza, 20);
    racun2.DodajArtikal(jogurtMeggle, 20);
    cout << racun2 << endl;

    Racun racun3(racun2);
    cout << racun3 << endl;
    //racun3.Sortiraj();

#pragma endregion
    system("pause");
}
//popust mozete izracunati kao procenat od ukupne sume racuna (pozeljna opcija) 
//ili kao vrijednost u KM-ovima (kao u nastavku)
/*
FITStore::Racun::RN000001
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.1KM
| Za platiti : 131.15KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.25KM
| Za platiti : 131KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.4KM
| Za platiti : 130.85KM
*/