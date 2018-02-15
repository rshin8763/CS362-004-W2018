
/*********************************************************************
 ** Program Filename:  unittest3.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the updateCoins() function in dominion.c. 
 *********************************************************************/

#include "dominion.h"
#include "myTestFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 500
#define testPlayer 0
#define TEST_ITERATIONS 1024

int discardCard(int, int, struct gameState*, int);

int checkDiscard(int *failFlag, int handPos, struct gameState * pre, struct gameState * post, int trashFlag){
    int i;

    int testFlag = 0;

    // Create arrays to count the number of each card type
    int preArray[treasure_map+1];
    int postArray[treasure_map+1];

    // Get card quantities
    getCardQuantities(pre->playedCards, pre->playedCardCount, preArray);
    getCardQuantities(post->playedCards, post->playedCardCount, postArray);

    //Check if card is trashed or in played pile
    if(trashFlag < 1){
    } else {
    }

    ////Check card quantitites

    //Compare handCount
    testFlag += myAssert("Hand Count Decremented", failFlag, pre->handCount[testPlayer] == post->handCount[testPlayer] + 1);

    // Get card quantities
    getCardQuantities(pre->hand[testPlayer], pre->handCount[testPlayer], preArray);
    getCardQuantities(post->hand[testPlayer], post->handCount[testPlayer], postArray);

    int card = pre->hand[testPlayer][handPos];

    printf("CHECKING IF THE CORRECT CARD (AND ONLY THE CORRECT CARD) WAS DISCARDED: ");
    fflush(stdout);

    for (i=0; i<=treasure_map; i++){
        if (i == card){
            //Check if card was decremented from count of all cards in hand
            testFlag += myAssert("Discarded Card Removed from Hand", failFlag, preArray[i] == postArray[i] + 1);
        } else {
            testFlag += myAssert("Rest of Hand Not Discarded", failFlag, preArray[i] == postArray[i]);
        }
    }
    return testFlag;
}

int main(){
    printf("----------UNIT TEST for DISCARDCARD()----------\n");
    srand(time(0));
    struct gameState post;
    struct gameState pre;
    int failFlag = 0; int testFlag;
    int i;
    int testHandSize[] = {1, 40, 500};

    //Test discarding from end of hand

    //Testing hand size 1, 40, 500.
    //
    for (i=0; i < 3; i++){
        //Create Random Game
        randomGame(2, &post);
        randomHand(testPlayer, testHandSize[i], &post);

        //Save initial state
        memcpy(&pre, &post, sizeof(struct gameState));

        printf("---------HAND SIZE %d ----------\n", testHandSize[i]);

        //Check Discard Mechanics
        printf("TESTING DISCARD FROM END POSITION\n");
        fflush(stdout);
        int handPos = testHandSize[i]-1;
        int trashFlag = rand()%2;

        discardCard(handPos, testPlayer, &post, trashFlag);
        testFlag = checkDiscard(&failFlag, handPos, &pre, &post, trashFlag);
        if (testFlag == 0) printf("PASS\n");
        else printf("FAIL\n");

    }

    for (i=0; i < 3; i++){
        //Create Random Game
        randomGame(2, &post);
        randomHand(testPlayer, testHandSize[i], &post);

        //Save initial state
        memcpy(&pre, &post, sizeof(struct gameState));

        printf("---------HAND SIZE %d ----------\n", testHandSize[i]);

        //Check Discard Mechanics
        printf("TESTING DISCARD FROM MID POSITION\n");
        fflush(stdout);
        int handPos = (0+testHandSize[i])/2;
        int trashFlag = rand()%2;

        discardCard(handPos, testPlayer, &post, trashFlag);
        testFlag = checkDiscard(&failFlag, handPos, &pre, &post, trashFlag);
        if (testFlag == 0) printf("PASS\n");
        else printf("FAIL\n");

    }

    for (i=0; i < 3; i++){
        //Create Random Game
        randomGame(2, &post);
        randomHand(testPlayer, testHandSize[i], &post);

        //Save initial state
        memcpy(&pre, &post, sizeof(struct gameState));

        printf("---------HAND SIZE %d ----------\n", testHandSize[i]);

        //Check Discard Mechanics
        printf("TESTING DISCARD FROM FRONT POSITION\n");
        fflush(stdout);
        int handPos = 0;
        int trashFlag = rand()%2;

        discardCard(handPos, testPlayer, &post, trashFlag);
        testFlag = checkDiscard(&failFlag, handPos, &pre, &post, trashFlag);
        if (testFlag == 0) printf("PASS\n");
        else printf("FAIL\n");

    }

    //Give overall Test result
    if (failFlag == 0)
        printf("TESTS SUCCESSFUL\n");
    return 0;
}
