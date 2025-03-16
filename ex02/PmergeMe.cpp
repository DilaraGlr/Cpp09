#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>

// ---------------------- CONSTRUCTEURS/DESTRUCTEUR -----------------------
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) { 
    *this = other; 
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// ---------------------------- FONCTIONS UTILITAIRES --------------------------
bool PmergeMe::parseArgs(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        int num;
        if (!(iss >> num) || num < 0) {
            std::cerr << "Error: Invalid input => " << argv[i] << std::endl;
            return false;
        }
        vec.push_back(num);
        deq.push_back(num);
    }
    return true;
}

void PmergeMe::printVector() const {
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printDeque() const {
    for (size_t i = 0; i < deq.size(); ++i)
        std::cout << deq[i] << " ";
    std::cout << std::endl;
}

// ---------------------------- ALGORITHME PRINCIPAL --------------------------

// Fonction de comparaison pour trier les paires
static bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first < b.first;
}

// Génère la séquence de Jacobsthal
static std::vector<size_t> generateJacobsthalSequence(size_t n) {
    std::vector<size_t> seq;
    if (n == 0) return seq;
    seq.push_back(0);
    if (n == 1) return seq;
    
    seq.push_back(1);
    for (size_t i = 2; ; ++i) {
        size_t next = seq[i-1] + 2 * seq[i-2];
        if (next > n) break;
        seq.push_back(next);
    }
    return seq;
}

// Tri Ford-Johnson générique pour std::vector et std::deque
template <typename Container>
static void fordJohnsonSortGeneric(Container& c) {
    if (c.size() <= 1) return;

    typedef typename Container::value_type Val;
    std::vector<std::pair<Val, Val> > pairs;
    const bool has_odd = c.size() % 2;
    const Val last = has_odd ? c.back() : Val();
    const size_t limit = has_odd ? c.size() - 1 : c.size();

    // Création des paires
    for (size_t i = 0; i < limit; i += 2) {
        if (c[i] < c[i+1])
            pairs.push_back(std::make_pair(c[i], c[i+1]));
        else
            pairs.push_back(std::make_pair(c[i+1], c[i]));
    }

    // Tri des paires
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    // Construction de la chaine principale
    Container main_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        main_chain.push_back(pairs[i].first);

    // Séquence Jacobsthal optimisée
    std::vector<size_t> jacob = generateJacobsthalSequence(pairs.size());
    std::vector<bool> inserted(pairs.size(), false);

    // Phase 1 : Insertion Jacobsthal
    for (size_t i = 0; i < jacob.size(); ++i) {
        const size_t pos = jacob[i];
        if (pos >= pairs.size() || inserted[pos]) continue; // Évite les doublons
        
        const Val value = pairs[pos].second;
        typename Container::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), value);
        main_chain.insert(it, value);
        inserted[pos] = true;
    }

    // Phase 2 : Insertion restante
    for (int i = pairs.size() - 1; i >= 0; --i) {
        if (!inserted[i]) {
            const Val value = pairs[i].second;
            typename Container::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), value);
            main_chain.insert(it, value);
        }
    }

    // Élément impair
    if (has_odd) {
        typename Container::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), last);
        main_chain.insert(it, last);
    }

    c = main_chain;
}

// Tri Ford-Johnson pour std::vector
void PmergeMe::fordJohnsonSortVector(std::vector<int>& v) {
    fordJohnsonSortGeneric(v);
}

// Tri Ford-Johnson pour std::deque
void PmergeMe::fordJohnsonSortDeque(std::deque<int>& d) {
    fordJohnsonSortGeneric(d);
}

// ---------------------------- MESURE PERFORMANCE ------------------------
void PmergeMe::sortAndMeasureTime() {
    const int iterations = 1000;
    std::clock_t start, end;

    std::cout << "Before: ";
    printVector();

    // Tri principal
    std::vector<int> vec_copy = vec;
    std::deque<int> deq_copy = deq;
    
    fordJohnsonSortVector(vec_copy);
    fordJohnsonSortDeque(deq_copy);

    // Affichage résultat
    std::cout << "After:  ";
    for (size_t i = 0; i < vec_copy.size(); ++i)
        std::cout << vec_copy[i] << " ";
    std::cout << std::endl;

    // Mesure temps vector
    start = std::clock();
    for (int i = 0; i < iterations; ++i) {
        std::vector<int> copy = vec;
        fordJohnsonSortVector(copy);
    }
    end = std::clock();
    double vec_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC / iterations;

    // Mesure temps deque
    start = std::clock();
    for (int i = 0; i < iterations; ++i) {
        std::deque<int> copy = deq;
        fordJohnsonSortDeque(copy);
    }
    end = std::clock();
    double deq_time = 1000000.0 * (end - start) / CLOCKS_PER_SEC / iterations;

    // Affichage temps
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " 
              << std::fixed << std::setprecision(5) << vec_time << " us\n"
              << "Time to process a range of " << deq.size()
              << " elements with std::deque  : "
              << std::fixed << std::setprecision(5) << deq_time << " us" 
              << std::endl;
}