#include "myTestFunctions.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void getCardQuantities(int array[], int size, int cardArray[]){
    int i, j;
    //clear card array
    for (i=0; i<= treasure_map; i++){
        cardArray[i] = 0;
    }
    //get quantities
    for (j=0; j<size; j++) {
        cardArray[array[j]]++;
    }
}

int inArray(int arr[], int size, int val){
    int i;
    for(i=0; i<size; i++){
        if (val == arr[i]) 
            return 1;
    }
    return 0;
}

int randomGame(int numPlayers, struct gameState *state){
    int kingdomCards[10] = {-1};
    int i=0;

    while (i < 10){
        int randomKingdomCard = rand()%(treasure_map - adventurer + 1) + adventurer;
        if (!inArray(kingdomCards, 10, randomKingdomCard)){
            kingdomCards[i] = randomKingdomCard;
            i++;
        }
    }
    int randomSeed = rand()%1024;

    //initialize game
    initializeGame(numPlayers, kingdomCards, randomSeed, state);

    return 0;
}

int randomHand(int player, int size, struct gameState *state){
    int i;
    state->handCount[player] = size;
    for (i=0; i<size; i++){
        int randomCard = rand()%(treasure_map + 1);
        state->hand[player][i] = randomCard ;
    }
}

// My function returns 0 if the assertion is held and 1 if not. 
int myAssert(char * msg, int *failFlag, int boolean){
    if (!boolean){
        *failFlag = 1;
        printf("ASSERT %s: ", msg);
        printf("Failed!\n");
    }
    return !boolean;
}

int compareStates(int *failFlag, struct gameState *pre, struct gameState *post){
    char *preData = (char*)pre;
    char *postData = (char*)post;
    int i;
    int testFlag = 0;

    printf("TEST THAT NO STATE DATA OUTSIDE OF SPECIFICATION HAS CHANGED: ");
    fflush(stdout);

    for (i=0; i < sizeof(struct gameState); i++){
        testFlag += myAssert("", failFlag, preData[i] == postData[i]);
    }

    if (testFlag == 0) printf("PASS\n");
    else printf("FAIL\n");
}
