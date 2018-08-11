/*****
* Author: Keane Lim
* Date: 08/04/18
* Description: Random Test for greatHall -- card where we made a unit test in Assignment 3
****/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> //taken from cardtest4.c template

#define NUM_TESTS 2000
#define DISCARD 1 //great hall should be discarded after being played
#define CARDS_DRAWN 1 //great hall draws one card
#define ACTION_INCREASE 1 //great hall increases numActions by 1

//as per HW specs,
//use own asserttrue function to avoid crashing from standard C assert
int asserttrue(int left, int right){
	if (left == right)
		return 1;
	else return 0;
} 

//randomizing tests for greatHall
//greatHall takes state and handPos, so we randomize those inputs
//should see a net zero in handCount because draws 1 and discards 1, and numActions should increase by 1

int main(){

	int passed = 0, failed = 0;

	int passedAll = 1;

	//cards
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("BEGINNING GREAT HALL RANDOM TEST GENERATOR\n");
	printf("------------------------------------------\n");

		//num tests denotes how many times random test generator is run for
	for (int i = 0; i < NUM_TESTS; i++){

		//greatHallEff takes input of gameState, therefore randomize this.

		struct gameState state; // declare new one each time
		int numPlayers = rand() % 3 + 2; //need +2 to ensure atleast 2 players [2,4]
		int randSeed = rand() % 28 + 36; //arbitrary number for the seed, +36 to ensure positive seed
		initializeGame(numPlayers, k, randSeed, &state);

		//for each randomized game state, test greatHall card

		//saving previous state
		int player = state.whoseTurn; //person who will be playing the card

		int prevActions = state.numActions; //preserve numActions
		int prevHandCount = numHandCards(&state); //preserve handCount

		int r = greatHallEff(&state, rand() % prevHandCount); //notice randomizing of handPos

		int postHandCount = numHandCards(&state); //should be neutral, no gain
		int postActions = state.numActions; //should be +1

		//handCount
		if ( !asserttrue(prevHandCount + CARDS_DRAWN - DISCARD, postHandCount) ){
			failed++;
			printf("failed handCount test\nprev: %d, post: %d\n", prevHandCount, postHandCount);
			passedAll = 0;
		} else passed++;

		//actionCount, should add 1 action
		if ( !asserttrue(prevActions + ACTION_INCREASE, postActions) ){
			failed++;
			printf("failed actionCount test\nprev: %d, post: %d\n", prevActions, postActions);
			passedAll = 0;
		}
		else passed++;


	}

	printf("passed tests: %d, failed tests: %d\n", passed, failed);
	return 0;
}