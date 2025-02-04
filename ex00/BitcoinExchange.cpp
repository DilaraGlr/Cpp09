#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string filename) : _filename(filename)
{
    updateFromFile();
}

BitcoinExchange::~BitcoinExchange()
{
    // Pas besoin de saveToFile() car le fichier "data.csv" est en lecture seule.
}

void BitcoinExchange::updateExchangeRate(std::string date, double rate)
{
    _exchangeRate[date] = rate;
}

double BitcoinExchange::getExchangeRate(std::string date)
{
    std::map<std::string, double>::iterator it = _exchangeRate.lower_bound(date);

    if (it == _exchangeRate.end() || it->first != date)
    {
        if (it == _exchangeRate.begin())
        {
            std::cerr << "Error: no valid exchange rate for " << date << std::endl;
            return -1;
        }
        --it;
    }
    return it->second;
}

void BitcoinExchange::updateFromFile()
{
    std::ifstream file(_filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::getline(file, line); // Ignore la première ligne (en-tête)

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, valueStr;
        double rate;

        if (std::getline(iss, date, ',') && std::getline(iss, valueStr))
        {
            try
            {
                rate = std::stod(valueStr);
                if (rate < 0)
                {
                    std::cerr << "Error: negative exchange rate at " << date << std::endl;
                    continue;
                }
                updateExchangeRate(date, rate);
            }
            catch (std::exception &e)
            {
                std::cerr << "Error: invalid number format at " << date << std::endl;
            }
        }
    }
}
