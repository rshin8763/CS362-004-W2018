#ifndef MYTESTFUNCTIONS_H
#define MYTESTFUNCTIONS_H

#include <stdio.h>
#include "dominion.h"

void getCardQuantities(int array[], int size, int cardArray[]);
int inArray(int arr[], int size, int val);
int randomGame(int numPlayers, struct gameState *state);
int myAssert(char *, int *failFlag, int boolean);
void randomHand(int player, int size, struct gameState *state);
void compareStates(int *failFlag, struct gameState *pre, struct gameState *post);
int compareData(void *pre, void *post, int size);
int compareArray(int pre[], int post[], int size);

#endif
