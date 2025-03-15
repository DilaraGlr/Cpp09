#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

class RPN 
{
    public:
        RPN(const std::string& expression);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
        
        int evaluate();  // Évalue l'expression et retourne le résultat

    private:
        std::stack<int> stack;  // Utilisation d'une pile
        std::string expression; // L'expression RPN sous forme de string

        bool isOperator(const std::string& token) const; // Vérifie si c'est un opérateur
        int applyOperation(const std::string& op, int a, int b) const; // Effectue l'opération
};

// Exception personnalisée pour RPN
class RPNException : public std::exception 
{
    private:
        std::string message;
    public:
        RPNException(const std::string& msg) : message(msg) {}
        virtual ~RPNException() throw() {}
        virtual const char* what() const throw() 
        {
            return message.c_str();
        }
};

#endif