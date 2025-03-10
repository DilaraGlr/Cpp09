#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>

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

#endif