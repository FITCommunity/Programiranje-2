/*
	BIG DISCLAIMER

	Ja nisam izlazio na ovaj rok, samo sam prikupio odredene informacije kroz pricu
	drugih studenata i slika koje su nekako uslikane tokom ispita. Moguce je da postoji
	mnogo vise razlicitih stvari nego sto sam naveo ovdje.

	Teoretska pitanja sam postavio na osnovu onoga sto sam cuo.
*/

#include <iostream>
using namespace std;
const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. "
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEÅ ENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";

enum Drzava { ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA };

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}

template<class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max]{};
	T2* _elementi2[max]{};
	int _trenutno{ 0 };
public:
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};

class Vrijeme {
	int* _sat, * _minuta, * _sekunda;
public:
	Vrijeme(int sat = 10, int minuta = 0, int sekunda = 0) {
		_sat = new int(sat);
		_minuta = new int(minuta);
		_sekunda = new int(sekunda);
	}
	~Vrijeme() {
		delete _sat; _sat = nullptr;
		delete _minuta; _minuta = nullptr;
		delete _sekunda; _sekunda = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Vrijeme& obj) {
		COUT << obj._sat << ":" << obj._minuta << ":" << obj._sekunda;
		return COUT;
	}
};

class Pogodak {
	Vrijeme* _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena)
	{
		_napomena = GetNizKaraktera(napomena);
		_vrijemePogotka = new Vrijeme(vrijeme);
	}
	~Pogodak()
	{
		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;
	}
	Vrijeme GetVrijemePogotka() { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}
};

class Igrac {
	static int _id;
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID i vrijednost statickog clana _id
	char* _imePrezime;
	vector<Pogodak*> _pogoci;
public:
	Igrac(const char* imePrezime) {
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	~Igrac() {
		delete[] _ID; _ID = nullptr;
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); ++i) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << *obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			COUT << *obj._pogoci[i] << endl;
		return COUT;
	}
};

class DrzavaTim {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	DrzavaTim(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}
	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }
};

class Prventstvo {
	Kolekcija<DrzavaTim*, DrzavaTim*, 20> _utakmice;
public:
	Kolekcija<DrzavaTim*, DrzavaTim*, 20>& GetUtakmice() {
		return _utakmice;
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite kljucnu rijec virtual? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite function tip podatka? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/*
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale, tj. zadnje slovo imena i prvo slovo prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne vrijednosti parametara. Ukoliko se proslijede
	mala slova imena ili prezimena, potrebno ih je konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti S0003M
	cout << GenerisiID("jasmin azemovic", 14) << endl;//treba vratiti N0041A
	cout << GenerisiID("Goran skondric", 156) << endl;//treba vratiti N0651S
	cout << GenerisiID("emina Junuz", 1798) << endl;//treba vratiti A8971J

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//Vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("S0003M"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("N0041A"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("N00651S"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("a8971j"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti drugog i treceg
   parametra na lokaciju koja je definisana prvim parametrom. Povratna
   vrijednost metode je pokazivac na pozivaoca metode (u konkretnom slucaju objekat
   kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
   zahtijevani parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
   kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	10 10
	0 0
	1 1
	2 2
	* ....
	*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(0, 10, 10);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji
	metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/
	Kolekcija<int, int, 10>* kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << *kolekcija3 << endl;
	cout << kolekcija1 << crt;
	/*kolekcija3 bi trebala sadrzavati sljedece elemente:
	0 0
	1 1
	2 2
	dok bi kolekcija1 trebala sadrzavati sljedece elemente:
	10 10
	3 3
	4 4
	......
	*/
	kolekcija1 = *kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");
	if (strcmp(denis.GetID(), "S0001M") == 0 && strcmp(jasmin.GetID(), "N0002A") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtom pogotku");
	DrzavaTim BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		//onemoguciti dodavanje istih igraca - provjeravati ID, baciti izuzetak
		BIH.AddIgrac(denis);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		//onemoguciti ponovne susrete drzave tokom istog prvenstva, baciti izuzetak
		euro2024.AddUtakmicu(BIH, ENG);
	}
	catch (exception& obj)
	{
		cout << obj.what() << '\n';
	}
	//omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "S0001M", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "N0002A", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//u zasebnom thread-u, poslati email, u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	/*
	To: S0001M@euro2024.com
	From: info@euro2024.com
	Subject: Informacija
	Postovani,
	U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
   pogodak na ovoj utakmici.
	Trenutni rezultat je:
	BOSNA_I_HERCEGOVINA : ENGLESKA
		  (2)			    (0)
	Puno srece u nastavku susreta.
	Neka bolji tim pobijedi.
	*/
	//ispisuje detaljnije informacije o susretu, kako je navedeno u narednom ispisu
	cout << euro2024;
	/*
	-------------------------------------------
	BOSNA_I_HERCEGOVINA : ENGLESKA
		  (3)			    (1)
	-------------------------------------------
	Denis Music Goran Skondric
	Jasmin Azemovic
	Jasmin Azemovic
	-------------------------------------------
	*/
	//vraca sve igrace koji su na takmicenju postigli broj pogodaka proslijeden
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;
	cin.get();
	system("pause>0");
}
