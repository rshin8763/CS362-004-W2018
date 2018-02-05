#ifndef MYTESTFUNCTIONS_H
#define MYTESTFUNCTIONS_H

#include <stdio.h>
#include "dominion.h"

void getCardQuantities(int array[], int size, int cardArray[]);
int inArray(int arr[], int size, int val);
int randomGame(int numPlayers, struct gameState *state);
int myAssert(char *, int *failFlag, int boolean);
int randomHand(int player, int size, struct gameState *state);
int compareStates(int *failFlag, struct gameState *pre, struct gameState *post);

#endif
