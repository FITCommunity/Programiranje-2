#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<regex>
#include<mutex>

using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nije dodan zavrsni rad!";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;
const char* crt = "\n-------------------------\n";
char* AlocirajNizKaraktera(const char* sadrzaj)
{
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
public:
    Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
    Kolekcija(const Kolekcija& original) : _trenutno(original._trenutno)
    {
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        for (int i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = original._elementi1[i];
            _elementi2[i] = original._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& druga)
    {
        if (this != &druga)
        {
            if (_trenutno != 0)
            {
                delete[] _elementi1;
                delete[] _elementi2;
            }
            _trenutno = druga._trenutno;
            _elementi1 = new T1[_trenutno];
            _elementi2 = new T2[_trenutno];
            for (int i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = druga._elementi1[i];
                _elementi2[i] = druga._elementi2[i];
            }
        }
        return *this;
    }
    void AddElement(const T1& elem1, const T2& elem2) {

        for (int i = 0; i < _trenutno; i++)
            if (_elementi1[i] == elem1 || _elementi2[i] == elem2)
                throw exception(nedozvoljena_operacija);

        T1* temp1 = new T1[_trenutno + 1];
        T2* temp2 = new T2[_trenutno + 1];
        for (int i = 0; i < _trenutno; i++) {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
        _elementi1 = temp1;
        _elementi2 = temp2;

        _elementi1[_trenutno] = elem1;
        _elementi2[_trenutno++] = elem2;

    }
    T1* getElementi1Pok() { return _elementi1; }
    T2* getElementi2Pok() { return _elementi2; }
    T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
    int getTrenutno()const { return _trenutno; }

    friend ostream& operator<<(ostream& COUT, Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << "   " << obj.getElement2(i) << endl;
        return COUT;
    }
};
class Poglavlje {
    char* _naslov;
    char* _sadrzaj;
    bool _prihvaceno;
    int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
    Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
        :_ocjena(7), _prihvaceno(true) {
        _naslov = AlocirajNizKaraktera(naslov);
        _sadrzaj = AlocirajNizKaraktera(sadrzaj);
    }
    Poglavlje(const Poglavlje& original) : _naslov(AlocirajNizKaraktera(original._naslov)), _sadrzaj(AlocirajNizKaraktera(original._sadrzaj)), _prihvaceno(original._prihvaceno), _ocjena(original._ocjena) {}
    Poglavlje& operator=(const Poglavlje& drugi)
    {
        if (this != &drugi)
        {
            delete[] _naslov;
            delete[] _sadrzaj;
            _naslov = AlocirajNizKaraktera(drugi._naslov);
            _sadrzaj = AlocirajNizKaraktera(drugi._sadrzaj);
            _prihvaceno = drugi._prihvaceno;
            _ocjena = drugi._ocjena;
        }
        return *this;
    }
    Poglavlje() {
        delete[] _naslov; _naslov = nullptr;
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    char* GetNaslov() { return _naslov; }
    char* GetSadrzaj() { return _sadrzaj; }
    bool GetPrihvaceno() { return _prihvaceno; }
    int GetOcjena() { return _ocjena; }
    void OcijeniPoglavlje(int ocjena) {
        _ocjena = ocjena;
        if (_ocjena > 5 && ocjena <= 10)
            _prihvaceno = true;
    }
    void DodajNoviSadrzaj(string sadrzaj)
    {
        char* temp = AlocirajNizKaraktera((_sadrzaj + string(" " + sadrzaj)).c_str());
        delete[] _sadrzaj;
        _sadrzaj = temp;
    }
    friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
        if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
            return COUT;
        COUT << "Naslov poglavlja -> " << obj._naslov << endl;
        COUT << "Sadrzaj poglavlja: " << obj._sadrzaj << crt;
        if (obj._prihvaceno)
            COUT << "Ocjena poglavlja: " << obj._ocjena << endl;;
        return COUT;
    }
};

class ZavrsniRad {
    char* _tema;
    vector<Poglavlje> _poglavljaRada;
    string _datumOdbrane;
    float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
    ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
        _tema = AlocirajNizKaraktera(nazivTeme);
    }
    ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
        _tema = AlocirajNizKaraktera(org._tema);
    }
    ZavrsniRad& operator=(const ZavrsniRad& drugi)
    {
        if (this != &drugi)
        {
            delete[]_tema;
            _tema = AlocirajNizKaraktera(drugi._tema);
            _poglavljaRada = drugi._poglavljaRada;
            _datumOdbrane = drugi._datumOdbrane;
            _konacnaOcjena = drugi._konacnaOcjena;
        }
        return *this;
    }
    ~ZavrsniRad() {
        delete[] _tema; _tema = nullptr;
    }
    char* GetNazivTeme()const { return _tema; }
    vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
    string GetDatumOdbrane()const { return _datumOdbrane; }
    void SetDatumOdbrane(string datum) { _datumOdbrane = datum; }
    float GetKonacnaOcjena() { return _konacnaOcjena; }
    bool operator==(const ZavrsniRad& drugi)
    {
        return strcmp(_tema, drugi._tema) == 0 && _datumOdbrane == drugi._datumOdbrane;
    }
    friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj)
    {
        if (obj._tema != nullptr)
            COUT << "Tema rada: " << obj._tema << endl;
        COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Konacna ocjena zavrsnog rada: " << obj._konacnaOcjena << endl;
        COUT << ":::: POGLAVLJA :::: " << crt;
        for (int i = 0; i < obj._poglavljaRada.size(); i++)
            COUT << obj._poglavljaRada[i] << endl;
        return COUT;
    }
    bool ValidnaPoglavlja()
    {
        for (int i = 0; i < _poglavljaRada.size(); i++)
        {
            if (strlen(_poglavljaRada[i].GetSadrzaj()) < min_karaktera_po_poglavlju || !_poglavljaRada[i].GetPrihvaceno())
                return false;
        }
        return true;
    }
    float IzracunajProsjek()
    {
        float prosjek = 0;
        for (int i = 0; i < _poglavljaRada.size(); i++)
        {
            prosjek += _poglavljaRada[i].GetOcjena();
        }
        return prosjek / _poglavljaRada.size();
    }
    void SetKonacnaOcjena(float prosjek)
    {
        _konacnaOcjena = prosjek;
    }
    bool DodajPoglavlje(const char* nazivPoglavlja, string sadrzaj)
    {
        for (int i = 0; i < _poglavljaRada.size(); i++)
        {
            if (strcmp(_poglavljaRada[i].GetNaslov(), nazivPoglavlja) == 0)
            {
                _poglavljaRada[i].DodajNoviSadrzaj(sadrzaj);
                return true;
            }
        }
        _poglavljaRada.push_back(Poglavlje(nazivPoglavlja, sadrzaj.c_str()));
        return true;
    }
    void OcijeniPoglavlje(const char* nazivPoglavlja, int ocjena)
    {
        for (int i = 0; i < _poglavljaRada.size(); i++)
        {
            if (strcmp(_poglavljaRada[i].GetNaslov(), nazivPoglavlja) == 0)
                _poglavljaRada[i].OcijeniPoglavlje(ocjena);
        }
    }
};

