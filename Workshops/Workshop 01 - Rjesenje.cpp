#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/*
    Vježbe 1 - Principi OOP, klase, objekti.
    Zadatak: Na osnovu opisa sistema prepoznati osnovne klase i atribute, kao i njihove relacije,
    te implementirati osnovne metode koje omogućavaju kreiranje i
    ispis narudžbi klijentu. Obavezno implementirati Get i Set metode.
    Tema: e-Restoran

    Namjena aplikacije e-Restoran jeste da omogući kreiranje narudžbi klijentima restorana putem standardnih PC i
    mobilnih uređaja. U procesu kreiranja narudžbe neophodno je da klijent obavi registraciju gdje upisuje svoje
    osnovne podatke: ime, prezime, kontakt broj i adresu. Nakon uspješne registracije klijenti mogu da kreiraju
    narudžbu na osnovu online ponude odabranog restorana. Ponuda restorana se sastoji od jela i pića.
    Uz svako jelo i piće prikazuje se kratak opis i cijena. Narudžba koju klijent kreira sadrži najmanje jedno
    jelo ili piće, ukupnu cijenu narudžbe i status isporuke.
*/

class Jelo
{
    char* naziv;
    char* opis;
    float cijena;
public:
    void Kreiraj()
    {
        char tempNaziv[20];

        cout << "Unesite naziv (max 20): ";
        cin.ignore();
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv);
        naziv = new char[velicinaNaziv];
        strcpy_s(naziv, velicinaNaziv, tempNaziv);

        char tempOpis[200];

        cout << "Unesite opis (max 200): ";
        cin.ignore();
        cin.getline(tempOpis, sizeof tempOpis);

        int velicinaOpis = strlen(tempOpis);
        naziv = new char[velicinaOpis];
        strcpy_s(opis, velicinaOpis, tempOpis);

        cout << "Unesite cijenu: ";
        cin >> cijena;
    }

    void Kreiraj(const char* nazivJela, const char* opisJela, float cijenaJela)
    {
        int velicina;

        velicina = strlen(nazivJela) + 1;
        naziv = new char[velicina];
        strcpy_s(naziv, velicina, nazivJela);

        velicina = strlen(opisJela) + 1;
        opis = new char[velicina];
        strcpy_s(opis, velicina, opisJela);

        cijena = cijenaJela;
    }

    void Ispis()
    {
        cout << "Naziv: " << naziv << endl
            << "Opis: " << opis << endl
            << "Cijena: " << cijena << endl;
    }

    const char* GetNaziv() { return naziv; }
    const char* GetOpis() { return opis; }
    const float GetCijena() { return cijena; }

    void Dealociraj()
    {
        delete[] naziv; naziv = nullptr;
        delete[] opis; opis = nullptr;
    }
};


class Pice
{
    char* naziv;
    char* opis;
    float cijena;
public:
    void Kreiraj()
    {
        char tempNaziv[20];

        cout << "Unesite naziv (max 20): ";
        cin.ignore();
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv);
        naziv = new char[velicinaNaziv];
        strcpy_s(naziv, velicinaNaziv, tempNaziv);

        char tempOpis[200];

        cout << "Unesite opis (max 200): ";
        cin.ignore();
        cin.getline(tempOpis, sizeof tempOpis);

        int velicinaOpis = strlen(tempOpis);
        naziv = new char[velicinaOpis];
        strcpy_s(opis, velicinaOpis, tempOpis);

        cout << "Unesite cijenu: ";
        cin >> cijena;
    }

    void Kreiraj(const char* nazivPica, const char* opisPica, float cijenaPica)
    {
        int velicina;

        velicina = strlen(nazivPica) + 1;
        naziv = new char[velicina];
        strcpy_s(naziv, velicina, nazivPica);

        velicina = strlen(opisPica) + 1;
        opis = new char[velicina];
        strcpy_s(opis, velicina, opisPica);

        cijena = cijenaPica;
    }

    void Ispis()
    {
        cout << "Naziv: " << naziv << endl
            << "Opis: " << opis << endl
            << "Cijena: " << cijena << endl;
    }

    const char* GetNaziv() { return naziv; }
    const char* GetOpis() { return opis; }
    const float GetCijena() { return cijena; }

    void Dealociraj()
    {
        delete[] naziv; naziv = nullptr;
        delete[] opis; opis = nullptr;
    }
};


class Narudzba
{
    Jelo* jela;
    int brojJela;
    Pice* pica;
    int brojPica;

    float ukupnaCijena;
    bool statusIsporuke;
public:
    void Kreiraj()
    {
        jela = nullptr;
        brojJela = 0;
        pica = nullptr;
        brojPica = 0;
    }


    void DodajJelo(Jelo jelo)
    {
        Jelo* temp = new Jelo[brojJela + 1];
        for (int i = 0; i < brojJela; i++)
            temp[i] = jela[i];
        temp[brojJela].Kreiraj(jelo.GetNaziv(), jelo.GetOpis(), jelo.GetCijena());
        jela = temp;
        brojJela++;

    }

    void DodajPice(Pice pice)
    {
        Pice* temp = new Pice[brojJela + 1];
        for (int i = 0; i < brojPica; i++)
            temp[i] = pica[i];
        temp[brojPica].Kreiraj(pice.GetNaziv(), pice.GetOpis(), pice.GetCijena());
        pica = temp;
        brojPica++;
    }


