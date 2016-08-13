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
