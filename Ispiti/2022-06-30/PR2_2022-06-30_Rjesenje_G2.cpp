#include<iostream>
#include<string>
#include<thread>
#include<regex>
#include<mutex>
#include<vector>
#include<fstream>
#include<memory>
using namespace std;


const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };
const char* IspisKarakteristke[] = { "NARUDZBA", "KVALITET", "PAKOVANJE", "ISPORUKA" };

/*
* za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
sljedeceg formata:
- pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
- nakon toga slijede tri ili cetiri broja
- nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
- nakon toga slijede dva mala slova unutar viticastih zagrada

pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
*/

bool ValidirajJedinstveniKod(string kod) {
    return regex_match(kod, regex("[\\[][A-Z]{1,2}[\\]][0-9]{3,4}[-]?\\s?[\\{][a-z]{2}[\\}]"));
}

char* GetNizKaraktera(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}

unique_ptr<char[]> GetUniquePtr(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    unique_ptr<char[]> novi(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}


template<class T1, class T2, int max>
class Rijecnik {
    T1* _elementi1[max];
    T2* _elementi2[max];
    int* _trenutno;
    bool _omoguciDupliranje;

public:
    Rijecnik(bool omoguciDupliranje = true) {
        _trenutno = new int(0);
        _omoguciDupliranje = omoguciDupliranje;
    };

    Rijecnik(const Rijecnik& obj) {
        _trenutno = new int(*obj._trenutno);
        _omoguciDupliranje = obj._omoguciDupliranje;
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = new T1(*obj._elementi1[i]);
            _elementi2[i] = new T2(*obj._elementi2[i]);
        }
    }

    Rijecnik& operator=(const Rijecnik& obj) {
        if (this != &obj) {

            delete _trenutno; _trenutno = nullptr;
            for (size_t i = 0; i < *_trenutno; i++)
            {
                delete[]_elementi1[i]; _elementi1 = nullptr;
                delete[]_elementi2[i]; _elementi2 = nullptr;
            }

            _trenutno = new int(*obj._trenutno);
            _omoguciDupliranje = obj._omoguciDupliranje;
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = new T1(*obj._elementi1[i]);
                _elementi2[i] = new T2(*obj._elementi2[i]);
            }
        }
        return *this;
    }

    void AddElement(T1 el1, T2 el2) {
        if (_omoguciDupliranje == false) {
            for (size_t i = 0; i < *_trenutno; i++) {
                if (*_elementi1[i] == el1 && *_elementi2[i] == el2)
                    throw exception("Nema dupliranja!");
            }
        }
        if (*_trenutno == max)
            throw exception("Rijecnik je popunjen");

        _elementi1[*_trenutno] = new T1(el1);
        _elementi2[*_trenutno] = new T2(el2);

        (*_trenutno)++;
    }

    Rijecnik<T1, T2, max> RemoveAt(int lokacija) {
        Rijecnik<T1, T2, max> novi;
        novi.AddElement(*_elementi1[lokacija], *_elementi2[lokacija]);

        for (size_t i = lokacija; i < *_trenutno - 1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }
        (*_trenutno)--;
        return novi;

    }

    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Rijecnik& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    ~Rijecnik() {
        for (size_t i = 0; i < *_trenutno; i++)
        {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        delete _trenutno; _trenutno = nullptr;
    }


};

class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            delete _dan; _dan = nullptr;
            delete _mjesec; _mjesec = nullptr;
            delete _godina; _godina = nullptr;
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }

    bool operator==(const Datum& obj) {
        return *_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan;
    }

    bool operator!=(const Datum& obj) {
        return !(*this == obj);
    }

    int toDays() const {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }

    bool operator>(const Datum& obj) {
        return this->toDays() > obj.toDays();
    }

    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

class ZadovoljstvoKupca {
    char* _komentar;
    //uz komentar, kupci mogu ocijeniti svaku od karakteristika proizvoda, a int se odnosi na ocjenu u rasponu od 1 - 10.
    //onemoguciti dupliranje karakteristika tj. svaki karakteristika se moze ocijeniti samo jednom...u suprotnom baciti objekat tipa exception
    Rijecnik<Karakteristike, int, 4>* _ocjeneKarakteristika;
public:
    ZadovoljstvoKupca(const char* komentar = "") {
        //kreirajte funkciju GetNizKaraktera ili na drugi adekvatan nacin izvrsite inicijalizaciju pokazivaca
        _komentar = GetNizKaraktera(komentar);
        _ocjeneKarakteristika = new Rijecnik<Karakteristike, int, 4>();
    }

