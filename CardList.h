/**
 * CardList class header file.
 * CECS 275 - Fall 2021
 * @author Rodrigo Becerril Ferreyra
 * @author Ethan Hua
 * @version 1
 */

#ifndef CARDLIST_H
#define CARDLIST_H

/**
 * CardList is a singly-linked list class that can store all of the cards in a
 * standard French 52-card deck. It implements several functions including
 * shuffle, which randomizes the order of the deck.
 */
class CardList
{
    public:
        enum listOfSuits {CLUBS, DIAMONDS, HEARTS, SPADES};

    private:
        struct Card
        {
            listOfSuits suit;
            // note that 1 is A, 11 is J, 12 is Q, and 13 is K
            unsigned int value;
            Card* nextCard;
        };
        Card* headPtr;

    public:
        /**
         * The constructor simply initializes an empty list.
         */
        CardList() {headPtr = nullptr;}

        /**
         * The destructor deletes all cards in the list and frees all memory.
         */
        ~CardList();

        /**
         * Creates a card and adds it to the front of the list. Checks if an
         * identical card exists; if so, no card is created.
         * @param cardSuit The suit of the card (CLUBS, DIAMONDS, HEARTS, or
         * SPADES).
         * @param cardValue The value of the card (between 1 and 13 inclusive).
         * @return True if a card was created, false otherwise. Note that if
         * either of the parameters are out of range.
         */
        bool createCard(enum listOfSuits cardSuit, unsigned int cardValue);

        /**
         * Adds an existing card to the front of the list. This function does
         * not create a new card. THIS FUNCTION DOES NOT CHECK FOR THE EXISTENCE
         * OF A Card OBJECT THAT IS POINTED TO BY cardPtr!!!
         * This is very important, because many things can go
         * wrong if a random pointer is put into this function.
         * However, if cardPtr is nullptr, nothing is put onto the list.
         * @param cardPtr The pointer to the Card object to add to the list.
         */
        void addCard(Card* cardPtr);

        /**
         * Searches the list, removes the Card that matches the parameters
         * provided, and returns the pointer to the object. Note that this
         * function does not destroy the Card nor free the memory taken by it.
         * @param cardSuit The suit of the card (CLUBS, DIAMONDS, HEARTS, or
         * SPADES).
         * @param cardValue The value of the card (between 1 and 13 inclusive).
         * @return The pointer to the Card (if found). If the requested Card was
         * not found, returns nullptr instead.
         */
        Card* pop(enum listOfSuits cardSuit, unsigned int cardValue);

        /**
         * Removes the Card at the top of the list and returns a pointer to it.
         * Note that this function does not destroy the Card nor free the memory
         * taken by it.
         * @return The pointer to the first Card in the list. If the list is
         * empty, return nullptr.
         */
        Card* pop();

        /**
         * Shuffles the list in place.
         */
        void shuffle();
};

#endif//CARDLIST_H
