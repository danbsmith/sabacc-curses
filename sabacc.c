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

void switch_card(card* deck, card* hand) {
  int switchable_cards = 0;
  for(int i = 0; i < 5; i++) {
    if(hand[i].value < 21 && hand[i].switchable) {switchable_cards++;}
  }
  if(switchable_cards == 0) {return;}
  int hand_index = random() % 5;
  while(!((hand[hand_index].value < 21) && (hand[hand_index].switchable))) {hand_index = random() % 5;}
  int deck_index = random() % 76;
  while(!(deck[deck_index].value < 21)) {deck_index = random() % 76;}
  card tmpcard = hand[hand_index];
  hand[hand_index] = deck[deck_index];
  deck[deck_index] = tmpcard;
  return;
}

/*
 * Returns the number of the hand which will win, or 0 in case of a tie
 */

int handeval(card* hand1, card* hand2) {
  int winner;
  int hand1_vals[5];
  int hand2_vals[5];
  int hand1_tot, hand2_tot;
  int hand1_size = get_hand_vals(hand1, hand1_vals);
  int hand2_size = get_hand_vals(hand2, hand2_vals);
  for(int i = 0; i < hand1_size; i++) {
    hand1_tot = hand1_tot + hand1_vals[i];
  }
  for(int i = 0; i < hand2_size; i++) {
    hand2_tot = hand2_tot + hand2_vals[i];
  }
  int hand1_diff = hand1_tot - 23;
  int hand2_diff = hand2_tot - 23;
  if(hand1_diff < hand2_diff) {
    if(hand2_diff == 0) {winner = 2;}
    else if(hand2_diff > 0) {winner = 1;}
    else {
      if(hand1_diff == -46) {winner = 1;}
      else                  {winner = 2;}
    }
  }
  else if(hand1_diff > hand2_diff) {
    if(hand1_diff == 0) {winner = 1;}
    else if(hand2_diff > 0) {winner = 2;}
    else {
      if(hand2_diff == -46) {winner = 2;}
      else                  {winner = 1;}
    }
  }
  else {winner = 0;}
  // Detect idiots arrays (special case)
  uint8_t hand1_idiots = 0;
  uint8_t hand2_idiots = 0;
  if(hand1_size == 3) {
    for(int i = 0; i < 3; i++) {
      if(hand1_vals[i] == 0) {hand1_idiots = hand1_idiots | 1;}
      if(hand1_vals[i] == 2) {hand1_idiots = hand1_idiots | 2;}
      if(hand1_vals[i] == 3) {hand1_idiots = hand1_idiots | 4;}
    }
  }
  if(hand2_size == 3) {
    for(int i = 0; i < 3; i++) {
      if(hand2_vals[i] == 0) {hand2_idiots = hand2_idiots | 1;}
      if(hand2_vals[i] == 2) {hand2_idiots = hand2_idiots | 2;}
      if(hand2_vals[i] == 3) {hand2_idiots = hand2_idiots | 4;}
    }
  }
  if(hand1_idiots == 7) {winner = 1;}
  if(hand2_idiots == 7) {winner = 2;}
  if(hand1_idiots == 7 && hand2_idiots == 7) {winner = 0;}
  return winner;
}
