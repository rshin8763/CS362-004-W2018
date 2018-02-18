/*********************************************************************
 ** Program Filename:  cardtest1.c
 ** Author: Ryan Shin
 ** Date: 2/04/18
 ** Description: This is a unit test for the great_hall card in dominion.c
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

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int main(){
    int overallFail = 0;
    int testFail;
    int testCount;
    int firstFail = 1;
    int i;

    //// Test flags
    // Deck is updated
    int tf_deckUpdate = 0;
    // Hand is updated with cards missing from Deck
    int tf_handUpdate = 0;
    // Action value is the same
    int tf_actionValue = 0;
    // Other player's state is invariant
    int tf_otherPlayerState = 0;
    // All player's victory point states are the same
    int tf_otherStates = 0;
    // Embargo tokens are not changed
    int tf_embargo = 0;
    // Supply cards are not changed
    int tf_supply = 0;


    printf("------TEST FOR GREAT HALL------\n");
    for (testCount = 0; testCount < 10000; ++testCount){
        testFail = 0;

        srand(time(0));
        struct gameState post;
        struct gameState pre;

        // between 2 and MAX_PLAYERS players
        int numPlayers = rand()%(MAX_PLAYERS-1) + 2;

        //initialize random game
        randomState(numPlayers, &post);

        //set prerequisite conditions
        int testPlayer = post.whoseTurn;
        int choice1, choice2, choice3;
        choice1 = choice2 = choice3 = 0;
        int bonus = -5;
        int handPos = rand()%post.handCount[testPlayer];

        //set card int hand position to great_hall
        post.hand[testPlayer][handPos] = great_hall;

        //save game state
        memcpy(&pre, &post, sizeof(struct gameState));

        // Apply card effect
        cardEffect(great_hall, choice1, choice2, choice3, &post, handPos, &bonus);

        // Hand should have the same number of cards. +1 then the great_hall discard
        if(!(pre.handCount[testPlayer] == post.handCount[testPlayer])){
            tf_handUpdate++;
            testFail = 1;
        }

        // Action value should be incremented
        if ( !( pre.numActions + 1 == post.numActions)){
            tf_actionValue++;
            testFail = 1;
        }

        // Due to the fact that an empty deck will cause shuffling, the invariant is that deck + played/discard should have 2 fewer cards due to the drawn cards being
        // in hand.
        if (!((pre.deckCount[testPlayer] + pre.discardCount[testPlayer] + pre.playedCardCount) == (post.discardCount[testPlayer] + post.deckCount[testPlayer] + post.playedCardCount ))){
            tf_deckUpdate++;
            testFail = 1;
        }

        //Other player's cards are not changed
        if (testOtherPlayerStates(&pre, &post, testPlayer)){
            tf_otherPlayerState++;
            testFail = 1;
        }
        //Check other state variables
        int stateFlag = 0;
        if ( !( pre.numPlayers == post.numPlayers))
            stateFlag = 1;
        if ( !( pre.outpostPlayed == post.outpostPlayed))
            stateFlag = 1;
        if ( !( pre.outpostTurn == post.outpostTurn))
            stateFlag = 1;
        if ( !( pre.coins == post.coins))
            stateFlag = 1;
        if ( !( pre.numBuys == post.numBuys))
            stateFlag = 1;

        if (stateFlag) {
            tf_otherStates++;
            testFail = 1;
        }

        for (i = 0; i<= treasure_map; ++i){
            if ( ! ( pre.supplyCount[i] == post.supplyCount[i])){
                tf_supply += 1;
                testFail = 1;
            }
            if ( ! ( pre.embargoTokens[i] == post.embargoTokens[i])){
                tf_embargo += 1;
                testFail = 1;
            }
        }

        if (testFail){
            if(firstFail){
                //print PreState
                printState("pre", &pre, handPos, testPlayer);
                //print PostState
                printState("post", &post, handPos, testPlayer);
                firstFail = 0;
            }
        }
        overallFail += testFail;
    }

    // Print Test Results
    printf(" ----- TEST RESULTS -----\n");
    printf("Deck and Discard correctly updated: %d out of %d FAILED\n", tf_deckUpdate, testCount);
    printf("Hand correctly updated: %d out of %d FAILED\n", tf_handUpdate, testCount);
    printf("Action value: %d out of %d FAILED\n", tf_actionValue, testCount);
    printf("Other Player States: %d out of %d FAILED\n", tf_otherPlayerState, testCount);
    printf("Embargo tokens: %d out of %d FAILED\n", tf_embargo, testCount);
    printf("Supply unchanged: %d out of %d FAILED\n", tf_supply, testCount);
    printf("Other state variables unchanged: %d out of %d FAILED\n", tf_otherStates, testCount);
    printf("Overall: %d out of %d PASSED\n\n", testCount - overallFail, testCount);

    return 0;
}


