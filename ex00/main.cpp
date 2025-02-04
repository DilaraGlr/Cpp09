#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong number of arguments." << std::endl;
        return 1;
    }

    BitcoinExchange btc("data.csv");

    std::ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        std::cerr << "Error: could not open input file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inputFile, line); // Ignore la première ligne

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string date, valueStr;
        double value;

        if (std::getline(iss, date, '|') && std::getline(iss, valueStr))
        {
            try
            {
                value = std::stod(valueStr);
                if (value < 0 || value > 1000)
                {
                    std::cerr << "Error: value out of range for " << date << std::endl;
                    continue;
                }

                double exchangeRate = btc.getExchangeRate(date);
                if (exchangeRate != -1)
                    std::cout << date << " => " << value << " = " << (value * exchangeRate) << std::endl;
            }
            catch (std::exception &e)
            {
                std::cerr << "Error: invalid input at " << date << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }

    return 0;
}
