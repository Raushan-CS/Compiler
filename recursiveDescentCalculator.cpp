#include <iostream>
#include <string>
#include <cctype>

class RecursiveDescentCalculator {
public:
    RecursiveDescentCalculator(const std::string& expr) : expression(expr), currentPos(0) {}

    double evaluate() {
        double result = parseExpression();
        if (currentPos < expression.length()) {
            std::cerr << "Error: Unexpected character encountered at position " << currentPos << std::endl;
            return 0; // Return 0 if error occurs
        }
        return result;
    }

private:
    const std::string& expression;
    size_t currentPos;

    double parseExpression() {
        double result = parseTerm();
        while (currentPos < expression.length() && (expression[currentPos] == '+' || expression[currentPos] == '-')) {
            char op = expression[currentPos++];
            if (op == '+')
                result += parseTerm();
            else
                result -= parseTerm();
        }
        return result;
    }

    double parseTerm() {
        double result = parseFactor();
        while (currentPos < expression.length() && (expression[currentPos] == '*' || expression[currentPos] == '/')) {
            char op = expression[currentPos++];
            double factor = parseFactor();
            if (op == '*')
                result *= factor;
            else if (factor != 0) // Check for division by zero
                result /= factor;
            else {
                std::cerr << "Error: Division by zero" << std::endl;
                return 0; // Return 0 if division by zero occurs
            }
        }
        return result;
    }

    double parseFactor() {
        if (currentPos < expression.length() && std::isdigit(expression[currentPos])) {
            size_t startPos = currentPos;
            while (currentPos < expression.length() && std::isdigit(expression[currentPos]))
                currentPos++;
            return std::stod(expression.substr(startPos, currentPos - startPos));
        } else if (currentPos < expression.length() && expression[currentPos] == '(') {
            currentPos++;
            double result = parseExpression();
            if (currentPos < expression.length() && expression[currentPos] == ')')
                currentPos++;
            else
                std::cerr << "Error: Missing closing parenthesis" << std::endl;
            return result;
        } else {
            std::cerr << "Error: Unexpected character encountered at position " << currentPos << std::endl;
            return 0; // Return 0 if error occurs
        }
    }
};

int main() {
    std::string expression;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expression);

    RecursiveDescentCalculator calculator(expression);
    double result = calculator.evaluate();

    if (result != 0)
        std::cout << "Result: " << result << std::endl;

    return 0;
}
