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