#define _CRT_SECURE_NO_WARNINGS /* Disable security warnings in Microsoft Visual Studio */
#include <stdio.h>

#define INVALID_OPERATOR 'X'

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

	while ((iochar = getchar()) != EOF) {
		// Reset operands and operator for each new expression
		left_operand = 0;
		right_operand = 0;
		operator_symbol = INVALID_OPERATOR;

		// Process left operand and skip initial whitespace
		while (isSpace(iochar)) { iochar = getchar(); } // Skip leading spaces

		while (isDigit(iochar)) {
			left_operand = left_operand * 10 + (iochar - '0');
			iochar = getchar();
		}

		// Skip whitespace before operator
		while (isSpace(iochar)) { iochar = getchar(); }

		// Validate and set operator
		operator_symbol = getOperatorType(iochar);
		if (operator_symbol == INVALID_OPERATOR) {
			// Skip to the end of the current line to avoid processing the rest of it
			printf("Error: Invalid Operator\n");
			while ((iochar = getchar()) != '\n' && iochar != EOF);
		}
		else {
			// Get next character which could be the start of the right operand or whitespace
			iochar = getchar();

			// Skip whitespace before right operand
			while (isSpace(iochar)) { iochar = getchar(); }

			// Process right operand
			while (isDigit(iochar)) {
				right_operand = right_operand * 10 + (iochar - '0');
				iochar = getchar();
			}

			// Assuming computeOperation does something meaningful with the operands and operator
			performSpecifiedOperation(left_operand, right_operand, operator_symbol);

			// Skip to the end of the line or file to handle the next expression cleanly
			while (iochar != '\n' && iochar != EOF) { iochar = getchar(); }
		}
	}

	return 0;
}

int isDigit(int ch) {
	return (ch >= '0' && ch <= '9');
}

int isSpace(int ch) {
	return (ch == ' ');
}

char getOperatorType(int ch) {
	switch (ch) {
		case '+':
			break;
		case '-':
			break;
		case '*':
			break;
		case '/':
			break;
		case '%':
			break;
		default:
			ch = INVALID_OPERATOR;
			break;
	}
	return ch;
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