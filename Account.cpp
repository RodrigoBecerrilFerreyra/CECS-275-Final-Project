/**
 * Account class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <string>
#include <fstream>
#include <ostream>
#include "Account.h"

Account::NumOutOfBounds::NumOutOfBounds(int errval, int lower, int upper)
{
    errorvalue = errval;
    lowerbounds = lower;
    upperbounds = upper;
}

std::string Account::NumOutOfBounds::getErrorMessage()
{
    return "NumOutOfBounds; Value received: " + std::to_string(errorvalue)
      + "; expected value between " + std::to_string(lowerbounds)
      + " and " + std::to_string(upperbounds) + " (inclusive).";
}

Account::FileNotFoundError::FileNotFoundError(std::string name)
{
    filename = name;
}

std::string Account::FileNotFoundError::getErrorMessage()
{
    return "FileNotFoundError; The file " + filename + " could not be found.";
}

Account::Account()
{
    this->accountNumber = 0;
    this->balance = 0;
    this->gamesPlayed = 0;
    this->amountWon = 0;
    this->amountLost = 0;
}

Account::Account(int accountNumber, int balance)
{
    // account number must be a positive eight-digit number
    if(accountNumber < 10000000 || accountNumber > 99999999)
        throw NumOutOfBounds(accountNumber, 10000000, 99999999);
    
    // balance must be non-negative
    if(balance < 0)
        throw NumNegative();
    
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->gamesPlayed = 0;
    this->amountWon = 0;
    this->amountLost = 0;
    save();
}

void Account::load()
{
    // open file
    std::fstream infile(getFilename().c_str(), std::ios::in);
    if(infile.fail())
        throw FileNotFoundError(getFilename());
    
    // load all values into variables
    std::string lines[5] = {};

    for(int i = 0; i < 5; ++i)
        std::getline(infile, lines[i]);
    
    // cast string into appropriate type
    accountNumber = std::stoi(lines[0].substr(16));
    balance       = std::stod(lines[1].substr(18));
    gamesPlayed   = std::stoi(lines[2].substr(13));
    amountWon     = std::stod(lines[3].substr(19));
    amountLost    = std::stod(lines[4].substr(20));

    infile.close();
}

void Account::save()
{
    // open file
    std::fstream outfile(getFilename().c_str(), std::ios::out);

    // populate file
    outfile << *this << "\n";

    outfile.close();
}

void Account::inputGameResults(double moneyWon, double moneyLost)
{
    ++gamesPlayed;
    amountWon += moneyWon;
    amountLost += moneyLost;
    balance += (moneyWon - moneyLost);
    save();
}

Account::~Account()
{
    save();
}

std::string Account::getFilename()
{
    std::string filename = "acc_";
    filename += std::to_string(accountNumber);
    filename += ".txt";
    return filename;
}

std::ostream& operator<< (std::ostream& os, const Account& acc)
{
    os << "Account Number: " << acc.accountNumber << "\n";
    os << "Current Balance: $" << acc.balance << "\n";
    os << "Game Played: " << acc.gamesPlayed << "\n";
    os << "Total Amount Won: $" << acc.amountWon << "\n";
    os << "Total Amount Lost: $" << acc.amountLost;
    return os;
}
