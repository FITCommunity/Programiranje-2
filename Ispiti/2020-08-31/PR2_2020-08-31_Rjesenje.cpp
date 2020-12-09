#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
#include<regex>
using namespace std;



const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
const char* ispisPredmeta[] = { "UIT", "PRI", "PRII", "PRIII"," RSI", "RSII" };
enum Dupliranje { SA_DUPLIKATIMA, BEZ_DUPLIKATA };
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";


char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}
bool ValidirajLozinku(string lozinka)
{
    return regex_match(lozinka, regex("(?=.{6,7})[*_/][0-9][a-z][\\s]?[A-Z][0-9][a-z]"));
}
template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
    Dupliranje _dupliranje;

    bool PostojeLiIsti(T1 el1, T2 el2)
    {
        for (int i = 0; i < *_trenutno; i++)
        {
            if (_dupliranje == BEZ_DUPLIKATA && (_elementi1[i] == el1 && _elementi2[i] == el2))
                return true;
        }
        return false;
    }

public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _dupliranje = dupliranje;
    }

    Kolekcija(const Kolekcija& original) : _trenutno(new int(*original._trenutno)), _dupliranje(original._dupliranje)
    {
        _elementi1 = new T1[*_trenutno];
        _elementi2 = new T2[*_trenutno];
        for (int i = 0; i < *_trenutno; i++)
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
            *_trenutno = *drugi._trenutno;
            _elementi1 = new T1[*_trenutno];
            _elementi2 = new T2[*_trenutno];
            for (int i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = drugi._elementi1[i];
                _elementi2[i] = drugi._elementi2[i];
            }
        }
        return *this;
    }


    void AddElement(T1 el1, T2 el2)
    {
        if (PostojeLiIsti(el1, el2))
            throw exception("Nije moguce dodavati duple elemente!\n");
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
        _elementi1 = temp1; temp1 = nullptr;
        _elementi2 = temp2; temp2 = nullptr;
    }


    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }


    Kolekcija<T1, T2> operator[](T1 vrijednost)
    {
        Kolekcija<T1, T2> nova;
        for (int i = 0; i < *_trenutno; i++)
            if (_elementi1[i] == vrijednost)
                nova.AddElement(_elementi1[i], _elementi2[i]);
        return nova;
    }

    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (int i = 0; i < obj.getTrenutno(); i++)
            COUT << obj.getElement1(i) << "   " << obj.getElement2(i) << endl;
        return COUT;
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

    int toDays()
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }

    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << endl;
        return COUT;
    }
};


int GetRazlika(Datum& prvi, Datum& drugi)
{
    return abs(prvi.toDays() - drugi.toDays());
}


class Pitanje {
    char* _sadrzaj;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    Pitanje(const Pitanje& original) : _sadrzaj(GetNizKaraktera(original._sadrzaj)), _ocjeneRjesenja(original._ocjeneRjesenja) {}

    Pitanje& operator=(const Pitanje& drugi)
    {
        if (this != &drugi)
        {
            delete[] _sadrzaj;
            _sadrzaj = GetNizKaraktera(drugi._sadrzaj);
            _ocjeneRjesenja = drugi._ocjeneRjesenja;
        }
        return *this;
    }

    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*>& GetOcjene() { return _ocjeneRjesenja; }

    bool AddOcjena(int ocjena, Datum& datumOcjene)
    {
        int trenutno = _ocjeneRjesenja.getTrenutno();
        //mora se koristiti * prije _ocjeneRjesenja.getElement2 zato jer je u kolekciji pokazivac tipa Datum (treba se uzeti njegova vrijednost)
        if (trenutno != 0 && GetRazlika(datumOcjene, *_ocjeneRjesenja.getElement2(trenutno - 1)) < 3)
            return false;
        //da bi uspjesno dodali potrebno je dodati & prije datumOcjene da bi poslali adresu u kolekciju 
        _ocjeneRjesenja.AddElement(ocjena, &datumOcjene);
        return true;
    }

    bool operator==(Pitanje& drugo)
    {
        return strcmp(_sadrzaj, drugo._sadrzaj) == 0;
    }


    float GetProsjekPitanja()const
    {
        float prosjek = 0;
        if (_ocjeneRjesenja.getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++)
            prosjek += _ocjeneRjesenja.getElement1(i);
        return prosjek / _ocjeneRjesenja.getTrenutno();
    }

