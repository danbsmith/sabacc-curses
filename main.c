#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <curses.h>
#include "sabacc.h"
#include "deck.h"

int main(int argc, char** argv) {
	int playerpoints = 0;
	int computerpoints = 0;
	initscr();						// Init and setup for curses
	cbreak();							// ^
	noecho();							// ^
	keypad(stdscr, TRUE);	// ^
	WINDOW* pcardspots[5];
	WINDOW* ccardspots[5];
	pcardspots[0] = newwin(12, 10, 5, 0);
	pcardspots[1] = newwin(12, 10, 5, 10);
	pcardspots[2] = newwin(12, 10, 5, 20);
	pcardspots[3] = newwin(12, 10, 5, 30);
	pcardspots[4] = newwin(12, 10, 5, 40);
	ccardspots[0] = newwin(12, 10, 18, 0);
	ccardspots[1] = newwin(12, 10, 18, 10);
	ccardspots[2] = newwin(12, 10, 18, 20);
	ccardspots[3] = newwin(12, 10, 18, 30);
	ccardspots[4] = newwin(12, 10, 18, 40);
	WINDOW* score = newwin(3, 80, 0, 0);
	WINDOW* msgwindow = newwin(6, 80, 31, 0);
	while(playerpoints < 10 && computerpoints < 10) {
		card deck[76];
		gendeck(deck);
		card playerhand[5];
		card computerhand[5];
		deal_hand(deck, playerhand);
		deal_hand(deck, computerhand);
		bool handdone = false;
		mvwprintw(msgwindow, 1, 1, "Thisisatest");
		while(!handdone) {
			int vals[5];
			int cards;
			int cardnum;
			bool playercalled = false;
			bool computercalled = false;
			bool validcmd = false;
			while(!validcmd) {
				display_hand(playerhand, computerhand, playerpoints, computerpoints, "Press 'd' to discard, 't' to take a card, k to place a card in the interference field or c to call", pcardspots, ccardspots, score, msgwindow);
				int act = wgetch(score);
				validcmd = true;
				switch(act) {
					case 'T':
					case 't':
						take_card(deck, playerhand);
						break;
					case 'D':
					case 'd':
						werase(msgwindow);
						cards = get_hand_vals(playerhand, vals);
						mvwprintw(msgwindow, 1, 1, "Pick number for card to discard: ");
						for(int i = 1; i < cards; i++) {
							wprintw(msgwindow, "%d: %d?  ", i, vals[i]);
						}
						wrefresh(msgwindow);
						cardnum = wgetch(score);
						cardnum = cardnum - 48;
						discard(playerhand, cardnum - 1);
						break;
					case 'K':
					case 'k':
						werase(msgwindow);
						cards = get_hand_vals(playerhand, vals);
						mvwprintw(msgwindow, 1, 1, "Pick number for card to freeze: ");
						for(int i = 1; i < cards; i++) {
							wprintw(msgwindow, "%d: %d?  ", i , vals[i]);
						}
						wrefresh(msgwindow);
						cardnum = wgetch(score);
						cardnum = cardnum - 48;
						freeze_card(playerhand, cardnum);
						break;
					case 'C': // Call hand (player)
					case 'c':
						playercalled = true;
					break;
					default:
						werase(msgwindow);
						mvwprintw(msgwindow, 1, 1, "Invalid command.  Press any key to try again.");
						wrefresh(msgwindow);
						wgetch(score);
						validcmd = false;
				}
			}
			if(computercalled) {
				vals[5];
				cards = get_hand_vals(playerhand, vals);
				if(random() % 2) {
					switch_card(playerhand, deck);
				}
				if(random() % 2) {
					switch_card(computerhand, deck);
				}
				if(cards > 3) {
					werase(msgwindow);
					mvwprintw(msgwindow, 1, 1, "You have too many cards.  Please choose one to discard: ");
					for(int i = 1; i < cards; i++) {
						wprintw(msgwindow, "%d: %d?  ", i, vals[i]);
					}
					wrefresh(msgwindow);
					cardnum = wgetch(score);
					cardnum = cardnum - 48;
					discard(playerhand, cardnum - 1);
				}
				handdone = true;
				end_hand(playerhand, computerhand, deck, &playerpoints, &computerpoints, pcardspots, ccardspots, score, msgwindow);
			}
			else {
				computer_turn(); // TODO: Create some AI for this
				//TODO: This is where it will announce the AI's action
				vals[5];
				cards = get_hand_vals(playerhand, vals);
				if(cards > 3) {
					werase(msgwindow);
					mvwprintw(msgwindow, 1, 1, "You have too many cards.  Please choose one to discard: ");
					for(int i = 1; i < cards; i++) {
						wprintw(msgwindow, "%d: %d?  ", i, vals[i]);
					}
					wrefresh(msgwindow);
					cardnum = wgetch(score);
					cardnum = cardnum - 48;
					discard(playerhand, cardnum - 1);
				}
				if(playercalled) {
					if(random() % 2) {
						switch_card(playerhand, deck);
					}
					if(random() % 2) {
						switch_card(computerhand, deck);
					}
					handdone = true;
					end_hand(playerhand, computerhand, deck, &playerpoints, &computerpoints, pcardspots, ccardspots, score, msgwindow);
				}
				else {
					if(random() % 2) {
						switch_card(playerhand, deck);
					}
					if(random() % 2) {
						switch_card(computerhand, deck);
					}

				}
			}
		}
	}
}
