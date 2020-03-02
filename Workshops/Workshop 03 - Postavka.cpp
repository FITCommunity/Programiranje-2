#include<iostream>
using namespace std;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Uposlenik {

	const int _sifra; //Automatski uvecavati za 1 za svakog novog uposlenika.
	char _ime[30];
	char _prezime[30];
	char* _radnoMjesto;
public:


	//Implementirati potrebne konstruktor i destruktor funkcije
	Uposlenik(const char* ime, const char* prezime, const char* radnoMjesto)
	{
		strncpy_s(_ime, ime, _TRUNCATE);
		strncpy_s(_prezime, prezime, _TRUNCATE);

		_radnoMjesto = AlocirajNizKaraktera(radnoMjesto);
	}

	~Uposlenik()
	{
		delete[] _radnoMjesto;
		_radnoMjesto = NULL;
	}

	//Ostale funkcije dodati po potrebi

	void Info()
	{
		cout << "Sifra: " << _sifra << endl;
		cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
		cout << "Radno mjesto: " << _radnoMjesto << endl;

	}

};


class Aktivnost {
	char* _naziv;
	bool _zavrsena;
	int* _trajanje; //Izrazeno u danima
	Uposlenik* _uposlenici[5];
public:
	//Implementirati potrebne konstruktor i destruktor funkcije

	//Funkciju koja omogucava angazovanje uposlenika na projektnoj aktivnosti. Funkcija treba da vrati vrijednost tipa
	//bool za uspjesno, odnosno neuspjesno dodavanje uposlenika. Nije moguce dodati istog uposlenika vise puta. 
    //Nije moguce
	//angazovati uposlenike na vec zavrsenoj aktivnosti.

	//Funkciju koja uklanja uposlenika na aktivnosti sa sifrom proslijedjenom kao parametar.

	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti.

};

class Projekat {
	char* _naziv;
	char* _oblast;
	int _trajanje; //Izrazeno u mjesecima
	Aktivnost* _aktivnosti;
	int _brojAktivnosti;
public:

	//Implementirati potrebne konstruktor i destruktor funkcije.

	//Funkciju za dodavanje projektnih aktivnosti. Sprijeciti dodavanje vise aktivnosti sa istim nazivom.
	//Za potrebe poredjenja aktivnosti kreirati funkciju unutar klase Aktivnosti.


	//Funkciju koja oznacava aktivnost kao zavrsenu. Funkcija kao parametar prima naziv aktivnosti.


	//Funkciju koja treba da aktivnosti sa proslijedjenim nazivom dodijeli novog uposlenika.


	//Funkciju koja treba da vrati sve uposlenike angazovane na odredjenoj aktivnosti. 
    //Ulazni parametar je naziv aktivnosti.


	//Funkciju koja uklanja odredjenog uposlenika na aktivnosti. 
    //Ulazni parametri funkcije su naziv aktivnosti i sifra uposlenika.


	//Funkciju koja uklanja sve uposlenike angazovane na aktivnosti sa nazivom proslijedjenim kao parametar.


	//Funkciju koja pronalazi uposlenika sa najvecim brojem angazmana na aktivnostima.


	//Funkciju koja pronalazi 3 uposlenika koja su angazovana na najvecem broju nezavrsenih aktivnosti.


	//Funkciju koja ispisuje sve zavrsene aktivnosti na projektu.

};


/*Kreirati globalnu funkciju koja pronalazi najuspjesnijeg uposlenika na projektima (vise projekata) 
proslijedjenim kao parametar.
Uposlenik se smatra najuspjesnijim ako je angazovan na najvecem broju zavrsenih aktivnosti. Ako vise uposlenika
ima isti broj zavrsenih aktivnosti, uspjesnijim se smatra onaj cije su aktivnosti trajale duze.
*/


int main()
{
	//Testirati sve dostupne funkcionalnosti


    system("pause");
	return 0;
}
