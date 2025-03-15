#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    // Vérifie que le fichier d'entrée est fourni
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Crée une instance de BitcoinExchange avec le fichier CSV
    BitcoinExchange btc("data.csv");

    // Ouvre le fichier d'entrée
    std::ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::string line;

    // Vérifie si le fichier est vide
    if (!std::getline(inputFile, line))
    {
        std::cerr << "Error: file is empty." << std::endl;
        inputFile.close();
        return 1;
    }

    // Vérifie la première ligne (en-tête)
    if (line != "date | value")
    {
        std::cerr << "Error: invalid input header => " << line << std::endl;
        inputFile.close();
        return 1;
    }

    // Traite chaque ligne du fichier d'entrée
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string date, separator;
        double value;

        // Vérifie le format "date | valeur"
        if (!(iss >> date >> separator >> value) || separator != "|")
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Vérifie si la date est valide
        if (!btc.isValidDate(date))
        {
            std::cerr << "Error: invalid date => " << date << std::endl;
            continue;
        }

        // Vérifie si la valeur est valide
        if (!btc.isValidValue(value))
        {
            continue;
        }

        // Récupère le taux de change pour la date donnée
        double rate = btc.getExchangeRate(date);
        if (rate == 0)
        {
            std::cerr << "Error: no exchange rate found for date " << date << std::endl;
            continue;
        }

        // Affiche le résultat
        std::cout << date << " => " << std::fixed << std::setprecision(2) << value << " = " << value * rate << std::endl;
    }

    inputFile.close();
    return 0;
}