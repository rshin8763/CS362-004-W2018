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

    int failFlag = 0; int testFlag;

    printf("------TEST FOR SMITHY--------");

    //initialize random game
    randomGame(MAX_PLAYERS, &post);

    int testPlayer = pre.whoseTurn;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0;
    int bonus = -5;

    int handPos = 5;

    randomHand(testPlayer, 10, &post);
    
    //set position 5 card to smithy
    post.hand[testPlayer][5] = smithy;

    //save game state
    memcpy(&pre, &post, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);

    printf("3 cards were drawn from player's deck: ");
    testFlag = 0;

    testFlag += myAssert ("Player has 2 extra cards", &failFlag, (post.handCount[testPlayer] - pre.handCount[testPlayer])== 2);

    testFlag += myAssert ("Played Pile has 1 extra card", &failFlag, (post.playedCardCount - pre.playedCardCount == 1));

    testFlag += myAssert ("Player deck has 3 fewer cards", &failFlag, pre.deckCount[testPlayer] - post.deckCount[testPlayer] == 3 );

    if (!testFlag) printf("PASS\n");
    else printf ("FAIL\n");

    int j;

    testFlag = 0;
    printf("Test that gameState for all other players is constant: ");

    for (j=0; j<MAX_PLAYERS; j++){
        if (j != testPlayer){
            testFlag += myAssert("player hand is preserved", &failFlag, !compareArray(pre.hand[j], post.hand[j], MAX_HAND));

            testFlag += myAssert("player handCount is preserved", &failFlag, pre.handCount[j] == post.handCount[j]);

            testFlag += myAssert("player deck is preserved", &failFlag, !compareArray(pre.deck[j], post.deck[j], MAX_DECK));


            testFlag += myAssert("player deckCount is preserved", &failFlag, pre.deckCount[j] == post.deckCount[j]);

            testFlag += myAssert("player discard is preserved", &failFlag, !compareArray(pre.discard[j], post.discard[j], MAX_DECK));

            testFlag += myAssert("player discardCount is preserved", &failFlag, pre.discardCount[j] == post.discardCount[j]);
        }
    }
    if (!testFlag) printf("PASS\n");
    else printf ("FAIL\n");

    printf("Test that kingdom card piles and victory card piles are unchanged: ");
    testFlag = 0;
    testFlag += myAssert("Assert that Supply cards are unchanged", &failFlag, !compareData(pre.supplyCount, post.supplyCount, sizeof(pre.supplyCount)));   
    if (!testFlag) printf("PASS\n");
    else printf ("FAIL\n");

    if (!failFlag) printf("ALL TESTS SUCCESSFUL\n");
    else printf("TESTS FAILED\n");
    return 0;
}

//int main(){
//
//    srand(time(0));
//    struct gameState post;
//    struct gameState pre;
//
//
//    printf("------TEST FOR SMITHY--------");
//
//    int numPlayers = 3;
//        
//    //initialize random game
//    randomGame(numPlayers, &pre);
//
//    //set prerequisite conditions
//    int currentPlayer = pre.whoseTurn;
//    int choice1, choice2, choice3;
//    choice1 = choice2 = choice3 = 0;
//    int bonus = -5;
//    int handPos = rand()%pre.handCount[currentPlayer];
//
//    //set card int hand position to smithy
//    post.hand[currentPlayer][handPos] = smithy;
//
//    printf("handPos:%d\n", handPos);
//
//    //save game state
//    memcpy(&pre, &post, sizeof(struct gameState));
//
//    printf("pre:%d\n", pre.handCount[currentPlayer]);
//    printf("post:%d\n", post.handCount[currentPlayer]);
//
//    cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);
//
//    
//    printf("pre:%d\n", pre.handCount[currentPlayer]);
//    printf("post:%d\n", post.handCount[currentPlayer]);
//
//    // Hand should have 2 extra cards. +3 then the smithy discard
//    assert (pre.handCount[currentPlayer] + 2 == post.handCount[currentPlayer]);
//
//    // Deck and discard together should have 2 fewer cards
//    assert (pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] == post.discardCount[currentPlayer] + post.deckCount[currentPlayer] + 2);
//
//    printf("ALL TESTS SUCCESSFUL\n");
//    return 0;
//}
//
//
