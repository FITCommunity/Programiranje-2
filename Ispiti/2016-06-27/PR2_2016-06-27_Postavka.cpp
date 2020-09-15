#include <iostream>

using namespace std;

char * crt = "\n----------------------------------------------------\n";

template<class T1, class T2>
class Kolekcija 
{
    T1 * _elementi1;
    T2 * _elementi2;
    int * _trenutno;
public:
    Kolekcija()
    {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = new int(0);
    }
    //1. potrebne funkcije	
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }	
};
class Datum 
{
    int *_dan, *_mjesec, *_godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) 
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }	
    ~Datum() 
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream &COUT, const Datum &obj) 
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
    }
    //1. potrebne funkcije
};
class Osoba 
{
protected:
    char * _imePrezime;
    Datum * _datumRodjenja;
public:
    Osoba(char * imePrezime, Datum datum) 
    {
        _imePrezime = new char[strlen(imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
        _datumRodjenja = new Datum(datum);
    }
    Osoba(const Osoba & obj)
    {
        _imePrezime = new char[strlen(obj._imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
        _datumRodjenja = new Datum(*obj._datumRodjenja);
    }
    ~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
    //1. potrebne funkcije
};


class Kupac 
{
    //svaki kupac ima popust koji mu se zaracunava prilikom svake kupovine
    //pocetni popust je 0.10%
    //svaka kupovina u iznosu 100 - 500KM povecava iznos popusta za 0.15%
    //svaka kupovina u iznosu 500 - 1000KM povecava iznos popusta za 0.25%
    //svaka kupovina u iznosu vecem od 1000KM povecava iznos popusta za 0.30%
    float _odobreniPopust;	
public:
    //1. potrebne funkcije

};
class Artikal 
{
    string _barCode;
    char * _naziv;
    float _cijena;
public:
    Artikal(char * naziv, float cijena, string barCode) 
    {
        int vel = strlen(naziv) + 1;
        _naziv = new char[vel];
        strcpy_s(_naziv, vel, naziv);
        _cijena = cijena;
        _barCode = barCode;
    }
    ~Artikal() { delete[]_naziv; _naziv = nullptr; }
    friend ostream& operator<< (ostream &COUT, const Artikal &obj) 
    { 
        COUT << obj._naziv << " " << obj._cijena << " KM"<<endl; 
        return COUT;
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
    Kolekcija<Artikal *, int> * _stavkeRacuna;
    Kupac * _kupac;
public:
// 1. potrebne (de)konstruktor i druge funkcije
// 2. DodajArtikal - dodaje novi artikal u listu artikala zajedno sa njegovom kolicinom. Onemoguciti ponavljanje 
//    artikala na nacin da se uvecava samo kolicina ukoliko korisnik vise puta pokusa dodati isti artikal.
// 3. operator<< - ispisuje racun u formatu prikazanom na slici(nije obavezno da bude identican, ali je svakako pozeljno).
//    Nakon ispisa svakog racuna, ukoliko su ispunjeni definisani uslovi, kupcu se uvecava popust.
// 4. Sortiraj - sortira artikle (rastuci) po kolicini novca kojom ucestvuju u ukupnom iznosu racuna
};
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
    Artikal sokCppyNarandza("Cappy narandza", 2.10, "699511236545");
    Artikal cokoladaMilkaMilkins("Milka Milkins", 2.55, "622445875463");
    Artikal jogurtMeggle("Meggle jogurt", 2.55, "155338774458");

    cout << sokCppyNarandza << cokoladaMilkaMilkins << jogurtMeggle << endl;
    sokCppyNarandza = cokoladaMilkaMilkins;
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
    racun3.Sortiraj();

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