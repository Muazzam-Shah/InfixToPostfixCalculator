# InfixToPostfixCalculator

## Description
This project is a C++ implementation of an arithmetic expression solver using a circular doubly linked list. It converts infix expressions to postfix notation and evaluates them using a stack-based approach.

## Features
- **Custom Linked List Implementation**: Uses a circular doubly linked list to store and manipulate expressions.
- **Infix to Postfix Conversion**: Converts mathematical expressions into postfix notation.
- **Postfix Evaluation**: Solves postfix expressions using a stack-based approach.
- **Handles Basic Arithmetic Operations**: Addition, subtraction, multiplication, division, and exponentiation.
- **Error Handling**: Detects division by zero and provides appropriate error messages.

## Usage
1. Compile the program using a C++ compiler:
   ```sh
   g++ -o ExpressionSolver main.cpp
   ```
2. Run the executable:
   ```sh
   ./ExpressionSolver
   ```
3. Enter a mathematical expression when prompted.
4. The program will display the postfix expression and compute the result.

## Example Run
```
Enter your expression: 3+5*2
*************Results*************
Your Expression: 3+5*2
Postfix Expression: 3 5 2 * +
Result: 13
```


