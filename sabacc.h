#ifndef _SABACC_H
#define _SABACC_H

#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

void display_hand(card* playerhand, card* computerhand, int playerpoints, int computerpoints, char* msg, WINDOW** pcardspots, WINDOW** ccardspots, WINDOW* score, WINDOW* msgwindow);

void erase_windows(WINDOW** cardspots1, WINDOW** cardspots2, WINDOW* score, WINDOW* msgwindow);

void take_card(card* deck, card* hand);

void discard(card* hand, int cardnum);

void freeze_card(card* hand, int cardnum);

void switch_card(card* deck, card* hand);

int handeval(card* hand1, card* hand2);

void end_hand(card* playerhand, card* computerhand, card* deck, int* playerpoints, int* computerpoints, WINDOW** cardspots1, WINDOW** cardspots2, WINDOW* score, WINDOW* msgwindow);

void computer_turn();

#endif
