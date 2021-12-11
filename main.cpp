/**
 * Main function file; game logic goes here.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <iostream>
#include "CardList.h"
#include "Player.h"

int main()
{
    int ID; int useroption = 0;
    // build deck
    CardList deck;
    // create 52 cards
    for(int i = 1; i <= 13; ++i)
    {
        deck.createCard(CardList::CLUBS, i);
        deck.createCard(CardList::DIAMONDS, i);
        deck.createCard(CardList::HEARTS, i);
        deck.createCard(CardList::SPADES, i);
    }

    std::cout << "************************************************\n";
    std::cout << "Welcome to Ethan's and Rodrigo's Blackjack game.\n";
    std::cout << "************************************************\n";

    std::cout << "Please enter your ID number (if you do not have one, input"
        << " any number): ";
    //std::cin >> ID;
    ID = 11111111;

    Player player(ID);
    Player dealer;

    // do-while loops until user decides to exit program
    do
    {
        deck.shuffle();

        // deals two cards to each
        std::cout << "Dealer's cards:\n";
        dealer.drawCard(1, deck, 2);
        std::cout << "Your cards:\n";
        player.drawCard(1, deck, 2);

        

        std::cout << "Enter 0 to quit or 1 to continue: ";
        //std::cin >> useroption;
        useroption = 0;
    } while(useroption);

    return 0;
}
