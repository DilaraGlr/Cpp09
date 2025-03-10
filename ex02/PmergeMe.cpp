#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>  // Pour la précision décimale

// Constructeur
PmergeMe::PmergeMe() {}

// Destructeur
PmergeMe::~PmergeMe() {}

// Fonction pour parser les arguments et remplir les conteneurs
bool PmergeMe::parseArgs(int argc, char **argv) 
{
    for (int i = 1; i < argc; i++) 
    {
        std::istringstream iss(argv[i]);
        int num;
        if (!(iss >> num) || num < 0) 
        {
            std::cerr << "Error: Invalid input => " << argv[i] << std::endl;
            return false;
        }
        vec.push_back(num);
        deq.push_back(num);
    }
    return true;
}

// Afficher le contenu d'un conteneur (vector)
void PmergeMe::printVector() const 
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

// Afficher le contenu d'un conteneur (deque)
void PmergeMe::printDeque() const 
{
    for (size_t i = 0; i < deq.size(); i++)
        std::cout << deq[i] << " ";
    std::cout << std::endl;
}

// Tri Merge-Insertion (Version Vector)
void PmergeMe::mergeInsertSortVector(std::vector<int> &v) 
{
    if (v.size() <= 1)
        return;
    
    std::vector<int> left(v.begin(), v.begin() + v.size() / 2); // On divise le vecteur en deux
    std::vector<int> right(v.begin() + v.size() / 2, v.end()); 

    mergeInsertSortVector(left); // On trie les deux parties
    mergeInsertSortVector(right);
    
    mergeVector(v, left, right); // On fusionne les deux parties
}

// Fonction de fusion pour vector (ex: [2] [] => [1, 2])
void PmergeMe::mergeVector(std::vector<int> &v, std::vector<int> &left, std::vector<int> &right) 
{
    size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) 
    {
        if (left[i] < right[j]) // On compare les éléments des deux parties
            v[k++] = left[i++];
        else 
            v[k++] = right[j++];
    }
    while (i < left.size()) v[k++] = left[i++]; // On ajoute les éléments restants
    while (j < right.size()) v[k++] = right[j++];
}

// Tri Merge-Insertion (Version Deque)
void PmergeMe::mergeInsertSortDeque(std::deque<int> &d) 
{
    if (d.size() <= 1)
        return;
    
    std::deque<int> left(d.begin(), d.begin() + d.size() / 2);
    std::deque<int> right(d.begin() + d.size() / 2, d.end());

    mergeInsertSortDeque(left);
    mergeInsertSortDeque(right);
    
    mergeDeque(d, left, right);
}

// Fonction de fusion pour deque
void PmergeMe::mergeDeque(std::deque<int> &d, std::deque<int> &left, std::deque<int> &right) 
{
    size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) 
    {
        if (left[i] < right[j])
            d[k++] = left[i++];
        else
            d[k++] = right[j++];
    }
    while (i < left.size()) d[k++] = left[i++];
    while (j < right.size()) d[k++] = right[j++];
}

// Fonction principale qui exécute le tri et affiche les résultats
void PmergeMe::sortAndMeasureTime() 
{
    std::clock_t start, end;
    double timeVector, timeDeque;

    std::cout << "Before: ";
    printVector();

    // Mesure du temps pour le vector
    start = std::clock();
    mergeInsertSortVector(vec);
    end = std::clock();
    timeVector = 1000.0 * (end - start) / CLOCKS_PER_SEC; // Conversion en microsecondes

    std::cout << "After: ";
    printVector();

    // Affichage du temps avec une précision décimale
    std::cout << "Time to process " << vec.size() << " elements with std::vector: ";
    std::cout << std::fixed << std::setprecision(5) << timeVector << " ms" << std::endl;

    // Mesure du temps pour le deque
    start = std::clock();
    mergeInsertSortDeque(deq);
    end = std::clock();
    timeDeque = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    // Affichage du temps avec une précision décimale
    std::cout << "Time to process " << deq.size() << " elements with std::deque: ";
    std::cout << std::fixed << std::setprecision(5) << timeDeque << " ms" << std::endl;
}
