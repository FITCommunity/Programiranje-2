// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
#include <iostream>
#include<string>
#include<vector>
using namespace std;
char* AlocirajNizKaraktera(const char* sadrzaj)
{
    if (sadrzaj == nullptr) return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
const char* crt = "\n--------------------------------------------------\n";
template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1;
    T2* _elementi2;
    int _trenutnoElemenata;
public:
    Kolekcija()
    {
        _trenutnoElemenata = 0;
        _elementi1 = nullptr;
        _elementi2 = nullptr;
    }
    Kolekcija(const Kolekcija& original) : _trenutnoElemenata(original._trenutnoElemenata)
    {
        if (_trenutnoElemenata == 0)
        {
            _elementi1 = nullptr;
            _elementi2 = nullptr;
            return;
        }
        _elementi1 = new T1[_trenutnoElemenata];
        _elementi2 = new T2[_trenutnoElemenata];
        for (int i = 0; i < _trenutnoElemenata; i++)
        {
            _elementi1[i] = original._elementi1[i];
            _elementi2[i] = original._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& drugi)
    {
        if (this != &drugi)
        {
            delete[] _elementi1;
            delete[] _elementi2;
            _trenutnoElemenata = drugi._trenutnoElemenata;
            _elementi1 = new T1[_trenutnoElemenata];
            _elementi2 = new T2[_trenutnoElemenata];
            for (int i = 0; i < _trenutnoElemenata; i++)
            {
                _elementi1[i] = drugi._elementi1[i];
                _elementi2[i] = drugi._elementi2[i];
            }
        }
        return *this;
    }
    ~Kolekcija()
    {
        if (_trenutnoElemenata != 0)
        {
        delete[] _elementi1;_elementi1=nullptr;
        delete[] _elementi2;_elementi2=nullptr;
        }
    }
    int getTrenutno() const { return _trenutnoElemenata; }
    void AddElement(T1 el1, T2 el2)
    {
        if (_trenutnoElemenata == 0)
        {
            _elementi1 = new T1[_trenutnoElemenata + 1];
            _elementi2 = new T2[_trenutnoElemenata + 1];
            _elementi1[_trenutnoElemenata] = el1;
            _elementi2[_trenutnoElemenata] = el2;
            _trenutnoElemenata++;
            return;
        }

        T1* temp1 = new T1[_trenutnoElemenata + 1];
        T2* temp2 = new T2[_trenutnoElemenata + 1];
        for (int i = 0; i < _trenutnoElemenata; i++)
        {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        delete[] _elementi1;
        delete[] _elementi2;
        temp1[_trenutnoElemenata] = el1;
        temp2[_trenutnoElemenata] = el2;
        _trenutnoElemenata++;
        _elementi1 = temp1; temp1=nullptr;
        _elementi2 = temp2; temp2=nullptr;
    }
    void RemoveElement(int lokacija)
    {
        if (lokacija < 0 || lokacija >= _trenutnoElemenata)
        {
            cout << "Niste unijeli validnu lokaciju" << endl;
            return;
        }
        for (int i = lokacija; i < _trenutnoElemenata-1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
            
        }
        _trenutnoElemenata--;
    }
    T1& GetElement1(int indeks) { return _elementi1[indeks]; }
    T2& GetElement2(int indeks) { return _elementi2[indeks]; }
    friend ostream& operator<<(ostream& cout, Kolekcija& objekat)
    {
        for (int i = 0; i < objekat.getTrenutno(); i++)
        {
            cout << objekat.GetElement1(i) << "  " << objekat.GetElement2(i) << endl;
        }
        return cout;
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
    friend ostream& operator<< (ostream& COUT, Datum& obj)
    {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};
class Student
{
    char* _imePrezime;
    Datum* _datumRodjenja;
public:
    Student(const char* imePrezime = "---", Datum d = Datum())
    {
        _imePrezime = AlocirajNizKaraktera(imePrezime);
        _datumRodjenja = new Datum(d);
    }
    Student(const Student& original)
    {
        _imePrezime = AlocirajNizKaraktera(original._imePrezime);
        _datumRodjenja = new Datum(*original._datumRodjenja);
    }
    Student& operator=(const Student& drugi)
    {
        if (this != &drugi)
        {
            delete[] _imePrezime;
            delete _datumRodjenja;
            _imePrezime = AlocirajNizKaraktera(drugi._imePrezime);
            _datumRodjenja = new Datum(*drugi._datumRodjenja);
        }
        return *this;
    }
    ~Student() { delete[] _imePrezime; delete _datumRodjenja; }
    bool operator==(const Student& drugi)
    {
        return strcmp(_imePrezime, drugi._imePrezime) == 0;
    }
    friend ostream& operator<<(ostream& cout, Student& objekat)
    {
        cout << "Ime prezime-> " << objekat._imePrezime << endl;
        cout << "Datum rodjenja-> " << *objekat._datumRodjenja;
        return cout;
    }
};
class Ispit
{
    Datum _datumOdrzavanja;
    char* _opisIspita;
    Kolekcija<Student, Datum> _prijave;
    Kolekcija<Student, int> _rezultati;
public:
    Ispit(const char* opisIspita=nullptr, Datum datum=0)
    {
        _opisIspita = AlocirajNizKaraktera(opisIspita);
        _datumOdrzavanja = datum;
    }
    Ispit(const Ispit& original)
    {
        _opisIspita = AlocirajNizKaraktera(original._opisIspita);
        _datumOdrzavanja = original._datumOdrzavanja;
        _prijave = original._prijave;
        _rezultati = original._rezultati;
    }
    Ispit& operator=(const Ispit& drugi)
    {
        if (this != &drugi)
        {
            delete[] _opisIspita;
            _opisIspita = AlocirajNizKaraktera(drugi._opisIspita);
            _datumOdrzavanja = drugi._datumOdrzavanja;
            _prijave = drugi._prijave;
            _rezultati = drugi._rezultati;
        }
        return *this;
    }
    ~Ispit()
    {
        delete[] _opisIspita; _opisIspita = nullptr;
    }
    friend ostream& operator<<(ostream& cout, Ispit& obj)
    {
        if (obj._opisIspita != nullptr)
            cout << "Opis ispita-> " << obj._opisIspita << endl;
        cout << obj._datumOdrzavanja << endl;
        for (int i = 0; i < obj._rezultati.getTrenutno(); i++)
            cout << obj._rezultati.GetElement1(i) << " ,  ocjena->   " << obj._rezultati.GetElement2(i) << endl;
        return cout;
    }
    bool DodajPrijavu(Student& student, Datum& datum)
    {
        for (int i = 0; i < _prijave.getTrenutno(); i++)
            if (_prijave.GetElement1(i) == student) //ako postoji isti student vrati false
                return false;
            _prijave.AddElement(student, datum);
            return true;
    }
    bool DodajRezultat(Student& student, int ocjena)
    {
        for (int i = 0; i < _prijave.getTrenutno(); i++)
            if (_prijave.GetElement1(i) == student) //ako pronadje tog studenta dodjeli mu ocjenu
            {
                _rezultati.AddElement(student, ocjena);
                    return true;
            }
    }
    void Sortiraj()
    {
        bool prolaz = true;
        while (prolaz)
        {
            prolaz = false;

             for (int i = 0; i < _rezultati.getTrenutno()-1; i++) //sortira se kao i u kolekciji samo se za elemente uzmu ovi elementi tj. ocjena i student
             if (_rezultati.GetElement2(i) > _rezultati.GetElement2(i + 1))
                {
                int ocjena = _rezultati.GetElement2(i);
                _rezultati.GetElement2(i) = _rezultati.GetElement2(i + 1);
                _rezultati.GetElement2(i + 1) = ocjena;

                Student student = _rezultati.GetElement1(i);
                _rezultati.GetElement1(i) = _rezultati.GetElement1(i + 1);
                _rezultati.GetElement1(i + 1) = student;
                prolaz = true;
                }

        }
    }
    void ZakljuciRezultate()
    {
        for (int i = 0; i < _prijave.getTrenutno(); i++)
        {
            for (int j = 0; j < _rezultati.getTrenutno(); j++)
                if (_prijave.GetElement1(i) == _rezultati.GetElement1(j))
                    return;

            _rezultati.AddElement(_prijave.GetElement1(i), 5);
        }
    }
};
void main()
{
    //REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost
#pragma region TestiranjeKolekcije
    Kolekcija<int, double> kolekcija1;
    for (size_t i = 0; i < 50; i++)
        kolekcija1.AddElement(i, i + 0.3);
    cout << kolekcija1 << endl;
    cout << crt;

    Kolekcija<int, double> kolekcija2;
    kolekcija2 = kolekcija1;
    kolekcija1.RemoveElement(2);//UMANJITI VELIÈINU NIZA
    cout << kolekcija2 << crt;

    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, double> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeStudenta
    Student denis("Denis Music", Datum(26, 11, 1990));
    Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
    Student goran;
    goran = jasmin;
    Student adel("Adel Handzic", Datum(25, 8, 1990));
    Student marija("Marija Herceg", Datum(15, 6, 1990));
   
#pragma endregion
//
#pragma region TestiranjeIspita
    Ispit prIII("PRIII::26.11.2015", danas);
    //DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispti. 
    //onemoguciti dodavanje dva ista studenta
    if (prIII.DodajPrijavu(denis, danas))
        cout << denis << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(jasmin, danas))
        cout << jasmin << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(goran, danas))
        cout << goran << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(adel, danas))
        cout << adel << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(marija, danas))
        cout << marija << " DODAT na spisak" << endl;
//
    cout << crt << endl;
//    /*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu.
//    za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
    
    prIII.DodajRezultat(goran, 7);
    prIII.DodajRezultat(jasmin, 6);
    prIII.DodajRezultat(adel, 8);
    prIII.DodajRezultat(marija, 9);
    cout << prIII << endl;
//
//    /*Sortiraj - sortira rezultate ispita prema ocjeni*/
    prIII.Sortiraj();
    cout << prIII << endl;

//    /*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit
//    a nije im evidentirana ocjena*/
    prIII.ZakljuciRezultate();
//    //rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuèeni
      prIII.Sortiraj();
      cout << prIII << crt;
//
    Ispit prIII_2(prIII);
    cout << prIII_2 << crt;
#pragma endregion
}