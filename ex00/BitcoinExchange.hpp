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
    // Constructeur par défaut
    BitcoinExchange();

    // Constructeur avec paramètre
    BitcoinExchange(std::string filename);

    // Constructeur de copie
    BitcoinExchange(const BitcoinExchange &other);

    // Destructeur
    ~BitcoinExchange();

    // Opérateur d'affectation
    BitcoinExchange &operator=(const BitcoinExchange &other);

    // Méthodes publiques
    void updateExchangeRate(const std::string &date, double rate);
    double getExchangeRate(const std::string &date) const;
    void updateFromFile();
    bool isValidDate(const std::string &date) const;
    bool isValidValue(double value) const;
};

#endif