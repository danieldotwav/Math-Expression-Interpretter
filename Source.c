#define _CRT_SECURE_NO_WARNINGS /* Disable security warnings in Microsoft Visual Studio */
#include <stdio.h>

#define INVALID_OPERATOR 'X'

int isDigit(int ch);
char getOperatorType(int ch);

/* Wrapper function */
void computeOperation(int left_operand, int right_operand, char operator_symbol);

int performAddition(int left_operand, int right_operand);
int performSubtraction(int left_operand, int right_operand);
int performMultiplication(int left_operand, int right_operand);
float performDivision(int left_operand, int right_operand);
int performModulo(int left_operand, int right_operand);

int main(void) {
	int iochar;
	
	int is_valid_left_operand = 0;
	int is_valid_right_operand = 0;

	int is_valid_operator = 1;
	int is_valid_expression = 1;

	printf("%d", performAddition(5, 10));
	printf("\n");
	printf("%.2f", performDivision(10, 5));
	printf("\n");

	printf("%c", getOperatorType('+', 0));

	int left_operand = 0;
	int right_operand = 0;
	char user_operator = 0;

	int white_space_encountered = 0;
	int still_processing_left_operand = 1;
	int still_processing_right_operand = 1;
		
	/* First, we'll consider all characters up to the newline character as being part of the same expression */
	while (iochar != EOF) {
		/* First, process left operand */
		if (still_processing_left_operand) {
			/* Once we encounter a non-numeric value, we can move on */
			if (!isDigit(iochar)) {
				still_processing_left_operand = 0;
			}
			else {
				TODO: /* Form the number here */
			}
		}

		/* Next, we will check for a valid operator symbol */
		char operator_symbol;
		if (is_valid_left_operand && is_valid_expression) {
			while ((iochar = getchar() == ' ')) { /* consume white spaces leading to next input */ }

			/* Validate operator */
			operator_symbol = getOperatorType(iochar);

			if (operator_symbol == INVALID_OPERATOR) {
				is_valid_expression = 0;
			}
		}

		/* Finally, we check for a valid right operand */
		if (still_processing_right_operand && is_valid_expression) {
			if (!isDigit(iochar)) {
				/* Once we encounter a non-numeric value, we can move on */
				still_processing_right_operand = 0;
			} 
			else {
				TODO: /* Form the number here */
			}
		}

		/* Consume all whitespaces following right operand */
		while ((iochar = getchar()) == ' ') {  }

		/* If all that's left is a newline character, then the expression is valid */
		if (iochar == '\n') {
			computeOperation(left_operand, right_operand, operator_symbol);
		}
		else {
			/* Otherwise, consume all characters until we reach a newline or EOF */
			while ((iochar = getchar()) != EOF && iochar != '\n') {  }
		}
	}

	return 0;
}

int isDigit(int ch) {
	return (ch >= '0' && ch <= '9');
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

void computeOperation(int left_operand, int right_operand, char operator_symbol) {
	int whole_num_val = 0;
	float decimal_val = 0;
	int is_division = 0;

	switch (operator_symbol) {
		case '+':
			whole_num_val = performAddition(left_operand, right_operand);
			break;
		case '-':
			whole_num_val = performSubtraction(left_operand, right_operand);
			break;
		case '*':
			whole_num_val = performMultiplication(left_operand, right_operand);
			break;
		case '/':
			decimal_val = performDivision(left_operand, right_operand);
			is_division = 1;
			break;
		case '%':
			whole_num_val = performModulo(left_operand, right_operand);
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

int performAddition(int left_operand, int right_operand) {
	return left_operand + right_operand;
}

int performSubtraction(int left_operand, int right_operand) {
	return left_operand - right_operand;
}

int performMultiplication(int left_operand, int right_operand) {
	return left_operand * right_operand;
}

float performDivision(int left_operand, int right_operand) {
	return ((float) left_operand / right_operand);
}

int performModulo(int left_operand, int right_operand) {
	return left_operand % right_operand;
}