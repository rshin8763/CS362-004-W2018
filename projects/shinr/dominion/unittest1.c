/*********************************************************************
 ** Program Filename:  unittest1.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the shuffle() function in dominion.c
 *********************************************************************/
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 500
#define testPlayer 0
#define debug 0

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
            state->deck[i][j] = rand() % (treasure_map+1);
        }
    }
}

int _checkIfShuffled(int playerNo, struct gameState *pre, struct gameState *post){
    int flag = 0;
    int j;

    for (j=0; j<pre->deckCount[playerNo]; j++) {
        // If the card in position j doesn't match.
        flag += !(pre->deck[playerNo][j]  == post->deck[playerNo][j]);
        if (debug) printf("%d\t%d\n", pre->deck[playerNo][j], post->deck[playerNo][j]);
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
        int preArray[treasure_map+1] = {0};
        int postArray[treasure_map+1] = {0};

        for (j=0; j<pre->deckCount[playerNo]; j++) {
            preArray[pre->deck[playerNo][j]]++;
        }

        for (j=0; j<post->deckCount[playerNo]; j++) {
            postArray[post->deck[playerNo][j]]++;
        }


        for (j=0; j<=treasure_map; j++) {
            flag += !(preArray[j] == postArray[j]);
        }

        if (debug){
            printf("Deck Count : %d\n", pre->deckCount[playerNo]);

            for (j=0; j<=treasure_map; j++) {
                printf("%d\t%d\n", preArray[j], postArray[j]);
            }
                printf("\n");
        }
        //return 0 if card quantity is unchanged.
        if (flag == 0) return 0;
        else return 1;

    } else {
        printf("Deck Count does not match!\n");
        return 1;
    }
}

int _testShuffle(int players, int decksize){
    struct gameState post;
    struct gameState pre;
    int i;
    int ret = 0;

    createRandomDecks(players, decksize, &post);

    // Copy gamestate
    memcpy (&pre, &post, sizeof(struct gameState));

    // Shuffle original gamestate
    shuffle(testPlayer, &post);

    //Confirm that the new deck has the same number of each card type as before
    printf("shuffled deck has same cards: ");

    if (!_checkCardQuantity(testPlayer, &pre, &post)) {
        printf("PASS\n");
    }
    else {
        printf("FAIL\n");
        ret++;
    }

    //Check if the deck order is identical

    printf("shuffle() shuffles deck:  ");

    if (_checkIfShuffled(testPlayer, &pre, &post)) {
        printf("PASS\n");
    } else {
        printf("WARNING: Card order after shuffling was identical! Check decksize.\n");
    }


    //Confirm that none of the other player's decks have changed

    printf("No other player's decks were changed: ");

    int flag = 0;

    for (i=0; i<players; i++){
        if ( i != testPlayer ){
            flag += _checkIfShuffled(i, &pre, &post);
            flag += _checkCardQuantity(i, &pre, &post);
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

int main(){

    printf("-------UNIT TEST FOR SHUFFLE()--------\n");

    int players = 2;
    int testFail = 0;

    //test empty deck
    printf("---------TESTING EMPTY DECK--------\n");
    testFail += _testShuffle(players, 0);

    //Test size 1 deck
    printf("---------TESTING 1 CARD DECK--------\n");
    testFail += _testShuffle(players, 1);


    //Test size 40 deck
    printf("---------TESTING 40 CARD  DECK--------\n");
    testFail += _testShuffle(players, 40);


    //Test MAX_DECK deck
    printf("---------TESTING MAX_DECK DECK--------\n");
    testFail += _testShuffle(players, MAX_DECK);

    if (!testFail){
        printf("ALL TESTS SUCCESSFUL\n");
    } else {
        printf("TESTS FAILED\n");
    }

    return 0;
}


