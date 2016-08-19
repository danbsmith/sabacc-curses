#ifndef _SABACC_H
#define _SABACC_H

#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

void display_hand(card* hand, int playerpoints, int computerpoints, char* msg, WINDOW** cardspots, WINDOW* score, WINDOW* msgwindow);

void erase_windows(WINDOW** cardspots, WINDOW* score, WINDOW* msgwindow);

void take_card(card* deck, card* hand);

void discard(card* hand, int cardnum);

void freeze_card(card* hand, int cardnum);

#endif