    void Dealociraj()
    {
        for (int i = 0; i < brojJela; i++)
            jela[i].Dealociraj();
        delete[] jela; jela = nullptr;
        brojJela = 0;

        for (int i = 0; i < brojPica; i++)
            pica[i].Dealociraj();
        delete[] pica; pica = nullptr;
        brojPica = 0;

        ukupnaCijena = 0;
    }
};

class Klijent
{
    char *ime;
    char *prezime;
    char *kontaktBroj;
    char *adresa;
    Narudzba* narudzbe;
    int brojNarudzbi;
public:
    void Registracija()
    {
        char tempIme[20];

        cout << "Unesite ime (max 20): ";
        cin.ignore();
        cin.getline(tempIme, sizeof tempIme);

        int velicinaIme = strlen(tempIme);
        ime = new char[velicinaIme];
        strcpy_s(ime, velicinaIme, tempIme);

        char tempPrezime[20];

        cout << "Unesite prezime (max 20): ";
        cin.ignore();
        cin.getline(tempPrezime, sizeof tempPrezime);

        int velicinaPrezime = strlen(tempPrezime);
        prezime = new char[velicinaPrezime];
        strcpy_s(prezime, velicinaPrezime, tempPrezime);

        char tempKontaktBroj[10];

        cout << "Unesite kontakt broj (max 10): ";
        cin.ignore();
        cin.getline(tempKontaktBroj, sizeof tempKontaktBroj);

        int velicinaKontaktBroj = strlen(tempKontaktBroj);
        kontaktBroj = new char[velicinaKontaktBroj];
        strcpy_s(kontaktBroj, velicinaKontaktBroj, tempKontaktBroj);

        char tempAdresa[100];

        cout << "Unesite adresu (max 100): ";
        cin.ignore();
        cin.getline(tempAdresa, sizeof tempAdresa);

        int velicinaAdresa = strlen(tempAdresa);
        adresa = new char[velicinaAdresa];
        strcpy_s(adresa, velicinaAdresa, tempAdresa);

        narudzbe = nullptr;
        brojNarudzbi = 0;
    }

    void DodajNarudzbu(Narudzba& narudzba)
    {
        Narudzba *temp = new Narudzba[brojNarudzbi + 1];
        for (int i = 0; i < brojNarudzbi; i++)
            temp[i] = narudzbe[i];
        temp[brojNarudzbi] = narudzba;
        narudzbe = temp;
        brojNarudzbi++;
    }

    void Dealociraj()
    {
        delete[] ime; ime = nullptr;
        delete[] prezime; prezime = nullptr;
        delete[] kontaktBroj; kontaktBroj = nullptr;
        delete[] adresa; adresa = nullptr;
        for (int i = 0; i < brojNarudzbi; i++)
            narudzbe[i].Dealociraj();
        delete[] narudzbe; narudzbe = 0;
    }

};

class Restoran
{
    char *naziv;
    Jelo *jela;
    int brojJela;
    Pice *pica;
    int brojPica;
public:
    void Kreiraj()
    {
        char tempNaziv[50];

        cout << "Unesite naziv (max 50): ";
        cin.ignore();
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv);
        naziv = new char[velicinaNaziv];
        strcpy_s(naziv, velicinaNaziv, tempNaziv);

        jela = nullptr;
        brojJela = 0;
        pica = nullptr;
        brojPica = 0;
    }

    void Kreiraj(const char *nazivRestorana)
    {
        int velicina = strlen(nazivRestorana) + 1;
        naziv = new char[velicina];
        strcpy_s(naziv, velicina, nazivRestorana);

        jela = nullptr;
        brojJela = 0;
        pica = nullptr;
        brojPica = 0;
    }


    void DodajJelo(Jelo jelo)
    {
        Jelo *temp = new Jelo[brojJela + 1];
        for (int i = 0; i < brojJela; i++)
            temp[i] = jela[i];
        temp[brojJela].Kreiraj(jelo.GetNaziv(), jelo.GetOpis(), jelo.GetCijena());
        jela = temp;
        brojJela++;

    }

    void DodajPice(Pice pice)
    {
        Pice* temp = new Pice[brojJela + 1];
        for (int i = 0; i < brojPica; i++)
            temp[i] = pica[i];
        temp[brojPica].Kreiraj(pice.GetNaziv(), pice.GetOpis(), pice.GetCijena());
        pica = temp;
        brojPica++;
    }

    void Dealociraj()
    {
        delete[] naziv; naziv = nullptr;
        for (int i = 0; i < brojJela; i++)
            jela[i].Dealociraj();
        delete[] jela; jela = nullptr;
        brojJela = 0;
        for (int i = 0; i < brojPica; i++)
            pica[i].Dealociraj();
        delete[] pica; pica = nullptr;
        brojPica = 0;
    }
};




int main()
{
    Jelo test1, test2;
    test1.Kreiraj("AAA", "AAAA", 1);
    test2.Kreiraj("BBB", "BBBB", 2);

    Restoran rest1;
    rest1.Kreiraj("Restoran");
    rest1.DodajJelo(test1);
    rest1.DodajJelo(test2);

    Narudzba narudzba;
    narudzba.Kreiraj();
    narudzba.DodajJelo(test1);
    narudzba.DodajJelo(test2);

    rest1.Dealociraj();
    narudzba.Dealociraj();

    return 0;
}