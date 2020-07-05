#include <iostream>
#include<vector>
#include<string>
#include<exception>
#include<regex>
#include<thread>
#include<sstream>

using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum OznakaKrvneGrupe { O, A, B, AB };
enum Sortiranje { ASC, DESC };
const char* ispisKrvneKrupe[] = { "O", "A", "B", "AB" };

char* Alociraj(const char* sadrzaj)
{
    if (sadrzaj == nullptr) return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

class Datum
{
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan, int mjesec, int godina)
    {
        _dan = new int(dan), _mjesec = new int(mjesec), _godina = new int(godina);
    }
    Datum(const Datum& original)
    {
        _dan = new int(*original._dan), _mjesec = new int(*original._mjesec), _godina = new int(*original._godina);
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
    ~Datum() { delete _dan; delete _mjesec; delete _godina; }
    bool operator>(const Datum& drugi)
    {
        return (*_godina * 365 + *_mjesec * 30 + *_dan)>(*drugi._godina * 365 + *drugi._mjesec * 30 + *drugi._dan);
    }

    bool operator<(const Datum& drugi)
    {
        return (*_godina * 365 + *_mjesec * 30 + *_dan) < (*drugi._godina * 365 + *drugi._mjesec * 30 + *drugi._dan);
    }
    bool ProsloTriMjeseca(const Datum& drugi)
    {
        return abs((*_godina * 365 + *_mjesec * 30 + *_dan) - (*drugi._godina * 365 + *drugi._mjesec * 30 + *drugi._dan)) >= 90;
    }
    friend ostream& operator<<(ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << endl;
        return COUT;
    }
};

template <class T1, class T2, int max, Sortiranje sortiranje = ASC>
class Kolekcija
{
    T1* _elementi1[max];
    T2* _elementi2[max];
    int _trenutnoElemenata;
    bool _sortiranje;
    void Sortiraj()
    {
        bool prolaz = true;
        while (prolaz)
        {
            prolaz = false;
            for (int i = 0; i < _trenutnoElemenata-1; i++)
            {
                if (*_elementi2[i] > * _elementi2[i + 1] && Sortiranje::ASC==sortiranje || *_elementi2[i] < * _elementi2[i + 1] && Sortiranje::DESC == sortiranje)
                {
                    T1 temp1 = *_elementi1[i];
                    *_elementi1[i] = *_elementi1[i+1];
                    *_elementi1[i + 1] = temp1;

                    T2 temp2 = *_elementi2[i];
                    *_elementi2[i] = *_elementi2[i + 1];
                    *_elementi2[i + 1] = temp2;
                    prolaz = true;
                }
            }
        }
    }
public:
    Kolekcija(bool sortiranje = true)
    {
        _trenutnoElemenata = 0;
        _sortiranje = sortiranje;
    }
    Kolekcija(const Kolekcija& original) : _sortiranje(original._sortiranje), _trenutnoElemenata(original._trenutnoElemenata)
    {
        for (int i = 0; i < _trenutnoElemenata; i++)
        {
            _elementi1[i] = new T1(*original._elementi1[i]);
            _elementi2[i] = new T2(*original._elementi2[i]);
        }
    }
    Kolekcija& operator=(const Kolekcija& drugi)
    {
        if (this != &drugi)
        {
            _trenutnoElemenata = drugi._trenutnoElemenata;
            _sortiranje = drugi._sortiranje;
            for (int i = 0; i < _trenutnoElemenata; i++)
            {
                delete _elementi1[i];
                delete _elementi2[i];
                _elementi1[i] = new T1(*drugi._elementi1[i]);
                _elementi2[i] = new T2(*drugi._elementi2[i]);
            }
        }
        return *this;
    }
    ~Kolekcija()
    {
        for (size_t i = 0; i < _trenutnoElemenata; i++)
        {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
    }
    bool AddElement(T1 ele1, T2 ele2)
    {
        /*ukoliko je vrijednost atributa _sortiranje true, prilikom svakog dodavanja elementa se treba
        vrsiti sortiranje po redoslijedu definisanom u formalnom template argumentu sortiranje*/
        if (_trenutnoElemenata == max)
            return false;
        _elementi1[_trenutnoElemenata] = new T1(ele1);
        _elementi2[_trenutnoElemenata] = new T2(ele2);
        _trenutnoElemenata++;
        if (_sortiranje)
            Sortiraj();
        return true;
    }
    void SetElement2(int lokacija, T2 ele2)
    {
        *_elementi2[lokacija] = ele2;
    }
    void SetSortiranje(bool sortiranje)
    {
        _sortiranje = sortiranje;
    }
    int GetTrenutno() const { return _trenutnoElemenata; }
    int GetMax() const { return max; }

    T1 GetElement1(int lokacija) const
    {
        if (lokacija < 0 || lokacija >= _trenutnoElemenata)
            throw exception("Nepostojeca lokacija!");
        return *_elementi1[lokacija];
    }
    T2 GetElement2(int lokacija) const
    {
        if (lokacija < 0 || lokacija >= _trenutnoElemenata)
            throw exception("Nepostojeca lokacija!");
        return *_elementi2[lokacija];
    }
    friend ostream& operator<<(ostream& COUT, const Kolekcija& obj)
    {
        for (size_t i = 0; i < obj.GetTrenutno(); i++)
            COUT << obj.GetElement1(i) << "   " << obj.GetElement2(i) << endl;
        return COUT;
    }
};

class KrvnaGrupa
{
    /*postoje 4 krvne grupe koje su navedene u enumeracije OznakaKrvneGrupe, pri cemu svaka od navedenih moze imati
    pozitivan (+) i negativan (-) Rh faktor*/
    OznakaKrvneGrupe _oznaka;//npr: AB
    char _rhFaktor; // + ili -
    //prethodno pomenuto je izuzetno bitno iz razloga sto postoje jasna pravila vezana za darivanje krvi tj. 
    //koji primalac moze primiti krv od kojeg donatora sto je prikazano u tabeli, a naredna dva vector-a su zaduzena
    //da cuvaju informacije o tome, npr. za krvnu grupu A+ vector donatori ce cuvati vrijednosti: A+ i AB+ 
    vector<KrvnaGrupa*> _donatori; //krvne grupe kojima odredjena krvna grupa moze donirati krv.
    vector<KrvnaGrupa*> _primaoci; //krvne grupe od kojih odredjena krvna grupa moze primiti krv.
public:
    KrvnaGrupa(OznakaKrvneGrupe oznaka, char rhFaktor) :
        _oznaka(oznaka), _rhFaktor(rhFaktor) {}
    void SetDonatori(vector<KrvnaGrupa*> donatori)
    {
        _donatori = donatori;
    }
    void SetPrimaoci(vector<KrvnaGrupa*> primaoci)
    {
        _primaoci = primaoci;
    }
    string ToString()
    {
        stringstream ss;
        ss << "Krvna grupa: " << ispisKrvneKrupe[_oznaka] << _rhFaktor << endl;
        ss << "Donatori krvne grupe " << crt;
        for (int i = 0; i < _donatori.size(); i++)
            ss << ispisKrvneKrupe[_donatori[i]->_oznaka] << _donatori[i]->_rhFaktor << endl;
        ss << "Primaoci krvne grupe " << crt;
        for (int i = 0; i < _primaoci.size(); i++)
            ss << ispisKrvneKrupe[_primaoci[i]->_oznaka] << _primaoci[i]->_rhFaktor << endl;
        ss << crt;
        return ss.str();
    }
    string GetKrvnaString()
    {
        stringstream ss;
        ss << _oznaka << _rhFaktor;
        return ss.str();
    }
    bool operator==(const KrvnaGrupa& druga)
    {
        return _oznaka == druga._oznaka && _rhFaktor == druga._rhFaktor;
    }
};

class Osoba
{
protected:
    char* _imePrezime;
    KrvnaGrupa* _krvnaGrupa;
public:
    Osoba(const char* imePrezime, KrvnaGrupa* krvnaGrupa) : _krvnaGrupa(new KrvnaGrupa(*krvnaGrupa))
    {
        _imePrezime = Alociraj(imePrezime);
    }
    Osoba(const Osoba& original)
    {
        _imePrezime = Alociraj(original._imePrezime);
        _krvnaGrupa = new KrvnaGrupa(*original._krvnaGrupa);
    }
    Osoba& operator=(const Osoba& druga)
    {
        if (this != &druga)
        {
            delete[] _imePrezime;
            delete _krvnaGrupa;
            _imePrezime = Alociraj(druga._imePrezime);
            _krvnaGrupa = new KrvnaGrupa(*druga._krvnaGrupa);
        }
        return *this;
    }
    ~Osoba()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
        delete _krvnaGrupa; _krvnaGrupa = nullptr;
    }
    KrvnaGrupa GetKrvnaGrupa() { return *_krvnaGrupa; }
    virtual void Info() = 0;
    friend ostream& operator<<(ostream& COUT, Osoba& obj)
    {
        COUT << "Ime i prezime: " << obj._imePrezime << "   Krvna grupa:  " << obj._krvnaGrupa->ToString() << endl;
        return COUT;
    }
};

class Donator : public Osoba
{
    //u slucaju da email nije u validnom formatu potrebno ga je postaviti na podrazumijevanu vrijednost: info@donatori.ba
    string _email; //regex: nekiTekst@nekaDomena.com ili .ba ili .org
    Datum _datumPosljednjegDoniranja;
    bool _kontaktirajMe;
    bool ValidanFormat(string email)
    {
        return regex_match(email, regex("\[a-z]{5,10}@[a-z]{0,5}\.(ba|net)"));
    }

public:
    void Info() {}
    Donator(const char* imePrezime, KrvnaGrupa* krvnaGrupa, string email, Datum dpd, bool contact = true)
        : Osoba(imePrezime, krvnaGrupa), _datumPosljednjegDoniranja(dpd)
    {
        if (ValidanFormat(email))
            _email = email;
        else
            _email = "info@donatori.ba";
    }
    Donator(const Donator& original) : Osoba(original), _datumPosljednjegDoniranja(original._datumPosljednjegDoniranja), _email(original._email)
    {

    }
    Donator& operator=(const Donator& drugi)
    {
        if (this != &drugi)
        {
            Osoba::operator=(drugi);
            _email = drugi._email;
            _datumPosljednjegDoniranja = drugi._datumPosljednjegDoniranja;
        }
        return *this;
    }
    
    void SetDatumPosljednjegDoniranja(Datum datum)
    {
        _datumPosljednjegDoniranja = datum;
    }
    Datum& getDatumPosljednjegDoniranja() { return _datumPosljednjegDoniranja; }
    friend ostream& operator<<(ostream& COUT, Donator& obj)
    {
        COUT << "Donator:  " << obj._imePrezime << "   email:  " << obj._email << "    Posljednje doniranje:  " << obj._datumPosljednjegDoniranja << endl;
        COUT << obj._krvnaGrupa->ToString();
        return COUT;
    }
    
};

class Zahtjev
{
    string _ustanova;
    KrvnaGrupa* _krvnaGrupa;
    double _kolicina;
public:
    Zahtjev(string ustanova, KrvnaGrupa* krvnaGrupa, double kolicina) :
        _ustanova(ustanova), _krvnaGrupa(new KrvnaGrupa(*krvnaGrupa)), _kolicina(kolicina) { }
    Zahtjev(const Zahtjev& original) : _ustanova(original._ustanova), _kolicina(original._kolicina), _krvnaGrupa(new KrvnaGrupa(*original._krvnaGrupa)) {}
    Zahtjev& operator=(const Zahtjev& drugi)
    {
        if (this != &drugi)
        {
            _ustanova = drugi._ustanova;
            _kolicina = drugi._kolicina;
            *_krvnaGrupa = *drugi._krvnaGrupa;
        }
        return *this;
    }
    ~Zahtjev()
    {
        delete _krvnaGrupa;
    }
    friend ostream& operator<<(ostream& COUT, const Zahtjev& obj)
    {
        COUT << "Ustanova: " << obj._ustanova << endl;
        COUT << "Krvna grupa: " << obj._krvnaGrupa->ToString() << endl;
        COUT << "Kolicina: " << obj._kolicina << endl;
        return COUT;
    }

};

class TransfuzijskiCentar
{
    //stanje zaliha za svaku pojedinu krvnu grupu
    Kolekcija<KrvnaGrupa, double, 8, DESC> _zalihe;
    //evidentira svaku donaciju krvi
    Kolekcija<Osoba*, double, 100> _donacije;
    vector<Zahtjev> _zahtjevi;
   
public:
   
    bool AddDonaciju(Datum datumDonacije, Osoba* osoba, double kolicina)
    {
        Donator* donator = dynamic_cast<Donator*>(osoba);
        if (!donator->getDatumPosljednjegDoniranja().ProsloTriMjeseca(datumDonacije))
            throw exception("Nije proslo tri mjeseca od posljednjeg doniranja!");
        for (int i = 0; i < _zalihe.GetTrenutno(); i++)
        {
            if (_zalihe.GetElement1(i) == osoba->GetKrvnaGrupa())
            {
                _zalihe.SetElement2(i, _zalihe.GetElement2(i) + kolicina);
                donator->SetDatumPosljednjegDoniranja(datumDonacije);
                return true;
            }
        }

        _zalihe.AddElement(donator->GetKrvnaGrupa(), kolicina);
        return true;
    }
    double ProvjeriStanje(string krvnaGrupa)
    {
        for (int i = 0; i < _zalihe.GetTrenutno(); i++)
            if (_zalihe.GetElement1(i).GetKrvnaString() == krvnaGrupa)
                return _zalihe.GetElement2(i);
        return 0;
    }

    bool DodajZahtjev(Zahtjev& zahtjev)
    {
        _zahtjevi.push_back(zahtjev);
        return true;
    }

};

void main()
{
    /**************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME
    // ERROR CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU code.TXT
    // 5. NAZIVI FUNKCIJA MORAJU BITI IDENTIENI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.OSTALE, POMOANE FUNKCIJE
    // MOŽETE IMENOVATI PO ŽELJI. TAKO?ER, MOŽETE DODAVATI KOLIKO ŽELITE TESTNIH PODATAKA
    ****************************************************************************/
    Datum dat_12_03_2018(12, 3, 2018), dat_01_02_2018(1, 2, 2018);
    Datum danas(dat_12_03_2018);
    cout << danas << endl;

    Kolekcija<int, int, 10> kolekcija1;
    for (size_t i = 0; i < kolekcija1.GetMax() - 1; i++)
        if (!kolekcija1.AddElement(10 + i, 170000 + i))
            cout << "Elementi " << 10 + i << " i " << 170000 + i << " nisu dodati u kolekciju" << endl;

    cout << kolekcija1 << endl;
    kolekcija1.SetSortiranje(DESC);
    kolekcija1.AddElement(16, 170016);
    cout << kolekcija1 << endl;

    Kolekcija<int, int, 10> kolekcija2(kolekcija1);
    cout << kolekcija2 << endl;


    vector<KrvnaGrupa*> krvneGrupe;
    krvneGrupe.push_back(new KrvnaGrupa(O, '+')); //0 - O_poz
    krvneGrupe.push_back(new KrvnaGrupa(O, '-')); //1 - O_neg
    krvneGrupe.push_back(new KrvnaGrupa(A, '+')); //2 - A_poz
    krvneGrupe.push_back(new KrvnaGrupa(A, '-')); //3 - A_neg
    krvneGrupe.push_back(new KrvnaGrupa(B, '+')); //4 - B_poz
    krvneGrupe.push_back(new KrvnaGrupa(B, '-')); //5 - B_neg
    krvneGrupe.push_back(new KrvnaGrupa(AB, '+'));//6 - AB_poz
    krvneGrupe.push_back(new KrvnaGrupa(AB, '-'));//7 - AB_neg

    vector<KrvnaGrupa*> donori_O_poz{ krvneGrupe[0], krvneGrupe[2], krvneGrupe[4], krvneGrupe[6] };
    krvneGrupe[0]->SetDonatori(donori_O_poz);
    //ili krace napisano
    krvneGrupe[0]->SetPrimaoci(vector<KrvnaGrupa*>{krvneGrupe[0], krvneGrupe[1]});
    krvneGrupe[2]->SetDonatori(vector<KrvnaGrupa*>{krvneGrupe[2], krvneGrupe[6]});
    krvneGrupe[2]->SetPrimaoci(vector<KrvnaGrupa*>{krvneGrupe[0], krvneGrupe[2], krvneGrupe[1], krvneGrupe[3]});

    krvneGrupe[4]->SetDonatori(vector<KrvnaGrupa*>{krvneGrupe[4], krvneGrupe[6]});
    krvneGrupe[4]->SetPrimaoci(vector<KrvnaGrupa*>{krvneGrupe[0], krvneGrupe[4], krvneGrupe[1], krvneGrupe[5]});

    Osoba* jasmin = new Donator("Jasmin Azemovic", krvneGrupe[0], "jasmin@fit.ba", Datum(12, 2, 2017), true);
    Osoba* adel = new Donator("Adel Handzic", krvneGrupe[3], "adelfit.ba", Datum(9, 1, 2017), true);
    Osoba* goran = new Donator("Goran Skondric", krvneGrupe[5], "goran@fit.net", Datum(9, 3, 2017), true);

   
    TransfuzijskiCentar tcMostar;
    // prilikom svake donacije je potrebno povecati zalihe za tu krvnu grupu
    // ukoliko krvna grupa vec postoji na zalihi onda se uvecava samo njena kolicina
    // takodjer, donatoru se postavlja nova vrijednost datuma posljednje donacije.
    // ukoliko je neki od dodantora darivao krv prije isteka 3 mjeseca od posljednjeg
    // darivanja, funkcija baca izuzetak
    //datum donacije, donator, kolicina
    try
    {
        tcMostar.AddDonaciju(Datum(20, 5, 2017), jasmin, 2.5);
        tcMostar.AddDonaciju(Datum(20, 5, 2017), adel, 3);
        tcMostar.AddDonaciju(Datum(6, 5, 2017), goran, 1.2);
    }
    catch (exception & err)
    {
        cout << "Greska-> " << err.what() << endl;
    }
    try
    {
        tcMostar.AddDonaciju(Datum(10, 9, 2017), jasmin, 2);
        tcMostar.AddDonaciju(Datum(18, 10, 2017), adel, 1.8);
        tcMostar.AddDonaciju(Datum(15, 9, 2017), goran, 3.8);
    }
    catch (exception & err)
    {
        cout << "Greska-> " << err.what() << endl;
    }
    Zahtjev zahtjev_0_poz("Tranfuziologija KCUS", krvneGrupe[0], 15),
        zahtjev_0_neg("Tranfuziologija Bakir Nakas", krvneGrupe[1], 8);
    //ukoliko na stanju postoji dovoljno iste ili zamjense krvne grupe
    if (tcMostar.ProvjeriStanje("0+") >= 2)
          tcMostar.DodajZahtjev(zahtjev_0_poz);

    

    // ukoliko transfuzijski centar posjeduje zahtijevane kolicine na stanju, odmah ce ih ustupiti prema zahtjevu,
    // a u slucaju da ne posjeduje onda ce (koristeci multithreading) kontaktirati (poslati email poruku sa
    // odgovarajucim sadrzajem) sve donore koji zadovoljavaju sljedece uslove:
    // - mogu donirati krv zahtijevanoj krvnoj grupi
    // - oznacili su da zele biti kontaktirani
    // - nisu davali krv u posljednja 3 mjeseca
    if (tcMostar.ProvjeriStanje("0-") >= 8)
        tcMostar.DodajZahtjev(zahtjev_0_neg);


    //// ispisuje matricu ili tablicu iz koje je vidljiva kompatibilnost izme?u pojedinih krvnih grupa. 
    //// pored naziva i rh faktora krvne grupe, u zagradi ispisati i trenutnu kolieinu na stanju. matrica 
    //// prikazana na kraju zadatka
    //tcMostar.IspisiMatricuKompatibilnosti(krvneGrupe);

    delete adel;
    delete jasmin;
    delete goran;

    for (size_t i = 0; i < krvneGrupe.size(); i++)
        delete krvneGrupe[i];
    system("pause>0");
}