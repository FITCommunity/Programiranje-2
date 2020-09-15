#include <iostream>
using namespace std;

#pragma warning(disable:4996)
const char *crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
const float minimalan_prosjek = 4.5;

char * AlocirajNizKaraktera(const char * sadrzaj) 
{
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char * temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

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
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream &COUT, Kolekcija &obj) 
    {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};

class DatumVrijeme 
{
    int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
public:
    DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) 
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
        _sati = new int(sati);
        _minuti = new int(minuti);
    }
    ~DatumVrijeme() 
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
        delete _sati; _sati = nullptr;
        delete _minuti; _minuti = nullptr;
    }
    friend ostream& operator<< (ostream &COUT, DatumVrijeme &obj) 
    {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
        return COUT;
    }
};

class Predmet 
{
    char * _naziv;
    int _ocjena;
    string _napomena;
public:
    Predmet(const char * naziv, int ocjena, string napomena = ""):_ocjena(ocjena), _napomena(napomena) 
    {	
        _naziv = AlocirajNizKaraktera(naziv);	
    }
    ~Predmet() 
    {
        delete[] _naziv; _naziv = nullptr;
    }
    friend ostream& operator<< (ostream &COUT, Predmet &obj) 
    {
        COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
        return COUT;
    }
    char * GetNaziv() { return _naziv; }
    string GetNapomena() { return _napomena; }
    void DodajNapomenu(string napomena) 
    {
        _napomena += " " + napomena;
    }
};
struct Uspjeh 
{
    eRazred _razred;
    //datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
    Kolekcija<Predmet*, DatumVrijeme> * _predmeti;
public:
    Uspjeh(eRazred razred):_razred(razred), _predmeti(nullptr) 
    {	
    }
    ~Uspjeh() 
    {
        delete[] _predmeti; _predmeti = nullptr;
    }

    Kolekcija<Predmet*, DatumVrijeme> * GetPredmeti() { return _predmeti; }

    friend ostream& operator<< (ostream &COUT, const Uspjeh &obj) 
    {
        COUT << obj._razred << *obj._predmeti << endl;
        return COUT;
    }	
};

class Kandidat 
{
    char * _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh *> _uspjeh;
public:
    Kandidat(const char * imePrezime, string emailAdresa, string brojTelefona)
    : _emailAdresa(emailAdresa), _brojTelefona(brojTelefona)
    {
        _imePrezime = AlocirajNizKaraktera(imePrezime);
    }
    ~Kandidat() 
    {
        delete[] _imePrezime; _imePrezime = nullptr;
        for (size_t i = 0; i < _uspjeh.size(); i++) 
        {
            delete _uspjeh[i];
            _uspjeh[i] = nullptr;
        }
    }
    friend ostream& operator<< (ostream &COUT, Kandidat &obj) 
    {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << *obj._uspjeh[i] << endl;
        return COUT;
    }
    vector<Uspjeh *> GetUspjeh() { return _uspjeh; }

};

void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR 
    // ÆE BITI OZNACENO KAO "RE"
    // 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM 
    // CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE 
    // MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
    ****************************************************************************/

    DatumVrijeme temp,
    datum19062018_1015(19, 6, 2018, 10, 15),
    datum20062018_1115(20, 6, 2018, 11, 15),
    datum30062018_1215(30, 6, 2018, 12, 15),
    datum05072018_1231(5, 7, 2018, 12, 31),
    datum20062018_1115_Copy(datum20062018_1115);
    //funkcija ToCharArray vraca datum i vrijeme kao char *
    cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
    temp = datum05072018_1231;
    cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
    cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15

    const int kolekcijaTestSize = 10;
    Kolekcija<int, int> kolekcija1;
    for (size_t i = 0; i < kolekcijaTestSize; i++)
    kolekcija1.AddElement(i + 1, i * i);
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    Kolekcija<int, int> kolekcija3;
    kolekcija3 = kolekcija1;
    kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
    cout << kolekcija3 << crt;

    //napomena se moze dodati i prilikom kreiranja objekta
    Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
    Fizika("Fizika", 5),
    Hemija("Hemija", 2),
    Engleski("Engleski", 5);
    Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
    cout << Matematika << endl;

    Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");

    // uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    // tom prilikom onemoguciti:
    // - dodavanje vise od 6 predmeta za jedan razred
    // - dodavanje istoimenih predmeta na nivou jednog razreda,
    // - dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja 
    // pojedinih predmeta mora biti najmanje minut).
    // razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
    // razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!" << crt;
    //ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
    if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!" << crt;
    
    // pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
    // upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
    // sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od 
    // minimalan_prosjek kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova 
    // implemenitrati koristeci zasebne thread-ove.
    	

    Uspjeh * u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
    if (u != nullptr) cout << *u << endl;

    system("pause>0");
}