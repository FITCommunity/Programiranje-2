#include<iostream>
using namespace std;



class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2020) {
		_dan = &dan;
		_mjesec = &mjesec;
		_godina = &godina;
	}
	friend ostream& operator<<(ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "."
			<< *obj._godina;
		return COUT;
	}
};
int main() {
	Datum danas, sutra(9, 6, 2020);
	cout << danas << " " << sutra << endl;
	//ispis nije moguce predvidjeti
	return 0;
}


template<class T>
class Vrijednost {
	T _vrijednost;
public:
	Vrijednost(T vrijednost) {
		_vrijednost = vrijednost;
	}
	Vrijednost& operator++() {
		_vrijednost++;
		return *this;
	}
	friend ostream& operator<< (ostream& COUT,
		const Vrijednost& obj) {
		COUT << obj._vrijednost << endl;
		return COUT;
	}
};
int main() {
	Vrijednost<int> a = 10;
	cout << a++ << endl; 
	//kompajler prijavljuje gresku jer je u mainu pozvan postinkrement operator a u klasi je napravljen preinkrement
	cout << ++a << endl;
	//ovo je pravilno pozivanje gdje ce ispisati 11

	return 0;
}



//Nacin na koji se pozivaju lamba funkcije (struktura)
[/* LISTA_PARAMETARA_IZ_OPSEGA */] (/* LISTA_ULAZNIH_PARAMETARA */) {  /* TIJELO_FUNCKIJE (ono sta radi funkcija)*/   }

//Primjer lambda funkcije koja samo ispisuje poruku
[]() { cout << "lambda..." <<endl };


//Prethodnom linijom koda je samo definisana lambda funkcija, ali ne i pozvana Poziv funkcije se vrši koristeći zagrade
[]() { cout << "lambda....."<< endl} ();


const int max = 5;
int niz[]={3,9,1,56,83};
int suma = [] (int niz[],int max)
{
	int sum=0;
	for (int i = 0; i < max; ++i)
	{
		sum+=niz[i];
	}
	return sum;
}(niz[],max); //funkciji proslijedjujemo niz i max


/*ukoliko zelimo da unutar lambda funkcije budu dostupne vrijednosti unutar tog bloka
gdje se funkcija pravi onda samo navodimo u dijelu _LISTA_PARAMETARA_IZ_OPSEGA */

const int max = 5;
int niz[]={3,9,1,56,83};
int suma = [niz,max] ()
{
	int sum=0;
	for (int i = 0; i < max; ++i)
	{
		sum+=niz[i];
	}
	return sum;
}(); //sada se ovdje nista ne proslijedjuje


//pravila vezana za proslijedjivanje parametara unutar lambda funkcija
[&] //Sve varijable unutar bloka gdje se pravi lambda ce po referenci biti dostupne unutar lambda funkcije

[=] //Sve varijable iz bloka gdje se pravi lambda ce po vrijednosti biti dostupne unutar lambda funckije

[=,&naziv_Varijable] //Sve varijable iz opsega ce biti dostupne po vrijednosti unutar lambda funkcije,samo ce varijabla naziv_Varijable biti dostupna po referenci

[naziv_Varijable] // Samo ce varijabla naziv_Varijable biti dostupna unutar lambda funkcije

[this] //this je interni pokazivac koji pokazuje na objekat koji je pozvao funckiju





//Kada određeni sadržaj želimo upisati u fajl tada koristimo objekat klase ofstream, dok za ispis sadržaja nekog fajla koristimo objekat klase ifstream.
//Za manipulisanje fajlovima moramo ukljuciti biblioteku #include<fstream>


//kreiramo ofstream objekat koji se naziva upis
 ofstream upis; 
// ofstream je tip podatka


 //Da bi otvorili fajl koji zelimo trebamo navesti 
 upis.open();

 //i ne smijemo zaboravljati uvijek zatvoriti fajl nakon sto u njega upisemo neki tekst
 upis<<"Neki tekst";

 upis.close();




 //kreiramo objekat za čitanje - ispis sadržaja fajla
  	ifstream ispis("mojFajl.txt");
   if(ispis.fail()) cout<<"ISPIS :: Greska: Nemoguce otvoriti fajl....\n"; 
   else
  { 
    //kreiramo varijablu koju ćemo koristiti u while petlji
    char znak; 

    //sve dok u fajlu postoji sadržaja,funkcija get() uzimaj znak po znak i 
    //pohranjuje ga u varijablu znak

     while(ispis.get(znak)) 
     cout<< znak;//ispisi trenutno učitani znak
  }
   
  ispis.close();//kada je sadržaj fajla ispisan, zatvaramo fajl


ifstream ispis(nazivFajla);

while(!ispis.eof())//sve do kraja fajla
{
//preuzimaj po jedan red teksta i pohrani ga u niz jedanRed
ispis.getline(jedanRed,max);

//ispiši sadržaj niza
cout<<jedanRed<<endl;
}

ispis.close();






void Prikazi (ifstream & ispis)//funkcija prikazi kao argument prima referencu na objekat tipa ifstream 
{ 
	int brojMjesta=0;
	 char znak; 
	 cout<<"Za koliko mjesta zelite pomjeriti pokazivac: ";
	  cin>>brojMjesta; ispis.seekg(brojMjesta); //pomjera kursor za uneseni broj mjesta
	   while(ispis.get(znak))
	   	{ 
	   		cout<<"\nPokazivaca je na lokaciji: "<<ispis.tellg(); //govori na kojoj je lokaciji kursor
	   		 cout<<" a tu je znak :"<<znak;
	   	} 
}



Interakciju sa niti unutar koje se izvršava određeni dio programskog koda moguće je ostvariti i preko objekta this_thread. 
Svaka nit posjeduje jedinstveni identifikacioni broj koji možemo dobiti pozivom metode get_id nad objektom this_thread ili nad objektom koji je kreirao određenu nit.




void PosaljiEmailPoruke(string sadrzaj, int brojEmailPoruka,int & brojacEmailPoruka) //funkcija prima tri parametra,sve ono sto se iz maina prima proslijedjuje se po referenci
{
	cout << ln;
	for (size_t i = 0; i < brojEmailPoruka; i++)
	{
	cout << "Poslana " << i + 1 << "/" << brojEmailPoruka
	<<" email poruka sadrzaja -> " << sadrzaj << endl;
	brojacEmailPoruka++;
	}
	cout << ln;
}



void main()
 {
	int brojacEmailPoruka = 0;
	thread nThread1(PosaljiEmailPoruke,"Odgodjeno predavanje iz predmeta PRIII", 5, ref(brojacEmailPoruka)); //u nit proslijedjujemo parametre koje prima funkcija proslijedjena u nit
	nThread1.join();//obavezno join
	cout << ln << "Ukupno poslano " << brojacEmailPoruka << " email poruka/e!"
	<< ln;
	cin.get();
}




/*simuliramo slanje maila na nacin da trenutnoj niti "pauziramo" izvrsenje u trajanju od 2 sekunde*/
//include<chrono>
this_thread::sleep_for(chrono::seconds(2));