    ZadovoljstvoKupca(const ZadovoljstvoKupca& obj) {
        _komentar = GetNizKaraktera(obj._komentar);
        _ocjeneKarakteristika = new Rijecnik<Karakteristike, int, 4>(*obj._ocjeneKarakteristika);
    }

    ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& obj) {
        if (this != &obj) {
            delete[] _komentar; _komentar = nullptr;
            delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
            _komentar = GetNizKaraktera(obj._komentar);
            _ocjeneKarakteristika = new Rijecnik<Karakteristike, int, 4>(*obj._ocjeneKarakteristika);
        }
        return *this;
    }

    void AddOcjenuKarakteristike(Karakteristike karakteristike, int ocjena) {
        if (_ocjeneKarakteristika->getTrenutno() != 0)
        {
            for (size_t i = 0; i < _ocjeneKarakteristika->getTrenutno(); i++)
            {
                if (_ocjeneKarakteristika->getElement1(i) == karakteristike)
                    throw exception("Kakrakteristika je vec ocjenjena!");
            }
        }
        _ocjeneKarakteristika->AddElement(karakteristike, ocjena);
    }

    float ProsjekKarakteristika() const {
        float suma = 0;
        if (_ocjeneKarakteristika->getTrenutno() == 0)
            return suma;
        for (size_t i = 0; i < _ocjeneKarakteristika->getTrenutno(); i++)
        {
            suma += _ocjeneKarakteristika->getElement2(i);
        }
        return suma / _ocjeneKarakteristika->getTrenutno();
    }

    bool operator==(const ZadovoljstvoKupca& obj) {
        return strcmp(_komentar, obj._komentar) == 0;
    }

    bool operator!=(const ZadovoljstvoKupca& obj) {
        return !(*this == obj);
    }

    ~ZadovoljstvoKupca() {
        delete[] _komentar; _komentar = nullptr;
        delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
    }
    char* GeKomentar() { return _komentar; }
    Rijecnik<Karakteristike, int, 4>* GetOcjeneKarakteristika() { return _ocjeneKarakteristika; }

    friend ostream& operator<< (ostream& COUT, const ZadovoljstvoKupca& obj) {
        COUT << "Komentar: " << obj._komentar << endl;
        for (size_t i = 0; i < obj._ocjeneKarakteristika->getTrenutno(); i++)
        {
            COUT << IspisKarakteristke[i] << " (" << obj._ocjeneKarakteristika->getElement2(i) << ")" << endl;
        }
        return COUT;
    }

};

class Kupac {
    unique_ptr<char[]>_imePrezime;
    string _emailAdresa;
    string _jedinstveniKod;
public:
    Kupac(const char* imePrezime, string emailAdresa, string jedinstveniKod) {
        _imePrezime = GetUniquePtr(imePrezime);
        _emailAdresa = emailAdresa;
        //_jedinstveniKod = "ISKORISTITI FUNKCIJU ValidirajJedinstveniKod";

        if (ValidirajJedinstveniKod(jedinstveniKod))
            _jedinstveniKod = jedinstveniKod;
        else
            jedinstveniKod = "NOT VALID";

    }

    Kupac(const Kupac& obj) {
        _imePrezime = GetUniquePtr(obj._imePrezime.get());
        _emailAdresa = obj._emailAdresa;
        _jedinstveniKod = obj._jedinstveniKod;
    }

    Kupac& operator=(const Kupac& obj) {
        if (this != &obj) {
            _imePrezime = GetUniquePtr(obj._imePrezime.get());
            _emailAdresa = obj._emailAdresa;
            _jedinstveniKod = obj._jedinstveniKod;
        }
        return *this;
    }

    bool operator==(Kupac& obj) {
        if (strcmp(GetImePrezime(), obj.GetImePrezime()) != 0)
            return false;
        if (GetEmail() == obj.GetEmail())
            return false;
        if (GetJedinstveniKod() == obj.GetJedinstveniKod())
            return false;
        return true;
    }

    string GetEmail() { return _emailAdresa; }
    string GetJedinstveniKod() { return _jedinstveniKod; }
    char* GetImePrezime() { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._jedinstveniKod << endl;
        return COUT;
    }
};

mutex m;
class Kupovina {
    Datum _datumKupovine;
    //jedna kupovina moze podrazumjevati isporuku proizvoda vecem broju kupaca
    //onemoguciti dodavanje kupaca sa istom email adresom ili jedinstvenim kodomu okviru jedne kupovine
    vector<Kupac> _kupaci;
    //za svaku kupovinu se moze ostaviti samo jedan komentar odnosno ocjena zadovoljstva, bez obzirana broj kupaca
    ZadovoljstvoKupca _zadovoljstvoKupca;

