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
         * Initialization constructor to create a new Player.
         */
        Player();

        /**
         * Copy constructor to copy the hands and Account of another Player.
         */ 
        Player(Player &other);

        /** This enum specifies the action that the user takes after
        receiving a card. */
        enum action {HIT, HOLD, BUST};

        /**
         * Has the player decide what to do in the current state of the game.
         * Should be called after receiving a card.
         * @returns The action to be taken by the Player.
         */
        action takeAction();
        
        /**
         * Gives the designated Player's hand the top cards from 
         * another CardList. Updates corresponding hand value once 
         * all cards are drawn.
         * @param hand  Player hand to draw cards into. 
         * @param deck  Base CardList to take cards from.
         * @param count How many cards from the CardList to take.
         */
        void drawCard(CardList* &hand, CardList* &deck, int count);

    private:
        CardList* hand1, * hand2; // the hands to hold the CardLists
        int value1, value2; // the values of each hand
};

#endif//PLAYER_H