    friend ostream& operator<< (ostream& COUT, Pitanje obj)
    {
        COUT << "Sadrzaj pitanja-> " << obj._sadrzaj << endl;
        COUT << ":: OCJENE RJESENJA ::" << endl;
        for (int i = 0; i < obj.GetOcjene().getTrenutno(); i++)
            COUT << "Ocjena-> " << obj.GetOcjene().getElement1(i) << "     postignuta -> " << *obj.GetOcjene().getElement2(i) << endl;
        COUT << "Prosjek ocjena za pitanje je -> " << obj.GetProsjekPitanja() << endl;
        return COUT;
    }
};

class Ispit {
    Predmet _predmet;
    //string se odnosi na napomenu/zapazanje nastavnika
    Kolekcija<Pitanje, string> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = predmet;
    }

    Ispit(const Ispit& original) : _predmet(original._predmet), _pitanjaOdgovori(original._pitanjaOdgovori) {}

    Ispit& operator=(const Ispit& drugi)
    {
        if (this != &drugi)
        {
            _predmet = drugi._predmet;
            _pitanjaOdgovori = drugi._pitanjaOdgovori;
        }
        return *this;
    }


    Kolekcija<Pitanje, string>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return _predmet; }


    float GetProsjekSvihPitanja()
    {
        float prosjek = 0;
        if (_pitanjaOdgovori.getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _pitanjaOdgovori.getTrenutno(); i++)
            prosjek += _pitanjaOdgovori.getElement1(i).GetProsjekPitanja();
        return prosjek / _pitanjaOdgovori.getTrenutno();
    }

    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << "Predmet-> " << ispisPredmeta[obj._predmet] << endl;
        COUT << ":: PITANJA ODGOVORI ::" << endl;
        for (int i = 0; i < obj._pitanjaOdgovori.getTrenutno(); i++)
        {
            COUT << obj._pitanjaOdgovori.getElement1(i) << endl;
            COUT << "Napomena-> " << obj._pitanjaOdgovori.getElement2(i) << endl;
        }
        return COUT;
    }
};
class Korisnik {
    char* _imePrezime;
    string _emailAdresa;
    string _lozinka;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
    {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        //_lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
    }

    Korisnik(const Korisnik& original) : _imePrezime(GetNizKaraktera(original._imePrezime)), _emailAdresa(original._emailAdresa), _lozinka(original._lozinka) {}

    Korisnik& operator=(const Korisnik& drugi)
    {
        if (this != &drugi)
        {
            delete[] _imePrezime;
            _imePrezime = GetNizKaraktera(drugi._imePrezime);
            _emailAdresa = drugi._emailAdresa;
            _lozinka = drugi._lozinka;
        }
        return *this;
    }

    ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    virtual void Info() = 0;
};


mutex m;

class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
    void PosaljiEmail(const char* sadrzajPitanja, float prosjekPitanja)
    {
        m.lock();
        cout << "FROM: info@kursevi.ba\nTO: " << GetEmail() << "\n Postovani " << GetImePrezime() << ", evidentirana vam je ocjena->   za odgovor na pitanje-> " << sadrzajPitanja;
        cout << ".Dosadasnji uspjeh za pitanje-> " << sadrzajPitanja << " iznosi-> " << prosjekPitanja << ", a ukupni uspjeh na svim predmetima iznosi -> " << ProsjekSvihOdgovora() << endl;
        cout << "Pozdrav.\nEDUTeam.\n";
        m.unlock();
    }

