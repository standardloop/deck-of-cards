#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "./main.h"

int placeCardOnBottomOfDeck(Deck *, Card *);
int placeCardOnTopOfDeck(Deck *, Card *);
int placeCardRandomlyInDeck(Deck *, Card *);
void swapCardsInDeck(Deck *, int, int);

bool isDeckEmpty(Deck *);

bool isDeckEmpty(Deck *deck)
{
    return (deck->size == 0 && deck->cards == NULL);
}
void swapCardsInDeck(Deck *deck, int swap_index_1, int swap_index_2)
{
    if (deck == NULL || (swap_index_1 == swap_index_2) || isDeckEmpty(deck) || deck->cards == NULL ||
        swap_index_1 < 0 || swap_index_2 < 0 || swap_index_1 > deck->size || swap_index_2 > deck->size)
    {
        //printf("Invalid inputs to swapCardsInDeck\n");
        return;
    }
    if (swap_index_1 > swap_index_2)
    {
        swapCardsInDeck(deck, swap_index_2, swap_index_1);
        return;
    }
    // printf("Swapping index %d and %d!\n", swap_index_1, swap_index_2);
    Card *swap_index_1_ptr = deck->cards;
    Card *swap_index_1_prev_ptr = NULL;
    Card *swap_index_2_ptr = deck->cards;
    Card *swap_index_2_prev_ptr = NULL;

    for (int i = 0; i < swap_index_1; i++)
    {
        swap_index_1_prev_ptr = swap_index_1_ptr;
        swap_index_1_ptr = swap_index_1_ptr->next;
    }
    for (int i = 0; i < swap_index_2; i++)
    {
        swap_index_2_prev_ptr = swap_index_2_ptr;
        swap_index_2_ptr = swap_index_2_ptr->next;
    }

    if (swap_index_1_ptr == NULL || swap_index_2_ptr == NULL)
    {
        //printf("Couldn't located nodes at index in swapCardsInDeck\n");
        return;
    }
    // only need to check head for swap_index_1 because
    // swap_index_1 is always less than swap_index_2
    if (swap_index_1_prev_ptr == NULL && swap_index_1_ptr == deck->cards)
    {
        deck->cards = swap_index_2_ptr;
    }
    else
    {
        swap_index_1_prev_ptr->next = swap_index_2_ptr;
    }

    swap_index_2_prev_ptr->next = swap_index_1_ptr;
    Card *temp = swap_index_1_ptr->next;
    swap_index_1_ptr->next = swap_index_2_ptr->next;
    swap_index_2_ptr->next = temp;
}

void ShuffleDeck(Deck *deck)
{
    if (deck == NULL || isDeckEmpty(deck))
    {
        //printf("Invalid inputs to ShuffleDeck\n");
        return;
    }
    srand(time(NULL));
    for (int i = deck->size - 1; i > 0; i--)
    {
        int j = rand() % (deck->size);
        if (j == i)
        {
            j++;
            if (j == deck->size - 1)
            {
                j -= 2;
            }
        }
        (void)swapCardsInDeck(deck, i, j);
    }
}

Deck *InitDeck()
{
    Deck *deck = malloc(sizeof(Deck));
    if (deck == NULL)
    {
        return NULL;
    }
    deck->max = NUM_CARDS_IN_STANDARD_DECK;
    deck->size = 0;
    deck->cards = NULL;

    for (enum Suit curr_suit = Clubs; curr_suit < NUM_SUITS; curr_suit++)
    {
        char *char_suit = NULL;
        switch (curr_suit)
        {
        case Clubs:
            char_suit = "♣";
            break;
        case Diamonds:
            char_suit = "♦";
            break;
        case Hearts:
            char_suit = "♥";
            break;
        case Spades:
            char_suit = "♠";
            break;
        default:
            break;
        }

        for (enum CardValue enum_card_value = Ace; enum_card_value < NUM_CARDS_IN_SUITS; enum_card_value++)
        {
            char *char_card_value;
            switch (enum_card_value)
            {
            case Ace:
                char_card_value = "A";
                break;
            case Two:
                char_card_value = "2";
                break;
            case Three:
                char_card_value = "3";
                break;
            case Four:
                char_card_value = "4";
                break;
            case Five:
                char_card_value = "5";
                break;
            case Six:
                char_card_value = "6";
                break;
            case Seven:
                char_card_value = "7";
                break;
            case Eight:
                char_card_value = "8";
                break;
            case Nine:
                char_card_value = "9";
                break;
            case Ten:
                // char_card_value = "10";
                char_card_value = "T";
                break;
            case Jack:
                char_card_value = "J";
                break;
            case Queen:
                char_card_value = "Q";
                break;
            case King:
                char_card_value = "K";
                break;
            default:
                break;
            }
            Card *card = InitCard(char_suit, char_card_value);
            if (card == NULL)
            {
                // FIXME mem leak
                printf("Couldn't allocate memory for a card\n");
                exit(EXIT_FAILURE);
                return NULL;
            }
            (void)PlaceCardInDeck(deck, card, 'b');
        }
    }

    if (deck->cards == NULL)
    {
        FreeDeck(deck);
        return NULL;
    }
    if (deck->size != NUM_CARDS_IN_STANDARD_DECK)
    {
        printf("[FATAL]: couldn't create enough cards for deck of size: %d != %d\n", deck->size, NUM_CARDS_IN_STANDARD_DECK);
        exit(1);
    }

    return deck;
}

int PlaceCardInDeck(Deck *deck, Card *card, char mode)
{
    switch (mode)
    {
    case 't':
    case 'T':
        return placeCardOnTopOfDeck(deck, card);
    case 'b':
    case 'B':
        return placeCardOnBottomOfDeck(deck, card);
    case 'r':
    case 'R':
        return placeCardRandomlyInDeck(deck, card);
    default:
        printf("Unsupported mode for placing card in deck");
        return ERROR_FIXME;
    }
}

int placeCardOnBottomOfDeck(Deck *deck, Card *card)
{
    if (deck == NULL || card == NULL)
    {
        return ERROR_FIXME;
    }
    Card *head = deck->cards;
    if (head == NULL)
    {
        deck->cards = card;
        deck->size = 1;
        return deck->size;
    }
    Card *last = deck->cards;

    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = card;
    deck->size++;

    return deck->size;
}

int placeCardOnTopOfDeck(Deck *deck, Card *card)
{
    if (deck == NULL || card == NULL)
    {
        return ERROR_FIXME;
    }
    Card *head = deck->cards;
    if (head == NULL)
    {
        deck->cards = card;
        deck->size = 1;
        return deck->size;
    }
    card->next = head;
    deck->cards = card;
    deck->size++;

    return deck->size;
}

int placeCardRandomlyInDeck(Deck *deck, Card *card)
{
    if (deck == NULL || card == NULL)
    {
        return ERROR_FIXME;
    }
    return deck->size;
}

void FreeDeck(Deck *deck)
{
    if (deck == NULL)
    {
        return;
    }
    if (deck->cards != NULL)
    {
        (void)FreeAllCards(deck->cards);
    }
    free(deck);
}

Card *GetTopOfDeck(Deck *deck)
{
    if (deck == NULL || isDeckEmpty(deck))
    {
        return NULL;
    }
    Card *top_card = deck->cards;
    if (deck->size == 1)
    {
        deck->cards = NULL;
    }
    else
    {
        deck->cards = deck->cards->next;
    }
    deck->size--;
    top_card->next = NULL;
    return top_card;
}
