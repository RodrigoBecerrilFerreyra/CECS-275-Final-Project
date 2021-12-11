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
    int hand1val, hand2val, dealval;
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
                << " split? 0 for no, 1 for yes: ";
            std::cin >> useroption;
            if(useroption)
            {
                splitflag = true;
                player.split();
            }
        }

        // hand 1
        std::cout << "Now playing: hand 1." << std::endl;
        player.outputPrettyWrapper(0);
        std::cout << "Value: " << player.getValue(0) << "\n";
        while(true)
        {
            if(player.getValue(0) >= 21)
                break;

            std::cout << "Enter 0 for hit, 1 for stand: ";
            std::cin >> useroption;
            if(useroption == 0) // hit
            {
                player.drawCard(0, deck, 1);
                std::cout << "Value: " << player.getValue(0) << "\n";
            }
            else // stand
                break;
        }

        // hand 2
        if(splitflag)
        {
            std::cout << "Now playing: hand 2." << std::endl;
            player.outputPrettyWrapper(1);
            std::cout << "Value: " << player.getValue(1) << "\n";
            while(true)
            {
                if(player.getValue(1) >= 21)
                    break;

                std::cout << "Enter 0 for hit, 1 for stand: ";
                std::cin >> useroption;
                if(useroption == 0) // hit
                {
                    player.drawCard(1, deck, 1);
                    std::cout << "Value: " << player.getValue(1) << "\n";
                }
                else // stand
                    break;
            }
        }

        hand1val = player.getValue(0);
        hand2val = player.getValue(1);
        dealval  = dealer.getValue(0);

        std::cout << "Dealer's hand:" << std::endl;
        dealer.outputPrettyWrapper(0);
        std::cout << "Value: " << dealval << "\n";

        std::cout << "Results for Game 1:\n";
        if(hand1val > 21)
        {
            std::cout << "Bust! You lose.\n";
            // lose bet
        }
        else if(hand1val > dealval)
        {
            std::cout << "You win!\n";
            // double bet
        }
        else if(hand1val < dealval)
        {
            std::cout << "You lose.\n";
            // lose bet
        }
        else // tie
        {
            std::cout << "It's a tie!\n";
            // split bet
        }

        if(splitflag)
        {
            std::cout << "Results for Game 2:\n";
            if(hand2val > 21)
            {
                std::cout << "Bust! You lose.\n";
                // lose bet
            }
            else if(hand2val > dealval)
            {
                std::cout << "You win!\n";
                // double bet
            }
            else if(hand2val < dealval)
            {
                std::cout << "You lose.\n";
                // lose bet
            }
            else // tie
            {
                std::cout << "It's a tie!\n";
                // split bet
            }
        }

        std::cout << "Enter 0 to quit or 1 to continue: ";
        //std::cin >> useroption;
        useroption = 0;
    } while(useroption);

    return 0;
}
