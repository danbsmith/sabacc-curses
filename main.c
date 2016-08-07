#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <curses.h>
#include "sabacc.h"
#include "deck.h"

int main(int argc, char** argv) {
	card emptydeck[76];
	card* deck = gendeck(emptydeck);
	for(int i = 0; i < 76; i++) {
		printf("The %s has value %d\n", deck[i].name, deck[i].value);
	}
	return 0;
}
