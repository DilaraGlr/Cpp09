#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm> // Pour std::sort

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// Parse les arguments et stocke les valeurs dans les structures de données
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

// Affiche les éléments du vecteur
void PmergeMe::printVector() const
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

// Affiche les éléments de la deque
void PmergeMe::printDeque() const
{
    for (size_t i = 0; i < deq.size(); i++)
    {
        std::cout << deq[i] << " ";
    }
    std::cout << std::endl;
}

// Fonction de comparaison pour trier les paires
bool comparePairs(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.first < b.first;
}

// Tri Ford-Johnson (Merge-Insertion Sort) - Version Vector
void PmergeMe::fordJohnsonSortVector(std::vector<int> &v)
{
    if (v.size() <= 1)
    {
        return;
    }

    // Étape 1: Créer des paires et les trier localement
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < v.size(); i += 2)
    {
        if (v[i] < v[i + 1])
        {
            pairs.push_back(std::make_pair(v[i], v[i + 1]));
        }
        else
        {
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
        }
    }

    // Étape 2: Trier les paires en fonction du premier élément (le plus petit)
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    // Étape 3: Créer une séquence triée avec les premiers éléments de chaque paire
    std::vector<int> sorted;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        sorted.push_back(pairs[i].first);
    }

    // Étape 4: Insérer les seconds éléments de chaque paire dans la séquence triée
    for (size_t i = 0; i < pairs.size(); i++)
    {
        int value = pairs[i].second;
        size_t left = 0;
        size_t right = sorted.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (sorted[mid] < value)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        sorted.insert(sorted.begin() + left, value);
    }

    // Étape 5: Ajouter l'élément impair s'il existe
    if (v.size() % 2 == 1)
    {
        int lastElement = v.back();
        size_t left = 0;
        size_t right = sorted.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (sorted[mid] < lastElement)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        sorted.insert(sorted.begin() + left, lastElement);
    }

    v = sorted; // Remplacer le vecteur original par le trié
}

// Tri Ford-Johnson (Merge-Insertion Sort) - Version Deque
void PmergeMe::fordJohnsonSortDeque(std::deque<int> &d)
{
    if (d.size() <= 1)
    {
        return;
    }

    // Étape 1: Créer des paires et les trier localement
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < d.size(); i += 2)
    {
        if (d[i] < d[i + 1])
        {
            pairs.push_back(std::make_pair(d[i], d[i + 1]));
        }
        else
        {
            pairs.push_back(std::make_pair(d[i + 1], d[i]));
        }
    }

    // Étape 2: Trier les paires en fonction du premier élément (le plus petit)
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    // Étape 3: Créer une séquence triée avec les premiers éléments de chaque paire
    std::deque<int> sorted;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        sorted.push_back(pairs[i].first);
    }

    // Étape 4: Insérer les seconds éléments de chaque paire dans la séquence triée
    for (size_t i = 0; i < pairs.size(); i++)
    {
        int value = pairs[i].second;
        size_t left = 0;
        size_t right = sorted.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (sorted[mid] < value)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        sorted.insert(sorted.begin() + left, value);
    }

    // Étape 5: Ajouter l'élément impair s'il existe
    if (d.size() % 2 == 1)
    {
        int lastElement = d.back();
        size_t left = 0;
        size_t right = sorted.size();
        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            if (sorted[mid] < lastElement)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        sorted.insert(sorted.begin() + left, lastElement);
    }

    d = sorted; // Remplacer la deque originale par le trié
}

// Trie et mesure le temps d'exécution pour le vecteur et la deque
void PmergeMe::sortAndMeasureTime()
{
    std::clock_t start, end;
    double timeVector, timeDeque;
    const int iterations = 1000; // Nombre d'itérations

    std::cout << "Before: ";
    printVector();

    // Mesure du temps pour std::vector
    start = std::clock();
    for (int i = 0; i < iterations; i++)
    {
        std::vector<int> vecCopy = vec; // Copie du vecteur pour ne pas modifier l'original
        fordJohnsonSortVector(vecCopy);
    }
    end = std::clock();
    timeVector = 1000000.0 * (end - start) / CLOCKS_PER_SEC / iterations; // Temps moyen en microsecondes

    std::cout << "After: ";
    printVector();
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << std::fixed << std::setprecision(5) << timeVector << " us" << std::endl;

    // Mesure du temps pour std::deque
    start = std::clock();
    for (int i = 0; i < iterations; i++)
    {
        std::deque<int> deqCopy = deq; // Copie de la deque pour ne pas modifier l'original
        fordJohnsonSortDeque(deqCopy);
    }
    end = std::clock();
    timeDeque = 1000000.0 * (end - start) / CLOCKS_PER_SEC / iterations; // Temps moyen en microsecondes

    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << std::fixed << std::setprecision(5) << timeDeque << " us" << std::endl;
}