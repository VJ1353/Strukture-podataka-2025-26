#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

//Struct declaration:
typedef struct person* position
struct person {
	char name[];
	char surname[];
	int birthyear = 0;
	position next;
};

//List of functions:
void addToStart(person **head, char *name, char *surname, int year);
void printlist(person *head);
void addToEnd(person** head, char* name, char* surname, int year);
person* findSurname(person* head, char* surname);
void deletePerson(person** head, char* surname);



int main() {

	person* head = NULL;

	//B) Print the list:
    printf("Printed list:\");
    printlist(head);


	return 0;
}


void printlist(person* head) {
    person* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }
}