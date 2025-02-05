#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange exchange(argv[1]);

        std::ifstream input_file(argv[1]);
        std::string line;

        if (!input_file.is_open())
        {
            std::cerr << "Error: could not open input file" << std::endl;
            return 1;
        }

        std::cout << std::fixed << std::setprecision(2);

        while (std::getline(input_file, line))
        {
            std::istringstream iss(line);
            std::string date, separator;
            double value;

            if (!(iss >> date >> separator >> value) || separator != "|")
            {
                std::cerr << "Error: Invalid line format => " << line << std::endl;
                continue;
            }

            if (!exchange.isValidDate(date))
            {
                std::cerr << "Error: Invalid date format => " << line << std::endl;
                continue;
            }

            if (!exchange.isValidValue(value))
            {
                continue;
            }

            double rate = exchange.getExchangeRate(date);
            std::cout << date << " => " << value << " = " << rate * value << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
