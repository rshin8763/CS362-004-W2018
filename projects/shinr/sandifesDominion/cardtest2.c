/*********************************************************************
 ** Program Filename:  cardtest2.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the great_hall card in dominion.c
 *********************************************************************/
#include "myTestFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 500
#define debug 0
#define players 3

int main(){

    srand(time(0));
    struct gameState post;
    struct gameState pre;

    int failFlag = 0; int testFlag;


    printf("------TEST FOR GREAT HALL --------\n");

    //initialize random game
    randomGame(players, &post);

    int testPlayer = pre.whoseTurn;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0;

    int bonus = -5;
    int handPos = 5;

    randomHand(testPlayer, 10, &post);
    
    //set position 5 card to great hall
    post.hand[testPlayer][5] = great_hall;

    //save game state
    memcpy(&pre, &post, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &post, handPos, &bonus);

    printf("3 cards were drawn from player's deck: ");
    testFlag = 0;

    //Test draw +1
    testFlag += myAssert ("Player has 1 extra drawn card", &failFlag, (post.handCount[testPlayer] - pre.handCount[testPlayer])== 0); // One draw then discard = 0

    testFlag += myAssert ("Played Pile has 1 extra card", &failFlag, (post.playedCardCount - pre.playedCardCount == 1));

    testFlag += myAssert ("Player deck has 1 fewer card", &failFlag, pre.deckCount[testPlayer] - post.deckCount[testPlayer] == 1 );

    if (!testFlag) printf("PASS\n");
    else printf ("FAIL\n");

    //Test action +1
    printf("Test Action +1: ");
    testFlag = 0;
    testFlag += myAssert("Player has one more action", &failFlag, pre.numActions == post.numActions - 1);

    if (!testFlag) printf("PASS\n");
    else printf ("FAIL\n");


    int j;
    testFlag = 0;
    printf("Test that gameState for all other players is constant: ");

    for (j=0; j<players; j++){
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

