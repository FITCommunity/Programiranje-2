#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
using namespace std;


const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
const char* ispisPojaseva[] = { " BIJELI", "ZUTI", "NARANDZASTI", "ZELENI", "PLAVI", "SMEDJI", "CRNI" };
const int brojTehnika = 6;
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

template<class T1, class T2, int max = 10>
class Kolekcija {
    T1* _elementi1[max] = { nullptr };
    T2* _elementi2[max] = { nullptr };
    int  _trenutno;
public:
    Kolekcija() { _trenutno = 0; }

    Kolekcija(const Kolekcija& original) : _trenutno(original._trenutno)
    {
        for (int i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = new T1(*original._elementi1[i]);
            _elementi2[i] = new T2(*original._elementi2[i]);
        }
    }

    Kolekcija& operator=(const Kolekcija& druga)
    {
        if (this != &druga)
        {
            if (_trenutno != 0)
            {
                for (int i = 0; i < _trenutno; i++)
                {
                    delete _elementi1[i];
                    delete _elementi2[i];
                }
            }
            _trenutno = druga._trenutno;
            for (int i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = new T1(*druga._elementi1[i]);
                _elementi2[i] = new T2(*druga._elementi2[i]);
            }
        }
        return *this;
    }

    ~Kolekcija() {
        for (size_t i = 0; i < _trenutno; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
    }


    void AddElement(T1 el1, T2 el2)
    {
        if (_trenutno >= max)
            throw exception("Dosegli ste maksimum kolekcije!\n");
        //ako nema pokazivaca onda ide samo _elementi1[_trenutno]=el1 jer je rijec o statickom nizu, u suprotnom se mora napraviti alokacija memorije za taj novi clan tj. el1
        _elementi1[_trenutno] =new T1(el1);
        _elementi2[_trenutno] = new T2(el2);
        _trenutno++;
    }

    void AddElement(T1 el1, T2 el2, int lokacija)
    {
        for (int i = _trenutno; i > lokacija; i--)
        {
            *_elementi1[i] = *_elementi1[i - 1];
            *_elementi2[i] = *_elementi2[i - 1];
        }

        _elementi1[lokacija] = new T1(el1);
        _elementi2[lokacija] = new T1(el2);
        _trenutno++;
    }


    void RemoveAt(int lokacija)
    {
        for (int i = lokacija; i < _trenutno-1; i++)
        {
            *_elementi1[i] =*_elementi1[i + 1];
            *_elementi2[i] =*_elementi2[i + 1];
        }
        _trenutno--;
    }


    //na osnovu vrijednosti T1 mijenja vrijednost T2. 
    T2& operator[](T1 vrijednost)
    {
        for (int i = 0; i < _trenutno; i++)
        {
            if (*_elementi1[i] == vrijednost)
                return *_elementi2[i];
        }
    }

    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << "    " << obj.getElement2(i) << endl;
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

    int toDane()
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }

    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina<<endl;
        return COUT;
    }
};

int GetRazliku(Datum& prvi, Datum& drugi)
{
    return abs(prvi.toDane() - drugi.toDane());
}


class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a Datum na datum kada je ocijenjena odredjena tehnika 
    Kolekcija<int, Datum, brojTehnika>* _ocjene;
