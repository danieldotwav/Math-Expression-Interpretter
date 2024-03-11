#define _CRT_SECURE_NO_WARNINGS /* Disable security warnings in Microsoft Visual Studio */
#include <stdio.h>

#define ADDITION '+'
#define SUBTRACTION '-'
#define MULTIPLICATION '*'
#define DIVISION '/'
#define MODULO '%'

int isDigit(int iochar);
int isSpace(int iochar);
int isValidOperatorSymbol(int iochar);

void performSpecifiedOperation(int left_operand, int right_operand, char operation);
int addition(int left_operand, int right_operand);
int subtraction(int left_operand, int right_operand);
int multiplication(int left_operand, int right_operand);
float division(int left_operand, int right_operand);
int modulo(int left_operand, int right_operand);

char promptUserToRepeatProgram(void);

int main(void) {
	int iochar;
	int left_operand, right_operand, negative_sign_encountered, negative_number_encountered, count;
	char operation;
	char response = 'Y';

	printf("Welcome to the Math Expression Interpretter\n");
	printf("\nEnter an expression in the form of: A <operator> B\n");

	while (((iochar = getchar()) != EOF) && (response == 'Y' || response == 'y')) {
		/* Reset operands */
		left_operand = right_operand = negative_sign_encountered = negative_number_encountered = count = 0;
		operation = '\0';

		/* Print current character to console */
		putchar(iochar);

		/* Consume initial whitespaces */
		while (isSpace(iochar)) {
			iochar = getchar();
			putchar(iochar);
		}

		/* Check if we've reached the end of the line */
		if (iochar != '\n') {
			if (isDigit(iochar)) {
				/* We need to read every digit in the number */
				while (isDigit(iochar)) {
					/* Convert the character representation of the left_operand to an integer */
					left_operand = left_operand * 10 + (iochar - '0');
					iochar = getchar();
					putchar(iochar);
				}

				/* Consume whitespaces following left_operand */
				while (isSpace(iochar)) {
					iochar = getchar();
					putchar(iochar);
				}

				/* Once again, we check if we've reached the end of the line */
				if (iochar != '\n') {
					if (isValidOperatorSymbol(iochar)) {
						/* Now that we have a valid operation, we need to get the next character */
						operation = iochar;
						iochar = getchar();
						putchar(iochar);

						/* Consume whitespaces following operator symbol */
						while (isSpace(iochar)) {
							iochar = getchar();
							putchar(iochar);
						}

						/* Check if we encounter a newline before reaching the right operand */
						if (iochar != '\n') {
							if (isDigit(iochar)) {
								/* Convert the character representation of the right_operand to an integer */
								while (isDigit(iochar)) {
									right_operand = right_operand * 10 + (iochar - '0');
									iochar = getchar();

									/* If we encounter a newline character immediately after the right operand, don't print it to the screen yet */
									if (iochar != '\n') {
										putchar(iochar);
									}
								}

								/* Consume whitespaces following right_operand */
								while (isSpace(iochar)) {
									iochar = getchar();
									putchar(iochar);
								}

								/* Final check for newline character */
								if (iochar == '\n' || iochar == EOF) {
									/* Check for division by zero */
									if ((operation == DIVISION || operation == MODULO) && right_operand == 0) {
										printf("Error: Division By Zero\n");
									}
									else {
										/* If the only characters following the right_operand are tabs/spaces/newline characters/or EOF, then the expression is valid */
										performSpecifiedOperation(left_operand, right_operand, operation);
									}
								}
								else {
									printf("Error: Invalid Expression Format\n");
								}
							}
							else {
								/* * * If we reach this part, the user entered an invalid right operand * * */
								/* First, we check to see if the user entered a negative number */
								if (iochar == '-') {
									negative_sign_encountered = 1;
								}

								/* Read and print remaining input before printing the appropriate error message */
								while (iochar != '\n' && iochar != EOF) {
									iochar = getchar();
									putchar(iochar);

									/* If the first character following the negative sign is a digit, then we print a unique error message */
									if (count == 0 && negative_sign_encountered && isDigit(iochar)) {
										negative_number_encountered = 1;
									}

									count++;
								}

								if (negative_number_encountered) {
									printf("Error: Negative Numbers Are Invalid\n");
								}
								else {
									printf("Error: Invalid Character(s) Detected\n");
								}
							}
						}
						else {
							/* If we reach this part, the user entered an incomplete expression */
							printf("Error: Incomplete Expression\n");
						}
					}
					else {
						/* * * If we reach this part, the user entered an invalid operator symbol * * */
						/* Consume remaining characters until the end of the line or file */
						while (iochar != '\n' && iochar != EOF) {
							iochar = getchar();
							putchar(iochar);
						}

						printf("Error: Invalid Operator Symbol\n");
					}
				}
				else {
					/* * * If we reach this part, there's nothing left to process in the line * * */
					printf("Error: Incomplete Expression\n");
				}
			}
			else {
				/* * * If we reach this part, the user entered an invalid left operand * * */
				/* First, we check to see if the user entered a negative number */
				if (iochar == '-') {
					negative_sign_encountered = 1;
				}

				/* Read and print remaining input before printing the appropriate error message */
				while (iochar != '\n' && iochar != EOF) {
					iochar = getchar();
					putchar(iochar);

					/* If the first character following the negative sign is a digit, then we print a unique error message */
					if (count == 0 && negative_sign_encountered && isDigit(iochar)) {
						negative_number_encountered = 1;
					}

					count++;
				}

				if (negative_number_encountered) {
					printf("Error: Negative Numbers Are Invalid\n");
				}
				else {
					printf("Error: Invalid Character(s) Detected\n");
				}
			}
		}
		else {
			/* * * If we reach this part, there's nothing left to process in the line */
			printf("Error: Empty Line Encountered\n");
		}

		/* Prompt user to repeat the program */
		response = promptUserToRepeatProgram();

		/* If the user decides to repeat the program, we must print the original prompt again */
		if (response == 'Y' || response == 'y') {
			printf("\n\nEnter an expression in the form of: A <operator> B\n");
		}
	}

	return 0;
}

