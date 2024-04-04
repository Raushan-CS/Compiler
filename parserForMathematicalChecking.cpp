#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>

// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | number


// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to evaluate an expression based on operator and operands
int evaluate(int operand1, char op, int operand2) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            return 0; // Invalid operator
    }
}

// Function to perform Shift operation
void shift(std::stack<int>& operandStack, std::stack<char>& operatorStack, char inputChar, std::ofstream& outFile) {
    outFile << "Shift: Push " << inputChar << " onto the operator stack." << std::endl;
    operatorStack.push(inputChar);
}

// Function to perform Reduce operation
void reduce(std::stack<int>& operandStack, std::stack<char>& operatorStack, std::ofstream& outFile) {
    char op = operatorStack.top();
    operatorStack.pop();

    int operand2 = operandStack.top();
    operandStack.pop();

    int operand1 = operandStack.top();
    operandStack.pop();

    int result = evaluate(operand1, op, operand2);
    outFile << "Reduce: Pop two operands (" << operand1 << " and " << operand2 << ") and operator " << op << " from stacks. Evaluate: " << operand1 << " " << op << " " << operand2 << " = " << result << ". Push the result " << result << " onto the operand stack." << std::endl;

    operandStack.push(result);
}

// Function to parse and evaluate a mathematical expression using Shift-Reduce parsing technique
void parseAndEvaluate(const std::string& expression, std::ofstream& outFile) {
    std::stack<int> operandStack;
    std::stack<char> operatorStack;

    for (char c : expression) {
        if (isdigit(c)) { // Operand
            operandStack.push(c - '0');
            outFile << "Shift: Push " << c << " onto the operand stack." << std::endl;
        } else if (isOperator(c)) { // Operator
            while (!operatorStack.empty() && operatorStack.top() != '(' && ((c == '*' || c == '/') || (operatorStack.top() == '+' || operatorStack.top() == '-'))) {
                reduce(operandStack, operatorStack, outFile);
            }
            shift(operandStack, operatorStack, c, outFile);
        } else if (c == '(') {
            operatorStack.push(c);
            outFile << "Shift: Push " << c << " onto the operator stack." << std::endl;
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                reduce(operandStack, operatorStack, outFile);
            }
            if (!operatorStack.empty()) {
                operatorStack.pop(); // Pop the '('
            }
        }
    }

    while (!operatorStack.empty()) {
        reduce(operandStack, operatorStack, outFile);
    }

    if (!operandStack.empty()) {
        outFile << "Result: " << operandStack.top() << std::endl;
    } else {
        outFile << "Error: Empty operand stack." << std::endl;
    }
}

int main() {
    std::string expression;
    std::cout << "Enter a mathematical expression (containing integers only): ";
    std::getline(std::cin, expression);

    std::ofstream outFile("parsing_output.txt");
    if (outFile.is_open()) {
        outFile << "Expression: " << expression << std::endl;
        parseAndEvaluate(expression, outFile);
        outFile.close();
        std::cout << "Parsing and evaluation details written to parsing_output.txt" << std::endl;
    } else {
        std::cerr << "Error: Unable to open output file." << std::endl;
    }

    return 0;
}