public:
    Tehnika(const char* naziv) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<int, Datum, brojTehnika>();
    }
    Tehnika(const Tehnika& original) : _naziv(GetNizKaraktera(original._naziv))
    {
        _ocjene = new Kolekcija<int, Datum, brojTehnika>(*original._ocjene);
    }
    Tehnika& operator=(const Tehnika& druga)
    {
        if (this != &druga)
        {
            delete[] _naziv;
            delete _ocjene;
            _naziv = GetNizKaraktera(druga._naziv);
            _ocjene = new Kolekcija<int, Datum, brojTehnika>(*druga._ocjene);
        }
        return *this;
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum, brojTehnika>& GetOcjene() { return *_ocjene; }


   
    bool AddOcjena(int ocjena, Datum& datumOcjene)
    {
        //spremimo broj ocjena u jedan int trenutno
        int trenutno = _ocjene->getTrenutno();
        //samo ukoliko nesto postoji unutar kolekcije tek onda provjeravas da li je proslo tri dana od posljednjeg dodavanja
        //da je kojim slucajem ovdje bilo _trenutno==0 onda bi probala proslijediti datum koji se nalazi na lokaciji _trenutno-1 sto bi izazvalo gresku
        if (trenutno != 0 && GetRazliku(datumOcjene, _ocjene->getElement2(trenutno - 1)) < 3)
            return false;
        _ocjene->AddElement(ocjena, datumOcjene);
        return true;
    }

    float GetProsjekTehnike()
    {
        //prosjek jedne tehnike (najmanja jedinica)
        float prosjek = 0;
        if (_ocjene->getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _ocjene->getTrenutno(); i++)
            prosjek += _ocjene->getElement1(i);
        return prosjek / _ocjene->getTrenutno();
    }

    bool operator==(const Tehnika& druga)
    {
        return strcmp(_naziv, druga._naziv) == 0;
    }

    friend ostream& operator<<(ostream& COUT, Tehnika& obj)
    {
        COUT << "Tehnika-> " << obj._naziv << endl;
        COUT << ":: OCJENE TEHNIKE :: " << endl;
        for (int i = 0; i < obj._ocjene->getTrenutno(); i++)
            COUT << "Ocjena-> " << obj._ocjene->getElement1(i) << "     datum ocjene-> " << obj._ocjene->getElement2(i) << endl;
        COUT << "Prosjek za tehniku je-> " <<obj.GetProsjekTehnike() << endl;
        return COUT;
    }
};

class Polaganje {
    Pojas _pojas;
    vector<Tehnika*> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Polaganje(const Polaganje& original) : _pojas(original._pojas)
    {
        for (int i = 0; i < original._polozeneTehnike.size(); i++)
        {
            _polozeneTehnike.push_back(new Tehnika(*original._polozeneTehnike[i]));
        }
    }
    ~Polaganje() {
        for (size_t i = 0; i < _polozeneTehnike.size(); i++) {
            delete _polozeneTehnike[i];
            _polozeneTehnike[i] = nullptr;
        }
    }
    vector<Tehnika*>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }

    float GetProsjekPojasa()
    {
        //prosjek pojasa je prosjek koji u sebi ima vise tehnika(saberemo sve prosjeke tehnika i podijelimo s brojem njih) (veca jedinica od tehnike)
        float prosjek = 0;
        if (_polozeneTehnike.size() == 0)
            return prosjek;
        for (int i = 0; i < _polozeneTehnike.size(); i++)
            prosjek += _polozeneTehnike[i]->GetProsjekTehnike();
        return prosjek / _polozeneTehnike.size();
    }

    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT <<"Pojas-> "<<ispisPojaseva[obj._pojas] << endl;
        COUT << "::: POLOZENE TEHNIKE ZA POJAS ::: " << endl;
        for (size_t i = 0; i < obj._polozeneTehnike.size(); i++)
            COUT << *obj._polozeneTehnike[i];
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
       // _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
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
    virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    virtual void info() = 0;
    friend ostream& operator<<(ostream& COUT, Korisnik& obj)
    {
        COUT << "Korisnik-> " << obj._imePrezime << "   email-> " << obj._emailAdresa << "  lozinka-> " << obj._lozinka << endl;
        return COUT;
    }
};

mutex mjuteks;

