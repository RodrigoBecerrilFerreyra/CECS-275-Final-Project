/**
 * Account class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <fstream>
#include "Account.h"

Account::NumOutOfBounds::NumOutOfBounds(int lower, int upper)
{
    lowerbounds = lower;
    upperbounds = upper;
}

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

// this constructor simply calls the other constructor with default values
Account::Account() : Account(10000000, 0){}