    void SaljiMail(ZadovoljstvoKupca kupac) {
        m.lock();
        cout << "TO: " << endl;
        for (size_t i = 0; i < _kupaci.size(); i++)
        {
            cout << _kupaci[i].GetEmail() << endl;
        }
        cout << "Subject: Informacija" << endl;
        cout << "Postovani,\nZaprimili smo Vase ocjene, a njihova prosjecna vrijednost je " << kupac.ProsjekKarakteristika() << endl;
        cout << "Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima." << endl;
        cout << "Nadamo se da cete i dalje poslovati sa nama\nPuno pozdrava" << endl;
        m.unlock();
    }

public:
    Kupovina(Datum& datum, Kupac& kupac) : _datumKupovine(datum) {
        _kupaci.push_back(kupac);
    }

    Kupovina(const Kupovina& obj) {
        _datumKupovine = obj._datumKupovine;
        _kupaci = obj._kupaci;
        _zadovoljstvoKupca = obj._zadovoljstvoKupca;
    }
    Kupovina& operator=(const Kupovina& obj) {
        if (this != &obj) {
            _datumKupovine = obj._datumKupovine;
            _kupaci = obj._kupaci;
            _zadovoljstvoKupca = obj._zadovoljstvoKupca;
        }
        return *this;
    }

    bool AddKupca(Kupac kupac) {
        for (size_t i = 0; i < _kupaci.size(); i++)
        {
            if (_kupaci[i].GetEmail() == kupac.GetEmail() && _kupaci[i].GetJedinstveniKod() == kupac.GetJedinstveniKod())
                return false;
        }
        _kupaci.push_back(kupac);
        return true;
    }


    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
    //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
    void SetZadovoljstvoKupca(ZadovoljstvoKupca z_kupac) {
        _zadovoljstvoKupca = z_kupac;
        int brojac = 0;
        for (size_t i = 0; i < _zadovoljstvoKupca.GetOcjeneKarakteristika()->getTrenutno(); i++)
        {
            if (_zadovoljstvoKupca.GetOcjeneKarakteristika()->getElement2(i) < 5)
                brojac++;
        }
        if (brojac >= 2) {
            thread t1(&Kupovina::SaljiMail, this, z_kupac);
            t1.join();
        }
    }

    vector<Kupac>& GetKupci() { return _kupaci; }
    ZadovoljstvoKupca GetZadovoljstvoKupca() { return _zadovoljstvoKupca; }

    friend ostream& operator<< (ostream& COUT, Kupovina& obj) {
        COUT << crt << "Kupovina " << obj._datumKupovine << " za kupce: " << endl;
        for (size_t i = 0; i < obj._kupaci.size(); i++)
        {
            COUT << "\t" << i + 1 << "." << obj._kupaci[i];
        }
        cout << crt << "Zadovoljstvo kupca: " << endl << obj._zadovoljstvoKupca << crt;
        cout << "Prosjecna ocjena -> " << obj._zadovoljstvoKupca.ProsjekKarakteristika() << endl;
        return COUT;
    }

    tuple<int, int, int> GetBrojZnakova(const char* naziv)
    {
       int velikaSlova = 0, malaSlova = 0, brojRazmaka = 0;
        char znak;
        ifstream fajl(naziv);
        if (!fajl.fail())
        {
            while (fajl.get(znak))
            {
                if (znak >= 'A' && znak <= 'Z')
                    velikaSlova++;
                else if (znak >= 'a' && znak <= 'z')
                    malaSlova++;
                else if (znak == ' ')
                    brojRazmaka++;
            }
        }
        fajl.close();
        return { velikaSlova,malaSlova, brojRazmaka };
    }
};

//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> \Nabrojite i ukratko pojasnite osnovne ios modove koji se koriste u radu sa fajlovima?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Pojasnite prednosti i nedostatke visestrukog nasljedjivaja, te ulogu virtualnog nasljedjivanja u tom kontekstu?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}

