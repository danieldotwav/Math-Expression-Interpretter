#define _CRT_SECURE_NO_WARNINGS /* Disable security warnings in Microsoft Visual Studio */
#include <stdio.h>

#define INVALID_OPERATOR '\0'

/* Helper Functions */
int isDigit(int ch);
int isSpace(int ch);
char getOperatorType(int ch);
char getUserSelection();

/* Wrapper function */
void performSpecifiedOperation(int left_operand, int right_operand, char operator_symbol);

/* Individual Operation Functions */
int add(int left_operand, int right_operand);
int subtract(int left_operand, int right_operand);
int multiply(int left_operand, int right_operand);
float divide(int left_operand, int right_operand);
int modulo(int left_operand, int right_operand);

int main(void) {
	int iochar;
	int left_operand = 0;
	int right_operand = 0;
	char operator_symbol = INVALID_OPERATOR;

	/* Program flags */
	int left_operand_found = 0; /* Flag to check if left operand is found */
	int right_operand_found = 0; /* Flag to check if right operand is found */
	int negative_flag = 0; /* Flag to identify negative operands */
	int division_flag = 0; /* Flag to perform additional operand checks */
	int extraneous_data_flag = 0; /* Flag that checks for additional data following right_operand */

	printf("---- Expression Interpretter ----\n");
	char user_selection = 'Y';

	printf("\nEnter an expression in the form of: A <operator> B\n");

	while (((iochar = getchar()) != EOF) && (user_selection == 'Y' || user_selection == 'y')) {
		/* Reset operands, operator, and flags for each new expression */
		left_operand = right_operand = left_operand_found = right_operand_found = negative_flag = division_flag = extraneous_data_flag = 0;
		operator_symbol = INVALID_OPERATOR;

		/* Process left operand and skip initial whitespace */
		while (isSpace(iochar)) { iochar = getchar(); }

		/* Check for negative sign for left operand */
		if (iochar == '-') {
			negative_flag = 1;
			iochar = getchar();
		}

		/* Convert the number string to its integer representation */
		while (isDigit(iochar)) {
			left_operand_found = 1;
			left_operand = left_operand * 10 + (iochar - '0');
			iochar = getchar();
		}

		/* We only continue to process the expression if the operand is positive */
		if (!left_operand_found) {
			printf("\nError: Invalid Expression Format - Missing Left Operand\n");
		}
		else if (left_operand_found && negative_flag) {
			printf("\nError: Invalid Left Operand - Negative Numbers Cannot Be Processed\n");
		}
		else {
			/* Skip whitespace before operator */
			while (isSpace(iochar)) { iochar = getchar(); }

			/* Validate and set operator */
			operator_symbol = getOperatorType(iochar);
			if (operator_symbol == INVALID_OPERATOR) {
				printf("\nError: Invalid Operator - '%c' Is Not A Valid Operator\n", iochar);
			}
			else {
				/* Check the valid operator for any type of division */
				division_flag = (operator_symbol == '/' || operator_symbol == '%') ? 1 : 0;

				/* Get next character which could be the start of the right operand or whitespace */
				iochar = getchar();

				/* Skip whitespace before right operand */
				while (isSpace(iochar)) { iochar = getchar(); }

				/* Check for negative sign for right operand */
				if (iochar == '-') {
					negative_flag = 1;
					iochar = getchar();
				}

				/* Convert the characters to an integer */
				while (isDigit(iochar)) {
					right_operand_found = 1;
					right_operand = right_operand * 10 + (iochar - '0');
					iochar = getchar();
				}

				/* Consume whitespaces following right operand */
				while (isSpace(iochar)) { iochar = getchar(); }

				/* Check for extraneous data */
				extraneous_data_flag = (iochar == '\n') ? 0 : 1;

				/* Once we have extracted the right operand, we need to perform the following checks */
				if (extraneous_data_flag) {
					printf("\nError: Invalid Expression Format - Extraneous Characters\n");
				}
				else if (!right_operand_found) {
					printf("\nError: Invalid Expression Format - Missing Right Operand\n");
				}
				else if (right_operand_found && negative_flag) {
					printf("\nError: Invalid Right Operand - Negative Numbers Cannot Be Processed\n");
				}
				else if (right_operand_found && division_flag && right_operand == 0) {
					printf("\nError: Invalid Right Operand - Division By Zero Is Not Allowed\n");
				}
				else if ((iochar == '\n' || iochar == EOF) && right_operand_found) {
					performSpecifiedOperation(left_operand, right_operand, operator_symbol);
				}
			}
		}
		/* Skip any remaining characters until the end of the line or file */
		while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }

		/* Prompt user to repeat program */
		user_selection = getUserSelection();

		/* Consume the newline character after the user makes a selection */
		if (user_selection == 'Y' || user_selection == 'y') {
			while ((iochar = getchar()) != '\n' && iochar != EOF);
			printf("\nEnter an expression in the form of: A <operator> B\n"); 
		}
	}

	return 0;
}

int isDigit(int ch) {
	return (ch >= '0' && ch <= '9');
}

int isSpace(int ch) {
	return (ch == ' ' || ch == '\t');
}

char getOperatorType(int ch) {
	char operator_type;
	switch (ch) {
		case '+':
			operator_type = '+';
			break;
		case '-':
			operator_type = '-';
			break;
		case '*':
			operator_type = '*';
			break;
		case '/':
			operator_type = '/';
			break;
		case '%':
			operator_type = '%';
			break;
		default:
			operator_type = INVALID_OPERATOR;
			break;
	}
	return operator_type;
}

char getUserSelection() {
	int ch; /* Capture EOF */
	char user_selection = '\0';

	printf("\nWould you like to run the program again?\nEnter 'Y' or 'N': ");
	scanf(" %c", &user_selection);
	
	while (user_selection != 'Y' && user_selection != 'y' && user_selection != 'N' && user_selection != 'n') {
		printf("\nError: Invalid Selection\nEnter 'Y' to restart the program and 'N' to exit: ");
		while ((ch = getchar()) != '\n' && ch != EOF); /* Clear the input buffer */
		scanf(" %c", &user_selection);
	} 

	return user_selection;
}

void performSpecifiedOperation(int left_operand, int right_operand, char operator_symbol) {
	int whole_num_val = 0;
	float decimal_val = 0;
	int is_float = 0;

	/* When performing division or modulo, the operands have additional restrictions */
	switch (operator_symbol) {
		case '+':
			whole_num_val = add(left_operand, right_operand);
			break;
		case '-':
			whole_num_val = subtract(left_operand, right_operand);
			break;
		case '*':
			whole_num_val = multiply(left_operand, right_operand);
			break;
		case '/':
			decimal_val = divide(left_operand, right_operand);
			is_float = 1;
			break;
		case '%':
			whole_num_val = modulo(left_operand, right_operand);
			break;
		default:
			printf("\nError: Unable to determine operation type\n");
			break;
	}

	/* Print the operation and result */
	printf("%d %c %d = ", left_operand, operator_symbol, right_operand);
	if (is_float) {
		printf("%.2f\n", decimal_val);
	}
	else {
		printf("%d\n", whole_num_val);
	}
}

int add(int left_operand, int right_operand) {
	return left_operand + right_operand;
}

int subtract(int left_operand, int right_operand) {
	return left_operand - right_operand;
}

int multiply(int left_operand, int right_operand) {
	return left_operand * right_operand;
}

float divide(int left_operand, int right_operand) {
	return ((float) left_operand / right_operand);
}

int modulo(int left_operand, int right_operand) {
	return left_operand % right_operand;
}