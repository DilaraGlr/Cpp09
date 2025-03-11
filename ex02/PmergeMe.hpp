#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe 
{
    private:
        std::vector<int> vec; // Vecteur d'entiers
        std::deque<int> deq; // Deque d'entiers

        void fordJohnsonSortVector(std::vector<int> &v); 
        void fordJohnsonSortDeque(std::deque<int> &d);

    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        bool parseArgs(int argc, char **argv);
        void sortAndMeasureTime();
        void printVector() const;
        void printDeque() const;
};

#endif
