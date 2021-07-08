#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

const char* imeDatoteke = "zaposlenici.bin";



int main(void) {

	FILE* fp = NULL;
	fp = fopen(imeDatoteke, "ab");
	if (fp == NULL) {
		printf("Datoteka %s ne postoji na disku.\n", imeDatoteke);
	}
	else {
		printf("Datoteka %s postoji na disku.\n", imeDatoteke);
		fclose(fp);
	}

	pocetnoUcitavanje(imeDatoteke);

	int uvjet = 1;

	while (uvjet) {
		uvjet = izbornik(imeDatoteke);
	}

	return 0;
}