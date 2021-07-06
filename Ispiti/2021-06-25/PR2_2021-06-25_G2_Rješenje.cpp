#include <iostream>
#include <vector>
#include <thread>
#include <regex>
#include <mutex>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };
const char* ispisPojaseva[] = { " BIJELI", "ZUTI", "NARANDZASTI", "ZELENI", "PLAVI", "SMEDJI", "CRNI" };

bool ValidirajEmail(string mail) {
    return regex_search(mail, regex("[0-9][_][a-zA-Z]{3,}[_.]?[a-zA-Z]{3,}@(karate|edu.karate)\.(ba|com|org)"));
}


char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
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
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            delete _dan;
            delete _mjesec;
            delete _godina;
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }
    int getDane()const
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    bool operator>(const Datum drugi)
    {
        return this->getDane() > drugi.getDane();
    }
    bool operator==(const Datum& obj) {
        return *obj._dan == *_dan && *obj._mjesec == *_mjesec && *obj._godina == *_godina;
    }
};
template<class T1, class T2, int max = 15>
class Kolekcija {
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    void AddElement(const T1 element1, const T2 element2) {
        if (_dupliranje == Dupliranje::BEZ_DUPLIKATA) {
            for (size_t i = 0; i < *_trenutno; i++) {
                if (_elementi1[i] == element1 && _elementi2[i] == element2)
                    throw exception("Nije dozvoljeno dupliranje elemenata.\n");
            }
        }
        _elementi1[*_trenutno] = element1;
        _elementi2[*_trenutno] = element2;

        (*_trenutno)++;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }
    Kolekcija(const Kolekcija& obj) {
        _trenutno = new int(*obj._trenutno);
        for (size_t i = 0; i < *obj._trenutno; i++) {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
        _dupliranje = obj._dupliranje;
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
        {
            delete _trenutno;
            _trenutno = new int(*obj._trenutno);
            for (size_t i = 0; i < *obj._trenutno; i++) {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }
    Kolekcija& operator()(int pocetak, int kraj) {
        Kolekcija* objekat = new Kolekcija();
        if (*_trenutno == 0 || pocetak<0 || kraj>*_trenutno)
        {
            throw exception("Elementi iz objekta nisu validni.\n");
        }
        for (size_t i = pocetak; i <= kraj; i++)
            objekat->AddElement(_elementi1[i], _elementi2[i]);
        return *objekat;
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};


class Tehnika {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 � 5, a datum na momenat postizanja ocjene
    Kolekcija<Datum, int>* _ocjene;
public:
    bool operator==(const Tehnika& obj) {
        //provjerava SAMO naziv.
        return strcmp(_naziv, obj._naziv) == 0;
    }
    Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = nullptr;
        if (ocjena > 0)
            AddOcjena(&datum, ocjena);
    }
    Tehnika(const Tehnika& obj) {
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = new Kolekcija<Datum, int>(*obj._ocjene);

    }
    bool AddOcjena(const Datum* obj, int ocjena) {
        if (_ocjene != nullptr) {
            _ocjene->AddElement(*obj, ocjena);
            return 1;
        }
        _ocjene = new Kolekcija<Datum, int>();
        _ocjene->AddElement(*obj, ocjena);
        return 1;
    }
    float GetProsjekTehnike()
    {
        //prosjek jedne tehnike (najmanja jedinica)
        float prosjek = 0;
        if (_ocjene->getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _ocjene->getTrenutno(); i++)
            prosjek += _ocjene->getElement2(i);
        return prosjek / _ocjene->getTrenutno();
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv()const { return _naziv; }
    Kolekcija<Datum, int> GetOcjene() const { return *_ocjene; }

    friend ostream& operator<<(ostream& COUT, const Tehnika& obj) {
        COUT << "Naziv tehnike " << obj.GetNaziv() << endl;
        COUT << "Datum \t Ocjena" << endl;
        for (size_t i = 0; i < obj._ocjene->getTrenutno(); i++) {
            COUT << obj.GetOcjene().getElement1(i) << " " << obj.GetOcjene().getElement2(i) << endl;
        }

        return COUT;
    }
};
class Polaganje {
    Pojas _pojas;
    //string se odnosi na napomenu o polozenoj tehnici
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    void DodajTehniku(const Tehnika& tehnika, string napomena) {
        _polozeneTehnike.AddElement(new Tehnika(tehnika), napomena);
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        //popravljen ispis.
        //COUT << obj._pojas << " " << obj._polozeneTehnike << endl;

        COUT << ispisPojaseva[obj._pojas] << " ";
        for (size_t i = 0; i < obj._polozeneTehnike.getTrenutno(); i++) {
            COUT << *obj._polozeneTehnike.getElement1(i) << " " << obj._polozeneTehnike.getElement2(i) << endl;
            COUT << ":::::::::::::::::::::\n";
        }

        return COUT;
    }
    float GetProsjekPojasa()
    {
        //prosjek pojasa je prosjek koji u sebi ima vise tehnika(saberemo sve prosjeke tehnika i podijelimo s brojem njih) (veca jedinica od tehnike)
        float prosjek = 0;
        if (_polozeneTehnike.getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); i++)
            prosjek += _polozeneTehnike.getElement1(i)->GetProsjekTehnike();
        return prosjek / _polozeneTehnike.getTrenutno();
    }
};
mutex mjuteks;
class KaratePolaznik {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
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
    bool PostojeLiIsti(Pojas pojas, Tehnika& tehnika)
    {
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (_polozeniPojasevi[i].GetPojas() == pojas)
            {
                for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
                {
                    if (*_polozeniPojasevi[i].GetTehnike().getElement1(j) == tehnika)
                        return true;
                }
            }
        }
        return false;
    }

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

    bool AddTehniku(Pojas pojas, Tehnika& tehnika, string napomena)
    {
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            //ako je proslijedjeni pojas visi od prethodnog pojasa i taj prethodni pojas nema nijednu tehniku i dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5 - ne treba dodati 
            if (pojas > _polozeniPojasevi[i].GetPojas() && _polozeniPojasevi[i].GetTehnike().getTrenutno() < 1 && _polozeniPojasevi[i].GetProsjekPojasa() < 3.5)
                return false;

            if (_polozeniPojasevi[i].GetPojas() == pojas)
            {
                if (PostojeLiIsti(pojas, tehnika))
                    return false;
                _polozeniPojasevi[i].DodajTehniku(tehnika, napomena);
                //prvi parametar lokacija funkcije koja je zaduzena za slanje maila, drugi parametar na koji objekat se odnosi tj. na this jer se Polazniku salje mail
                //naredni parametri su oni koji se traze u ispisu(ako se ne traze ne salje se nista)
                thread saljemMail(&KaratePolaznik::PosaljiMail, this, pojas, tehnika);
                //obavezno za svaki thread mora se join-at glavnom programu OBAVEZNO!
                saljemMail.join();
                return true;
            }
        }

        Polaganje p(pojas);
        p.DodajTehniku(tehnika, napomena);
        _polozeniPojasevi.push_back(p);
        thread saljemMail(&KaratePolaznik::PosaljiMail, this, pojas, tehnika);
        saljemMail.join();
        return true;
    }


    KaratePolaznik(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojTelefona = brojTelefona;
    }

    float GetProsjecanBrojDana()
    {
        float prosjek = 0;
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
            {
                for (int k = 0; k < _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno() - 1; k++)
                {
                    prosjek = _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k).getDane()
                        + _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k + 1).getDane();
                }
                return prosjek / _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno();
            }
        }
    }

    Kolekcija<Tehnika*, float>& operator()(Datum prvi, Datum drugi)
    {
        //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
       //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici      
        Kolekcija<Tehnika*, float>* objekat = new Kolekcija<Tehnika*, float>();

        float prosjecanBrojDana = GetProsjecanBrojDana();
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
            {
                for (int k = 0; k < _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno(); k++)
                {
                    if (_polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k) > prvi && drugi > _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k))
                    {
                        objekat->AddElement(_polozeniPojasevi[i].GetTehnike().getElement1(j), GetProsjecanBrojDana());
                    }
                }
            }
        }
        return *objekat;

    }
    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Za sta se koriste modovi ios::ate i ios::trunc ?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasniti ulogu i na�in koristenja iteratora?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {


    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);


    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);

    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    ////svaka tehnika moze imati vise ocjena i polaze se u vise navrata (istog ili drugog dana)
    ////parametri: nazivTehnike, prva ocjena, datum polaganja
    Tehnika choku_zuki("choku_zuki", datum19062021, 5),
        gyaku_zuki("gyaku_zuki", datum20062021, 5),
        kizami_zuki("kizami_zuki", datum30062021, 2),
        oi_zuki("oi_zuki", datum05072021, 5);

    choku_zuki.AddOcjena(&datum05072021, 3);
    choku_zuki.AddOcjena(&datum05072021, 5);

    //// ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
    //// ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
    cout << choku_zuki << endl;

    ///*
    //email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljede�a pravila:
    //- poceti sa jednim brojem nakon cega slijedi donja crtica
    //- u imenu posjedovati najmanje 3 karaktera
    //- izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    //- u prezimenu posjedovati najmanje 3 karaktera
    //- znak @
    //- domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.

    //za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    //validacija email adrese ce se vrsiti unutar konstruktora klase KaratePolaznik, a u slucaju da nije validna
    //postaviti je na defaultnu adresu: notSet@edu.karate.ba
    //*/



    if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("3_ime_prezime@karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("4_imeprezime@karate.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("8_imeprezime@karate.org"))
        cout << "Email validan" << crt;
    if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;
    if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic", "1_jasmin.azemovic@karate.ba", "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic", "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime", "korisnik@karate.ru", "033 281 170");

    ///*
    //svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    //uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    //tom prilikom onemoguciti:
    //- dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    //- dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI pojas)
    //- dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    //funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    //*/

    //ne treba dodati kizami_zuki jer ne postoji niti jedna tehnika za ZUTI pojas
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodan!" << crt;
    //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana!" << crt;
        
    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << *jasmin << crt;

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06, 2021), Datum(21, 06, 2021));

    for (size_t i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " << jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}
