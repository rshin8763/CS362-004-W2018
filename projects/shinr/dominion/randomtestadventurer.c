/*********************************************************************
 ** Program Filename:  cardtest1.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the adventurer card in dominion.c
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
int tf_handUpdate = 0; // Hand was properly updated
int tf_actionValue = 0; // Action value was properly updated
int tf_playedPile = 0; // Played pile was properly udpated
int tf_coinCount = 0; // Number of treasure gained was correct
int tf_coinValue = 0; // Value of coins state variable matches treasures drawn
int tf_adventurerDiscard = 0; // Adventurer was discarded
int tf_otherPlayerState = 0; // Other player's states are unchagned
int tf_otherStates = 0; // All other states are unchanged

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
            myAssert("Coppers gained is non negative", &tf_coinCount,
                    copperGained >= 0);
        }
        else if(i == silver){
            silverGained = postCardQuantity[i] - preCardQuantity[i];
            myAssert("Silvers gained is non negative", &tf_coinCount,
                    silverGained >= 0);
        }
        else if(i == gold){
            goldGained = postCardQuantity[i] - preCardQuantity[i];
            myAssert("Golds gained is non negative", &tf_coinCount,
                    goldGained >= 0);
        }
        else if(i == adventurer){
            myAssert("An adventurer card was removed from hand", &tf_adventurerDiscard,
                    postCardQuantity[i] == preCardQuantity[i] - 1);
        }
    }
    myAssert("2 treasures were drawn", &tf_coinCount,
            (copperGained + silverGained + goldGained == 2));

    myAssert("Coin value matches the 2 treasures drawn", &tf_coinValue,
            (post->coins - pre->coins == copperGained + 2*silverGained + 3*goldGained));
}

int main(){
    int overallFail;
    int testFail;
    int testCount;
    int i;
    int j;

    printf("------TEST FOR ADVENTURER--------\n");
    for (testCount = 0; testCount < 10000; ++testCount){
        testFail = 0;

        tf_deckUpdate = 0;
        tf_handUpdate = 0;
        tf_actionValue = 0;
        tf_playedPile = 0;
        tf_coinCount = 0;
        tf_coinValue = 0;
        tf_adventurerDiscard = 0;
        tf_otherPlayerState = 0;
        tf_otherStates = 0;

        printf("------TEST %d--------\n", testCount);

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
        int bonus = 0;
        int handPos = rand()%post.handCount[testPlayer];

        //set card int hand position to adventurer
        post.hand[testPlayer][handPos] = adventurer;

        updateCoins(testPlayer, &post, bonus);
        //save game state

        memcpy(&pre, &post, sizeof(struct gameState));

        playCard(handPos, choice1, choice2, choice3, &post);

        // Test adventurer card effect
        testAdventurer(&pre, &post, testPlayer);

        // Test that other player's cards are not changed
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

        // Test all other state invariants
        for (i = 0; i<= treasure_map; ++i){
            myAssert("supplyCount unchanged", &tf_otherStates, pre.supplyCount[i] == post.supplyCount[i]);
            myAssert("embargoTokens unchanged", &tf_otherStates, pre.embargoTokens[i] == post.embargoTokens[i]);
        }
        myAssert("outpostPlayed unchanged", &tf_otherStates, pre.outpostPlayed == post.outpostPlayed);
        myAssert("outpostTurn unchanged", &tf_otherStates, pre.outpostTurn == post.outpostTurn);
        myAssert("numActions decremented", &tf_otherStates, pre.numActions == post.numActions + 1);
        myAssert("numBuys unchanged", &tf_otherStates, pre.numBuys == post.numBuys);

        testFail += tf_deckUpdate + tf_handUpdate + tf_actionValue + tf_playedPile + tf_coinCount + tf_coinValue + tf_adventurerDiscard + tf_otherPlayerState + tf_otherStates;

        if (testFail){
            //print PreState
            if(DEBUG)
                printState("pre", &pre, handPos, testPlayer);
            //print PostState
            if(DEBUG)
                printState("post", &post, handPos, testPlayer);
        }
        overallFail += testFail;
    }
    if (overallFail){
    } else printf("ALL TESTS SUCCESSFUL\n");
    return 0;
}
