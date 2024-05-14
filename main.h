#ifndef MAIN_H
#define MAIN_H

#define NUM_CARDS_IN_STANDARD_DECK 52 // no jokers for now
#define HAND_MAX_SIZE 52
#define NUM_SUITS 4
#define NUM_CARDS_IN_SUITS (NUM_CARDS_IN_STANDARD_DECK / NUM_SUITS)

#define ERROR_FIXME -1
#define NULL_CHAR '\0'

#define CARD_WIDTH 12
#define CARD_HEIGHT 10

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum Suit
{
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3,
};

/*
    These are not blackjack values
    Just simply for iterating through
*/
enum CardValue
{
    Ace = 0,
    Two = 1,
    Three = 2,
    Four = 3,
    Five = 4,
    Six = 5,
    Seven = 6,
    Eight = 7,
    Nine = 8,
    Ten = 9,
    Jack = 10,
    Queen = 11,
    King = 12,
};

typedef struct card
{
    struct card *next;
    char *suit;
    char *turned_suit;
    char *value;
    char *turned_value;
} Card;

typedef struct
{
    int max;
    int size;
    Card *cards;
    char *name;
} Hand;

typedef struct
{
    int max;
    int size;
    Card *cards;
} Deck;

void PrintCard(Card *, bool);
void PrintCards(Card *, bool);

void FreeCard(Card *);
void FreeAllCards(Card *);
Card *InitCard(char *, char *);

int PutCardInHand(Hand *, Card *);
Card *GetTopOfDeck(Deck *);

int PlaceCardInDeck(Deck *, Card *, char);

Hand *InitHand(char *);
void FreeHand(Hand *);

Deck *InitDeck();
void ShuffleDeck(Deck *);
void FreeDeck(Deck *);

#endif
