#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

//Struct declaration:
typedef struct person* position
struct person {
    char name[50];
    char surname[50];
    int birthyear = 0;
    position next;
};

//List of functions: (Zad2)
void printlist(person* head);
person* searchSurname(person* head, char* surname);
person* newPerson(char* ime, char* prezime, int godina);
void addToStart(person** head, char* name, char* surname, int year);
void addToEnd(person** head, char* name, char* surname, int year);

//List of functions: (Zad3)
person* addAfter(person* head, char* surname);
person* addBefore(person* head, char* surname);
person* sortBySurname(person* head);
void writeInFile(Osoba* head, char* filename);
person* readFromFile(char* filename);



int main() {

    //ZAD2:
  
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

    person * found = searchSurname(head, "Jurisic");
    if (found)
        printf("Person: %s %s (%d)\n", found->name, found->surname, found->birthyear);
    else
        printf("Surname not found.\n");

    //E) Delete element from the list:
    printf("\nDelete person: 'Jurisic'\n");
    deletePerson(&head, "Jurisic");
    printlist(head);

    //ZAD3:

    //A) Add an element after another element:
    printf("After which element: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = '\0';
    head = addAfter(head, surname);
    return 0;

    // B) Add an element before another element:
    printf("Before which element: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = '\0';
    head = addBefore(head, surname);

    // C) Sort the list by surname:
    head = sortBySurname(head);
    printf("List sorted by surname.\n");

    // D) Write the list in a file:
    writeInFile(head, filename);

    // E) Read the list from a file:
    head = readFromFile(filename);
}

//ZAD2

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

//ZAD3

//D) Write list in file:
void writeInFile(person* head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("ERROR! File not opened!\n");
        return;
    }
    while (head) {
        fprintf(fp, "%s %s %d\n", head->name, head->surname, head->birthyear);
        head = head->next;
    }
    fclose(fp);
}

//E) Read the list from the file:
person* readFromFile(char* filename) {
    FILE* fp = fopen(imeDatoteke, "r");
    if (!fp) {
        printf("ERROR! File not opened!\n");
        return NULL;
    }

    person* head = NULL, * temp = NULL;
    person person;

    while (fscanf(fp, "%s %s %d", person.name, person.surname, &person.birthyear) == 3) {
        person* newPer = (person*)malloc(sizeof(person));
        if (!newPer) {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return head;
        }
        strcpy(newPer->name, person.name);
        strcpy(newPer->surname, person.surname);
        newPer->birthyear = person.birthyear;
        newPer->next = NULL;

        if (!head) head = newPer;
        else temp->next = newPer;
        temp = newPer;
    }
    fclose(fp);
    return head;
}

//C) Sort by surname function:
person* sortBySurname(person* head) {
    if (!head || !head->next) return head;

    int swtch;
    person* end = NULL;
    do {
        swtch = 0;
        person* temp = head;
        while (temp->next != end) {
            if (strcmp(temp->surname, temp->next->surname) > 0) {
                
                char name[50], surname[50];
                int year;

                strcpy(name, temp->name);
                strcpy(surname, temp->surname);
                year = temp->birthyear;

                strcpy(temp->name, temp->next->name);
                strcpy(temp->surname, temp->next->surname);
                temp->birthyear = temp->next->birthyear;

                strcpy(temp->next->name, name);
                strcpy(temp->next->surname, surname);
                temp->next->birthyear = year;

                swtch = 1;
            }
            temp = temp->next;
        }
        end = temp;
    } while (swtch);
    return head;
}


//A) Add new element after another:
person* addAfter(person* head, char* surname) {
    person* found = searchSurname(head, surname);
    if (!found) {
        printf("Person not found.\n");
        return head;
    }
    Osoba* newPer = newPerson();
    if (!newPer) return head;
    newPer->next = found->next;
    found->next = newPer;
    return head;
}


//B) Add new element before another:
person* addBefore(person* head, char* surname) {
    person* newPer = newPerson();
    if (!newPer) return head;

    if (!head || strcmp(head->surname, surname) == 0) {
        newPer->next = head;
        return newPer;
    }

    person* temp = head;
    while (temp->next && strcmp(temp->next->surname, surname) != 0)
        temp = temp->next;

    if (!temp->next) {
        printf("Person not found.\n");
        free(newPer);
        return head;
    }

    newPer->next = temp->next;
    temp->next = newPer;
    return head;
}