public:
    void Info() {}
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) : Korisnik(imePrezime, emailAdresa, lozinka) {
    }
    Kandidat(const Kandidat& original) : Korisnik(original)
    {
        for (int i = 0; i < original._polozeniPredmeti.size(); i++)
            _polozeniPredmeti.push_back(new Ispit(*original._polozeniPredmeti[i]));
    }

    ~Kandidat() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i];
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << "Kandidat-> " << obj.GetImePrezime() << "   mail -> " << obj.GetEmail() << "   lozinka-> " << obj.GetLozinka() << endl;
        COUT << "::: POLOZENI PREDMETI :::" << endl;
        for (int i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }

    bool PostojeLiIsti(Predmet predmet, Pitanje& pitanje)
    {
        for (int i = 0; i < _polozeniPredmeti.size(); i++)
            if (_polozeniPredmeti[i]->GetPredmet() == predmet)
                for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno(); j++)
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore().getElement1(j) == pitanje)
                        return true;
        return false;
    }

    bool AddPitanje(Predmet predmet, Pitanje& pitanje, string napomena = "---")
    {
        for (int i = 0; i < _polozeniPredmeti.size(); i++)
        {
            if (predmet > _polozeniPredmeti[i]->GetPredmet() && (_polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno() < 3 || _polozeniPredmeti[i]->GetProsjekSvihPitanja() < 3.5))
                return false;

            if (PostojeLiIsti(predmet, pitanje))
                return false;

            _polozeniPredmeti[i]->GetPitanjaOdgovore().AddElement(pitanje, napomena);
            const char* sadrzaj = GetNizKaraktera(pitanje.GetSadrzaj());
            float prosjekPitanja = pitanje.GetProsjekPitanja();
            thread t1(&Kandidat::PosaljiEmail, this, sadrzaj, prosjekPitanja);
            t1.join();

            return true;
        }


        Ispit ispit(predmet);
        ispit.GetPitanjaOdgovore().AddElement(pitanje, napomena);
        _polozeniPredmeti.push_back(new Ispit(ispit));
        const char* sadrzaj = GetNizKaraktera(pitanje.GetSadrzaj());
        float prosjekPitanja = pitanje.GetProsjekPitanja();
        thread t1(&Kandidat::PosaljiEmail, this, sadrzaj, prosjekPitanja);
        t1.join();
        return true;
    }

    float ProsjekSvihOdgovora()
    {
        float prosjek = 0;
        if (_polozeniPredmeti.size() == 0)
            return prosjek;
        for (int i = 0; i < _polozeniPredmeti.size(); i++)
            prosjek += _polozeniPredmeti[i]->GetProsjekSvihPitanja();
        return prosjek / _polozeniPredmeti.size();
    }


    int operator()(string trazenaRijec)
    {
        regex pravilo(trazenaRijec);
        int brojRijeci = 0;
        for (int i = 0; i < _polozeniPredmeti.size(); i++)
            for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno(); j++)
                if (regex_search(_polozeniPredmeti[i]->GetPitanjaOdgovore().getElement2(j), pravilo))
                    brojRijeci++;
        return brojRijeci;
    }

};
//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Pojasnite na koji nacin tip nasljedjivanja (javno, zasticeno, privatno) utjece na dostupnost atributa bazne klase unutar izvedene klase?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Ukratko pojasnite primjenu funkcija seekg i tellg?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}



void main() {

    /* cout << PORUKA;
     cin.get();
     cout << GetOdgovorNaPrvoPitanje() << endl;
     cin.get();
     cout << GetOdgovorNaDrugoPitanje() << endl;
     cin.get();*/

    Datum   datum19062020(19, 6, 2020),
        datum20062020(20, 6, 2020),
        datum30062020(30, 6, 2020),
        datum05072020(5, 7, 2020);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*ukoliko dupliranje vrijednosti nije dozvoljeno (BEZ_DUPLIKATA)
        metoda AddElement baca izuzetak u slucaju da se pokusa dodati par sa vrijednostima
        identicnim postojecem paru unutar kolekcije */
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;

    /*na osnovu vrijednosti tip T1 (u primjeru vrijednost 1) pronalazi i vraca iz kolekcije sve parove
    koji kao vrijednost T1 imaju proslijedjenu vrijednost*/
    cout << kolekcija1[1] << crt;
    /* npr. ako unutar kolekcije postoje parovi:
    0 0
    1 9
    1 1
    2 2
    3 3
    ispis dobijenih/vracenih vrijednosti ce biti sljedeci:
    1 9
    1 1
    */

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza."),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom."),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa."),
        regex("Navedite par primjera regex validacije podataka.");


    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;

    //// ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
    // // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("*2gT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*7aT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("_6gU9z"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*3aB1y"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*1a T2l"))
        cout << "Lozinka validna" << endl;
    if (!ValidirajLozinku("-1a T2l"))
        cout << "Lozinka NIJE validna" << endl;

    ///*
    //za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
    //-   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
    //-   broj, nakon cega slijedi
    //-   malo slovo, nakon cega slijedi
    //-   razmak koji NIJE OBAVEZAN, nakon cega slijedi
    //-   veliko slovo, nakon cega slijedi
    //-   broj, nakon cega slijedi
    //-   malo slovo.
    //za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    //validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    //postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    //*/

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "*2gT2x");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "_6gU9z");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");


    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ukoliko je potrebno, doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);


    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija, "nedostaje operator delete"))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex, "unutar posljednjeg dijela nedostaje opis glavnih operatora"))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;

        // vraca broj ponavljanja odredjene rijeci unutar napomena nastalih tokom polaganja ispita.
        int brojPonavljanja = (*jasminPolaznik)("nedostaje");
        cout << "Rijec nedostaje se ponavlja " << brojPonavljanja << " puta." << endl;

    }
    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
    FROM:info@kursevi.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.
    EDUTeam.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */

    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
}
