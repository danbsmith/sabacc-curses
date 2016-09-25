#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "deck.h"

const int cardvals[76] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  -2, -2,
  -8, -8,
  -11, -11,
  -13, -13,
  -14, -14,
  -15, -15,
  -17, -17,
  0, 0
};

const cardsuit suits[76] = {
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  STAVES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  SABRES,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  COINS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FLASKS,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE,
  FACE
};

card* gendeck(card* deck) {
  for(int i = 0; i < 76; i++) {
    deck[i].value = 21;
  }
  srandom(time(NULL));
  int scramble = random() % 76;
  int cardsset = 0;
  while(cardsset < 76) {
    while(deck[scramble].value < 20) {scramble = random() % 76;}\
    deck[scramble].value = cardvals[cardsset];
    deck[scramble].suit = suits[cardsset];
    if(deck[scramble].value <= 0) {
      switch(cardvals[cardsset]) {
        case 0:
          snprintf(deck[scramble].name, 64, "The Idiot");
          break;
        case -2:
          snprintf(deck[scramble].name, 64, "Queen of Air and Darkness");
          break;
        case -8:
          snprintf(deck[scramble].name, 64, "Endurance");
          break;
        case -11:
          snprintf(deck[scramble].name, 64, "Balance");
          break;
        case -13:
          snprintf(deck[scramble].name, 64, "Demise");
          break;
        case -14:
          snprintf(deck[scramble].name, 64, "Moderation");
          break;
        case -15:
          snprintf(deck[scramble].name, 64, "The Evil One");
          break;
        case -17:
          snprintf(deck[scramble].name, 64, "The Star");
          break;
      }
    }
    else if(deck[scramble].value < 12) {
      char suit[8];
      switch(suits[cardsset]) {
      case STAVES:
        sprintf(suit, "Staves");
        break;
      case SABRES:
        sprintf(suit, "Sabres");
        break;
      case COINS:
        sprintf(suit, "Coins");
        break;
      case FLASKS:
        sprintf(suit, "Flasks");
        break;
      }
      snprintf(deck[scramble].name, 64, "%d of %s", deck[scramble].value, suit);
    }
    else {
      char suit[8];
      char face[10];
      switch(suits[cardsset]) {
      case STAVES:
        sprintf(suit, "Staves");
        break;
      case SABRES:
        sprintf(suit, "Sabres");
        break;
      case COINS:
        sprintf(suit, "Coins");
        break;
      case FLASKS:
        sprintf(suit, "Flasks");
        break;
      }
      switch(cardvals[cardsset]) {
        case 12:
          sprintf(face, "Commander");
          break;
        case 13:
          sprintf(face, "Mistress");
          break;
        case 14:
          sprintf(face, "Master");
          break;
        case 15:
          sprintf(face, "Ace");
          break;
      }
      snprintf(deck[scramble].name, 64, "%s of %s", face, suit);
    }
    cardsset++;
  }
  return deck;
}

void deal_hand(card* deck, card* hand) {
  int i = 0;
  while((deck + i)->value > 20) {
    i++;
  }
  *(hand + 0) = *(deck + i + 0);
  (deck + i + 0)->value = 21;
  (hand + 0)->switchable = true;
  *(hand + 1) = *(deck + i + 1);
  (hand + 1)->switchable = true;
  (deck + i + 1)->value = 21;
  *(hand + 2) = *(deck + i + 2);
  (hand + 2)->switchable = true;
  (deck + i + 2)->value = 21;
  (hand + 3)->value = 21;
  (hand + 4)->value = 21;
  return;
}

int get_hand_vals(card* hand, int* vals) {
  for(int i = 0; i < 5; i++) {
    if(hand[i].value < 21) {
      vals[cards] = hand[i].value;
      cards++;
    }
  }
  return cards;
}
