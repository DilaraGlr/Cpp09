#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe 
{
    private:
        std::vector<int> vec; // Vecteur d'entiers
        std::deque<int> deq; // Deque d'entiers

        void mergeInsertSortVector(std::vector<int> &v); 
        void mergeVector(std::vector<int> &v, std::vector<int> &left, std::vector<int> &right);//

        void mergeInsertSortDeque(std::deque<int> &d); 
        void mergeDeque(std::deque<int> &d, std::deque<int> &left, std::deque<int> &right);

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