class Osoba {
protected:
    string _imePrezime;
public:
    Osoba(string imePrezime) : _imePrezime(imePrezime) {}
    string GetImePrezime() { return _imePrezime; }
    virtual void Info() = 0;
};

class Nastavnik : public Osoba {
    //Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
    Kolekcija<string, ZavrsniRad> _teme;
public:
    void Info() {}
    Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
    Nastavnik(string imePrezime) : Osoba(imePrezime)
    {

    }
    Nastavnik(const Nastavnik& original) : Osoba(original), _teme(original._teme) {}
    Nastavnik& operator=(Nastavnik& drugi)
    {
        if (this != &drugi)
        {
            _teme = drugi._teme;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& COUT, Nastavnik& obj)
    {
        COUT << "Nastavnik -> " << obj.GetImePrezime() << endl;
        COUT << "::: MENTORSTVA :::" << crt;
        for (int i = 0; i < obj._teme.getTrenutno(); i++)
        {
            COUT << "Broj indeksa-> " << obj._teme.getElement1(i) << endl;
            COUT << obj._teme.getElement2(i) << endl;
        }
        return COUT;
    }


    bool DodajZavrsniRad(string brojIndeksa, ZavrsniRad& zavrsniRad)
    {
        try
        {
            _teme.AddElement(brojIndeksa, zavrsniRad);
            return true;//obavezno staviti true;
        }
        catch (const std::exception & err)
        {
            cout << err.what() << crt;
        }
        return true;
    }
    float GetProsjek()
    {
        float prosjek = 0;
        for (int i = 0; i < _teme.getTrenutno(); i++)
        {
            prosjek += _teme.getElement2(i).IzracunajProsjek();
        }
        return prosjek / _teme.getTrenutno();
    }
    ZavrsniRad* ZakaziOdbranuRada(string brojIndeksa, string datumOdbrane)
    {
        for (int i = 0; i < _teme.getTrenutno(); i++)
        {
            if (_teme.getElement1(i) == brojIndeksa && _teme.getElement2(i).GetPoglavlja().size() >= min_polgavlja && _teme.getElement2(i).ValidnaPoglavlja())
            {
                float prosjek = _teme.getElement2(i).IzracunajProsjek();
                _teme.getElement2(i).SetKonacnaOcjena(prosjek);
                _teme.getElement2(i).SetDatumOdbrane(datumOdbrane);
                return &_teme.getElement2(i);
            }
        }
        return nullptr;
    }

};


/*Funkcija PronadjiNajStudenta ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod nastavnika/mentora sa najnizom prosjecnom ocjenom
   i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem,
   "Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora}
   uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 20.09.2018. godine."
   da su svoj zavrsni rad uspjesno odbranili sa vecom ili manjom ocjenom od prosjecne.
   funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/


int NajmanjiProsjek(Nastavnik** nastavnici, int max)
{
    float prosjek = INT_MAX;
    int indeks = 0;
    for (int i = 0; i < max; i++)
    {
        if (nastavnici[i]->GetProsjek() < prosjek)
        {
            prosjek = nastavnici[i]->GetProsjek();
            indeks = i;
        }
    }
    return indeks;
}

mutex mjuteks;

void PosaljiSMS(string brojIndeksa, string imeMentora, float ocjena)
{
    mjuteks.lock();
    cout << "Postovani " << brojIndeksa << " uzimajuci u obzir cinjenicu da ste kod mentora " << imeMentora << endl;
    cout << "uspjesno odbranili rad sa ocjenom  " << ocjena << " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzati na FIT-u 20.09.2018. godine." << crt;
    mjuteks.unlock();
}


string PosaljiPozivZaDodjeluNagrada(Nastavnik** nastavnici, int max, double limitProsjek)
{
    string poruka = "NIJE PRONADJEN";
    int indeks = NajmanjiProsjek(nastavnici, max);
    Nastavnik* najgori = nastavnici[indeks];

    for (int i = 0; i < najgori->GetTeme().getTrenutno(); i++)
    {
        if (najgori->GetTeme().getElement2(i).IzracunajProsjek() >= limitProsjek)
        {
            string indeks = najgori->GetTeme().getElement1(i);
            string imeMentora = najgori->GetImePrezime();
            float prosjek = najgori->GetTeme().getElement2(i).IzracunajProsjek();
            poruka = "Student sa zadovoljavajucim prosjekom je -> " + najgori->GetTeme().getElement1(i);
            thread sms(PosaljiSMS, indeks, imeMentora, prosjek);
            this_thread::sleep_for(chrono::seconds(2));
            sms.join();
        }
    }
    return poruka;
}

int main() {
    const int max = 4;
    Nastavnik* nastavnici[max];

    nastavnici[0] = new Nastavnik("Denis Music");
    nastavnici[1] = new Nastavnik("Zanin Vejzovic");
    nastavnici[2] = new Nastavnik("Jasmin Azemovic");
    nastavnici[3] = new Nastavnik("Emina Junuz");


    ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
    ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
    ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
    ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");


    /*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu,
    funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor).
    u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
    //nazivPoglavlja, sadrzajPoglavlja
    multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
    multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
    multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
    multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
    multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");




    //nazivPoglavlja, ocjena
    multimedijalni.OcijeniPoglavlje("Uvod", 8);
    cout << multimedijalni;


    /*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu.
    zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
    sprijeciti dodavanje zavrsnih radova sa istom temom*/
    //brojIndeksa, zavrsniRad
    if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
        cout << "Zavrsni rad uspjesno dodat!" << endl;
    if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
        cout << "Zavrsni rad uspjesno dodat!" << endl;
    if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
        cout << "Zavrsni rad nije dodat!" << endl;
    if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
        cout << "Zavrsni rad nije dodat!" << endl;
    if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
        cout << "Zavrsni rad uspjesno dodat!" << endl;
    if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
        cout << "Zavrsni rad uspjesno dodat!" << endl;