class KaratePolaznik : public Korisnik{
    vector<Polaganje> _polozeniPojasevi;
    void PosaljiMail(Pojas pojas, Tehnika tehnika)
    {
        mjuteks.lock();
        cout << "FROM:info@karate.ba\nTO: " << GetEmail() << "\nPostovani " << GetImePrezime() << ", evidentirana vam je tehnika " << tehnika.GetNaziv() << " za " << ispisPojaseva[pojas] << " pojas" << endl;
        cout << "Dosadasnji uspjeh na pojasu " << ispisPojaseva[pojas] << " iznosi -> ";
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (_polozeniPojasevi[i].GetPojas() == pojas)
                cout << _polozeniPojasevi[i].GetProsjekPojasa();
        }
        cout << ", a ukupni prosjek na svim pojasevima je -> " << GetUkupanProsjek() << "\nPozdrav.\n\nKARATE Team." << crt;
        mjuteks.unlock();
    }


public:
    void info() {}
    KaratePolaznik(const char* imePrezime, string emailAdresa, string lozinka): Korisnik(imePrezime,emailAdresa,lozinka) {
    }
    KaratePolaznik(const KaratePolaznik& original) : Korisnik(original), _polozeniPojasevi(original._polozeniPojasevi) {}
    KaratePolaznik& operator=(const KaratePolaznik& drugi)
    {
        if (this != &drugi)
        {
            Korisnik::operator=(drugi);
            _polozeniPojasevi = drugi._polozeniPojasevi;
        }
        return *this;
    }
    virtual ~KaratePolaznik() {
        cout << crt << "DESTRUKTOR -> KaratePolaznik" << crt;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT <<"Karate polaznik-> "<< obj.GetImePrezime() << "   email-> " << obj.GetEmail() << "   lozinka->  " << obj.GetLozinka() << endl;
        COUT << "::: POLOZENI POJASEVI ::: " << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }

    float GetUkupanProsjek()
    {
        //ukupan prosjek svih pojaseva koji u svom prosjeku imaju prosjeke tehnika koji se nalaze u njima
        float prosjek = 0;
        if (_polozeniPojasevi.size() == 0)
            return prosjek;
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
            prosjek += _polozeniPojasevi[i].GetProsjekPojasa();
        return prosjek / _polozeniPojasevi.size();
    }


    bool PostojeLiIsti(Pojas pojas, Tehnika& tehnika)
    {
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (_polozeniPojasevi[i].GetPojas() == pojas)
            {
                for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().size(); j++)
                {
                    if (*_polozeniPojasevi[i].GetTehnike()[j] == tehnika)
                        return true;
                }
            }
        }
        return false;
    }

  

    bool AddTehniku(Pojas pojas, Tehnika& tehnika)
    {
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            //ako je proslijedjeni pojas visi od prethodnog pojasa i ( taj prethodni pojas ima manje od tri tehnike ili prosjek tog pojasa je manji od 3.5) ne treba dodati 
            if (pojas > _polozeniPojasevi[i].GetPojas() && (_polozeniPojasevi[i].GetTehnike().size() < 3 || _polozeniPojasevi[i].GetProsjekPojasa() < 3.5))
                return false;

            if (_polozeniPojasevi[i].GetPojas() == pojas)
            {
                if (PostojeLiIsti(pojas, tehnika))
                    return false;

                _polozeniPojasevi[i].GetTehnike().push_back(new Tehnika(tehnika));
                //prvi parametar lokacija funkcije koja je zaduzena za slanje maila, drugi parametar na koji objekat se odnosi tj. na this jer se Polazniku salje mail
                //naredni parametri su oni koji se traze u ispisu(ako se ne traze ne salje se nista)
                thread saljemMail(&KaratePolaznik::PosaljiMail,this,pojas,tehnika);
                //obavezno za svaki thread mora se join-at glavnom programu OBAVEZNO!
                saljemMail.join();
                return true;
            }
        }

        Polaganje p(pojas);
        p.GetTehnike().push_back(new Tehnika(tehnika));
        _polozeniPojasevi.push_back(p);
        thread saljemMail(&KaratePolaznik::PosaljiMail, this, pojas, tehnika);
        saljemMail.join();
        return true;
    }


};


