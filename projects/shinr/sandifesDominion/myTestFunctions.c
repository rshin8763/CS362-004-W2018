#include "myTestFunctions.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int testOtherPlayerStates(struct gameState * pre, struct gameState * post, int testPlayer){
    int j;
    int failFlag = 0;
    for (j=0; j<pre->numPlayers; j++){
        if (j != testPlayer){
            if ( !(!compareArray(pre->hand[j], post->hand[j], post->handCount[j])))
                failFlag = 1;
            if ( !( pre->handCount[j] == post->handCount[j]))
                failFlag = 1;
            if ( !( !compareArray(pre->deck[j], post->deck[j], post->deckCount[j])))
                failFlag = 1;
            if ( !( pre->deckCount[j] == post->deckCount[j]))
                failFlag = 1;
            if ( !( !compareArray(pre->discard[j], post->discard[j], post->discardCount[j])))
                failFlag = 1;
            if ( !( pre->discardCount[j] == post->discardCount[j]))
                failFlag = 1;
        }
    }
    return failFlag;
}

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
    state->whoseTurn = rand()%numPlayers;
    state->numActions = (rand()%5)+1; /* Starts at 1 each turn */
    state->numBuys = (rand()%5)+1; /* Starts at 1 each turn */

    // Randomize Deck and Hand State
    for (i = 0; i < numPlayers; ++i){
        // Set total cards in play for a person.
        // from starting deck size - MAX_DECK
        int startingDeck = state->deckCount[i];

        do {
            //Randomly distribute maxDeck count to the state variables below.
            int maxDeck = startingDeck + rand()%(MAX_DECK - startingDeck + 1);
            //Ensure that hand has at least 1 card in it (to be used as action card).
            maxDeck -= state->handCount[i] = rand()%(maxDeck-1+1)+1;
            maxDeck -= state->deckCount[i] = rand()%(maxDeck+1);
            state->discardCount[i] = maxDeck;
        } while (state->deckCount[i] + state->discardCount[i] <= 5); // Ensure that deck + discard have at least 5 cards

        assert(state->handCount[i] + state->deckCount[i] + state->playedCardCount + state->discardCount[i] <= MAX_DECK);

        // Fill all piles with random non Victory cards of types within supply
        // Ensuring at least 2 treasure cards in deck
        int treasureCount;
        do {
            treasureCount = 0;
            for ( j = 0; j < state->handCount[i]; ++j) {
                state->hand[i][j] = randomNonVictory(kingdomCards);
            }
            for ( j = 0; j < state->deckCount[i]; ++j) {
                int card = randomNonVictory(kingdomCards);
                state->deck[i][j] = randomNonVictory(kingdomCards);
                if ( (card == copper)|| (card == silver) || (card == gold) ) 
                    treasureCount++;
            }
            for ( j = 0; j < state->discardCount[i]; ++j) {
                int card = randomNonVictory(kingdomCards);
                state->discard[i][j] = randomNonVictory(kingdomCards);
                if ( (card == copper)|| (card == silver) || (card == gold) ) 
                    treasureCount++;
            }
        }while (treasureCount < 2);
    }
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

void printArray(char *name, int arr[], int size){
    int i;
    printf("%s: { ", name);
    for (i = 0; i < size; ++i){
        printf("%d ", arr[i]);
    }
    printf("}\n");
}

void printState(char * name, struct gameState *post, int handPos, int testPlayer){
    int i;
    printf("\n=== %s GAMESTATE ===:\n\nTestPlayer: %d\n", name, testPlayer);
    printf("HandPos: %d\n\n", handPos);
    printArray("supplyCount", post->supplyCount, treasure_map+1);
    printArray("embargoTokens", post->embargoTokens, treasure_map+1);


    for (i = 0; i < post->numPlayers; ++i){
        printf("----- PLAYER %d -----\n", i);
        printf("handCount: %d\n", post->handCount[i]);
        printArray("hand", post->hand[i], post->handCount[i]);
        printf("deckCount: %d\n", post->deckCount[i]);
        printArray("deck", post->deck[i], post->deckCount[i]);
        printf("discardCount: %d\n", post->discardCount[i]);
        printArray("discard", post->discard[i], post->discardCount[i]);
    }

    printf("playedCardCount: %d\n", post->playedCardCount);
    printArray("playedCards", post->playedCards, post->playedCardCount);

    printf("outpostPlayed: %d\n", post->outpostPlayed);
    printf("outpostTurn: %d\n", post->outpostTurn);
    printf("whoseTurn: %d\n", post->whoseTurn);
    printf("phase: %d\n", post->phase);
    printf("numActions: %d\n", post->numActions);
    printf("coins: %d\n", post->coins);
    printf("numBuys: %d\n\n", post->numBuys);
}

