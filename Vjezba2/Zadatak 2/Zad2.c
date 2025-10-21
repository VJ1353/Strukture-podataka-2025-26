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
void printlist(person *head);
person* searchSurname(person* head, char* surname);
person* newPerson(char* ime, char* prezime, int godina);
void addToStart(person** head, char* name, char* surname, int year);
void addToEnd(person** head, char* name, char* surname, int year);



int main() {

	person* head = NULL;
    //A) Add to the start of the list:
    addToStart(&head, "Viktoria", "Jurisic", 2005);

	//B) Print the list:
    printf("Printed list:\");
    printlist(head);

    //C)Add to the end of the list:
    addToEnd(&head, "Ana", "Filipovic", 2005);

    //D) Search by surname:
	printf("Search by surname 'Jurisic':\n");

    person* found = searchSurname(head, "Jurisic");
    if (found)
        printf("Person: %s %s (%d)\n", found->name, found->surname, found->birthyear);
    else
        printf("Surname not found.\n");

    //E) Delete element from the list:
    printf("\nDelete person: 'Jurisic'\n");
    deletePerson(&head, "Jurisic");
    printlist(head);

	return 0;
}

//Print the list function:
void printlist(person* head) {
    person* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }
}

//Search by surname function:
person* searchSurname(person* head, char* surname) {
person* temp = head;
while (temp != NULL) {
    if (strcmp(temp->surname, surname) == 0)
        return temp;
    temp = temp->next;
}
return NULL;
}

//Create a new element:
person* newPerson(char* ime, char* prezime, int godina) {
    person* newPer = (person*)malloc(sizeof(person));
    if (!newPer) {
        printf("Error: Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newPer->name, name);
    strcpy(newPer->surname, surname);
    newPer->birthyear = year;
    newPer->next = NULL;
    return newPer;
}

//Add new element at the start:
void addToStart(person** head, char* name, char* surname, int year) {
    person* newPer = newPerson(name, surname, year);
    if (!newPer) return;

    newPer->next = *head;
    *head = newPer;
}

//Add new element at the end:
void addToEnd(person** head, char* name, char* surname, int year) {
    person* newPer = newPerson(name, surname, year);
    if (!newPer) return;

    if (*head == NULL) {
        *head = newPer;
        return;
    }

    person* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newPer;
}

//Delete element function:
void deletePerson(person** head, char* surname) {
    person* temp = *head, * prev = NULL;

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Person not found.\n", prezime);
        return;
    }

    if (prev == NULL) 
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
}