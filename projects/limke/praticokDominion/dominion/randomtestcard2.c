/*****
* Author: Keane Lim
* Date: 08/04/18
* Description: Random Test for Smithy -- card we implemented unit tests for in Assignment 3
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
#define CARDS_DRAWN 3 //great hall draws one card

void smithyCard(int, struct gameState*, int); 

//as per HW specs,
//use own asserttrue function to avoid crashing from standard C assert
int asserttrue(int left, int right){
	if (left == right)
		return 1;
	else return 0;
} 

//randomizing game state and handPos for smithyEff function
//smithy should +3 cards, -1 discard, and should not change any other states

int main(){

	int passed = 0, failed = 0;

	int passedAll = 1;

	//cards
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("BEGINNING SMITHY RANDOM TEST GENERATOR\n");
	printf("------------------------------------------\n");

	//num tests denotes how many times random test generator is run for
	for (int i = 0; i < NUM_TESTS; i++){

		//smithyEff takes input of gameState, therefore randomize this.

		struct gameState state; // declare new one each time
		int numPlayers = rand() % 3 + 2; //need +2 to ensure atleast 2 players [2,4]
		int randSeed = rand() % 28 + 36; //arbitrary number for the seed, +36 to ensure positive seed
		initializeGame(numPlayers, k, randSeed, &state);

		//for each randomized game state, test smithy card

		//saving previous state
		int player = state.whoseTurn; //person who will be playing the card
		// int player = rand() % numPlayers;

		int prevHandCount = numHandCards(&state); //preserve handCount
		int prevActions = state.numActions;
		
		// state.whoseTurn = player; //make sure to set randomized player to the state

		// int r = smithyEff(&state, rand() % prevHandCount); //randomize hand position
		smithyCard(rand() % prevHandCount, &state, player); //randomize hand position

		int postHandCount = numHandCards(&state); //should be net two, +3 draw, -1 discard
		int postActions = state.numActions; //should not change

		//handCount, should +2 from previous handCount
		if ( !asserttrue(prevHandCount + CARDS_DRAWN - DISCARD, postHandCount) ){
			failed++;
			printf("failed handCount test\nprev: %d, post: %d\n", prevHandCount, postHandCount);
			passedAll = 0;
		} else passed++;

		//actionCount -- smithy should not change numActions
		if ( !asserttrue(prevActions, postActions) ){
			failed++;
			printf("failed actionCount test\nprev: %d, post: %d\n", prevActions, postActions);
			passedAll = 0;
		}
		else passed++;

	}

	printf("passed tests: %d, failed tests: %d\n", passed, failed);
	return 0;
}