const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite ulogu operatora reinterpret_cast.\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko opisite znacaj i vrste pametnih pokazivaca.\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
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

    Kolekcija<int, int> kolekcija1;
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*metoda AddElement baca izuzetak u slucaju da se pokusa
        dodati vise od maksimalnog broja elemenata*/
        kolekcija1.AddElement(11, 11);
    }
    catch (exception & err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;


    kolekcija1.RemoveAt(2);
    /*uklanja par (T1 i T2) iz kolekcije koji se nalazi na lokaciji sa proslijedjenim indeksom.
    nakon uklanjanja vrijednosti onemoguciti pojavu praznog prostora unutar kolekcije tj.
    pomjeriti sve elemente koji se nalaze nakon proslijedjene lokacije za jedno mjesto unazad
    npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon uklanjanja vrijednosti na lokaciji 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    2 2
    3 3
    */

    cout << kolekcija1 << crt;

    kolekcija1.AddElement(9, 9, 2);
    /*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
    nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
    u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    9 9
    1 1
    2 2
    3 3
    */

    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija1 << crt;

    //na osnovu vrijednosti T1 mijenja vrijednost T2. 
    kolekcija1[9] = 2;

    cout << kolekcija1 << endl;
    /* npr.ako unutar kolekcije postoje elementi:
    0 0
    9 9
    1 1
    2 2
    3 3
    nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
    0 0
    9 2
    1 1
    2 2
    3 3
    */

    Tehnika choku_zuki("choku_zuki"),
        gyaku_zuki("gyaku_zuki"),
        kizami_zuki("kizami_zuki"),
        oi_zuki("oi_zuki");

    /*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise navrata.
        -   razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (choku_zuki.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!choku_zuki.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (choku_zuki.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;

    ///* ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
    //   ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0*/
    cout << choku_zuki << endl;

    //if (ValidirajLozinku("john4Do*e"))
    //    cout << "OK" << crt;
    //if (!ValidirajLozinku("john4Doe"))
    //    cout << "Specijalni znak?" << crt;
    //if (!ValidirajLozinku("jo*4Da"))
    //    cout << "7 znakova?" << crt;
    //if (!ValidirajLozinku("4jo-hnoe"))
    //    cout << "Veliko slovo?" << crt;
    //if (ValidirajLozinku("@john2Doe"))
    //    cout << "OK" << crt;

    ///*
    //za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    //-   najmanje 7 znakova
    //-   velika i mala slova
    //-   najmanje jedan broj
    //-   najmanje jedan specijalni znak
    //za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    //validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    //postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    //*/

    Korisnik* jasmin = new KaratePolaznik("Jasmin Azemovic", "jasmin@karate.ba", "j@sm1N*");
    Korisnik* adel = new KaratePolaznik("Adel Handzic", "adel@edu.karate.ba", "4Ade1*H");
    Korisnik* emailNijeValidan = new KaratePolaznik("John Doe", "john.doe@google.com", "johndoe");


    /*
    sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
    (onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    ////doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    KaratePolaznik* jasminPolaznik = dynamic_cast<KaratePolaznik*>(jasmin);
    cout << *jasminPolaznik << endl;

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddTehniku(ZUTI, gyaku_zuki))
            cout << "Tehnika uspjesno dodan!" << crt;
        //ne treba dodati kizami_zuki jer ne postoje evidentirane 3 tehnike za ZUTI pojas
        if (!jasminPolaznik->AddTehniku(NARANDZASTI, kizami_zuki))
            cout << "Tehnika NIJE uspjesno dodana!" << crt;
        if (jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
            cout << "Tehnika uspjesno dodan!" << crt;
        //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
        if (!jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
            cout << "Tehnika NIJE uspjesno dodana!" << crt;

        //ispisuje sve dostupne podatke o karate polazniku
        cout << *jasminPolaznik << crt;
    }

    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */

    //osigurati da se u narednim linijama poziva i destruktor klase KaratePolaznik
    delete jasmin;
    delete adel;
    delete emailNijeValidan;

    cin.get();
    system("pause>0");
}
