#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Term //Pojam
{
	char* _key;
	char* _value;
public:
	//Konstruktor

	//Destruktor

	//Operator za ispis

	//Operatori poređenja == i != (koristiti samo vrijednost atributa _key)
};

class Dictionary //Riječnik pojmova
{
	string _title;
	int _publicationYear;
	//Ključne riječi bosanskog jezika u atribut _key
	//Odgovarajući prevod na engleskom jeziku u atribut _value
	vector<Term> _terms;
public:
	//Konstruktor

	//Operator () za dodavanje novih pojmova u riječnik (u paru key-value).
	//Spriječiti dodavanje istih vrijednosti u kolekciju (baciti izuzetak).
	//Pojmovi u svakom momentu treba da budu sortirani abecedno (koristiti funkciju sort iz biblioteke algorithm).

	//Operator -= za uklanjanje pojma iz riječnika na osnovu atributa _key.

	//Funkciju koja vraća trenutni broj pojmova u riječniku.

	//operator[] koji vraća vrijednost na osnovu ključne riječi (povratna vrijednost je engleska riječ-value, 
	//na osnovu bosanske-key)

	//Funkciju koja vraća kolekciju ključeva (bosanskih riječi) generisanih slučajnim odabirom.
	//Generisanje slučajnog broja između min i max: int randNum = rand()%(max-min + 1) + min;
	//Funkcija kao parametar prima broj riječi koje je potrebno generisati.

};

//Osmisliti i implementirati klasu Competitor (Takmičar) na način da se upotrebom objekta klase Dictionary
//svakom takmičaru dodijele određena pitanja (riječi bosanskog jezika) - koristiti implementiranu funkciju klase Dictionary.
//Svakom pitanju je potrebno pridružiti odgovor takmičara (kolekcija _odgovori).
//Obavezno implementirati funkciju koja vrši kalkulaciju osvojenih bodova (1 tačan odgovor = 1 bod).
//Po potrebi dopuniti klasu dodatnim atributima.
class Competitor //Takmičar
{
	string _ime;
	string _prezime;
	vector<string> _pitanja;
	vector<string*> _odgovori;
public:


};

int main()
{
	//Kreirati riječnik pojmova.
	//Kreirati niz objekata tipa Competitor i simulirati takmičenje u poznavanju riječi engleskog jezika.
	//Pronaći najboljeg među takmičarima (najveći broj bodova).

	system("pause");
	return 0;
}

