
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

int main(){
    printf("----------UNIT TEST for DISCARDCARD()----------\n");
    srand(time(0));
    struct gameState post;
    struct gameState pre;
    int failFlag = 0; int testFlag;
    int i; int j; int k;

    //Create Random Game
    randomGame(2, &post);
    
    //Save initial state
    memcpy(&pre, &post, sizeof(struct gameState));

    //Test discard from all hand positions
    printf("TESTNAME: ");
    fflush(stdout);

    testFlag = 0;

    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");

    //Check that no other state data has changed.
    pre.coins = 0;
    post.coins = 0;

    for (i=0; i<MAX_HAND; i++){
        pre.hand[testPlayer][i] = 0;
        post.hand[testPlayer][i] = 0;
    }

    pre.handCount[testPlayer] = 0;
    post.handCount[testPlayer] = 0;

    compareStates(&failFlag, &pre, &post);

    //Give overall Test result
    if (failFlag == 0)
        printf("TESTS SUCCESSFUL\n");
    return 0;
}
