#include "RPN.hpp"

RPN::RPN(const std::string& expr) : expression(expr) {}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) 
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::applyOperation(const std::string& op, int a, int b) 
{
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") 
    {
        if (b == 0) 
        {
            std::cerr << "Error: Division by zero" << std::endl;
            exit(EXIT_FAILURE);
        }
        return a / b;
    }
    return 0; // Ne devrait jamais arriver
}

int RPN::evaluate() 
{
    std::istringstream iss(expression); // On crée un flux à partir de l'expression
    std::string token;

    while (iss >> token) // On lit chaque token
    {
        if (isdigit(token[0])) 
        { // Si c'est un nombre, on l'empile
            stack.push(std::atoi(token.c_str()));
        } 
        else if (isOperator(token))
        {
            if (stack.size() < 2) // On vérifie qu'il y a assez d'opérandes
            {
                std::cerr << "Error: Invalid expression (not enough operands)" << std::endl;
                exit(EXIT_FAILURE);
            }
            int b = stack.top(); stack.pop(); // On dépile les deux opérandes
            int a = stack.top(); stack.pop(); // dans l'ordre inverse
            stack.push(applyOperation(token, a, b)); // On empile le résultat
        } 
        else 
        {
            std::cerr << "Error: Invalid token '" << token << "'" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (stack.size() != 1) 
    {
        std::cerr << "Error: Invalid expression (remaining elements in stack)" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return stack.top();
}
