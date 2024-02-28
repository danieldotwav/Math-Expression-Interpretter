#define _CRT_SECURE_NO_WARNINGS /* Disable security warnings in Microsoft Visual Studio */
#include <stdio.h>

#define INVALID_OPERATOR '\0'

/* Helper Functions */
int isDigit(int ch);
int isSpace(int ch);
char getOperatorType(int ch);

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
	int left_operand_found = 0; /* Flag to check if left operand is found */
	int right_operand_found = 0; /* Flag to check if right operand is found */
	int negative_flag = 0; /* Flag to identify negative operands */

	while ((iochar = getchar()) != EOF) {
		/* Reset operands, operator, and flags for each new expression */
		left_operand = 0;
		right_operand = 0;
		operator_symbol = INVALID_OPERATOR;
		left_operand_found = 0;
		right_operand_found = 0;
		negative_flag = 0;

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
			printf("Error: Invalid Expression Format - Missing Left Operand\n");
			while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
		}
		else if (left_operand_found && negative_flag) {
			printf("Error: Invalid Left Operand - Negative Numbers Cannot Be Processed\n");
			while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
		}
		else {
			/* Skip whitespace before operator */
			while (isSpace(iochar)) { iochar = getchar(); }

			/* Validate and set operator */
			operator_symbol = getOperatorType(iochar);
			if (operator_symbol == INVALID_OPERATOR) {
				printf("Error: Invalid Operator - '%c' Is Not A Valid Operator\n", iochar);
				while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
			}
			else {
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

				if (!right_operand_found) {
					printf("Error: Invalid Expression Format - Missing Right Operand\n");
				}
				else if (right_operand_found && negative_flag) {
					printf("Error: Invalid Right Operand - Negative Numbers Cannot Be Processed\n");
					while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
				}
				else if ((iochar == '\n' || iochar == EOF) && right_operand_found) {
					performSpecifiedOperation(left_operand, right_operand, operator_symbol);
				}
				else {
					printf("Error: Invalid Expression Format - Extraneous Characters\n");
				}

				/* Skip any remaining characters until the end of the line or file */
				while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
			}
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

void performSpecifiedOperation(int left_operand, int right_operand, char operator_symbol) {
	int whole_num_val = 0;
	float decimal_val = 0;
	int is_division = 0;

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
			is_division = 1;
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
	if (is_division) {
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