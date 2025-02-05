#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string filename) : _filename(filename) {
    updateFromFile();
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::updateExchangeRate(const std::string &date, double rate) {
    _exchangeRate[date] = rate;
}

double BitcoinExchange::getExchangeRate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = _exchangeRate.lower_bound(date);

    if (it == _exchangeRate.begin() && it->first != date) {
        return 0;
    }
    if (it == _exchangeRate.end() || it->first != date) {
        --it;
    }
    return it->second;
}

void BitcoinExchange::updateFromFile() {
    std::ifstream file(_filename.c_str());
    if (!file) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, separator;
        double value;

        // Vérification stricte du format "YYYY-MM-DD | VALUE"
        if (!(iss >> date >> separator >> value) || separator != "|") {
            std::cerr << "Error: Invalid line format => " << line << std::endl;
            continue;
        }

        if (!isValidDate(date) || !isValidValue(value)) {
            continue;
        }

        updateExchangeRate(date, value);
    }
    file.close();
}

// Vérifie si la date est valide (format YYYY-MM-DD)
bool BitcoinExchange::isValidDate(const std::string &date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year, month, day;
    char dash1, dash2;
    std::istringstream iss(date);
    if (!(iss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-')
        return false;
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}

// Vérifie si la valeur est valide (nombre positif et <= 1000)
bool BitcoinExchange::isValidValue(double value) const {
    if (value < 0) {
        std::cerr << "Error: Not a positive number => " << value << std::endl;
        return false;
    }
    if (value > 1000) {
        std::cerr << "Error: Int must be between [0-1000] => " << std::fixed << std::setprecision(2) << value << std::endl;
        return false;
    }
    return true;
}
