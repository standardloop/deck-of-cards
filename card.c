#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./main.h"

Card *InitCard(char *suit, char *value)
{
    Card *card = malloc(sizeof(Card));
    if (card == NULL)
    {
        return NULL;
    }
    card->suit = suit;
    card->turned_suit = suit;

    card->value = value;
    if (strcmp(value, "A") == 0)
    {
        card->turned_value = "Ɐ";
    }
    else if (strcmp(value, "2") == 0)
    {
        card->turned_value = "ᘔ";
    }
    else if (strcmp(value, "3") == 0)
    {
        card->turned_value = "Ɛ";
    }
    else if (strcmp(value, "4") == 0)
    {
        card->turned_value = "߈";
    }
    else if (strcmp(value, "5") == 0)
    {
        card->turned_value = "ဌ";
    }
    else if (strcmp(value, "6") == 0)
    {
        card->turned_value = "9";
    }
    else if (strcmp(value, "7") == 0)
    {
        // card->turned_value = "ㄥ";
        card->turned_value = "L";
    }
    else if (strcmp(value, "8") == 0)
    {
        card->turned_value = "8";
    }
    else if (strcmp(value, "9") == 0)
    {
        card->turned_value = "6";
    }
    // else if (strcmp(value, "10") == 0)
    // {
    //     card->turned_value = "⇂0";
    // }
    else if (strcmp(value, "T") == 0)
    {
        // card->turned_value = "上";
        card->turned_value = "⊥"; // ⊥
    }
    else if (strcmp(value, "J") == 0)
    {
        card->turned_value = "ᒋ";
    }
    else if (strcmp(value, "Q") == 0)
    {
        card->turned_value = "ტ";
    }
    else if (strcmp(value, "K") == 0)
    {
        card->turned_value = "ꓘ";
    }

    card->next = NULL;
    return card;
}

void FreeCard(Card *card)
{
    if (card == NULL)
    {
        return;
    }
    free(card);
}

void FreeAllCards(Card *head)
{
    Card *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        FreeCard(temp);
    }
}

void PrintCards(Card *head, bool simple_print)
{
    while (head != NULL)
    {
        (void)PrintCard(head, simple_print);
        head = head->next;
    }
}

void PrintCard(Card *card, bool simple_print)
{
    if (simple_print)
    {
        printf("%s %s\n", card->value, card->suit);
        return;
    }

    if (card == NULL)
    {
        return;
    }
    // size_t card_value_len = strlen(card->suit);
    // int card_value_len = (int)strlen(card->value);
    // int card_turned_value_len = (int)strlen(card->turned_value);
    // int card_turned_suit_len = (int)strlen(card->turned_suit);
    // int card_suit_len = (int)strlen(card->suit);

    for (int h = 0; h < CARD_HEIGHT; h++)
    {
        for (int w = 0; w < CARD_WIDTH; w++)
        {
            if (h == 0 || h == CARD_HEIGHT - 1)
            {
                if (w == 0 || w == CARD_WIDTH - 1)
                {
                    printf(" ");
                }
                else if (h == 0)
                {
                    printf("_");
                }
                else if (h == CARD_HEIGHT - 1)
                {
                    printf("~");
                }
            }
            else
            {
                if (w == 0 || w == CARD_WIDTH - 1)
                {
                    printf("|");
                }
                else if (w == 1 && h == 1)
                {
                    printf("%s", card->value);
                }
                else if (w == 2 && h == 2)
                {
                    printf("%s", card->suit);
                }
                else if (w == (CARD_WIDTH - 3) && h == (CARD_HEIGHT - 3))
                {
                    printf("%s", card->turned_suit);
                }
                else if (w == (CARD_WIDTH - 2) && h == (CARD_HEIGHT - 2))
                {
                    printf("%s", card->turned_value);
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    // exit(1);
}
