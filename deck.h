#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum CardSuit {
  STAVES,
  SABRES,
  COINS,
  FLASKS,
  FACE
} cardsuit;

typedef struct Card {
  int value;
  cardsuit suit;
  char name[64];
  bool switchable;
} card;

card* gendeck(card* deck);

void deal_hand(card* deck, card* hand);
#endif
