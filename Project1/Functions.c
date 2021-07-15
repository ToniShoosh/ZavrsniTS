#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojZaposlenika = 0;
static int u = 0;
static int o = 0;

static ZAPO* poljeZapos = NULL;
static ZAPO* pronadeniZapos = NULL;
static ZAPO* pronadeniZaposIme = NULL;
static ZAPO* pronadeniZaposPrezime = NULL;

const char* fname = "enc.txt";
const char* fnamet = "dec.txt";

int izbornik(const char* const imeDatoteke) {

	printf("\n__________________________________________________________________________________________________\n");

	printf("Unesite jednu od ponudenih opcija:");
	printf("                    \n\n");
	printf("\t\tOpcija 1: Unos novog zaposlenika.\n");
	printf("\t\tOpcija 2: Citanje zaposlenika iz datoteke.\n");
	printf("\t\tOpcija 3: Ispis svih zaposlenika.\n");
	printf("\t\tOpcija 4: Pretraga zaposlenika po ID-u i njegovo ispisivanje.\n");
	printf("\t\tOpcija 5: Pretraga zaposlenika po imenu i ispis zaposlenika.\n");
	printf("\t\tOpcija 6: Pretraga zaposlenika po prezimu i ispis zaposlenika.\n");
	printf("\t\tOpcija 7: Sortiranje i ispis zaposlenika po mjesecnom prihodu. (Manjem prihodu prema vecem)\n");
	printf("\t\tOpcija 8: Sortiranje i ispis zaposlenika po mjesecnom prihodu. (Vecem prihodu prema manjem)\n");
	printf("\t\tOpcija 9: Sortiranje i ispis zaposlenika po ID-u.\n");
	printf("\t\tOpcija 10: Zavrsetak programa.\n");

	printf("__________________________________________________________________________________________________\n\n");

	int uvjet = 0;
	
	scanf("%d", &uvjet);

	switch (uvjet) {
	case 1:

		dodZapo(imeDatoteke);
		pocetnoUcitavanje(imeDatoteke);
		break;

	case 2:
			
		if (poljeZapos != NULL) {
			free(poljeZapos);
			poljeZapos = NULL;
		}

		poljeZapos = (ZAPO*)ucitavanjeZapos(imeDatoteke);

		if (poljeZapos == NULL) {
			exit(EXIT_FAILURE);
		}
			
		break;

	case 3:

		pocetnoUcitavanje(imeDatoteke);
		ispisivanjeZapos(poljeZapos);
		break;
		
	case 4:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZapos = (ZAPO*)pretrazivanjeZapos(poljeZapos);
		break;

	case 10:

		uvjet = izlaz(poljeZapos, pronadeniZapos);
		break;

	case 5:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZaposIme = (ZAPO*)pretrazivanjeZaposIme(poljeZapos);
		break;

	case 6:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZaposPrezime = (ZAPO*)pretrazivanjeZaposPrezime(poljeZapos);
		break;

	case 7:

		pocetnoUcitavanje(imeDatoteke);
		selectionSort(poljeZapos);
		ispisivanjeZapos(poljeZapos);
		break;

	case 8:

		pocetnoUcitavanje(imeDatoteke);
		selectionSortMax(poljeZapos);
		ispisivanjeZapos(poljeZapos);
		break;

	case 9:

		pocetnoUcitavanje(imeDatoteke);
		selectionSortID(poljeZapos);
		ispisivanjeZapos(poljeZapos);
		break;

	default:
		uvjet = 0;

	}

	return uvjet;
}


void pocetnoUcitavanje(const char* const imeDatoteke) {

	if (poljeZapos != NULL) {
		free(poljeZapos);
		poljeZapos = NULL;
	}
	poljeZapos = (ZAPO*)ucitavanjeZapos(imeDatoteke);
	if (poljeZapos == NULL) {
		exit(EXIT_FAILURE);
	}

	return;
}


