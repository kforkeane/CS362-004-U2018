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

//testing numHandCards
//should return the number of cards
int main(){

	//variable setup
	struct gameState state; //state of game
	int numPlayer = 2, testPlayer = 0; //explicitly targetting testPlayer (since can't init game without 2 players)
	int seed = 28; //initGame seed
	//k stands for kingdom cards, from testUpdate template
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	memset(&state, 23, sizeof(struct gameState));   // clear the game state
    int r = initializeGame(numPlayer, k, seed, &state); // initialize a new game (taken from testUpdate template)

    int fails = 0, passes = 0, passedAll = 1; //passedAll is bool flag

	printf("BEGINNING UNIT TEST 1\n");
	printf("----------------------\n");

	//valid hand counts 0 <= n <= MAX_HAND
	int result;
	for (int i = 0; i <= MAX_HAND; i++){


		state.handCount[testPlayer] = i; 

		result = asserttrue(i, numHandCards(&state));
		if (result == 0){
			fails++;
			passedAll = 0;
		}
		else passes++;

	}

	//invalid hand counts, but will still pass because it simply returns handCount for whoseTurn
	//[-48, 0]

	for (int i = -48; i <= 0; i++){

		state.handCount[testPlayer] = i; 

		result = asserttrue(i, numHandCards(&state));
		if (result == 0){
			fails++;
			passedAll = 0;
		}
		else passes++;
	}

	//invalid hand counts, but will still pass because it simply returns handCount for whoseTurn
	//[MAXHAND+1, 49]

	for (int i = MAX_HAND; i <= MAX_HAND + 49; i++){


		state.handCount[testPlayer] = i; 

		result = asserttrue(i, numHandCards(&state));
		if (result == 0){
			fails++;
			passedAll = 0;
		}
		else passes++;
	}

	//test should fail

	for (int i = 0; i <= MAX_HAND; i++){
		state.handCount[testPlayer] = i; 

		result = asserttrue( (i-1) , numHandCards(&state));  //should be 1 off
		if (result == 1){
			fails++;
			passedAll = 0;
		}
		else passes++;

	}

	if (passedAll) //should be  501 + 49 + 50 + 501 = 1110 passes
		printf("%d tests failed\npassed all %d tests successfully\n", fails, passes);
	else
		printf("test(s) failed\n");

	return 0;
}