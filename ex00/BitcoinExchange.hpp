#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _exchangeRate;
        std::string _filename;

    public:
        BitcoinExchange(std::string filename);
        ~BitcoinExchange();

        void updateExchangeRate(std::string date, double rate);
        double getExchangeRate(std::string date);
        void updateFromFile();
};

#endif