void dodZapo(const char* const imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "rb+");
	if (pF == NULL) {
		perror("Dodavanje zaposlenika u datoteku zaposlenici.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojZaposlenika, sizeof(int), 1, pF);
	printf("brojZaposlenika: %d\n", brojZaposlenika);
	ZAPO temp = { 0 };
	temp.id = brojZaposlenika;
	getchar();
	printf("\nUnesite ime zaposlenika: ");
	scanf("%19[^\n]", temp.ime);
	printf("\nUnesite prezime zaposlenika: ");
	getchar();
	scanf("%19[^\n]", temp.prezime);
	printf("\nUnesite mjesecni prihod zaposlenika: ");
	scanf("%d", &temp.mjplaca);
	rewind(pF);
	fseek(pF, sizeof(int) + (sizeof(ZAPO) * brojZaposlenika), SEEK_CUR);
	fwrite(&temp, sizeof(ZAPO), 1, pF);
	rewind(pF);
	brojZaposlenika++;
	fwrite(&brojZaposlenika, sizeof(int), 1, pF);
	fclose(pF);

}


void* ucitavanjeZapos(const char* const imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "rb");
	if (pF == NULL) {
		perror("Ucitavanje zaposlenika iz datoteke zaposlenici.bin");
		return NULL;

	}
	fread(&brojZaposlenika, sizeof(int), 1, pF);
	printf("brojZaposlenika kod ucitavanja : %d\n", brojZaposlenika);
	ZAPO* poljeZapos = (ZAPO*)calloc(brojZaposlenika, sizeof(ZAPO));
	if (poljeZapos == NULL) {
		perror("Zauzimanje memorije za zaposlenike");
		return NULL;

	}
	fread(poljeZapos, sizeof(ZAPO), brojZaposlenika, pF);

	return poljeZapos;
}


void ispisivanjeZapos(const ZAPO* const poljeZapos) {
	if (poljeZapos == NULL) {
		printf("Polje zaposlenika je prazno!\n");
		return;
	}
	int i;
	for (i = 0; i < brojZaposlenika; i++)
	{
		printf("Zaposlenik broj %d\tID: %d\tIme: %s\tPrezime: %s\tMjesecni prihod: %d\t\n",
			i + 1,
			(poljeZapos + i)->id,
			(poljeZapos + i)->ime,
			(poljeZapos + i)->prezime,
			(poljeZapos + i)->mjplaca);
	}
}


void* pretrazivanjeZapos(ZAPO* const poljeZapos) {
	if (poljeZapos == NULL) {
		printf("Polje zaposlenika je prazno!\n");
		return NULL;
	}
	int i;
	int b;
	printf("\nUnesite ID trazenog zaposlenika: ");

	scanf("%d", &b);
	for (i = 0; i < brojZaposlenika; i++)
	{
		if (b == (poljeZapos + i)->id) {
			printf("Trazeni zaposlenik je zaposlenik broj %d\tID: %d\tIme: %s\tPrezime: %s\tMjesecni prihod: %d\n",
				i + 1,
				(poljeZapos + i)->id,
				(poljeZapos + i)->ime,
				(poljeZapos + i)->prezime,
				(poljeZapos + i)->mjplaca);
			return (poljeZapos + i);
		}
	}
	return NULL;
}


int izlaz(ZAPO* poljeZapos, ZAPO* pronadeniZapos) {
	char m[4] = { '\0' };

	printf("\nDa li ste sigurni kako zelite zavrsiti program?\n");

	printf("Unesite da ili ne: ");
	scanf("%2s", m);

	if (strcmp("da", m)==0|| strcmp("Da", m) == 0 || strcmp("DA", m) == 0 || strcmp("dA", m) == 0) {
		free(poljeZapos);
		poljeZapos = NULL;

		free(pronadeniZapos);
		pronadeniZapos = NULL;

		free(pronadeniZaposIme);
		pronadeniZaposIme = NULL;

		free(pronadeniZaposPrezime);
		pronadeniZaposPrezime = NULL;

		exit(EXIT_SUCCESS);
	}
	else {
		return 1;
	}

}


void* pretrazivanjeZaposIme(ZAPO* const poljeZapos) {
	if (poljeZapos == NULL) {
		printf("Polje zaposlenika je prazno!\n");
		return NULL;
	}
	int i;
	
	printf("\nUnesite ime trazenog zaposlenika: ");

	char m[20] = { '\0' };
	char tempo[20] = { '\0' };

	getchar();
	scanf("%19[^\n]", m);

	for (i = 0; i < brojZaposlenika; i++)
	{
		strcpy(tempo, (poljeZapos + i)->ime);

		if (strcmp(tempo, m) == 0) {
			printf("\nTrazeni zaposlenik je zaposlenik broj %d\tID: %d\tIme: %s\tPrezime: %s\tMjesecni prihod: %d\n",
				i + 1,
				(poljeZapos + i)->id,
				(poljeZapos + i)->ime,
				(poljeZapos + i)->prezime,
				(poljeZapos + i)->mjplaca);
			return (poljeZapos + i);
		}
	
	}

	if (strcmp(tempo, m) != 0) {
		printf("\nZaposlenik sa tim imenom ne postoji.\n");
	}
	return NULL;
}



