#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) 
{
    if (argc < 2) 
    {
        std::cerr << "Error: Not enough arguments." << std::endl;
        return 1;
    }

    PmergeMe sorter;

    if (!sorter.parseArgs(argc, argv)) 
    {
        return 1;
    }

    sorter.sortAndMeasureTime();
    return 0;
}
