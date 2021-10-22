/**
 * Account class testing file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "Account.h"

int main()
{
    // create an Account object
    int accnum; double money;
    Account* acc = nullptr;
    while(true)
    {
        try
        {
            std::cout << "Create a new account: enter your account number and "
              << "balance:\nAccount number (8 digit number): ";
            std::cin >> accnum;
            std::cout << "Balance (non-negative): ";
            std::cin >> money;
            acc = new Account(accnum, money);
            break;
        }
        catch(Account::NumOutOfBounds &e)
        {
            std::cerr << e.getErrorMessage() << "\n";
        }
        catch(Account::NumNegative &e)
        {
            std::cerr << "Money must be a non-negative number.\n";
        }
    }

    // add the result of a game
    acc->inputGameResults(500, 0);
    std::cout << *acc << std::endl;
    acc->inputGameResults(0, 1000);
    std::cout << *acc << std::endl;

    delete acc; acc = nullptr;
    return 0;
}
