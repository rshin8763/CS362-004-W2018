#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_DECK 500
#define testPlayer 0


// This is a unit test for the function shuffle(int player, struct gameState * state)

void createRandomDecks(int players, int size, struct gameState *state){
    //seed RNG
    srand(time(0));

    //This code was adapted from dominion.c
    //Set player decks
    int i, j;
    for (i = 0; i < players; i++)
    {
        state->deckCount[i] = size;
        for (j = 0; j < size; j++)
        {
            state->deck[i][j] = rand() % treasure_map+1;
        }
    }
}

int _checkIfShuffled(int playerNo, struct gameState *pre, struct gameState *post){
    int flag = 0;
    int j;

    for (j=0; j<pre->deckCount[playerNo]; j++) {
        // If the card in position j doesn't match.
        flag += !(pre->deck[playerNo][j]  == post->deck[playerNo][j]);
    }

    // return 0 if card order is identical
    if (flag == 0) return 0;
    else return 1;
}
int _checkCardQuantity(int playerNo, struct gameState *pre, struct gameState *post){

    if (pre->deckCount[playerNo] == post->deckCount[playerNo]){
        int j;
        int flag = 0;
        // Create arrays to count the number of each card type
        int preArray[treasure_map] = {0};
        int postArray[treasure_map] = {0};

        for (j=0; j<pre->deckCount[playerNo]; j++) {
            preArray[pre->deck[playerNo][j]]++;
        }

        for (j=0; j<post->deckCount[playerNo]; j++) {
            postArray[post->deck[playerNo][j]]++;
        }

        for (j=0; j<treasure_map; j++) {
            flag += !(preArray[j] == postArray[j]);
        }

        //return 0 if card quantity is unchanged.
        if (flag == 0) return 0;
        else return 1;

    } else {
        printf("Deck Count does not match!\n");
        return 1;
    }
}

int _testShuffle(int p, struct gameState *post){
    struct gameState pre;
    int i, j;
    int ret = 0;

    // Copy gamesate
    memcpy (&pre, post, sizeof(struct gameState));

    // Shuffle original gamestate
    shuffle(testPlayer, post);

    //Confirm that the new deck has the same number of each card type as before
    printf("shuffled deck has same cards: ");

    if (!_checkCardQuantity(testPlayer, &pre, post)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
        ret++;
    }

    //Check if the deck order is identical

    printf("shuffle() shuffles deck:  ");

    if (!_checkIfShuffled(testPlayer, &pre, post)) {
        printf("PASS\n");
    } else {
        printf("WARNING: Card order after shuffling was identical! Check decksize.\n");
    }


    //Confirm that none of the other player's decks have changed

    printf("No other player's decks were changed: ");

    int flag = 0;
    for (i=0; i<p; i++){
        if ( i != testPlayer ){
            flag += _checkIfShuffled(i, &pre, post);
            flag += _checkCardQuantity(i, &pre, post);
        }
    }

    if (flag == 0) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
        ret++;
    }

    return ret;
}

void main(){

    struct gameState state;

    int players = 3;
    int testFail = 0;

    //Test empty deck
    printf("---------TESTING EMPTY DECK--------\n");
    createRandomDecks(players, 0, &state);
    testFail += _testShuffle(players, &state);

    //Test size 1 deck
    printf("---------TESTING 1 CARD DECK--------\n");
    createRandomDecks(players, 1, &state);
    testFail += _testShuffle(players, &state);


    //Test size 40 deck
    printf("---------TESTING 40 CARD  DECK--------\n");
    createRandomDecks(players, 40, &state);
    testFail += _testShuffle(players, &state);


    //Test MAX_DECK deck
    printf("---------TESTING MAX_DECK DECK--------\n");
    createRandomDecks(players, MAX_DECK, &state);
    testFail += _testShuffle(players, &state);

    if (!testFail){
        printf("ALL TESTS SUCCESSFUL\n");
    } else {
        printf("TESTS FAILED\n");
    }
}


