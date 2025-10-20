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
person* 


int main() {

	person* head = NULL;

	//B) Print the list:
    printf("Printed list:\");
    printlist(head);

    //D) Search by surname:
	printf("Search by surname 'Jurisic':\n");

    person* found = searchSurname(head, "Jurisic");
    if (found)
        printf("Person: %s %s (%d)\n", found->name, found->surname, found->birthyear);
    else
        printf("Surname not found.\n");



	return 0;
}


void printlist(person* head) {
    person* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->birthyear);
        temp = temp->next;
    }
}

person* searchSurname(person* head, char* surname) {
person* temp = head;
while (temp != NULL) {
    if (strcmp(temp->surname, surname) == 0)
        return temp;
    temp = temp->next;
}
return NULL;
}