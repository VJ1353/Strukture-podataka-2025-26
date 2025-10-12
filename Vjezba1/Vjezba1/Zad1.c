#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct student {
	char ime;
	char prezime;
	int brBod;
	float relbrBod = brBod/maxbrBod*100;
} stud;

buffer[0];

int main{
	FILE * dat;
int brojac = 0;
int i = 0;


//Funckija koja cita koliko studenata ima zapisanih u datoteci.
dat = fopen("dat.txt", "r");   
fgets();
fclose(dat);    


//Funkcija koja dohva?a podatke o studentima.
(student*)malloc(brojac * sizeof(student));
dat = fopen("dat.txt", "r");
buffer = fgets();
fclose(dat);


//Dio koda za ispisivanje podataka o studentima.
i = 0;
do {
	printf("Ime: %s\n", stud[i].ime);
	printf("Prezime %s\n", stud[i].prezime);
	printf("Apsolutan broj bodova: %d\n", stud[i].brBod);
	printf("Relativan broj bodova: %.2f\n\n", stud[i].relbrBod);
	i++;
} while (i != brojac);


return 0;
}