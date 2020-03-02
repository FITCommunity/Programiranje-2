#include<iostream>
using namespace std;

template<class T1, class T2, int max>
class FITKolekcija
{
	int* _trenutno;
	T1 _elementi1[max];
	T2* _elementi2[max];
public:
	//Potrebne konstruktor i destruktor funkcije
	//Kreirati konstruktor kopije za kolekciju
	
	//Preklopiti operator() na način da omogući dodavanje novih elemenata u kolekciju
	//Pri tome spriječiti dodavanja duplih elemenata (odnosi se i na T1 i na T2)
	
	//Preklopiti operator[] na način da vraća element tipa T1 na osnovu njegove lokacije u nizu

	
	//Preklopiti operator-= na način da uklanja elemente iz kolekcije na osnovu rednog broja proslijeđenog kao parametar

	//Preklopiti operator za ispis. Implementaciju raditi izvan tijela klase.
};

class Anketa
{
	char* _pitanje;
	int _trajanje; //izraženo u danima
	//Kolekcija treba da pohrani moguće odgovore na pitanja, sa pripadajućim rednim brojem
	FITKolekcija<char*, int, 8> _odgovori;
public:
	//Kreirati potrebne konstruktor i destruktor funkcije
	
	//Kreirati funkciju DodajOdgovor koja treba da doda novi odgovor za anketu.
	//Spriječiti dodavanje istog odgovora više puta.

	//Kreirati funkciju UkloniOdgovor koja uklanja odgovor na osnovu njegovog rednog broja.
	
	
	//Preklopiti operator++ na način da povećava trajanje ankete za jedan dan
	//Pri tome voditi računa da se implementiraju dvije verzije ovog operatora (objekat++; ++objekat)

	//Preklopiti operator za ispis
};

int main()
{
return 0;
}

