#include <iostream>

using namespace std;

enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
char * ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
char * ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };

template<class T1, class T2>
class Kolekcija 
{
    T1 * _elementi1;
    T2 * _elementi2;
    int _trenutno;
public:
    Kolekcija()
    {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = 0;
    }
    ~Kolekcija()
    {
        delete[]_elementi1;
        delete[]_elementi2;
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

    Datum(const Datum&obj) 
    {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
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
};
class Osoba 
{
protected:
    char * _imePrezime;
    Datum * _datumRodjenja;
    string _brojTelefona;
public:
    Osoba(char * imePrezime, Datum datum) 
    {
        _imePrezime = new char[strlen(imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
        _datumRodjenja = new Datum(datum);
        _brojTelefona = "";
    }
    Osoba(const Osoba & obj) :_brojTelefona(obj._brojTelefona) 
    {
        _imePrezime = new char[strlen(obj._imePrezime) + 1];
        strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
        _datumRodjenja = new Datum(*obj._datumRodjenja);
    }
    ~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }

    bool setBrojTelefona(string brojTelefona)
    {
        if (ProvjeriValidnostBrojaTelefona(brojTelefona))
        {
            _brojTelefona = brojTelefona;
            return true;
        }
        return false;
    }

};

class Nastavnik :public Osoba 
{
    Kolekcija<Predmeti, Razredi> * _predmetiRazredi;
};
bool ProvjeriValidnostBrojaTelefona(string telefon)//globalna funkcija
{
 //broj telefona treba biti u formatu: +387(61)-222-333
}
class Ucenik : public Osoba 
{
    int _brojUDnevniku;
    Razredi _razred;
    vector<Nastavnik *> _nastavnici;
    Kolekcija<Predmeti, int> _predmetiOcjene;	
};

void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR 
    // CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
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

    kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
    cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
    #pragma endregion

    #pragma region TestiranjeNastavnika
    Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
    /*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA 
    RAZREDA (NA DVIJE RAZLICITE GODINE)*/
    if (jasmin.AddPredmetRazred(Matematika, I1))
        cout << "Predmeti dodan" << endl;
    if (jasmin.AddPredmetRazred(Historija, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografia, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografia, I2))
        cout << "Predmeti dodan" << endl;

    if (adel.AddPredmetRazred(Historija, III1))
        cout << "Predmeti dodan" << endl;

    if (adel.RemovePredmetRazred(Historija))
        cout << "Predmet uklonjen!" << endl;

    Nastavnik goran(adel);
    if (goran == adel)
        cout << "Nastavnici identicni" << endl;
    goran = jasmin;
    if (goran == jasmin)
        cout << "Nastavnici identicni" << endl;

    Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();

    if (!jasmin.setBrojTelefona("+38761111222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (!jasmin.setBrojTelefona("+387-61-111-222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (jasmin.setBrojTelefona("+387(61)-111-222"))
        cout << "Broj telefona uspjesno dodan!" << endl;
    #pragma endregion

    #pragma region TestiranjeUcenika
    Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
    Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
    Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
    /*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O 
    NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
    /*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
    if (denis.AddNastavnik(jasmin))
        cout << "Nastavnik uspjesno dodan" << endl;
    /*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
    if (denis.AddNastavnik(adel))
        cout << "Nastavnik uspjesno dodan" << endl;
    /*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
    if (denis.AddPredmetOcjenu(Matematika, 3))
        cout << "Ocjena uspjesno dodana" << endl;
    if (denis.AddPredmetOcjenu(Historija, 4))
        cout << "Ocjena uspjesno dodana" << endl;

    vector<Nastavnik*> & nastavnici = denis.getNastavnici();
    cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

    Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
    cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
    cout<<"Prosjecna ocjena kod nastavnika Jasmin Azemovic je "<< denis.GetProsjekByNastavnik("Jasmin Azemovic")<<endl;

    Ucenik denis2(denis);
    cout << denis2 << endl;	

    #pragma endregion
    system("pause");
}