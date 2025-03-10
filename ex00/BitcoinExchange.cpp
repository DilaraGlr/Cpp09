#include "BitcoinExchange.hpp"

// Constructeur
BitcoinExchange::BitcoinExchange(std::string filename) : _filename(filename)
{
    updateFromFile();
}

// Destructeur
BitcoinExchange::~BitcoinExchange()
{
}

// Met à jour le taux de change pour une date donnée
void BitcoinExchange::updateExchangeRate(const std::string &date, double rate)
{
    _exchangeRate[date] = rate;
}

// Récupère le taux de change pour une date donnée
double BitcoinExchange::getExchangeRate(const std::string &date) const
{
    // Trouve la date la plus proche (inférieure ou égale)
    std::map<std::string, double>::const_iterator it = _exchangeRate.lower_bound(date);

    // Si la date est avant la première date dans la map
    if (it == _exchangeRate.begin() && it->first != date)
    {
        return 0; // Aucun taux de change trouvé
    }

    // Si la date n'est pas exacte, on prend la date précédente
    if (it == _exchangeRate.end() || it->first != date)
    {
        --it;
    }

    return it->second;
}

// Lit le fichier CSV et met à jour les taux de change
void BitcoinExchange::updateFromFile()
{
    std::ifstream file(_filename.c_str());
    if (!file)
    {
        std::cerr << "Error: could not open file " << _filename << std::endl;
        return;
    }

    std::string line;

    // Vérifie la première ligne (en-tête)
    if (!std::getline(file, line) || line != "date,exchange_rate")
    {
        std::cerr << "Error: invalid CSV header => " << line << std::endl;
        file.close();
        return;
    }

    // Lit les lignes suivantes
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date;
        double rate;

        // Vérifie le format "date,taux"
        if (std::getline(iss, date, ',') && (iss >> rate))
        {
            updateExchangeRate(date, rate);
        }
        else
        {
            std::cerr << "Error: invalid line in CSV => " << line << std::endl;
        }
    }
    file.close();
}

// Vérifie si la date est valide (format YYYY-MM-DD)
bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    int year, month, day;
    char dash1, dash2;
    std::istringstream iss(date);
    if (!(iss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-')
    {
        return false;
    }

    // Vérifie les limites des mois et des jours
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

// Vérifie si la valeur est valide (positive et <= 1000)
bool BitcoinExchange::isValidValue(double value) const
{
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}