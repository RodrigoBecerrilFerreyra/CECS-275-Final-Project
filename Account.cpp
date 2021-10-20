/**
 * Account class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <string>
#include <fstream>
#include "Account.h"

Account::NumOutOfBounds::NumOutOfBounds(int lower, int upper)
{
    lowerbounds = lower;
    upperbounds = upper;
}

Account::Account() : Account(10000000, 0){}

Account::Account(int accountNumber, int balance)
{
    // account number must be a positive eight-digit number
    if(accountNumber < 10000000 || accountNumber > 99999999)
        throw NumOutOfBounds(10000000, 99999999);
    
    // balance must be non-negative
    if(balance < 0)
        throw NumNegative();
    
    this->accountNumber = accountNumber;
    this->balance = balance;
}

void Account::load()
{
    // open file
    std::fstream infile(getFilename().c_str(), std::ios::in);
    if(infile.fail())
        throw FileNotFoundError();
    
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

void Account::save() const
{
    // open file
    std::fstream outfile(getFilename().c_str(), std::ios::out);

    // populate file
    outfile << "Account Number: " << accountNumber << "\n";
    outfile << "Current balance: $" << balance << "\n";
    outfile << "Game played: " << gamesPlayed << "\n";
    outfile << "Total amount won: $" << amountWon << "\n";
    outfile << "Total amount lost: $" << amountLost << "\n";

    outfile.close();
}

void Account::inputGameResults(double moneyWon, double moneyLost)
{
    ++gamesPlayed;
    amountWon += moneyWon;
    amountLost += moneyLost;
}

bool Account::exists(bool throwExcept = false)
{
    std::fstream infile(getFilename().c_str(), std::ios::in);
    if(infile.is_open())
        if(throwExcept) throw FileNotFoundError();
        else return false;
    return true;
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
