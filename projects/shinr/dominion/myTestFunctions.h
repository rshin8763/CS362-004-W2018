#ifndef MYTESTFUNCTIONS_H
#define MYTESTFUNCTIONS_H

#include <stdio.h>
#include "dominion.h"

int inArray(int arr[], int size, int val);
int randomGame(int numPlayers, struct gameState *state);
int myAssert(int *failFlag, int boolean);
int randomHand(int player, int size, struct gameState *state);
int compareStates(int *failFlag, struct gameState *pre, struct gameState *post);

#endif
