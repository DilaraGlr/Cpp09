#include "RPN.hpp"

int main(int argc, char** argv) 
{
    if (argc != 2) 
    {
        std::cerr << "Error: Wrong number of arguments" << std::endl;
        return 1;
    }

    std::string expression = argv[1];
    RPN calculator(expression);

    try 
    {
        std::cout << calculator.evaluate() << std::endl;
    } 
    catch (const RPNException& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}