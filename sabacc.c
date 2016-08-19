#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "sabacc.h"
#include "deck.h"

void display_hand(card* hand, int playerpoints, int computerpoints, char* msg, WINDOW** cardspots, WINDOW* score, WINDOW* msgwindow) {
  card phand[5];
  int handsize = 0;
  for(int i = 0; i < 5; i++) {
    if((hand + i)->value < 20) {
      phand[handsize] = *(hand + i);
      handsize++;
    }
  }
  for(int i = 0; i < handsize; i++) {
    size_t namelength = strlen(phand[i].name);
    int neededlines = (namelength / 8) + 1;
    box(*(cardspots + i), 0, 0);
    mvwprintw(*(cardspots + i), 1, 1, "%d", phand[i].value);
    mvwprintw(*(cardspots + i), 3, 1,  "%.8s", phand[i].name);
    for(int j = 1; j < neededlines; j++) {
      mvwprintw(*(cardspots + i), 3 + j, 1,  "%.8s", (phand[i].name + (j * 8)));
    }
    if(!phand[i].switchable) {
      mvwprintw(*(cardspots + i), 2, 0, "LOCKED");
    }
    wrefresh(*(cardspots + i));
  }
  box(score, 0, 0);
  mvwprintw(score, 1, 1, "Player: %d vs. Computer: %d", playerpoints, computerpoints);
  wrefresh(score);
  box(msgwindow, 0, 0);
  mvwprintw(msgwindow, 1, 1, "%s", msg);
  wrefresh(msgwindow);
  return;
}

void erase_windows(WINDOW** cardspots, WINDOW* score, WINDOW* msgwindow) {
  for(int i = 0; i < 5; i++) {
    werase(cardspots[i]);
    wborder(cardspots[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(cardspots[i]);
  }
  werase(score);
  wborder(score, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(score);
  werase(msgwindow);
  wborder(msgwindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(msgwindow);
}

void take_card(card* deck, card* hand) {
  int i = 0;
  while((hand + i)->value < 20) {
    i++;
  }
  int j = 0;
  while((deck + j)->value > 20) {
    j++;
  }
  *(hand + i) = *(deck + j);
  (hand + i)->switchable = true;
  (deck + j)->value = 21;
  return;
}

void discard(card* hand, int cardnum) { // Cardnum starts from 0 (player input must be decremented before being passed to this)
  (hand + cardnum)->value = 21;
  (hand + cardnum)->switchable = false;
  return;
}

void freeze_card(card* hand, int cardnum) { // Cardnum starts from 0 (player input must be decremented before being passed to this)
  (hand + cardnum)->switchable = false;
  return;
}
