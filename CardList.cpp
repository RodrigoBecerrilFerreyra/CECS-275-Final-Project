/**
 * CardList class implementation file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <chrono>    // for std::chrono
#include <string>    // for std::string
#include "CardList.h"

CardList::Card* CardList::pop()
{
    // do nothing if list is empty
    if(!headPtr)
        return nullptr;
    
    // else pop the head and return it
    Card* oldhead = headPtr;
    headPtr = headPtr->nextCard;
    --numCards;
    return oldhead;
}

void CardList::addCard(Card* cardPtr)
{
    cardPtr->nextCard = headPtr;
    headPtr = cardPtr;
    ++numCards;
}

bool CardList::transfer(CardList &other, unsigned int amount)
{
    if(!headPtr)
        return false;
    
    Card* cardBeingTransferred = nullptr;

    // do not remove more cards than there are in the CardList
    if(amount > numCards) amount = numCards;

    // this loop transfers the number of cards requested
    for(int i = 0; i < amount; ++i)
    {
        cardBeingTransferred = pop();
        if(!cardBeingTransferred) // if the list is empty for any reason
            return false; // this prevents nullptr being added to other
        other.addCard(cardBeingTransferred);
    }

    return true;
}

bool CardList::createCard(CardList::listOfSuits cardSuit, unsigned int cardValue)
{
    // the function does not do anything if the value is out of range
    if(cardValue > 13 || cardValue < 1)
        return false;

    // next, look through the list and see if any cards match requested card
    Card* traversePtr = headPtr;
    while(traversePtr) // iterate until end of list
    {
        // if there is a match, return false
        if(traversePtr->suit == cardSuit && traversePtr->value == cardValue)
            return false;
        traversePtr = traversePtr->nextCard;
    }

    // if there is no match, create a new card and add it
    traversePtr = new Card;
    traversePtr->suit = cardSuit;
    traversePtr->value = cardValue;
    addCard(traversePtr);
    
    return true;
}

void CardList::shuffle()
{
    // if list is empty, do nothing
    if(!headPtr)
        return;

    // create an array of all the addresses of all nodes in the list
    int i = 0;
    Card** addressArray = new Card*[numCards];

    // start at head; loop until you reach the end of the list; go to next card
    for(Card* nodePtr = headPtr; nodePtr; nodePtr = nodePtr->nextCard)
        addressArray[i++] = nodePtr;
        // note that the array avoids putting nullptr into the array

    // shuffle the array of addresses
    // shuffle implementation taken from https://stackoverflow.com/a/26682712
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(&addressArray[0], &addressArray[numCards], rng);
    // std::shuffle takes the address of the first element and the address of
    //   the element after the last element. The last element is
    //   addressArray[numCards-1], so the element after it is
    //   addressArray[numCards].

    // re-link all nodes according to the new order of addressArray
    // start from the back and work your way up to the front
    addressArray[numCards-1]->nextCard = nullptr;
    for(i = numCards - 2; i >= 0; --i)
        addressArray[i]->nextCard = addressArray[i+1];
    headPtr = addressArray[0];

    // free array memory
    delete[] addressArray;
}

std::string CardList::outputBasic() const
{
    std::string outstring = "SUIT       VALUE\n";

    // traverse through the list and add data to the string
    Card* traversePtr = headPtr;
    while(traversePtr) // while not nullptr
    {
        // pick the suit
        switch(traversePtr->suit)
        {
            case CardList::CLUBS:
                outstring += "CLUBS      ";
                break;
            case CardList::DIAMONDS:
                outstring += "DIAMONDS   ";
                break;
            case CardList::HEARTS:
                outstring += "HEARTS     ";
                break;
            case CardList::SPADES:
                outstring += "SPADES     ";
        }

        // pick the value
        switch(traversePtr->value)
        {
            case 1: // ace
                outstring += "A";
                break;
            case 11: // j
                outstring += "J";
                break;
            case 12: // q
                outstring += "Q";
                break;
            case 13: // k
                outstring += "K";
                break;
            default: // anything else in between
                outstring += std::to_string(traversePtr->value);
                break;
        }

        outstring += "\n";
        traversePtr = traversePtr->nextCard;
    }

    return outstring;
}

CardList::~CardList()
{
    Card* currPtr = headPtr;
    Card* nextPtr = nullptr;

    // loop until currPtr is at the end of the list
    while(currPtr)
    {
        nextPtr = currPtr->nextCard;
        delete currPtr; --numCards;
        currPtr = nextPtr;
    }
    headPtr = nullptr;
}
