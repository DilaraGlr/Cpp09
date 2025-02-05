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
        ~RPN();
        
        int evaluate();  // Évalue l'expression et retourne le résultat

    private:
        std::stack<int> stack;  // Utilisation d'une pile pour l'évaluation
        std::string expression; // L'expression RPN sous forme de string

        bool isOperator(const std::string& token); // Vérifie si c'est un opérateur
        int applyOperation(const std::string& op, int a, int b); // Effectue l'opération
};

#endif
