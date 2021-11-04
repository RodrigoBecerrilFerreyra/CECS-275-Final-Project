/**
 * CardList class tester file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "CardList.h"

int main()
{
    // create two card lists
    CardList hand, deck;

    // create 52 cards and shuffle them
    for(int i = 1; i <= 13; ++i)
    {
        deck.createCard(CardList::CLUBS, i);
        deck.createCard(CardList::DIAMONDS, i);
        deck.createCard(CardList::HEARTS, i);
        deck.createCard(CardList::SPADES, i);
    }
    // attempt to create a card that is already in the deck
    deck.createCard(CardList::SPADES, 1);
    // attempt to create a card with an invalid value
    deck.createCard(CardList::CLUBS, 20);
    std::cout << "The deck contains " << deck.size() << " cards.\n";
    // above should output 52

    // print cards before shuffling
    std::cout << deck << "\n";
    deck.shuffle();
    // print cards after shuffling
    std::cout << deck << "\n";

    // deal two cards to the hand
    deck.transfer(hand, 2);
    std::cout << "The deck contains " << deck.size() << " cards.\n";
    std::cout << "The hand contains " << hand.size() << " cards.\n";

    // test output
    std::cout << hand.outputPretty() << "\n";
    // deal 10 more cards to hand
    deck.transfer(hand, 10);
    // test >10 card output
    std::cout << hand.outputPretty() << "\n";
    // compare to known list contents
    std::cout << hand << "\n";

    return 0;
}