int isDigit(int iochar) {
	return iochar >= '0' && iochar <= '9';
}

int isSpace(int iochar) {
	return iochar == ' ' || iochar == '\t';
}

int isValidOperatorSymbol(int iochar) {
	return iochar == ADDITION || iochar == SUBTRACTION || iochar == MULTIPLICATION || iochar == DIVISION || iochar == MODULO;
}

void performSpecifiedOperation(int left_operand, int right_operand, char operation) {
	int result = 0;
	float result_float = 0.0;

	/* Determine which operation to perform */
	switch (operation) {
		case ADDITION:
			result = addition(left_operand, right_operand);
			break;
		case SUBTRACTION:
			result = subtraction(left_operand, right_operand);
			break;
		case MULTIPLICATION:
			result = multiplication(left_operand, right_operand);
			break;
		case DIVISION:
			result_float = division(left_operand, right_operand);
			break;
		case MODULO:
			result = modulo(left_operand, right_operand);
			break;
		default:
			printf("Error: Unable To Determine Operation Type\n");
			break;
	}

	/* Print the result */
	if (operation == DIVISION) {
		printf(" = %f\n", result_float);
	}
	else {
		printf(" = %d\n", result);
	}
}

int addition(int left_operand, int right_operand) {
	return left_operand + right_operand;
}

int subtraction(int left_operand, int right_operand) {
	return left_operand - right_operand;
}

int multiplication(int left_operand, int right_operand) {
	return left_operand * right_operand;
}

float division(int left_operand, int right_operand) {
	return (float)left_operand / right_operand;
}

int modulo(int left_operand, int right_operand) {
	return left_operand % right_operand;
}

char promptUserToRepeatProgram(void) {
	char response;
	int isValid;
	int c; /* Variable to read any extra characters */

	do {
		isValid = 0; /* Assume input is not valid initially */
		printf("\nDo you want to repeat the program? (Y/N): ");
		response = getchar();
		putchar(response);

		if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
			if (getchar() == '\n') { // Check if next character is newline
				isValid = 1; // Input is valid
			}
		}

		while (!isValid && (c = getchar()) != '\n' && c != EOF) {
			// Flush the input buffer until newline or EOF
		}
	} while (!isValid);

	return response;
}