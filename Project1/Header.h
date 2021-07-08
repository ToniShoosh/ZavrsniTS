#ifndef HEADER_H
#define HEADER_H

typedef struct zaposlenik {
	int id;
	char ime[20];
	char prezime[20];
	int mjplaca;
}ZAPO;

int izbornik(const char* const imeDatoteke);
void pocetnoUcitavanje(const char* const imeDatoteke);
void dodZapo(const char* const imeDatoteke);
void* ucitavanjeZapos(const char* const imeDatoteke);
void ispisivanjeZapos(const ZAPO* const poljeZapos);
void* pretrazivanjeZapos(ZAPO* const poljeZapos);
void* pretrazivanjeZaposIme(ZAPO* const poljeZapos);
void* pretrazivanjeZaposPrezime(ZAPO* const poljeZapos);
int izlaz(ZAPO* poljeZapos, ZAPO* pronadeniZapos);
void zamjena(int* const veci, int* const manji);
void selectionSort(ZAPO* const poljeZapos);
void selectionSortMax(ZAPO* const poljeZapos);
void selectionSortID(ZAPO* const poljeZapos);

#endif
