/**
 * Player class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "CardList.h"
#include "Account.h"

/**
 * The Player class is responsible for all operations having to do with a Player
 * in the game of Blackjack: holding one (or two) hands with different values,
 * having an Account, etc.
 */
class Player
{
    public:
        /**
         * Class for exception handling of betting more than the playerRef 
         * Account's balance.
         */
        class InsufficientBalance : public std::exception
        {
            public:
                InsufficientBalance(double userBet, double accBal);
                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                double balance;
                double bet;
        };
        /**
         * Class for exception handling of invalid action.
         */
        class NotAction : public std::exception
        {
            public:
                NotAction(int useAction);
                /**
                 * Builds an error message and returns it.
                 * @return A detailed error message.
                 */
                std::string getErrorMessage();
            private:
                int action;
        };
        /**
         * Initialization constructor to create a new Player. Defaults to a 
         * "dealer"-type Player, which disables the ability to save or 
         * load an Account.
         */
        Player();

        /**
         * Constructor specific to a "player"-type Player. Similar 
         * implementation to default constructor but specifically 
         * activates ability to set up Account.
         * @param ID  Positive integer to attempt accessing account. 
         * @throws FileNotFound if no text file but valid account. 
         * @throws NumOutOfBounds if player ID not 8-digit positive integer. 
         */
        Player(int ID);

        /** This enum specifies the action that the user takes after
        receiving a card. */
        enum action {HIT, HOLD, BUST};

        /**
         * Overloaded function acepts a user's bet to begin the game.
         * @param newBet  Desired sum to bet for new game.
         * @throws InsufficientBalance if user bets more than account holds.
         */
        void setBet(double newBet);
        /**
         * Overloaded function copies the value of bet1 over to bet2. 
         * Used when splitting.
         * @throws InsufficientBalance if user bets more than account holds.
         */
        void setBet();

        /**
         * Getter function for hand/value1. 
         * @return Hand 1's value.
         */
        int getValue1()
            { return value1; }
        /**
         * Getter function for hand/value2. 
         * @return Hand 2's value.
         */
        int getValue2()
            { return value2; }
        
        /**
         * Has the player decide what to do in the current state of the game.
         * Should be called after receiving a card.
         * @param action   User's action.
         * @returns The action to be taken by the Player.
         */
        unsigned int takeAction(unsigned int action);

        /**
         * Generates a display of what actions the Player can take.
         * @return Displayable string regarding valid choices and their meaning.
         */
        std::string actionsTerminal();

        /**
         * Verifies that the user's hand1 is composed of only duplicate 
         * cards, therefore allowing the user to split.
         * @returns   The user's hand is only identically-valued cards.
         */
        bool canSplit();
        
        /**
         * Gives the designated Player's hand the top cards from 
         * another CardList. 
         * @param hand  Player hand to draw cards into. 
         * @param deck  Base CardList to take cards from.
         * @param count How many cards from the target CardList to take.
         */
        void drawCard(int hand, CardList &deck, int count);

        /**
         * Returns the designated Player's hand to a larger pool.
         * @param deck   Card pool to place Player's cards back into. 
         * @param hand   Player's hand to remove cards from.
         */
        void returnCards(CardList &deck, CardList &hand);

        /**
         * Wrapper function to retrieve the user's current balance in 
         * their account to verify that they are making a legal bet.
         * @return     The user's current balance of funds.
         */
        double checkMoney()
            { return playerRef->getBalance(); }

        /**
         * Wrapper function to update the value of Player's hand. 
         * @param corrVal  Flag used to differentiate which value to update.
         */
        void updateVal(int corrVal);
        
        /**
         * Fetch account details IFF the Player object is a "Player" 
         * rather than a "Dealer" as only the former needs to 
         * have an account.
         */
        void prevAccount()
            { if (playerType) playerRef->load(); }
    private:
        CardList hand1, hand2;    // the hands to hold the CardLists
        int value1, value2;       // the values of each hand
        int playerType;           // 0 for "Dealer" or 1 for "Player"
        Account *playerRef;       // Defines Player's statistics
        double bet1, bet2;        // Player's current bets
};

#endif//PLAYER_H
