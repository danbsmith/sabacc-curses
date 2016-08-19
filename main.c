#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <curses.h>
#include "sabacc.h"
#include "deck.h"

int main(int argc, char** argv) {
	int playerpoints = 0;
	int computerpoints = 0;
	card deck[76];
	gendeck(deck);
	card playerhand[5];
	deal_hand(deck, playerhand);
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	WINDOW* cardspots[5];
	cardspots[0] = newwin(12, 10, 5, 0);
	cardspots[1] = newwin(12, 10, 5, 10);
	cardspots[2] = newwin(12, 10, 5, 20);
	cardspots[3] = newwin(12, 10, 5, 30);
	cardspots[4] = newwin(12, 10, 5, 40);
	WINDOW* score = newwin(3, 80, 0, 0);
	WINDOW* msgwindow = newwin(6, 80, 20, 0);
	display_hand(playerhand, playerpoints, computerpoints, "TEMPORARY MESSAGE", cardspots, score, msgwindow);
	wgetch(score);
	erase_windows(cardspots, score, msgwindow);
	take_card(deck, playerhand);
	display_hand(playerhand, playerpoints, computerpoints, "DREW 1 CARD", cardspots, score, msgwindow);
	wgetch(score);
	erase_windows(cardspots, score, msgwindow);
	discard(playerhand, 3);
	display_hand(playerhand, playerpoints, computerpoints, "DISCARDED PREVIOUS CARD", cardspots, score, msgwindow);
	wgetch(score);
	erase_windows(cardspots, score, msgwindow);
	discard(playerhand, 2);
	display_hand(playerhand, playerpoints, computerpoints, "DISCARDED ANOTHER CARD", cardspots, score, msgwindow);
	wgetch(score);
	erase_windows(cardspots, score, msgwindow);
	freeze_card(playerhand, 0);
	display_hand(playerhand, playerpoints, computerpoints, "FROZE A CARD", cardspots, score, msgwindow);
	wgetch(score);
	erase_windows(cardspots, score, msgwindow);
	for(int i = 0; i < 5; i++) {
		delwin(cardspots[i]);
	}
	delwin(score);
	delwin(msgwindow);
	endwin();
	return 0;
/*	while(playerpoints <= 10 && computerpoints <= 10) {
		card deck[76];
		deck = gendeck(deck);
		card playerhand[5];
		card computerhand[5];
		deal_hand(deck, playerhand);
		deal_hand(deck, computerhand);
		bool handdone = false;
		while(!handdone) {
			bool playercalled = false;
			bool computercalled = false;
		}
	}*/
}
