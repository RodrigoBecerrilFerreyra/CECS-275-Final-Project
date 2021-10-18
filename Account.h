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
         * Class for exception handling of account number in constructor.
         */
        class NumOutOfBounds
        {
            public:
                /**
                 * Initializes the class to hold the expected lower and upper
                 * bounds of the value.
                 * @param lower The lower bound of the expected value
                 * (inclusive).
                 * @param upper The upper bound of the expected value
                 * (inclusive).
                 */
                NumOutOfBounds(int, int);

                int getLowerBounds() const {return lowerbounds;}
                int getUpperBounds() const {return upperbounds;}
            private:
                int lowerbounds;
                int upperbounds;
        };

        /**
         * Class for exception handling of balance in constructor.
         */
        class NumNegative{};

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
