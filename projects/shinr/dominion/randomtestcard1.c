/*********************************************************************
 ** Program Filename:  cardtest1.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the smithy card in dominion.c
 *********************************************************************/
#include "myTestFunctions.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_DECK 500
#define debug 0

// Global Testing Flags


// Deck is updated
int tf_playerDeckChanged = 1;
// Hand is updated with cards missing from Deck
int tf_handUpdate = 1;
// Action value is the same
int tf_actionValue = 1;
// Played pile has extra card
int tf_playedPile = 1;
// Supply cards are the same
int tf_supplyCards = 1;
// Other player's state is invariant
int tf_discardPile = 1;
// All player's victory point states are the same
int tf_victoryState = 1;

int testFail = 0;

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int main(){

    srand(time(0));
    struct gameState post;
    struct gameState pre;


    printf("------TEST FOR SMITHY--------");

    int numPlayers = 3;
        
    //initialize random game
    randomGame(numPlayers, &pre);

    //set prerequisite conditions
    int currentPlayer = pre.whoseTurn;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0;
    int bonus = -5;
    int handPos = rand()%pre.handCount[currentPlayer];

    //set card int hand position to smithy
    post.hand[currentPlayer][handPos] = smithy;

    printf("handPos:%d\n", handPos);

    //save game state
    memcpy(&pre, &post, sizeof(struct gameState));

    printf("pre:%d\n", pre.handCount[currentPlayer]);
    printf("post:%d\n", post.handCount[currentPlayer]);

    cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);

    
    printf("pre:%d\n", pre.handCount[currentPlayer]);
    printf("post:%d\n", post.handCount[currentPlayer]);

    // Hand should have 2 extra cards. +3 then the smithy discard
    assert (pre.handCount[currentPlayer] + 2 == post.handCount[currentPlayer]);

    // Deck and discard together should have 2 fewer cards
    assert (pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] == post.discardCount[currentPlayer] + post.deckCount[currentPlayer] + 2);

    printf("ALL TESTS SUCCESSFUL\n");
    return 0;
}