    /*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
    datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio.
    Za zakazivanje odbrane rada moraju biti zadovoljeni sljedeci uslovi:
                   1. zavrsni rad mora imati broj poglavlja veci od minimalnog
                   2. svako poglavlje mora imati broj karaktera veci od minimalnog
                   3. svako poglavlje mora biti prihvaceno/odobreno
    ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na
    rad kome je zakazan odbrana.
    u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//brojIndeksa, datumOdbrane

    ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
    if (zr1 != nullptr)
        cout << *zr1 << endl;

    zr1 = nastavnici[0]->ZakaziOdbranuRada("ib130111", "25.09.2018");//student sa brojem indeksa ib130111 jos uvijek nije prijavio rad
    if (zr1 != nullptr)
        cout << *zr1 << endl;
    else
        cout << "Student nije prijavio rad!" << crt;


    //ispisuje sve podatke o nastavniku i njegovim mentorstvima
    cout << *nastavnici[0] << endl;

    /*Funkcija PronadjiNajStudenta ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod nastavnika/mentora sa najnizom prosjecnom ocjenom
    i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem,
    "Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora}
    uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 20.09.2018. godine."
    da su svoj zavrsni rad uspjesno odbranili sa vecom ili manjom ocjenom od prosjecne.
    funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
    cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 6.5) << endl;
    //
    //    /*
    //    Koristeci postojeci programski code, demonstrirati i ukratko opisati polimorfizam.
    //    */

    for (int i = 0; i < max; i++)
    {
        delete nastavnici[i];
        nastavnici[i] = nullptr;
    }

    system("pause>0");
    return 0;
}