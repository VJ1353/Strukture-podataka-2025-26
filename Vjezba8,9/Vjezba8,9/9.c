#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree* position;
typedef struct tree {
	int value;
	position left;
	position right;
}Tree;

//List of functions:
Tree* newElement(int);
Tree* insert(Tree*, int);
int replace(Tree*);
Tree* search(Tree*, int);
Tree* delete(Tree*, int);
int inorder(Tree*, FILE *);
int postorder(Tree*, FILE *);
int preorder(Tree*, FILE *);
int levelorder(Tree*, FILE*);

int main() {
	Tree* root = NULL;
	int choose, value;
	int array1[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int array2[10];
	
	
	FILE* dat = fopen("datoteka.txt", "w");
	if (!dat) {
		printf("Error: File not opened!\n");
		return 1;
	}

	printf("1 - Insert element\n");
	printf("2 - Search\n");
	printf("3 - Delete\n");
	printf("4 - print Inorder\n");
	printf("5 - print Preorder\n");
	printf("6 - print Postorder\n");
	printf("7 - print Level order\n");
	printf("8 - Replace\n");
	printf("9 - Insert random array\n");
	scanf("%d", &choose);
	
	switch (choose) {

	case 1:
		for (int i = 0; i < 10; i++) {
			root = insert(root, array1[i]);
		}
		break;

	case 2:
		printf("Search value: ");
		scanf("%d", &value);
		if (search(root, value))
			printf("Element exists.\n");
		else
			printf("Element doesn't exist.\n");
		break;

	case 3:
		printf("Delete value: ");
		scanf("%d", &value);
		root = delete(root, value);
		break;

	case 4:
		inorder(root, dat);
		fprintf(dat, "\n");
		break;

	case 5:
		preorder(root, dat);
		fprintf(dat, "\n");
		break;

	case 6:
		postorder(root, dat);
		fprintf(dat, "\n");
		break;

	case 7:
		replace(root);
		break;

	case 8:
		for (int i = 0; i < 10; i++) {
			array2[i] = rand() % 81 + 10;
			root = insert(root, array2[i]);
		}

	default:
		printf("Invalid input!");
	}
	fclose(dat);
	return 0;
}

Tree* newElement(int value) {
	Tree* newEl = (Tree*)malloc(sizeof(Tree));
	newEl->value = value;
	newEl->left = NULL;
	newEl->right = NULL;
	return newEl;

}

//9. a)
Tree* insert(Tree* root, int value) {
	if (root == NULL);
		root = newElement(value);

		if (value < root->value) {
			root->right = insert(root->right, value);
		}
		if (value > root->value) {
			root->left = insert(root->left, value);
		}
		return root;
}

//9. b)
int replace(Tree* root) {
	if (root == NULL)
		return 0;

	int result;

	int lSum = replace(root->left);
	int rSum = replace(root->right);

	int prevValue = root->value;
	root->value = lSum + rSum;

	result = root->value + prevValue;

	return result;
}


Tree* search(Tree* root, int value) {
	if (root == NULL || root->value == value)
		return root;

	if (value < root->value)
		return search(root->right, value);
	else
		return search(root->right, value);
}

Tree* delete(Tree* root, int value) {
	if (root == NULL)
		return root;

	if (value < root->value)
		root->right = delete(root->right, value);
	else if (value > root->value)
		root->left = delete(root->left, value);
	else {
		if (root->left == NULL) {
			Tree* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Tree* temp = root->left;
			free(root);
			return temp;
		}
	}
	return root;
}

int inorder(Tree* root, FILE * dat) {
	if (root != NULL) {
		inorder(root->left, dat);
		fprintf(dat, "%d ", root->value);
		inorder(root->right, dat);
	}
	return 0;
}

int preorder(Tree* root, FILE * dat) {
	if (root != NULL) {
		fprintf(dat, "%d ", root->value);
		preorder(root->left, dat);
		preorder(root->right, dat);
	}
	return 0;
}

int postorder(Tree* root, FILE * dat) {
	if (root != NULL) {
		postorder(root->left, dat);
		postorder(root->right, dat);
		fprintf(dat, "%d ", root->value);
	}
	return 0;
}
