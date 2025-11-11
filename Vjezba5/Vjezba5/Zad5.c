#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct postfix* Position;
typedef struct postfix {
	double value;
	Position next;
} postfix;


//Function that adds a new element to the stack:
int push(Position* head, double num) {
	Position newEl = (Position)malloc(sizeof(Position));
	if (newEl == NULL) {
		printf("Error: memory allocation failed!\n");
		return 1;
	}
	newEl->value = num;
	newEl->next = *head;
	*head = newEl;
}

//Function for removing elements from the stack:
int pop(Position* first, Position* second) {
	
    Position temp1 = *first;
    *second = temp1->value;
    *first = temp1->next;
    free(temp1);

   
    Position temp2 = *first;
    *second = temp2->value;
    *first = temp2->next;
    free(temp2);
}

//Function to get the result:
double get_postfix(char* buffer)
{
    Position stack = NULL;
    int i = 0;
    double number = 0;

    while (buffer[i] != '\0')
    {
        if (isspace(buffer[i])) {
            i++;
            continue;
        }

        if (isdigit(buffer[i]) ||
            (buffer[i] == '-' && isdigit(buffer[i + 1])))
        {
            number = atof(&buffer[i]);
            push(&stack, number);

           
            while (isdigit(buffer[i]) || buffer[i] == '.' || buffer[i] == '-')
                i++;
        }

        
        else if (buffer[i] == '+' || buffer[i] == '-' ||
            buffer[i] == '*' || buffer[i] == '/')
        {
            double a, b, result;

            pop(&stack, &a, &b);

            switch (buffer[i])
            {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result= a * b; break;
            case '/':
                if (b == 0) {
                    printf("Error: division by zero!\n");
                    return 1;
                }
                result = a / b;
                break;
            default:
                printf("Unknown operator!\n");
                return 1;
            }

            push(&stack, result);
            i++;
        }

    }

    if (stack == NULL || stack->next != NULL) {
        printf("Error: Incorrect expression\n");
        return 1;;
    }

    double result = stack->value;
    free(stack);
    return result;
}

//Function for reading the file:
int readFile(FILE* f, char* buffer[100]) {
	FILE* f = fopen("dat.txt", "r");
	if (f == NULL) {
		printf("Error: file not opened!\n");
		return 1;
	}
	
	fgets(buffer, sizeof(buffer), f);
	fclose(f);
}


int main() {

    char buffer[100];

    //Function call: Read the expression from the file.
    readFile("dat.txt", buffer, sizeof(buffer));

	double result = get_postfix(buffer);

    //Result:
	printf("Rezultat: %.2f\n", result);

	return 0;
}