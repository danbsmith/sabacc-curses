#ifndef _SABACC_H
#define _SABACC_H

#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

void display_hand(card* hand, int playerpoints, int computerpoints, char* msg, WINDOW** cardspots, WINDOW* score, WINDOW* msgwindow);

#endif
