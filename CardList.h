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

        unsigned int numCards;

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
         * Removes the Card at the top of the list and returns a pointer to it.
         * Note that this function does not destroy the Card nor free the memory
         * taken by it.
         * @return The pointer to the first Card in the list. If the list is
         * empty, return nullptr.
         */
        Card* pop();

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
         * Transfers cards in the card list to another card list. This
         * function simply removes the desired amount of cards in the list that
         * calls this function and transfers them to other. No new cards
         * are created.
         * @param other The list to transfer all cards to.
         * @param amount The number of cards to transfer.
         * @return True if the transfer was successful, false if it was not
         * successful (for example, if there were no cards to transfer to
         * begin with).
         */
        bool transfer(CardList &other, unsigned int amount);

        /**
         * Shuffles the list in place.
         */
        void shuffle();

        /**
         * Getter function for numCards.
         * @return The length of the list; the amount of cards currently
         * held by the list.
         */
        unsigned int size() const {return numCards;}
};

#endif//CARDLIST_H
