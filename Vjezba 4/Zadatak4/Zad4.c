#include <stdio.h>
#include <stdlib.h>

//Struct member definition:
typedef struct member {
	int koef;
	int exp;
	struct member *next;
} Member;


//Memory allocation for a new member:
Member* newMember(int koef, int exp) {
	Member* newMem = (Member*)malloc(sizeof(Member));
	newMem->koef = koef;
	newMem->exp = exp;
	newMem->next = NULL;
	return newMem;
}


//Add a new member to the list:
void addMember(Member** polynome, int koef, int exp) {
	Member* newMem = newMember(koef, exp);
	if (*polynome = NULL) 
		*polynome = newMem;

	else {
		Member* temp = *polynome;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = newMem;
	}
	
}

//Function for printing the polynomes:
void printPolynome(Member* p) {
	while (p != NULL) {
		printf("%dx^%d", p->koef, p->exp);
		if (p->next != NULL) printf(" + ");
		p = p->next;
	}
	printf("\n");
}

//Adding the polynomes:
Member* addPol(Member* p1, Member* p2) {
	Member* result = NULL;

	while (p1 != NULL) {
		addMember(&result, p1->koef, p1->exp);
		p1 = p1->next;
	}


	//Adding the second polynome to the first:
	while (p2 != NULL) {
		Member* temp = result;
		int found = 0;
		while (temp != NULL) {
			if (temp->exp == p2->exp) {
				temp->koef += p2->koef;
				found = 1;
				break;
			}
			temp = temp->next;
		}
		if (!found)
			addMember(&result, p2->koef, p2->exp);
		p2 = p2->next;
	}


	return result;
}

//Read polynomes from file:
Member* readPolynome(FILE* f) {
	Member* p = NULL;
	int koef, exp;
	while (fscanf(f, "%d %d", &koef, &exp) == 2)
		addMember(&p, koef, exp);
	return p;
}

//Multiplying the polynomes:
Member* multiply(Member* p1, Member* p2) {
	Member* result = NULL;

	for (Member* i = p1; i != NULL; i = i->next) {
		for (Member* j = p2; j != NULL; j = j->next) {
			int newKoef = i->koef * j->koef;
			int newExp = i->exp + j->exp;

			Member* temp = result;
			int found = 0;
			while (temp != NULL) {
				if (temp->exp == newExp) {
					temp->koef += newKoef;
					found = 1;
					break;
				}
				temp = temp->next;
			}
			if (!found)
				addMember(&result, newKoef, newExp);
		}
	}
	return result;
}



int main() {
	// Opening the file:
	FILE* f = fopen("polynome.txt", "r");
	if (f == NULL) {
		printf("Error: File not opened!\n");
		return 1;
	}

	Member* p1 = NULL;
	Member* p2 = NULL;
	int koef, exp;


	//Read polynomes:
	while (fscanf(f, "%d", &koef) == 1) {
		if (koef == '\n') break;
		fscanf(f, "%d", &exp);
		addMember(&p1, koef, exp);
	}

	while (fscanf(f, "%d %d", &koef, &exp) == 2)
		addMember(&p2, koef, exp);


	//Print polynomes:
	printf("P1: ");
	printPolynome(p1);
	printf("P2: ");
	printPolynome(p2);


	//Print results:
	Member* addition = addPol(p1, p2);
	Member* product = multiply(p1, p2);

	printf("\nAddition: ");
	printPolynome(addition);
	printf("Product: ");
	printPolynome(product);



	fclose(f);

	return 0;
}

