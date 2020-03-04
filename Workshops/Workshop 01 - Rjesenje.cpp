#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

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
    char *naziv;
    char *opis;
    float cijena;
public:
    void Kreiraj()
    {
        char tempNaziv[20];
        cin.ignore();

        cout << "Unesite naziv (max 20): ";
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv) + 1;
        naziv = new char[velicinaNaziv];
        strcpy_s(naziv, velicinaNaziv, tempNaziv);

        char tempOpis[200];

        cout << "Unesite opis (max 200): ";
        cin.getline(tempOpis, sizeof tempOpis);

        int velicinaOpis = strlen(tempOpis) + 1;
        opis = new char[velicinaOpis];
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
        cout << "Naziv: " << GetNaziv() << endl
            << "Opis: " << GetOpis() << endl
            << "Cijena: " << GetCijena() << endl;
    }

    const char* GetNaziv() { return naziv; }
    void SetNaziv(const char* nazivJela)
    {
        if (nazivJela)
        {
            delete[] naziv;
            int velicina = strlen(nazivJela) + 1;
            naziv = new char[velicina];
            strcpy_s(naziv, velicina, nazivJela);
        }
    }
    const char* GetOpis() { return opis; }
    void SetOpis(const char* opisJela)
    {
        if (opisJela)
        {
            delete[] opis;
            int velicina = strlen(opisJela) + 1;
            opis = new char[velicina];
            strcpy_s(opis, velicina, opisJela);
        }
    }
    const float GetCijena() { return cijena; }
    void SetCijenu(float cijenaJela)
    {
        if (cijenaJela > 0)
        {
            cijena = cijenaJela;
        }
    }

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
        cin.ignore();

        cout << "Unesite naziv (max 20): ";
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv) + 1;
        naziv = new char[velicinaNaziv];
        strcpy_s(naziv, velicinaNaziv, tempNaziv);

        char tempOpis[200];

        cout << "Unesite opis (max 200): ";
        cin.getline(tempOpis, sizeof tempOpis);

        int velicinaOpis = strlen(tempOpis) + 1;
        opis = new char[velicinaOpis];
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
        cout << "Naziv: " << GetNaziv() << endl
            << "Opis: " << GetOpis() << endl
            << "Cijena: " << GetCijena() << endl;
    }

    const char* GetNaziv() { return naziv; }
    void SetNaziv(const char* nazivPica)
    {
        if (nazivPica)
        {
            delete[] naziv;
            int velicina = strlen(nazivPica) + 1;
            naziv = new char[velicina];
            strcpy_s(naziv, velicina, nazivPica);
        }
    }
    const char* GetOpis() { return opis; }
    void SetOpis(const char* opisPica)
    {
        if (opisPica)
        {
            delete[] opis;
            int velicina = strlen(opisPica) + 1;
            opis = new char[velicina];
            strcpy_s(opis, velicina, opisPica);
        }
    }
    const float GetCijena() { return cijena; }
    void SetCijenu(float cijenaPica)
    {
        if (cijenaPica > 0)
        {
            cijena = cijenaPica;
        }
    }

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

    void Ispisi()
    {
        const char* crt = "\n----------------------------------------------------------------------\n";
        cout << "Jela: " << crt;
        for (int i = 0; i < brojJela; i++)
            jela[i].Ispis();
        cout << "Pica: " << crt;
        for (int i = 0; i < brojPica; i++)
            pica[i].Ispis();
        cout << crt << "Ukupna cijena: " << ukupnaCijena << crt;
        statusIsporuke ? cout << "Isporuceno" 
                       : cout << "Nije isporuceno";
    }

    void DodajJelo(Jelo jelo)
    {
        Jelo* temp = new Jelo[brojJela + 1];
        for (int i = 0; i < brojJela; i++)
            temp[i] = jela[i];
        temp[brojJela].Kreiraj(jelo.GetNaziv(), jelo.GetOpis(), jelo.GetCijena());
        jela = temp;
        brojJela++;

        ukupnaCijena += jelo.GetCijena();

    }

    void DodajPice(Pice pice)
    {
        Pice* temp = new Pice[brojPica + 1];
        for (int i = 0; i < brojPica; i++)
            temp[i] = pica[i];
        temp[brojPica].Kreiraj(pice.GetNaziv(), pice.GetOpis(), pice.GetCijena());
        pica = temp;
        brojPica++;

        ukupnaCijena += pice.GetCijena();
    }


    Pice* GetPica() { return pica; }
    int GetBrojPica() { return brojPica; }
    Jelo* GetJela() { return jela; }
    int GetBrojJela() { return brojJela; }
    float GetUkupnuCijenu() { return ukupnaCijena; }
    bool GetStatusIsporuke() { return statusIsporuke; }
    void SetStatusIsporuke(bool status) { statusIsporuke = status; }

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
        cin.ignore();

        cout << "Unesite ime (max 20): ";
        cin.getline(tempIme, sizeof tempIme);

        int velicinaIme = strlen(tempIme) + 1;
        ime = new char[velicinaIme];
        strcpy_s(ime, velicinaIme, tempIme);

        char tempPrezime[20];

        cout << "Unesite prezime (max 20): ";
        cin.getline(tempPrezime, sizeof tempPrezime);

        int velicinaPrezime = strlen(tempPrezime) + 1;
        prezime = new char[velicinaPrezime];
        strcpy_s(prezime, velicinaPrezime, tempPrezime);

        char tempKontaktBroj[10];

        cout << "Unesite kontakt broj (max 10): ";
        cin.getline(tempKontaktBroj, sizeof tempKontaktBroj);

        int velicinaKontaktBroj = strlen(tempKontaktBroj) + 1;
        kontaktBroj = new char[velicinaKontaktBroj];
        strcpy_s(kontaktBroj, velicinaKontaktBroj, tempKontaktBroj);

        char tempAdresa[100];

        cout << "Unesite adresu (max 100): ";
        cin.getline(tempAdresa, sizeof tempAdresa);

        int velicinaAdresa = strlen(tempAdresa) + 1;
        adresa = new char[velicinaAdresa];
        strcpy_s(adresa, velicinaAdresa, tempAdresa);

        narudzbe = nullptr;
        brojNarudzbi = 0;
    }

    void Ispis()
    {
        cout << "Ime: " << GetIme() << endl
            << "Prezime: " << GetPrezime() << endl
            << "Kontakt broj: " << GetKontaktBroj() << endl
            << "Adresa " << GetAdresa() << endl;
    }

    const char* GetIme() { return ime; }
    void SetIme(const char* novoIme)
    {
        if (novoIme)
        {
            delete[] ime;
            int velicina = strlen(novoIme) + 1;
            ime = new char[velicina];
            strcpy_s(ime, velicina, novoIme);
        }
    }

    const char* GetPrezime() { return prezime; }
    void SetPrezime(const char* novoPrezime)
    {
        if (novoPrezime)
        {
            delete[] prezime;
            int velicina = strlen(novoPrezime) + 1;
            prezime = new char[velicina];
            strcpy_s(prezime, velicina, novoPrezime);
        }
    }

    const char* GetKontaktBroj() { return kontaktBroj; }
    void SetKontaktBroj(const char* noviKontaktBroj)
    {
        if (noviKontaktBroj)
        {
            delete[] kontaktBroj;
            int velicina = strlen(noviKontaktBroj) + 1;
            kontaktBroj = new char[velicina];
            strcpy_s(kontaktBroj, velicina, noviKontaktBroj);
        }
    }

    const char* GetAdresa() { return adresa; }
    void SetAdresa(const char* novaAdresa)
    {
        if (novaAdresa)
        {
            delete[] adresa;
            int velicina = strlen(novaAdresa) + 1;
            adresa = new char[velicina];
            strcpy_s(adresa, velicina, novaAdresa);
        }
    }

    void DodajNarudzbu(Narudzba& narudzba)
    {
        if (narudzba.GetBrojJela() > 0 || narudzba.GetBrojPica() > 0)
        {
            Narudzba* temp = new Narudzba[brojNarudzbi + 1];
            for (int i = 0; i < brojNarudzbi; i++)
                temp[i] = narudzbe[i];
            temp[brojNarudzbi] = narudzba;
            narudzbe = temp;
            brojNarudzbi++;
        }
    }

    Narudzba* GetNarudzbe() { return narudzbe; }
    void IspisiNarudzbe()
    {
        for (int i = 0; i < brojNarudzbi; i++)
            narudzbe[i].Ispisi();
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
        cin.ignore();

        cout << "Unesite naziv (max 50): ";
        cin.getline(tempNaziv, sizeof tempNaziv);

        int velicinaNaziv = strlen(tempNaziv) + 1;
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

    void Ispisi()
    {
        cout << "Naziv: " << naziv;
    }

    void Meni()
    {
        MeniJela();
        MeniPica();
    }

    void MeniJela()
    {
        for (int i = 0; i < brojJela; i++)
            GetJela()[i].Ispis();
    }

    void MeniPica()
    {
        for (int i = 0; i < brojPica; i++)
            GetPica()[i].Ispis();
    }

    Pice* GetPica() { return pica; }
    Jelo* GetJela() { return jela; }
    const char* GetNaziv() { return naziv; }
    void SetNaziv(const char* nazivRestorana)
    {
        if (nazivRestorana)
        {
            delete[] naziv;
            int velicina = strlen(nazivRestorana) + 1;
            naziv = new char[velicina];
            strcpy_s(naziv, velicina, nazivRestorana);
        }
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
        Pice* temp = new Pice[brojPica + 1];
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
    // ------------------------------------------------------------------------
    // Ignorisi assert funkcije
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // ToDo
    // ------------------------------------------------------------------------
    // [] Omoguciti klijentu da bira restoran
    // [] Omoguciti klijentu da bira pica odabranog restorana
    // [] Omoguciti klijentu da bira jela odabranog restorana
    // ------------------------------------------------------------------------

    //Jelo
    Jelo jelo;
    jelo.Kreiraj();
    jelo.Ispis();

    jelo.SetNaziv("Test Ime Jelo");
    jelo.SetOpis("Test Opis Jelo");
    jelo.SetCijenu(100000000);

    assert(strcmp(jelo.GetNaziv(), "Test Ime Jelo") == 0);
    assert(strcmp(jelo.GetOpis(), "Test Opis Jelo") == 0);
    assert(jelo.GetCijena() == 100000000);

    jelo.Dealociraj();

    //Pice
    Pice pice;
    pice.Kreiraj();
    pice.Ispis();

    pice.SetNaziv("Test Ime Pice");
    pice.SetOpis("Test Opis Pice");
    pice.SetCijenu(100000000);

    assert(strcmp(pice.GetNaziv(), "Test Ime Pice") == 0);
    assert(strcmp(pice.GetOpis(), "Test Opis Pice") == 0);
    assert(pice.GetCijena() == 100000000);

    pice.Dealociraj();

    //Klijent
    Klijent klijent;
    klijent.Registracija();
    klijent.Ispis();

    klijent.SetIme("Ime Klijenta");
    klijent.SetPrezime("Prezime Klijenta");
    klijent.SetKontaktBroj("Kontakt Broj Klijenta");
    klijent.SetAdresa("Adresa Klijenta");
    
    assert(strcmp(klijent.GetIme(), "Ime Klijenta") == 0);
    assert(strcmp(klijent.GetPrezime(), "Prezime Klijenta") == 0);
    assert(strcmp(klijent.GetKontaktBroj(), "Kontakt Broj Klijenta") == 0);
    assert(strcmp(klijent.GetAdresa(), "Adresa Klijenta") == 0);

    klijent.Dealociraj();

    //Restoran
    Restoran restoran;
    restoran.Kreiraj();
    restoran.Ispisi();

    restoran.SetNaziv("Naziv Restorana");
    
    assert(strcmp(restoran.GetNaziv(), "Naziv Restorana") == 0);

    restoran.Dealociraj();

    return 0;
}