void main() {

    //cout << PORUKA;
    //cin.get();
    //cout << GetOdgovorNaPrvoPitanje() << endl;
    //cin.get();
    //cout << GetOdgovorNaDrugoPitanje() << endl;
    //cin.get();

    Datum datum30062022(30, 6, 2022);

    const int rijecnikTestSize = 9;
    Rijecnik<int, int, rijecnikTestSize> rijecnik1(false);

    for (int i = 0; i < rijecnikTestSize - 1; i++)
        rijecnik1.AddElement(i, i);//dodaje vrijednosti u rijecnik

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    rijecnik1.AddElement(9, 9);

    try
    {
        //ukoliko je rijecnik popunje, metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(10, 10);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    cout << rijecnik1 << crt;

    /* metoda RemoveAt treba da ukloni i vrati (kao povratnu vrijednost)clanoverijecnika koji se nalaze na lokaciji definisanoj prvim parametrom.
    * Nakon izvrsenja metode RemoveAt, objekat rijecnik1 bi trebao posjedovati sljedeci sadrzaj:
    * 0  0
    * 1  1
    * 3  3
    * 4  4
    * ....
    *
    * a objekat rijecnik2 samo jedan par:
    *  2  2
    */
    Rijecnik<int, int, rijecnikTestSize> rijecnik2 = rijecnik1.RemoveAt(2);
    cout << rijecnik2 << crt;


    /*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva mala slova unutar viticastih zagrada

    pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    */

    if (ValidirajJedinstveniKod("[BH]235-{mo}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[MO]235{sa}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[B]2356 {ih}"))
        cout << "Jedinstveni kod validan" << endl;
    if (!ValidirajJedinstveniKod("[s]2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("[BH]2356{h}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("BH2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;


    Kupac denis("Denis Music", "denis@fit.ba", "[BH]235-{mo}");
    Kupac jasmin("Jasmin Azemovic", "jasmin@fit.ba", "[MO]235{sa}");
    Kupac adel("Adel Handzic", "adel@edu.fit.ba", "[B]2356 {ih}");
    Kupac jedinstveniKodNotValid("Ime Prezime", "korisnik@klix.ba", "BH2356{ih}");//_jedinstveniKod = NOT VALID

    //kupovini  se prilikom kreiranja mora dodijeliti kupac koji je kreator kupovine
    Kupovina kupovina(datum30062022, denis);
    if (kupovina.AddKupca(jasmin))
        cout << "Kupac uspjesno dodan!";

    ZadovoljstvoKupca zadovoljstvoKupca("Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem");
    zadovoljstvoKupca.AddOcjenuKarakteristike(NARUDZBA, 7);
    zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4);

    try {
        zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4); //kakrakteristika je vec ocjenjena
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.AddOcjenuKarakteristike(PAKOVANJE, 3);
    zadovoljstvoKupca.AddOcjenuKarakteristike(ISPORUKA, 6);

    //u okviru kupovine postavlja vrijednost atributa _zadovoljstvoKupca
    kupovina.SetZadovoljstvoKupca(zadovoljstvoKupca);

    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
    //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
   /*
       To: denis@fit.ba;jasmin@fit.ba;
       Subject: Informacija

       Postovani,

       Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
       Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

       Nadamo se da cete i dalje poslovati sa nama
       Puno pozdrava
   */

   //ispisuje sve podatke o kupovini, kupcima, komentar, ocjene pojedinih karakteristika i prosjecnu ocjenu.
   cout << kupovina << endl;
    /* Primjer ispisa:
       -------------------------------------------
       Kupovina 30.6.2022 za kupce:
               1.Denis Music denis@fit.ba [BH]235-{mo}
               2.Jasmin Azemovic jasmin@fit.ba [MO]235{sa}
       -------------------------------------------
       Zadovoljstvo kupca:
       Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
             NARUDZBA(7)
             KVALITET(4)
             PAKOVANJE(3)
             ISPORUKA(6)
       -------------------------------------------
       Prosjecna ocjena -> 5
   */

    Kupovina kupovinaSaAdelom = kupovina;
    if (kupovinaSaAdelom.AddKupca(adel))
        cout << "Kupac uspjesno dodan!";
    if (!kupovinaSaAdelom.AddKupca(denis))
        cout << "Kupac je vec dodan!";

    cout << kupovinaSaAdelom << endl;

    ///*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao parametar, nalazi: velikih slova, malih slova i razmaka..*/
    //tuple<int, int, int> brojac = kupovinaSaAdelom.GetBrojZnakova("sadrzaj.txt");
    //cout << "Velikih slova: " << get<0>(brojac) << endl;
    //cout << "Malih slova: " << get<1>(brojac) << endl;
    //cout << "Razmaka: " << get<2>(brojac) << endl;
    /*
    ukolikoo je sadrzaj fajla npr. "Denis Music" povratne vrijednosti metode GetBrojZnakova bi trebale biti 2 8 1. za potrebe testiranja kreirajte fajl sa zeljenim sadzajem
    */

    cin.get();
    system("pause>0");
}
