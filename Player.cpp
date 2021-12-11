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

Player::NotAction::NotAction(int useAction)
{
    action = useAction;
}

std::string Player::NotAction::getErrorMessage()
{
    return "Not a valid action.\n";
}

Player::Player()
{
    value1 = value2 = 0;
    playerType = 0;
    bet1 = 0;
    bet2 = 0;
    playerRef = nullptr;
}

Player::Player(int ID)
{
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
            std::cout << "Generating new account with provided ID.\n";
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
    } 
    bet1 = 0;
    bet2 = 0;
}

void Player::setBet(double newBet)
{
    double money = checkMoney();
    if(money < newBet)
        throw Player::InsufficientBalance(newBet,money);
    else
        bet1 = newBet;
}

void Player::setBet()
{
    // Verify once more that this is a possible bet.
    double money = checkMoney();
    if(money < bet1*2)
        throw Player::InsufficientBalance(bet1,money);
    else
        bet2 = bet1;
}

unsigned int Player::takeAction(unsigned int action)
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

std::string Player::actionsTerminal()
{
    bool outputFlag = canSplit();
    if (outputFlag)
        return "1. Hit\n 2. Stand\n 3. Split\n------\n 0. Exit\n";
    else
        return "1. Hit\n 2. Stand\n ------\n 0. Exit\n";
}

bool Player::canSplit()
{
    // Take the total value of the cards and halve it...
    int check = (hand1.listValue()) / 2;
    // ...then verify that each "half" is present. (e.g. 14 == 2*7)
    if (hand1.countCards(check) == 2)
    {
        if (bet1*2 < checkMoney())
            return true;
        else
            return false;
    }
    else
        return false;
}

void Player::drawCard(int hand, CardList &deck, int count)
{
    // sets the hand to hand1 or hand2
    CardList* chosenHand = (hand == 1) ? &hand1 : &hand2;

    deck.transferTo(*chosenHand, count);
    if (playerType)
        std::cout << chosenHand->outputPretty();
    else
        std::cout << chosenHand->outputBlackjack();
}

void Player::returnCards(CardList &deck, CardList &hand)
{
    hand.transferTo(deck);
}

void Player::updateVal(int corrVal)
{
    int numAces = 0;
    // Input is 0, 2, 4, etc. Ideally the input is 0 for hand1.
    if (corrVal % 2 == 0)
    {
        value1 = hand1.listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand1.countCards(1);
        if (numAces)
        {
            value1 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value1 > 21)
            {   
                do {
                    value1 -= 10;
                    numAces--;
                } while (numAces && value1 > 21);
            }
        }
    } else {
        value2 = hand2.listValue();
        // Special handling for Aces being both 1 and 11.
        numAces = hand2.countCards(1);
        if (numAces)
        {
            value2 += numAces*10;
            // If having Ace = 11 exceeded 21, revert increase.
            if (value2 > 21)
            {   
                do {
                    value2 -= 10;
                    numAces--;
                } while (numAces && value2 > 21);
            }
        }
    }
}