void* pretrazivanjeZaposPrezime(ZAPO* const poljeZapos) {
	if (poljeZapos == NULL) {
		printf("Polje zaposlenika je prazno!\n");
		return NULL;
	}
	int i;

	printf("\nUnesite prezime trazenog zaposlenika: ");

	char m[20] = { '\0' };
	char tempo[20] = { '\0' };

	getchar();
	scanf("%19[^\n]", m);

	for (i = 0; i < brojZaposlenika; i++)
	{
		strcpy(tempo, (poljeZapos + i)->prezime);

		if (strcmp(tempo, m) == 0) {
			printf("Trazeni zaposlenik je zaposlenik broj %d\tID: %d\tIme: %s\tPrezime: %s\tMjesecni prihod: %d\n",
				i + 1,
				(poljeZapos + i)->id,
				(poljeZapos + i)->ime,
				(poljeZapos + i)->prezime,
				(poljeZapos + i)->mjplaca);
			return (poljeZapos + i);
		}
		
	}
	if (strcmp(tempo, m) != 0) {
		printf("\nZaposlenik sa tim prezimenom ne postoji.\n");
	}
	return NULL;
}

void zamjena(ZAPO* const veci, ZAPO* const manji) {
	ZAPO temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSort(ZAPO* const poljeZapos) {
	int min = -1;
	for (int i = 0; i < brojZaposlenika - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojZaposlenika; j++)
		{
			if ((poljeZapos + j)->mjplaca < (poljeZapos + min)->mjplaca) {
				min = j;
			}
		}
		zamjena((poljeZapos + i), (poljeZapos + min));
	}
}

void selectionSortMax(ZAPO* const poljeZapos) {
	int min = -1;
	for (int i = 0; i < brojZaposlenika - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojZaposlenika; j++)
		{
			if ((poljeZapos + j)->mjplaca > (poljeZapos + min)->mjplaca) {
				min = j;
			}
		}
		zamjena((poljeZapos + i), (poljeZapos + min));
	}
}


void selectionSortID(ZAPO* const poljeZapos) {
	int min = -1;
	for (int i = 0; i < brojZaposlenika - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojZaposlenika; j++)
		{
			if ((poljeZapos + j)->id < (poljeZapos + min)->id) {
				min = j;
			}
		}
		zamjena((poljeZapos + i), (poljeZapos + min));
	}
}





//Izbornik za korisnika

int izbornik2(const char* const imeDatoteke) {

	printf("\n__________________________________________________________________________________________________\n");

	printf("Unesite jednu od ponudenih opcija:");
	printf("                    \n\n");
	printf("\t\tOpcija 1: Citanje zaposlenika iz datoteke.\n");
	printf("\t\tOpcija 2: Ispis svih zaposlenika.\n");
	printf("\t\tOpcija 3: Pretraga zaposlenika po ID-u i njegovo ispisivanje.\n");
	printf("\t\tOpcija 4: Pretraga zaposlenika po imenu i ispis zaposlenika.\n");
	printf("\t\tOpcija 5: Pretraga zaposlenika po prezimu i ispis zaposlenika.\n");
	printf("\t\tOpcija 6: Zavrsetak programa.\n");

	printf("__________________________________________________________________________________________________\n\n");

	int cap = 0;

	scanf("%d", &cap);

	switch (cap) {
	case 1:

		if (poljeZapos != NULL) {
			free(poljeZapos);
			poljeZapos = NULL;
		}

		poljeZapos = (ZAPO*)ucitavanjeZapos(imeDatoteke);

		if (poljeZapos == NULL) {
			exit(EXIT_FAILURE);
		}

		break;

	case 2:

		pocetnoUcitavanje(imeDatoteke);
		ispisivanjeZapos(poljeZapos);
		break;

	case 3:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZapos = (ZAPO*)pretrazivanjeZapos(poljeZapos);
		break;

	case 4:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZaposIme = (ZAPO*)pretrazivanjeZaposIme(poljeZapos);
		break;

	case 5:

		pocetnoUcitavanje(imeDatoteke);
		pronadeniZaposPrezime = (ZAPO*)pretrazivanjeZaposPrezime(poljeZapos);
		break;

	case 6:

		cap = izlaz(poljeZapos, pronadeniZapos);
		break;

	default:
		cap = 0;

	}

	return cap;
}

