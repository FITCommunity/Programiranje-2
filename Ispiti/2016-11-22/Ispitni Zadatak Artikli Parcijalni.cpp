#include <iostream>
#include<string>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/

const char* crt = "\n------------------------------------\n";

char* AlocirajNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
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
    int GetDays()
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

template<class T>
class Kolekcija {
    T* _niz;
    int _trenutno;
public:
    Kolekcija() : _trenutno(0), _niz(nullptr) {}
    Kolekcija(const Kolekcija& original) : _trenutno(original._trenutno)
    {
        _niz = new T[_trenutno];
        for (int i = 0; i < _trenutno; i++)
            _niz[i] = original._niz[i];
    }
    Kolekcija& operator=(const Kolekcija& druga)
    {
        if (this != &druga)
        {
            _trenutno = druga._trenutno;
            if (_trenutno != 0)
            {
                delete[] _niz;
            }
            _niz = new T[_trenutno];
            for (int i = 0; i < _trenutno; i++)
                _niz[i] = druga._niz[i];
        }
        return *this;
    }
    ~Kolekcija() { delete[] _niz; _niz = nullptr; _trenutno = 0; }
    T* GetNiz() { return _niz; }
    int GetTrenutno() { return _trenutno; }
    T& operator[](int indeks)
    {
        if (indeks<0 || indeks>_trenutno)
            throw exception("Ne valja indeks!");
        return _niz[indeks];
    }
    //implementirati potrebne funkcije
    void Add(T el)
    {
        T* temp = new T[_trenutno + 1];
        for (int i = 0; i < _trenutno; i++)
        {
            temp[i] = _niz[i];
        }
        delete[] _niz;
        temp[_trenutno] = el;
        _trenutno++;
        _niz = temp; 
    }
    friend ostream& operator<<(ostream& COUT, Kolekcija& obj)
    {
        for (int i = 0; i < obj.GetTrenutno(); i++)
            COUT << obj.GetNiz()[i] << endl;
        return COUT;
    }
};

class Usluga {
    char* _naziv;
    double _cijena;//cijena usluge je izrazena po danu koristenja
public:
    Usluga() : _naziv(nullptr), _cijena(0) {}
    Usluga(const char* naziv, double cijena) : _cijena(cijena) {
        _naziv = AlocirajNizKaraktera(naziv);
    }
    Usluga(const Usluga& original) : _naziv(AlocirajNizKaraktera(original._naziv)), _cijena(original._cijena) {}
    Usluga& operator=(const Usluga& druga)
    {
        if (this != &druga)
        {
            delete[] _naziv;
            _naziv = AlocirajNizKaraktera(druga._naziv);
            _cijena = druga._cijena;
        }
        return *this;
    }
    ~Usluga() { delete[] _naziv; _naziv = nullptr; }
    double GetCijena() { return _cijena; }
    const char* GetNaziv() { return _naziv; }
    bool operator==(const Usluga& druga)
    {
        return strcmp(_naziv, druga._naziv) == 0 && _cijena == druga._cijena;
    }
    friend ostream& operator<< (ostream& COUT, const Usluga& obj);
};
ostream& operator<< (ostream& COUT, const Usluga& obj) {
    COUT << obj._naziv << " -> \t\t" << obj._cijena << " KM" << endl;
    return COUT;
}

