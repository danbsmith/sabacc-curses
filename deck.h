#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdlib.h>

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
} card;

card* gendeck(card* deck);

void dealhand(card* deck, card* hand);
#endif
