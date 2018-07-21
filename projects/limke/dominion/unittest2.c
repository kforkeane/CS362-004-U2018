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

//testing to see if the kingdomCards array returns correctly

int main(){

	//variable setup
	struct gameState state; //state of game
	int numPlayer = 2; //explicitly targetting testPlayer (since can't init game without 2 players)
	int seed = 28; //initGame seed

	//k stands for kingdom cards, from testUpdate template
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	memset(&state, 23, sizeof(struct gameState));   // clear the game state
    int r = initializeGame(numPlayer, k, seed, &state); // initialize a new game (taken from testUpdate template)

    int fails = 0, passes = 0, passedAll = 1; //passedAll is bool flag

	printf("BEGINNING UNIT TEST 2\n");
	printf("----------------------\n");

	//init k_result array
	int* k_result = kingdomCards(adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room);

	//compare k_result to k initial,
	//the cards at each index should match each other

	//the same as testing:
	//if (k_result[0] == adventurer) 
	//if (k_result[1] == embargo) etc.

	int result;

	for (int i = 0; i < 10; i++){

		result = asserttrue(k[i], k_result[i]);
		if (result == 0){
			fails++;
			passedAll = 0;
		}
		else passes++;
	}

	//compare array with array of card that isn't in list
	//this card is not in the kingdomCards arguments, so it won't pass in any case
	int voodoo[10] = { curse, curse, curse, curse, curse, curse, curse, curse, curse, curse };

	for (int j = 0; j < 10; j++){
		result = asserttrue(voodoo[j], k_result[j]);
		if (result == 1){
			fails++;
			passedAll = 0;
		}
		else passes++;
	}

	if (passedAll) //should be 10 + 10 passes
		printf("%d tests failed\npassed all %d tests successfully\n", fails, passes);
	else
		printf("test(s) failed\n");

	return 0;
}