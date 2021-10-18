/**
 * Account class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <fstream>

/**
 * The Account class handles subjects such as account number and records
 * such as total money and money lost. The Account class also handles saving
 * all these values in a file.
 */
class Account
{
    public:
        /**
         * Class for exception handling in constructor.
         */
        class ParameterOutOfBounds
        {
            public:
                /**
                 * Sets the lower and upper bounds (inclusive) of the
                 * expected value.
                 * @param lower The lower bound (inclusive).
                 * @param upper The upper bound (inclusive).
                 */
                ParameterOutOfBounds(int, int);
                int getLowerBounds() const {return lowerBounds;}
                int getUpperBounds() const {return upperBounds;}
            private:
                int lowerBounds;
                int upperBounds;
        };

        /**
         * The default constructor initializes all values to 0.
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
        int getBalance() const {return balance;}

        /**
         * Getter function for amountWon.
         * @return amountWon
         */
        int getAmountWon() const {return amountWon;}

        /**
         * Getter function for amountLost.
         * @return amountLost
         */
        int getAmountLost() const {return amountLost;}

    private:
        int accountNumber;
        int gamesPlayed;
        int balance;
        int amountWon;
        int amountLost;
        std::ifstream infile;
        std::ofstream outfile;
};
