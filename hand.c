#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./main.h"

Hand *InitHand(char *name)
{
    if (name == NULL)
    {
        return NULL;
    }
    Hand *hand = malloc(sizeof(Hand));
    if (hand == NULL)
    {
        return NULL;
    }
    hand->max = HAND_MAX_SIZE;
    hand->size = 0;
    hand->cards = NULL;
    hand->name = name;

    return hand;
}

bool isHandEmpty(Hand *hand)
{
    return (hand->size == 0 && hand->cards == NULL);
}

int PutCardInHand(Hand *hand, Card *card)
{
    // Places in bottom of hand for now
    if (hand == NULL || hand == NULL)
    {
        return ERROR_FIXME;
    }
    Card *head = hand->cards;
    if (head == NULL)
    {
        hand->cards = card;
        hand->size = 1;
        return hand->size;
    }
    Card *last = hand->cards;

    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = card;
    hand->size++;

    return hand->size;
}

void FreeHand(Hand *hand)
{
    if (hand == NULL)
    {
        return;
    }
    if (hand->cards != NULL)
    {
        FreeAllCards(hand->cards);
    }
    if (hand->name != NULL)
    {
        // hand name wasn't allocated
    }
    free(hand);
}
