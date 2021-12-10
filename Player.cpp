/**
 * Player class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include "CardList.h"
#include "Account.h"
#include "Player.h"
#include <iostream>
#include <string>

Player::InsufficientBalance::InsufficientBalance(double userBet, double accBal)
{
    bet = userBet;
    balance = accBal;
}

std::string Player::InsufficientBalance::getErrorMessage()
{
    return "InsufficientBalance; Player bet" + std::to_string(bet - balance) + 
    "over maximum possible Account balance.\n";
}

Player::Player()
{
    hand1 = hand2 = nullptr;
    value1 = value2 = 0;
    playerType = 0;
    playerRef = nullptr;
}

Player::Player(int ID)
{
    hand1 = hand2 = nullptr;
    playerRef = nullptr;
    value1 = value2 = 0;
    // If ID is a positive value, attempt to load/save account.
    if (ID > 0)
    {
        playerType = ID;
        // Attempt to load account using ID value.
        try
        {
            playerRef = new Account(ID);
        }
        catch(Account::FileNotFoundError &e)
        {
            // File did not already exist, so make a new one.
            std::cerr << e.getErrorMessage() << "\n";
            playerRef->save();
        }
        catch(Account::NumOutOfBounds &e)
        {
            // File input is not valid.
            std::cerr << e.getErrorMessage() << "\n";
        }
    } 
    else
    {   
        // Default to playerType of dealer.
        playerType = 0;
        playerRef = nullptr;
    } 
}

unsigned int Player::takeAction()
{
    // TODO: 
    // Implement [Hit] logic
    // - drawCard(hand,deck,1)?
    // - [Hit] as many times as one wishes until over 21
    // Implement branch for [Split] logic
    // - some way to differentiate between hands
    // - also, verify that user can even make the second bet
    // Implement [Stand] logic
    // - reveal dealer's hand; values for player and dealer
    // - also, update balance
}

void Player::drawCard(CardList *hand, CardList deck, int count)
{
    deck.transferTo(*hand, count);
    if (playerType)
        std::cout << hand->outputPretty();
    else
        std::cout << hand->outputBlackjack();
}

void Player::returnCards(CardList deck, CardList* hand)
{
    hand->transferTo(deck);
}

void Player::updateVal(int corrVal)
{
    int numAces = 0;
    // Input is 0, 2, 4, etc. Ideally the input is 0 for hand1.
    if(corrVal % 2 == 0)
    {
        value1 = hand1->listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand1->countCards(1);
        if (numAces)
        {
            value1 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value1 > 21)
            {   
                do {
                    value1 -= 10;
                    numAces--;
                } while (numAces);
            }
        }
    } else {
        value2 = hand2->listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand2->countCards(1);
        if (numAces)
        {
            value2 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value2 > 21)
            {   
                do {
                    value2 -= 10;
                    numAces--;
                } while (numAces);
            }
        }
    }
}

