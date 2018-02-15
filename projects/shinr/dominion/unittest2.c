/*********************************************************************
 ** Program Filename:  unittest2.c
 ** Author: Ryan Shin 
 ** Date: 2/04/18
 ** Description: This is a unit test for the compare() function in dominion.c. I chose this 
 ** one because I wanted to practice the concepts of random testing on a simple model.
 *********************************************************************/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DECK 500
#define testPlayer 0
#define TEST_ITERATIONS 100000000
#define debug 0

int compare(const void* a, const void* b);

int main(){
    // seed rng
    srand(time(0));
    int num1, num2, i,
    val, ret, failFlag = 0;

    printf("-------UNIT TEST FOR COMPARE()--------\n");

    for( i=0; i<TEST_ITERATIONS; i++){
        num1 = rand() % (treasure_map + 1);
        num2 = rand() % (treasure_map + 1);
        
        if (num1 > num2) 
            val = 1;
        else if (num1 == num2)
            val = 0;
        else 
            val = -1;

        ret = compare(&num1, &num2);

        if (val != ret){
            failFlag = 1;
            printf("Num1: %d  Num2: %d  compare() return value: %d\n", num1, num2, ret);
        }
    }
    if (!failFlag) 
        printf("TEST COMPLETED SUCCESSFULLY\n");
    else 
        printf("TEST FAILED\n");

    return 0;
}

