#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> //taken from cardtest4.c template

//as per HW specs,
//use own asserttrue function to avoid crashing from standard C assert
int asserttrue(int left, int right){
	if (left == right)
		return 1;
	else return 0;
} 

//testing councilRoom

int main(){

	struct gameState state, statecopy;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(2, k, 6, &state);

	//hardcode random values to make it easier for comparisons
	int player = 0;
	int bonus = 0;
	state.handCount[player+1] = state.handCount[player] = 5;
	state.deckCount[player+1] = state.deckCount[player] = 10;
	state.numBuys = 2;
	state.numActions = 2; 

	// copy the game state to a test case
	memcpy(&statecopy, &state, sizeof(struct gameState));   

	printf("BEGINNING CARD TEST 4 - GREAT HALL\n");
	printf("----------------------\n");

	int r = cardEffect(great_hall, 0, 0, 0, &state, 0, &bonus);

	//test if you gain net zero (gain 1 card, but discard 1 card)
	if ( !asserttrue(5, state.handCount[player]) )
		printf("fail hand. expected: 5 cards after hall, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");

	//check if state changed to +1 actions
	if ( !asserttrue(3, state.numActions) )
		printf("fail numAct. expected: 3 cards after hall, actual: %d\n", state.numActions);
	else printf("pass numActions\n");

	//check if deckCount decreased by 1
	if ( !asserttrue(9, state.deckCount[player]) )
		printf("fail deck. expected: 9 cards after hall, actual: %d\n", state.deckCount[player]);
	else printf("pass deckCount\n");

	//make sure other players don't gain any cards
	if ( !asserttrue(10, state.deckCount[player+1]) )
		printf("fail deck. expected: 10 cards after hall, actual: %d\n", state.deckCount[player+1]);
	else printf("pass deckCount\n");

	return 0;
}