class Rezervacija {
    static int _rezervacijeIDBrojac;
    const int _rezervacijaID; ///broj rezervacije krece od 160000
    Datum _rezervacijaOD;
    Datum _rezervacijaDO;
    double _cijenaPoDanu; //cijena osnovnih usluga koja ne ukljucuje dodatne usluge
    Kolekcija<Usluga> _dodatneUsluge; //dodatne usluge mogu biti: sauna, sportski tereni, kuglanje, masaza i sl. 
public:
    //implementirati potrebne funkcije
    Rezervacija(Datum OD, Datum DO, double cijena) : _rezervacijaDO(DO), _rezervacijaOD(OD), _cijenaPoDanu(cijena), _rezervacijaID(_rezervacijeIDBrojac++) {}
    Rezervacija(const Rezervacija& original) : _rezervacijaDO(original._rezervacijaDO), _rezervacijaOD(original._rezervacijaOD), _cijenaPoDanu(original._cijenaPoDanu), _rezervacijaID(original._rezervacijaID)
    {
        _dodatneUsluge = original._dodatneUsluge;
    }
    Rezervacija& operator=(const Rezervacija& druga)
    {
        if (this != &druga)
        {
            _rezervacijaDO = druga._rezervacijaDO;
            _rezervacijaOD = druga._rezervacijaOD;
            _cijenaPoDanu = druga._cijenaPoDanu;
            _dodatneUsluge = druga._dodatneUsluge;
        }
        return *this;
    }
    bool operator+=(Usluga& usluga)
    {
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
            if (_dodatneUsluge.GetNiz()[i] == usluga)
                return false;
        _dodatneUsluge.Add(usluga);
        return true;
    }
    void PrintRacun()
    {
        cout << crt << "R.ID:  " << _rezervacijaID << endl;
        cout << "OD: " << _rezervacijaOD;
        cout << "\nDO: " << _rezervacijaDO;
        cout << crt << "DODATNE USLUGE:"<<crt;
        int sumaDodatnih = 0;
        int brojDana = _rezervacijaDO.GetDays() - _rezervacijaOD.GetDays();
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
        {
            sumaDodatnih += _dodatneUsluge.GetNiz()[i].GetCijena();
            cout << _dodatneUsluge.GetNiz()[i] << endl;
        }
        cout << crt << "Osnovne usluge -> " << brojDana * _cijenaPoDanu <<" KM"<< crt;
        cout << "Dodatne usluge -> " << sumaDodatnih*brojDana <<" KM"<< crt;
        cout << "Ukupno -> " << (sumaDodatnih*brojDana) + (brojDana * _cijenaPoDanu) << " KM" << crt;
    }
    Usluga* operator[](const char* nazivUsluge)
    {
        Usluga* u = nullptr;
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
            if (strcmp(_dodatneUsluge.GetNiz()[i].GetNaziv(), nazivUsluge) == 0)
                u = &_dodatneUsluge.GetNiz()[i];
        return u;
    }
    Kolekcija<Usluga> operator()(int donja, int gornja)
    {
        Kolekcija<Usluga> nova;
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
            if (_dodatneUsluge.GetNiz()[i].GetCijena() >= donja && _dodatneUsluge.GetNiz()[i].GetCijena() <= gornja)
                nova.Add(_dodatneUsluge.GetNiz()[i]);
        return nova;
    }
};

int Rezervacija::_rezervacijeIDBrojac = 160000;

void main() {
    cout << crt << "TRAJANJE ISPITA -> 90 minuta " << crt;
    Kolekcija<int> brojevi;
    for (int i = 0; i < 15; i++)
        brojevi.Add(i);
    cout << brojevi << crt;

    //u okviru klase Usluga implementirati MOVE konstruktor
    Usluga Parking("Parking", 5), Dorucak("Dorucak", 10), Rucak("Rucak", 15), Veseraj("Veseraj", 10);

    //rezervacijaOD, rezervacijaDO, cijenaPoDanu
    Rezervacija rezervacija(Datum(25, 10, 2018), Datum(30, 10, 2018), 59.9);

    //dodaje novu uslugu u rezervaciju. onemoguciti ponavljanje usluga
    if (rezervacija += Parking)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Dorucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Rucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Veseraj)
        cout << "Usluga uspjesno dodana!" << endl;
   /* if (!(rezervacija += Dorucak))
        cout << "Usluga vec postoji!" << endl;*/

    /*prikazuje racun formatiran na nacin prikazan na slici. prilikom izracunavanja iznosa koristiti cijene osnovnih i dodatnih usluga, kao i broj dana za koje je napravljena rezervacija (napomena: duzina trajanja rezervacije je maksimalno 30 dana)*/
    rezervacija.PrintRacun();

    //vraca pokazivac na uslugu sa proslijedjenim nazivom
    Usluga* p = rezervacija["Dorucak"];
    if (p != nullptr)
        cout << *p << crt;

    //vraca sve dodatne usluge koje imaju cijenu u opsegu vrijednosti parametara
    Kolekcija<Usluga> uslugePoCijeni = rezervacija(8, 12);
    for (size_t i = 0; i < uslugePoCijeni.GetTrenutno(); i++)
        cout << uslugePoCijeni[i] << crt;

    cin.get();
}

/*
------------------------------------
R.ID: 160000
OD: 25 10 2018
DO: 30 10 2018
------------------------------------
DODATNE USLUGE:
------------------------------------
Parking -> 5 KM
Dorucak -> 10 KM
Rucak -> 15 KM
Veseraj -> 10 KM
------------------------------------
Osnovne usluge-> 299.5 KM
------------------------------------
Dodatne usluge-> 200 KM
------------------------------------
Ukupno -> 499.5 KM
------------------------------------
*/