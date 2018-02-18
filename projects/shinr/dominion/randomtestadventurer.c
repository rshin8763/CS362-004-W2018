/*********************************************************************
 ** Program Filename:  cardtest1.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a random test generator and oracle for the adventurer card in dominion.c
 *********************************************************************/
#include "myTestFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_DECK 500
#define debug 0


//// Global Testing Flags


int tf_deckUpdate = 0; // Deck was properly updated
int tf_actionValue = 0; // Action value was properly updated
int tf_coinCount = 0; // Number of treasure gained was correct
int tf_coinValue = 0; // Value of coins state variable matches treasures drawn
int tf_adventurerDiscard = 0; // Adventurer was discarded
int tf_otherPlayerState = 0; // Other player's states are unchagned
int tf_otherStates = 0; // All other states are unchanged
int tf_supply = 0; // Supply cards unchanged
int tf_embargo = 0;  // Embargo tokens unchagned
int testFail;

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

void testAdventurer(struct gameState *pre, struct gameState *post, int testPlayer){
    int i;

    int preCardQuantity[treasure_map+1];
    int postCardQuantity[treasure_map+1];

    getCardQuantities(pre->hand[testPlayer], pre->handCount[testPlayer], preCardQuantity);
    getCardQuantities(post->hand[testPlayer], post->handCount[testPlayer], postCardQuantity);

    //All cards outside of treasure cards and adventurer should have the same quantity before and after.
    int copperGained;
    int silverGained;
    int goldGained;

    for (i = 0; i <= treasure_map; ++i){
        if(i == copper){
            copperGained = postCardQuantity[i] - preCardQuantity[i];
        }
        else if(i == silver){
            silverGained = postCardQuantity[i] - preCardQuantity[i];
        }
        else if(i == gold){
            goldGained = postCardQuantity[i] - preCardQuantity[i];
        }
        else if(i == adventurer){
            if (!(postCardQuantity[i] == preCardQuantity[i] - 1)) {
                tf_adventurerDiscard++;
                testFail = 1;
            }
        }
    }
    if (!(copperGained + silverGained + goldGained == 2)){
        tf_coinCount++;
        testFail = 1;
    }
        
    if (!(post->coins - pre->coins == copperGained + 2*silverGained + 3*goldGained)){
        tf_coinValue++;
        testFail = 1;
    }
}

int main(){
    int overallFail = 0;
    int testCount;
    int firstFail = 1;
    int i;

    printf("------TEST FOR ADVENTURER--------\n");
    for (testCount = 0; testCount < 100000; ++testCount){
        testFail = 0;


        srand(time(0));
        struct gameState post;
        struct gameState pre;

        // between 2 and MAX_PLAYERS players
        int numPlayers = rand()%(MAX_PLAYERS-1) + 2;

        //initialize random game
        //randomGame(numPlayers, &post);
        randomState(numPlayers, &post);

        //set prerequisite conditions
        int testPlayer = post.whoseTurn;
        int choice1, choice2, choice3;
        choice1 = choice2 = choice3 = 0;
        int bonus = 0;
        int handPos = rand()%post.handCount[testPlayer];

        //set card int hand position to adventurer
        post.hand[testPlayer][handPos] = adventurer;

        updateCoins(testPlayer, &post, bonus);

        //save game state
        memcpy(&pre, &post, sizeof(struct gameState));

        //play card
        playCard(handPos, choice1, choice2, choice3, &post);

        // Test adventurer card effect
        testAdventurer(&pre, &post, testPlayer);

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
                printf("AT LEAST ONE TEST FAILED!! HERE IS THE PRE AND POST STATE FOR DEBUGGING.\n");
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
    printf("Draw 2 treasures: %d out of %d FAILED\n", tf_coinCount, testCount);
    printf("Coin count matches treasures drawn: %d out of %d FAILED\n", tf_coinValue, testCount);
    printf("Adventurer card removed from hand: %d out of %d FAILED\n", tf_adventurerDiscard, testCount);
    printf("Action value: %d out of %d FAILED\n", tf_actionValue, testCount);
    printf("Other Player States: %d out of %d FAILED\n", tf_otherPlayerState, testCount);
    printf("Embargo tokens: %d out of %d FAILED\n", tf_embargo, testCount);
    printf("Supply unchanged: %d out of %d FAILED\n", tf_supply, testCount);
    printf("Other state variables unchanged: %d out of %d FAILED\n", tf_otherStates, testCount);
    printf("Overall: %d out of %d PASSED\n\n", testCount - overallFail, testCount);

    return 0;
}
