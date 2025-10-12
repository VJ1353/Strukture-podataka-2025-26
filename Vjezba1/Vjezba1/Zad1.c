#define _CRT_SECURE_NO_WARNINGS
#define FILE_NOT_OPENED -1
#define MAX_BR_BOD 50
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime;
	char prezime;
	int brBod = 0;
	float relbrBod = 0;
} student;

int main(){
FILE * dat;
int brojac = 0;
int i = 0;
int n = 0;


//Funckija koja cita koliko studenata ima zapisanih u datoteci:
dat = fopen("dat.txt", "r");   
if (dat = NULL) {
	printf("Couldn't open the file.\n");
	return -1;
}
while ((n = fgetc(dat)) != EOF) {
	if (n == '\n')
		brojac++;
}
fclose(dat);    


//Funkcija koja dohvaca podatke o studentima:
student* niz = (student*)malloc(brojac * sizeof(student)); //dinamicka alokacija memorije
dat = fopen("dat.txt", "r");
if (dat = NULL) {
	printf("Couldn't open the file.\n");
	return -1;
}
for (i = 0; i < brojac; i++) {
	fscanf(dat, "%s %s %d", niz[i].ime, niz[i].prezime, niz[i].brBod);
	niz[i].relbrBod = (float)niz[i].brBod / MAX_BR_BOD * 100;
}
fclose(dat);


//Dio koda za ispisivanje podataka o studentima:
i = 0;
do {
	printf("Ime: %s\n", niz[i].ime);
	printf("Prezime %s\n", niz[i].prezime);
	printf("Apsolutan broj bodova: %d\n", niz[i].brBod);
	printf("Relativan broj bodova: %.2f\n\n", niz[i].relbrBod);
	i++;
} while (i < brojac);


return 0;
}