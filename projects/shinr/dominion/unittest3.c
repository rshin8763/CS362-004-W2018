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

//updateCoins prototype
int updateCoins(int, struct gameState*, int);

int main(){
    printf("----------UNIT TEST for UPDATECOINS()----------\n");
    srand(time(0));
    struct gameState post;
    struct gameState pre;

    int i=0; int j=0; int k=0;

    int failFlag = 0; int testFlag;

    //initialize random game
    randomGame(2, &post);

    //save game state
    memcpy(&pre, &post, sizeof(struct gameState));

    //Test 0-MAX size hand with no coins
    printf("TEST HANDS WITH NO COINS: ");
    fflush(stdout);

    testFlag = 0;
    for(i=0; i<=MAX_HAND; i++){
        post.handCount[testPlayer] = i;
        for (j=0; j<post.handCount[testPlayer]; j++){
            int randomKingdomCard = rand()%(treasure_map - adventurer + 1) + adventurer;
            post.hand[testPlayer][j] = randomKingdomCard;
        }
        updateCoins(testPlayer, &post, 0);
        testFlag += myAssert("", &failFlag, post.coins == 0);
    }
    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");

    //Test 0-MAX size hand with Copper
    printf("TEST HANDS 0-MAX_SIZE of COPPER: ");
    fflush(stdout);

    testFlag = 0;
    for(i=0; i<=MAX_HAND; i++){
        post.handCount[testPlayer] = i;
        for (j=0; j<post.handCount[testPlayer]; j++){
            post.hand[testPlayer][j] = copper;
        }
        updateCoins(testPlayer, &post, 0);
        testFlag += myAssert("", &failFlag, post.coins == (i*1));
    }
    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");

    //Test 0-MAX size hand with Silver
    printf("TEST HANDS 0-MAX_SIZE OF SILVER: ");
    fflush(stdout);

    testFlag = 0;
    for(i=0; i<=MAX_HAND; i++){
        post.handCount[testPlayer] = i;
        for (j=0; j<post.handCount[testPlayer]; j++){
            post.hand[testPlayer][j] = silver;
        }
        updateCoins(testPlayer, &post, 0);
        testFlag += myAssert("", &failFlag, post.coins == (i*2));
    }
    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");

    //Test 0-MAX size hand with Gold
    printf("TEST HANDS 0-MAX_SIZE OF GOLD: ");
    fflush(stdout);

    testFlag = 0;
    for(i=0; i<=MAX_HAND; i++){
        post.handCount[testPlayer] = i;
        for (j=0; j<post.handCount[testPlayer]; j++){
            post.hand[testPlayer][j] = gold;
        }
        updateCoins(testPlayer, &post, 0);
        testFlag += myAssert("", &failFlag, post.coins == (i*3));
    }
    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");

    // Random test cases with random bonus
    //
    printf("TEST RANDOM HANDS WITH RANDOM BONUSES: ");
    fflush(stdout);

    testFlag = 0;

    for (k=0; k<TEST_ITERATIONS; k++){
        for(i=0; i<=MAX_HAND; i++){
            int numCopper = 0, numSilver = 0, numGold = 0;
            int bonus = rand()%10;
            post.handCount[testPlayer] = i;
            for (j=0; j<post.handCount[testPlayer]; j++){
                int randomCard =  rand()% (treasure_map + 1);
                post.hand[testPlayer][j] = randomCard;
                if (randomCard == copper) numCopper++;
                if (randomCard == silver) numSilver++;
                if (randomCard == gold) numGold++;
            }
            updateCoins(testPlayer, &post, bonus);
            testFlag += myAssert("", &failFlag, post.coins == numCopper + 2*numSilver + 3*numGold + bonus);
        }
    }
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
    
    if (failFlag == 0)
        printf("TESTS SUCCESSFUL\n");
    return 0;
}
