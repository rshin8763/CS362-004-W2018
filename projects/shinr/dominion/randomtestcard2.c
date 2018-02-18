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

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int main(){
    int overallFail;
    int testFail;
    int testCount;
    int i;
    int j;

    printf("------TEST FOR GREAT HALL------\n");
    for (testCount = 0; testCount < 100000; ++testCount){
        testFail = 0;
        // Deck is updated
        int tf_deckUpdate = 0;
        // Hand is updated with cards missing from Deck
        int tf_handUpdate = 0;
        // Action value is the same
        int tf_actionValue = 0;
        // Played pile has extra card
        int tf_playedPile = 0;
        // Supply cards are the same
        // Other player's state is invariant
        int tf_otherPlayerState = 0;
        // All player's victory point states are the same
        int tf_otherStates = 0;

        printf("------TEST %d------\n", testCount);

        srand(time(0));
        struct gameState post;
        struct gameState pre;

        int numPlayers = MAX_PLAYERS;

        //initialize random game
        //randomGame(numPlayers, &post);
        randomState(numPlayers, &post);

        //set prerequisite conditions
        int testPlayer = post.whoseTurn;
        int choice1, choice2, choice3;
        choice1 = choice2 = choice3 = 0;
        int bonus = -5;
        int handPos = rand()%post.handCount[testPlayer];

        //set card int hand position to smithy
        post.hand[testPlayer][handPos] = great_hall;

        //save game state
        memcpy(&pre, &post, sizeof(struct gameState));

        cardEffect(great_hall, choice1, choice2, choice3, &post, handPos, &bonus);

        // Hand should have the same number of cards. +1 then the great_hall discard
        myAssert ("Player's hand has drawn one card", &tf_handUpdate, pre.handCount[testPlayer] == post.handCount[testPlayer]);

        // Due to the fact that an empty deck will cause shuffling, the invariant is that deck + played/discard should have 2 fewer cards due to the drawn cards being 
        // in hand.
        myAssert ("Great_Hall card was discarded", &tf_deckUpdate, (pre.deckCount[testPlayer] + pre.discardCount[testPlayer] + pre.playedCardCount) == (post.discardCount[testPlayer] + post.deckCount[testPlayer] + post.playedCardCount));

        myAssert("numActions increased", &tf_otherStates, pre.numActions + 1 == post.numActions);
        
        //Other player's cards are not changed
        for (j=0; j<MAX_PLAYERS; j++){
            if (j != testPlayer){
                myAssert("Other player's hand is preserved", &tf_otherPlayerState, !compareArray(pre.hand[j], post.hand[j], MAX_HAND));

                myAssert("Other player's handCount is preserved", &tf_otherPlayerState, pre.handCount[j] == post.handCount[j]);

                myAssert("Other player's deck is preserved", &tf_otherPlayerState,  !compareArray(pre.deck[j], post.deck[j], MAX_DECK));

                myAssert("Other player's deckCount is preserved", &tf_otherPlayerState, pre.deckCount[j] == post.deckCount[j]);

                myAssert("Other player's discard is preserved",&tf_otherPlayerState, !compareArray(pre.discard[j], post.discard[j], MAX_DECK));

                myAssert("Other player's discardCount is preserved", &tf_otherPlayerState, pre.discardCount[j] == post.discardCount[j]);
            }
        }

        // The multiset of cards in hand + deck + discard should be the same before and afterwards
        myAssert("numPlayers unchanged", &tf_otherStates, pre.numPlayers == post.numPlayers); 
        for (i = 0; i<= treasure_map; ++i){
            myAssert("supplyCount unchanged", &tf_otherStates, pre.supplyCount[i] == post.supplyCount[i]);
            myAssert("embargoTokens unchanged", &tf_otherStates, pre.embargoTokens[i] == post.embargoTokens[i]);
        }
        myAssert("outpostPlayed unchanged", &tf_otherStates, pre.outpostPlayed == post.outpostPlayed);
        myAssert("outpostTurn unchanged", &tf_otherStates, pre.outpostTurn == post.outpostTurn);
        myAssert("coins unchanged", &tf_otherStates, pre.coins == post.coins);
        myAssert("numBuys unchanged", &tf_otherStates, pre.numBuys == post.numBuys);

        testFail += tf_deckUpdate + tf_handUpdate + tf_actionValue + tf_playedPile + tf_otherPlayerState;
        if (testFail){
            //print PreState
            printState("pre", &pre, handPos, testPlayer);
            //print PostState
            printState("post", &post, handPos, testPlayer);
        }
        overallFail += testFail;
    }
    if (overallFail){
    } else printf("ALL TESTS SUCCESSFUL\n");
    return 0;
}


