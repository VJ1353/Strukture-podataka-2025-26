#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct city* CityPos;
typedef struct city {
	char cityname[MAX];
	int population;
	CityPos next;
	CityPos left;
	CityPos right;
} City;

typedef struct country* Position;
typedef struct country {
	char name[MAX];
	char filename[MAX];
	Position next;
	Position left;
	Position right;
	CityPos cities;
} Country;

typedef struct hashtable {
	int size;
	Position* hashlist;
} HashTable;


CityPos newCity(char*, int); 
CityPos cityTree(CityPos, CityPos); 
Position newCountry(char*, char*); 
int countryList(Position*, Position);
Position countryTree(Position, Position);
int readCities(char*, CityPos*); 
int searchCity(CityPos, int); 
int printCityTree(CityPos); 
int printCountryList(Position);

//Hash table functions:
int key(HashTable*, char*);
HashTable* createHashTable(int);
void insertCountry(HashTable*, Position);
Position findCountry(HashTable*, char*);

int main() {

	HashTable* ht = createHashTable(11);
	char country[MAX];
	char filename[MAX];

	FILE* f = fopen("drzave.txt", "r");
	if (!f) {
		printf("Error: File not opened!\n");
		return 1;
	}

	while (fscanf(f, "%s %s", country, filename) == 2) {
		Position c1 = newCountry(country, filename);
		readCities(filename, &c1->cities);
		insertCountry(ht, c1);
	}

	printf("Country: ");
	scanf("%s", country);

	Position c2 = findCountry(ht, country);
	if (c2) {
		printf("Cities:\n");
		searchCity(c2->cities, 0);
	}

	fclose(f);

	return 0;
}

int key(HashTable* ht, char* name) {
	int sum = 0;
	for (int i = 0; i < 5 && name[i] != '\0'; i++) {
		sum += (int)name[i];
	}
	int key = sum % ht->size;
	return key;
}

HashTable* createHashTable(int size) {
	HashTable* ht = malloc(sizeof(HashTable));
	if (ht == NULL) {
		printf("Error: Memory alloation failed!\n");
		exit(1);
	}

	ht->size = size;
	ht->hashlist = malloc(sizeof(Position) * size);
	if (ht->hashlist == NULL) {
		printf("Error: Memory allocation failed!\n");
		exit(1);
	}

	for (int i = 0; i < size; i++)
		ht->hashlist[i] = NULL;

	return ht;
}

void insertCountry(HashTable* ht, Position country) {
	int index = key(ht, country->name);

	Position head = ht->hashlist[index];

	if (head == NULL || strcmp(country->name, head->name) < 0) {
		country->next = head;
		ht->hashlist[index] = country;
		return;
	}

	Position current = head;
	while (current->next != NULL && strcmp(country->name, current->next->name) > 0) {
		current = current->next;
	}

	country->next = current->next;
	current->next = country;
}

Position findCountry(HashTable* ht, char* name) {
	int index = key(ht, name);

	Position current = ht->hashlist[index];
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
			return current;

		current = current->next;
	}

	return NULL;
}

//Function that creates a node for a new city:
CityPos newCity(char* name, int population) {  
	CityPos city = malloc(sizeof(CityPos));
	if (city == NULL) {
		printf("Error: Memory allocation failed!\n");
		exit(1);
	}

	strcpy(city->cityname, name);
	city->population = population;
	city->left = NULL;
	city->right = NULL;
	city->next = NULL;
	return city;

}


//Function for creating the tree of cities:

	CityPos cityTree(CityPos root, CityPos city) {     
		if (!root) return city;

		if (city->population < root->population || city->population == root->population && strcmp(city->cityname, root->cityname) < 0)
			root->left = cityTree(root->left, city);

		else
			root->right = cityTree(root->right, city);

		return root;
	}

//Function that creates a node for a new country:
Position newCountry(char* name, char* filename) {
	Country* country = malloc(sizeof(Country));
	if (country == NULL) {
		printf("Error: Memory allocation failed!\n");
		exit(1);
	}

	strcpy(country->name, name);
	strcpy(country->filename, filename);
	country->cities = NULL;
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;

	return country;
}

//Reads cities from the file
int readCities(char* filename, CityPos* root) {   
	FILE* f = fopen(filename, "r");
	if (!f) return;

	char city[MAX];
	int number;

	while (fscanf(f, "%[^, ], %d", city, &number) == 2) {
		*root = cityTree(*root, newCity(city, number));
	}

	fclose(f);

	return 0;
}

//Searches for cities by population:
int searchCity(CityPos root, int minPop) {          
	if (!root) return;

	searchCity(root->left, minPop);
	if (root->population > minPop)
		printf(" %s %d\n", root->cityname, root->population);
	searchCity(root->right, minPop);

	return 0;
}


//Prints the cities as a tree:
int printCityTree(CityPos root) {          
	if (!root) return;
	printCityTree(root->left);
	printf(" %s %d\n", root->cityname, root->population);
	printCityTree(root->right);
	return 0;
}

//Prints countries as a linked list:
int printCountryList(Position head) {
	while (head) {
		printf("%s:\n", head->name);
		printCityTree(head->cities);
		head = head->next;
	}
	return 0;
}

//Creates the linked list of countries:
int countrylist(Position head, Position country) {
	if (!head || strcmp(country->name, (head)->name) < 0) {
		country->next = head;
		head = country;
		return;
	}

	Position current = head;
	while (current->next && strcmp(country->name, current->next->name) > 0)
		current = current->next;

	country->next = current->next;
	current->next = country;

	return 0;
}

//Sorts countries in a tree:
Position countryTree(Position root, Position country) {
	if (!root) return country;

	if (strcmp(country->name, root->name) < 0)
		root->left = countryTree(root->left, country);
	else
		root->right = countryTree(root->right, country);

	return root;
}


