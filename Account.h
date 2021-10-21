/**
 * Account class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <exception>
#include <fstream>

/**
 * The Account class handles subjects such as account number and records
 * such as total money and money lost. The Account class also handles saving
 * all these values in a file.
 */
class Account
{
    public:
// *****************************************************************************
// Exception handling classes
// *****************************************************************************
        /**
         * Class for exception handling of account number in constructor.
         */
        class NumOutOfBounds : public std::exception
        {
            public:
                /**
                 * Initializes the class to hold the expected lower and upper
                 * bounds of the value.
                 * @param errval The value that caused the error.
                 * @param lower The lower bound of the expected value
                 * (inclusive).
                 * @param upper The upper bound of the expected value
                 * (inclusive).
                 */
                NumOutOfBounds(int errval, int lower, int upper);

                int getLowerBounds() const {return lowerbounds;}
                int getUpperBounds() const {return upperbounds;}

                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                int errorvalue;
                int lowerbounds;
                int upperbounds;
        };

        /**
         * Class for exception handling of balance in constructor.
         */
        class NumNegative : public std::exception{};

        /**
         * Class for exception handling of file not existing.
         */
        class FileNotFoundError : public std::exception{};

// *****************************************************************************
// constructors
// *****************************************************************************

        /**
         * The default constructor initializes account number to 10000000
         * and balance to 0.
         */
        Account();

        /**
         * This overloaded constructor allows the user to set the value for
         * two of the class's members.
         * @param accountNumber The account number of the new account.
         * @param balance The new account's balance.
         * @throws ParameterOutOfBounds if the account number is not a
         * positive eight-digit number.
         * @throws ParameterOutOfBounds if the balance is 
         */
        Account(int, int);

// *****************************************************************************
// destructors
// *****************************************************************************

        /**
         * Automatically saves all data when object is destroyed.
         */
        ~Account();

// *****************************************************************************
// load and save functions
// *****************************************************************************

        /**
         * Reads the account data from the file acc_{accountNumber}.txt.
         * @throws FileNotFoundError if the file does not exist.
         */
        void load();

        /**
         * Writes the account data to the file acc_{accountNumber}.txt. Overwrites
         * the file if it exists, and creates a new file if it does not.
         */
        void save();

// *****************************************************************************
// other functions
// *****************************************************************************

        /**
         * Checks if the account registered with the account number exists
         * (checks whether or not a file with the filename
         * acc_{accountNumber}.txt exists).
         * @param throwExcept (Optional) if true, throws an exception if the
         * file does not exist. Defaults to false.
         * @return true if file exists, false otherwise
         * @throws FileNotFoundError if the file does not exist and if
         * throwExcept is true.
         */
        //bool exists(bool = false);

// *****************************************************************************
// setter and getter functions
// *****************************************************************************

        // setter functions
        /**
         * Use this function to input the results of a game of blackjack.
         * @param moneyWon The amount of money won from the game.
         * @param moneyLost The amount of money lost from the game.
         */
        void inputGameResults(double, double);

        // getter functions
        /**
         * Getter function for accountNumber.
         * @return accountNumber
         */
        int getAccountNumber() const {return accountNumber;}

        /**
         * Getter function for gamesPlayed.
         * @return gamesPlayed
         */
        int getGamesPlayed() const {return gamesPlayed;}

        /**
         * Getter function for balance.
         * @return balance
         */
        double getBalance() const {return balance;}

        /**
         * Getter function for amountWon.
         * @return amountWon
         */
        double getAmountWon() const {return amountWon;}

        /**
         * Getter function for amountLost.
         * @return amountLost
         */
        double getAmountLost() const {return amountLost;}

    private:
        int accountNumber;
        int gamesPlayed;
        double balance;
        double amountWon;
        double amountLost;

        /**
         * Gets the filename of the filename according to the account number.
         * @return The filename of the file where the account is saved.
         */
        std::string getFilename();
};

#endif//ACCOUNT_H
