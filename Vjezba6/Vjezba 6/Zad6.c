#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaring the struct for articles:
typedef struct item* Position;
typedef struct item{
	char name[30];
	int number = 0; 
	float price = 0;
}Item;

typedef struct receipt* pointer;
typedef struct receipt {
	Item *items;
	int year, month, day;
}Receipt;


//List of functions:
int getData(Receipt*, char*, int, int, int, int, int, int);
Receipt* getReceipt(const char*);
int compare_dates(int, int, int, int, int, int);
Item* item_sorted(Item* , Item*);
Receipt* receipt_sorted(Receipt* head, Receipt* newReceipt);


//Main function:
int main() {

	//Reading receipts from the file "racuni.txt":
	FILE* f = fopen("racuni.txt", "r");
	if (!f) {
		printf("Error: File not opened!\n");
		return -1;
	}
	
	Receipt* receipts = NULL;
	char filename[30];

	while (fscanf(f, "%s", filename) == 1) {
		Receipt* r = getReceipt(filename);
		if (r)
			receipts = receipt_sorted(receipts, r);
	}
	fclose(f);

	char item[50];
	int year1, month1, day1;
	int year2, month2, day2;

	//User input:
	printf("Item: ");
	scanf("%s", item);

	printf("\nAdd the start date: ");
	scanf("%d.%d.%d.", year1, month1, day1);

	printf("\nAdd the end date: ");
	fscanf("%d.%d.%d", year2, month2, day2);
	
	getData(receipts, item, year1, month1, day1, year2, month2, day2);

		return 0;
}

//Function that reads a receipt from the file:
Receipt* getReceipt(const char*) {
	FILE* racun = fopen(filename, "r");
	if (!racun) {
		printf("File not opened!\n");
		return NULL;
	}
	Receipt* r = malloc(sizeof(Receipt));
	r->items = NULL;
	r->next = NULL;

	fscanf(racun, "%d.%d.%d", r->year, r->month, r->day);

	while (!feof(racun)) {
		Item* i = malloc(sizeof(Item));
		i->next = NULL;

		if (fscanf(racun "%[^,], %d, %f\n", i->name, i->number, i->price) == 3) {
			r->items = item_sorted(r->items, i);
		}
		else {
			free(i);
			break;
		}
	}
	fclose(f);
	return r;
}

//Function for comparing dates:
int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2) {
	if (year1 != year2) return year1 - year2;
	if (month1 != month2) return month1 - month2;
	return day1 - day2;
}

//Calculating the total amount of items and price paid:
int getData(Receipt* receipts, const char* foundItem,
	int year1, int month1, int day1, int year2, int month2, int day2)
{
	int total_number = 0;
	float total_spent = 0;

	Receipt* r = receipts;

	while (r) {
		
		if (compare_dates(r->year, r->month, r->day, year1, month1, day1) >= 0 &&
			compare_dates(r->year, r->month, r->day, year2, month2, day2) <= 0) {

			Item* i = r->items;
			while (i) {
				if (strcmp(i->name, found) == 0) {
					total_number += i->number;
					total_spent += i->number * i->price;
				}
				i = i->next;
			}
		}
		r = r->next;
	}

	//Printing the result:
	printf("Item: %s\n", found);
	printf("Total number of items: %d items\n", total_number);
	printf("Total spent: %.2f EUR\n", total_spent);
}

//Sorting items:
Item* item_sorted(Item* head, Item* newItem) {
	if (!head || strcmp(newItem->name, head->name) < 0) {
		newItem->next = head;
		return newItem;
	}
	Item* curr = head;
	while (curr->next && strcmp(curr->next->name, newItem->name) < 0)
		curr = curr->next;
	newItem->next = curr->next;
	curr->next = newItem;
	return head;
}

//Sorting thr receipts by date:
Receipt* receipt_sorted(Receipt* head, Receipt* newReceipt) {
	if (!head ||
		compare_dates(newReceipt->year, newReceipt->month, newReceipt->day,
			head->year, head->month, head->day) < 0) {
		newReceipt->next = head;
		return newReceipt;
	}
	Receipt* curr = head;
	while (curr->next &&
		compare_dates(newReceipt->year, newReceipt->month, newReceipt->day,
			curr->next->year, curr->next->month, curr->next->day) > 0)
		curr = curr->next;

	newReceipt->next = curr->next;
	curr->next = newReceipt;
	return head;
}
