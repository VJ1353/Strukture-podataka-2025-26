#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CRT_SECURE_NO_WARNINGS
#define MAX 50

typedef struct directory* position;
typedef struct directory {
	position child;
	position sibling;
	char name[MAX];
}Directory;


typedef struct stack {
	Directory* directory;
	struct Stack* next;
	}Stack;

//List of functions:
Directory newDir(char*);
int push(Stack**, Directory*);
int makeDir(Directory*, char*);
int listDir(Directory*);
Directory* changeDir(Directory* , char*);
Directory* pop(Stack**);



int main() {
	Stack* s = 0;
	Directory* root = newDir("Root");
	Directory* curr = root;

	char nameDir[MAX];
	int command;

	do {
		scanf("%d", command);
		switch (command) {

		case 1: //MD - Make directory:
			printf("Create directory: ");
			scanf("%s", &nameDir);
			addDir(s, nameDir);
			break;

		case 2: //CD DIR
			printf("Directory name: ");
			scanf("%s", &nameDir);
			Directory* next = changeDir(curr, nameDir);
			if (next != curr) {
				push(&s, curr);
				curr = next;
			}
			break;

		case 3: // CD

			Directory* prev = pop(s);
			if (prev != NULL)
				curr = prev;
			break;

		case 4: // DIR
			listDir(curr);
			break;

		case 5: // Exit
			printf("Exit\n");
			break;

		default:
			printf("Error: Invalid command!\n");
		}
	} while (command != 5);
	

	return 0;
}

Directory newDir(char dir[MAX]) {
	Directory* newDirectory = malloc(sizeof(Directory));
	strcpy(newDirectory->name, dir);
	newDirectory->child = NULL;
	return newDirectory;
}

int makeDir(Directory* curr, char* name) {

	Directory* newDirectory = newDir(name);

	if (curr->child == NULL) {
		curr->child = newDirectory;
	}
	else {
		Directory* temp = curr->child;
		while (temp->sibling != NULL)
			temp = temp->sibling;
		temp->sibling = newDirectory;
	}

	return 0;
}

int listDir(Directory* curr) {
	Directory* temp = curr->child;
	if (temp == NULL) {
		printf("Empty directory!\n");
		return;
	}
	while (temp != NULL) {
		printf("%s\n", temp->name);
		temp = temp->sibling;
	}
	return 0;

}

	Directory* changeDir(Directory* curr, const char* name) {
		Directory* temp = curr->child;
			while (temp != NULL) {
				if (strcmp(temp->name, name) == 0)
					return temp;
				temp = temp->sibling;
			}
			printf("Error: Directory doesn't exist!\n");
			return curr;
	}

	int push(Stack** level, Directory* dir) {
		Stack* newMem = (Stack*)malloc(sizeof(Stack));
		newMem->directory = dir;
		newMem->next = *level;
		*level = newMem;

		return 0;
	}

	Directory* pop(Stack** level) {
		Stack* temp = *level;
		Directory* dir = temp->directory;
		*level = temp->next;
		free(temp);
		return dir;
	}

