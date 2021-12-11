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
    int useroption; bool splitflag;
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
    //std::cin >> useroption;
    useroption = 11111111;

    Player player(useroption);
    Player dealer;

    // do-while loops until user decides to exit program
    do
    {
        splitflag = false;
        deck.shuffle();

        // deals two cards to each
        std::cout << "Dealer's cards:\n";
        dealer.drawCard(0, deck, 2);
        std::cout << "Your cards:\n";
        player.drawCard(0, deck, 2);

        if(player.splitCondition())
        {
            std::cout << "You received two of the same card. Would you like to"
                << " split? 1 for yes, 0 for no: ";
            std::cin >> useroption;
            if(useroption)
            {
                splitflag = true;
                player.hand1.transferTo(player.hand2, 1);
            }
        }

        // hand 1
        std::cout << "Now playing: hand 1.\n";
        while(true)
        {
            std::cout << "Enter 0 for hit, 1 for stand: ";
            std::cin >> useroption;
            if(useroption == 0) // hit
            {
                player.drawCard(0, deck, 1);
                std::cout << "value: " << player.getValue(0) << "\n";
                if(player.getValue(0) >= 21)
                    break;
            }
            else // stand
                break;
        }

        // hand 2
        if(splitflag)
        {
            std::cout << "Now playing: hand 2.\n";
            while(true)
            {
                std::cout << "Enter 0 for hit, 1 for stand: ";
                std::cin >> useroption;
                if(useroption == 0) // hit
                {
                    player.drawCard(1, deck, 1);
                    if(player.getValue(1) >= 21)
                        break;
                }
                else // stand
                    break;
            }
        }

        std::cout << "Enter 0 to quit or 1 to continue: ";
        //std::cin >> useroption;
        useroption = 0;
    } while(useroption);

    return 0;
}
