#include "myTestFunctions.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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

int randomNonVictory(int kingdomCards[]){
    int i;
    while (1){
        int randomCard = rand()%(treasure_map + 1);
        if ( randomCard >= copper && randomCard <= gold ){
            return randomCard;
        }
        else if (randomCard >= adventurer){
            for (i = 0; i <10; ++i) {
                if (randomCard == kingdomCards[i])
                    return randomCard;
            }
        }
    }
}

int randomState(int numPlayers, struct gameState *state){
    int kingdomCards[10] = {-1};
    int i=0;
    int j;

    //Select random cards
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

    //Set other variables
    state->outpostPlayed = 0;
    state->outpostTurn = 0;
    state->whoseTurn = rand()%numPlayers;
    state->numActions = (rand()%5)+1; /* Starts at 1 each turn */
    state->coins = rand()%10; /* Use as you see fit! */
    state->numBuys = rand()%5+1; /* Starts at 1 each turn */

    // Randomize Deck and Hand State
    for (i = 0; i < numPlayers; ++i){

        // Set total cards in play for a person. 
        // from starting deck size - MAX_DECK
        int maxDeck = state->deckCount[i] + rand()%(MAX_DECK - state->deckCount[i] + 1); 

        //Randomly distribute maxDeck count to the state variables below.
        maxDeck -= state->handCount[i] = rand()%(maxDeck+1);
        maxDeck -= state->deckCount[i] = rand()%(maxDeck+1);
        //maxDeck -= state->playedCardCount = rand()%(maxDeck+1);
        maxDeck -= state->discardCount[i] = rand()%(maxDeck+1);
        
        assert(state->handCount[i] + state->deckCount[i] + state->playedCardCount + state->discardCount[i] <= MAX_DECK);

        // Fill all piles with random non Victory cards of types within supply
        for ( j = 0; j < state->handCount[i]; ++j) {
            state->hand[i][j] = randomNonVictory(kingdomCards);
        }
        for ( j = 0; j < state->deckCount[i]; ++j) {
            state->deck[i][j] = randomNonVictory(kingdomCards);
        }
        //for ( int j = 0; j <= state->playedCardCount; ++j) {
        //    state->playedCards[j]= randomNonVictory(kingdomCards);
        //}
        for ( j = 0; j < state->discardCount[i]; ++j) {
            state->discard[i][j] = randomNonVictory(kingdomCards);
        }
    }
    //Action phase must be phase 0
    state->phase = 0;
    return 0;
}

void randomHand(int player, int size, struct gameState *state){
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

void compareStates(int *failFlag, struct gameState *pre, struct gameState *post){
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

int compareArray(int preArr[], int postArr[], int size){

    int testFlag = 0;

    int i;

    for (i=0; i<size; i++){
        testFlag += !(preArr[i] == postArr[i]);
    }
    //returns 0 if the data perfectly matches.
    //returns nonzero otherwise
    return testFlag;
}

int compareData(void *pre, void *post, int size){
    char *preData = (char*)pre;
    char *postData = (char*)post;
    int i;
    int testFlag = 0;

    for (i=0; i < size; i++){
        testFlag += !(preData[i] == postData[i]) ;
    }
    return testFlag;
}

