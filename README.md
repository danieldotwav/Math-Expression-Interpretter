# Simple Calculator Program in C

This C program acts as a simple calculator that performs basic arithmetic operations such as addition, subtraction, multiplication, division, and modulo. It reads expressions from the standard input (stdin) or the command line (in the case of text files), processes each expression, and outputs the result to the standard output (stdout).

## Features

- **Arithmetic Operations:** Supports addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and modulo (`%`) operations.
- **Error Handling:** Provides feedback for common input errors, including missing operands, invalid operators, and attempts to use negative numbers.
- **Interactive:** Continuously reads and evaluates expressions from the standard input until an EOF (End-of-File) signal is received.

## Components

- **Main Function:** Orchestrates the reading of input, identification of operands and operators, and the execution of the specified operation.
- **Helper Functions:**
  - `isDigit(int ch)`: Checks if a character is a digit.
  - `isSpace(int ch)`: Checks if a character is a whitespace character (space or tab).
  - `getOperatorType(int ch)`: Determines the type of operator based on the input character.
- **Operation Functions:** Perform the actual arithmetic operations. These include:
  - `add(int left_operand, int right_operand)`: Returns the sum of two integers.
  - `subtract(int left_operand, int right_operand)`: Returns the difference between two integers.
  - `multiply(int left_operand, int right_operand)`: Returns the product of two integers.
  - `divide(int left_operand, int right_operand)`: Returns the quotient of two integers as a float.
  - `modulo(int left_operand, int right_operand)`: Returns the remainder of the division of two integers.
- **Wrapper Function:**
  - `performSpecifiedOperation(int left_operand, int right_operand, char operator_symbol)`: Executes the appropriate arithmetic operation based on the provided operator symbol and operands.

## Error Handling

The program now includes advanced error handling mechanisms for:

- Invalid expressions (missing operands or operators).
- Unsupported operators.
- Negative numbers as operands.
- Division by zero.
- Extraneous characters after the right operand.

## Limitations

- **Negative Numbers:** The current implementation does not support negative numbers as operands. Negative numbers may be printed as results, however (e.g., 5 - 10 = -5).
- **Floating-Point Numbers:** It does not support floating-point numbers; all operands are treated as integers except for the division operation, which returns a floating-point result.
- **Input Format:** Each expression must be in the form of `operand1 operator operand2` (e.g., `10 + 20`), with each component separated by whitespace.
