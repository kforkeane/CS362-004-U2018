/*****
* Author: Keane Lim
* Date: 07/22/18
* Description: Unit Test for initializeGame()
****/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"     //header taken from testUpdate sample

//as per HW specs,
//use own asserttrue function to avoid crashing from standard C assert
int asserttrue(int left, int right){
	if (left == right)
		return 1;
	else return 0;
} 

//testing to see if game is initialized correctly

int main(){

	//variable setup
	struct gameState state; //state of game
	int seed = 28; //initGame seed

	// theoretical values:
	// ++++++++++++++++++++++

	//k stands for kingdom cards, from testUpdate template
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	int numPlayer = 2; //explicitly targetting testPlayer (since can't init game without 2 players)

	memset(&state, 23, sizeof(struct gameState));   // clear the game state
	int r = initializeGame(numPlayer, k, seed, &state); // initialize a new game (taken from testUpdate template)

	int fails = 0, passes = 0, passedAll = 1; //passedAll is bool flag
	int result;

	printf("BEGINNING UNIT TEST 4\n");
	printf("----------------------\n");

	//check state->numPlayers
	result = asserttrue(2, state.numPlayers);
	if (result == 0){
		fails++;
		// printf("test failed check numPlayers\n");
		passedAll = 0;
	}
	else passes++;

	//check that initGame negates kingdom arrays with duplicates
	struct gameState state2;
	int k2[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, council_room, council_room}; //notice dup council_room

	memset(&state2, 23, sizeof(struct gameState));   // clear the game state
	int r2 = initializeGame(numPlayer, k2, seed, &state2); // initialize a new game (taken from testUpdate template)

	result = asserttrue(-1, r2);
	if (result == 0){
		fails++;
		// printf("test failed check -1\n");
		passedAll = 0;
	}
	else passes++;

	//check supply count for curse, it should be 10 for two players
	result = asserttrue(10, state.supplyCount[curse]);
	if (result == 0){
		fails++;
		// printf("test failed check curse\n");
		passedAll = 0;
	}
	else passes++;

	//check supply count for victory cards, it should be 8 for two players
	int victory_cards[3] = { estate, duchy, province };

	for (int i = 0; i < 3; i++){

		result = asserttrue(8, state.supplyCount[victory_cards[i]]);

		if (result == 0){
			fails++;
			// printf("test failed check victories\n");
			passedAll = 0;
		}
		else passes++;
	}

	//check supplycount for treasure cards is accurate
	result = asserttrue(46, state.supplyCount[copper]);
	if (result == 0){
		fails++;
		// printf("test failed check coppers\n");
		passedAll = 0;
	}
	else passes++;

	result = asserttrue(40, state.supplyCount[silver]);
	if (result == 0){
		fails++;
		// printf("test failed check silvers\n");
		passedAll = 0;
	}
	else passes++;

	result = asserttrue(30, state.supplyCount[gold]);
	if (result == 0){
		fails++;
		// printf("test failed check golds\n");
		passedAll = 0;
	}
	else passes++;

	//check kingdom cards supply counts are correct
	for (int j = 0; j < 10; j++){
		result = asserttrue(10, state.supplyCount[ k[j] ]); //there are no victory kingdom cards, all should be 10
		if (result == 0){
			fails++;
			// printf("test failed check kingdom supplys\n");
			passedAll = 0;
		}
		else passes++;
	}

	//check that cards that were not in the initialization have supplyCount -1
	result = asserttrue(-1, state.supplyCount[great_hall]);
	if (result == 0){
		fails++;
		// printf("test failed check supply greathalls\n");
		passedAll = 0;
	}
	else passes++;

	//check that each player has a deckCount of 10

	//player 1 will have drawn, so it will be less than the initial.
	//use player 2 as blank slate

	result = asserttrue(10, state.deckCount[1]);
	if (result == 0){
		fails++;
		// printf("test failed check deckCounts\n");
		passedAll = 0;
	}
	else passes++;
	

	//check that each player has 3 estates and 7 coppers at beginning of round
	for (int l = 0; l < 2; l++){

		int num_estates = 0;
		int num_coppers = 0;

		for (int m = 0; m < 10; m++){
			if (state.deck[l][m] == estate)
				num_estates++;

			if (state.deck[l][m] == copper)
				num_coppers++;
		}

		int result_estate = asserttrue(3, num_estates);
		int result_copper = asserttrue(7, num_coppers);
		
		if ((result_estate == 0) || (result_copper == 0)){
			fails++;
			// printf("test failed check estate/coppers\n");
			passedAll = 0;

		}
		else passes++;
	}

	//make sure that player 1 has handCount 0, and player 0 has handCount 5.
	//only draw at start of game, and after end turn is called.

	result = asserttrue(5, state.handCount[0]);
	if (result == 0){
		fails++;
		passedAll = 0;
	}
	else passes++;

	//discard count should be 0
	result = asserttrue(0, state.discardCount[0]);
	if (result == 0){
		fails++;
		// printf("test failed check discardCountss\n");
		passedAll = 0;
	}
	else passes++;
	
	//check there are no embargo tokens currently
	for (int i = 0; i <= treasure_map; i++){
		result = asserttrue(0, state.embargoTokens[i]);
		if (result == 0){
			fails++;
			// printf("test failed check tokens\n");
			passedAll = 0;
		}
		else passes++;
	}

	if (passedAll) 
	printf("%d tests failed\npassed all %d tests successfully\n", fails, passes);
	else
	printf("test(s) failed\n");

	return 0;
}

