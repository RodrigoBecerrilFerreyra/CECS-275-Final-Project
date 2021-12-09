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



Player::Player()
{
    value1 = value2 = 0;
    playerType = 0;
}

Player::Player(int ID)
{
    value1 = value2 = 0;
    if (ID != 0) playerType = ID;
    else playerType = 1;
}

void Player::drawCard(CardList *hand, CardList deck, int count)
{
    int numAces = 0;
    bool success = deck.transferTo(*hand, count);
    if (success)
    {
        if (value1) 
        {
            // expression must have class type (i.e. CardList) but has type [CardList *]
            value2 = hand.listValue();
            numAces = hand.CountCards(1);
            value2 += (numAces*10);
            if(value2>21) value2 -= (numAces*10);
        } 
        else 
        {
            // expression must have class type (i.e. CardList) but has type [CardList *]
            value1 = hand.listValue();
            numAces = hand.CountCards(1);
            value1 += (numAces*10);
            if(value1>21) value2 -= (numAces*10);
        }
    }
}
