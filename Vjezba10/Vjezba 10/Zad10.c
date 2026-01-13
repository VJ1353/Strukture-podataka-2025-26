#define _CRT_SECURE_NO_WARNINGS
#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Struct definitions:
typedef struct city {
	char cityname[MAX];
	int population;
	struct city* left;
	struct city* right;
	struct city* next;
} City;

typedef struct country {
	char name[MAX];
	char filename[MAX];
	struct country* left;
	struct country* right;
	struct country* next;
	City* list;
} Country;


//List of functions:
City* newCity(char*, int);
City* cityTree(City*, City*);
Country* newCountry(char*, char*);
int countryList(Country**, Country*); 
Country* countryTree(Country*, Country*); 
int readCities(char*, City**);
int searchCity(City*, int);
int printCityTree(City*);
int printCountryList(Country*);


int main() {

	Country* list = NULL;
	Country* tree = NULL;
	char country[MAX];
	char file[MAX];
	int pop;

	FILE* f = fopen("drzave.txt", "r");
	if (!f) {
		printf("Error: File not opened!\n");
		return 1;
	}

	while (fscanf(f, "%s %s", country, file) == 2) {
		Country* c1 = newCountry(country, file);
		readCities(file, &c1->list);
		countryList(&list, c1);


		Country* c2 = newCountry(country, file);
		readCities(file, &c2->list);
		tree = countryTree(tree, c2);

	}
//Search cities:
printf("\nCountry: ");
	scanf("%s", country);

	printf("\nPopulation: ");
	scanf("%d", &pop);

	Country* c3 = list;
	while (c3 && strcmp(c3->name, country) != 0) {
		c3 = c3->next;
	}

	if (c3) {
		printf("\nCities of %s with more than %d inhabitants:\n", c3->name, pop);
		searchCity(c3->list, pop);
	}

	else
		printf("\nCountry not found!\n");

	fclose(f);

	printCountryList(list);

	return 0;
}


//Function that creates a node for a new city:
City* newCity(char* name, int population) {
	City* city = malloc(sizeof(City));
	strcpy(city->cityname, name);
	city->population = population;
	city->left = NULL;
	city->right = NULL;
	city->next = NULL;
	return city;
}

//Function for creating the tree of cities:
City* cityTree(City* root, City* city) {
	if (!root) return city;

	if (city->population < root->population || city->population == root->population && strcmp(city->cityname, root->cityname) < 0)
	root->left = cityTree(root->left, city);

	else
		root->right = cityTree(root->right, city);

	return root;
}

//Function that creates a node for a new country:
Country* newCountry(char* name, char* filename) {
	Country* country = malloc(sizeof(Country));
	strcpy(country->name, name);
	strcpy(country->filename, filename);
	country->list = NULL;
	country->next = NULL;
	country->left = NULL;
	country->right = NULL;

	return country;
}

//Reads cities from the file
int readCities(char* filename, City** root) {
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
int searchCity(City* root, int minPop) {
	if (!root) return;

	searchCity(root->left, minPop);
	if (root->population > minPop)
		printf(" %s %d\n", root->cityname, root->population);
	searchCity(root->right, minPop);

	return 0;
}


//Prints the cities as a tree:
int printCityTree(City* root) {
	if (!root) return;
	printCityTree(root->left);
	printf(" %s %d\n", root->cityname, root->population);
	printCityTree(root->right);
	return 0;
}

//Prints countries as a linked list:
int printCountryList(Country* head) {
	while (head) {
		printf("%s:\n", head->name);
		printCityTree(head->list);
		head = head->next;
	}
	return 0;
}

//Creates the linked list of countries:
int countrylist(Country** head, Country* country) {
	if (!*head || strcmp(country->name, (*head)->name) < 0) {
		country->next = *head;
		*head = country;
		return;
	}

	Country* current = *head;
	while (current->next && strcmp(country->name, current->next->name) > 0)
		current = current->next;

	country->next = current->next;
	current->next = country;

	return 0;
}

//Sorts countries in a tree:
Country* countryTree(Country* root, Country* country) {
	if (!root) return country;

	if (strcmp(country->name, root->name) < 0)
		root->left = countryTree(root->left, country);
	else
		root->right = countryTree(root->right, country);

	return root;
}