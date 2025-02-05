#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _exchangeRate;
        std::string _filename;

    public:
        BitcoinExchange(std::string filename);
        ~BitcoinExchange();

        void updateExchangeRate(const std::string &date, double rate);
        double getExchangeRate(const std::string &date) const;
        void updateFromFile();
        bool isValidDate(const std::string &date) const;
        bool isValidValue(double value) const;
};

#endif
