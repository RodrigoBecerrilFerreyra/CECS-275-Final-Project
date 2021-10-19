/**
 * Account class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

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
    void save() const;

// *****************************************************************************
// setter and getter functions
// *****************************************************************************

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
};
