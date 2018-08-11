/*****
* Author: Keane Lim
* Date: 07/22/18
* Description: Unit Test for adventurer - REFACTORED FOR PRATICOK
****/

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

//testing adventurer
//current player should receive 2 cards, and discard 1

//observations
//only withdraws 1 treasure
//does not discard itself from hand (these two bugs negated each other)
//despite having two non treasure cards at the front, deckCount not correct

int main(){

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	struct gameState state, statecopy;

	// initialize a game state and player cards
	initializeGame(2, k, 6, &state);

	//hardcode random values to make it easier for comparisons
	int player = 0;
	int bonus = 0;
	state.handCount[player+1] = state.handCount[player] = 5;
	state.deckCount[player+1] = state.deckCount[player] = 10;

	// copy the game state to a test case
	memcpy(&statecopy, &state, sizeof(struct gameState));   

	//make it so all cards in player's deck are coppers except last 2 (for discard)
	for (int i = 0; i < 9; i++){
		state.deck[player][i] = copper;
	}
		state.deck[player][9] = state.deck[player][8] = minion; //make first 2 non-treasure


	printf("BEGINNING CARD TEST 2 - ADVENTURER\n");
	printf("----------------------\n");

	// //now edit state by calling cardEffect
	int r = cardEffect(adventurer, 0, 0, 0, &state, 0, &bonus);

	//test that 2 cards are drawn from deck - 1 discard after playing adventurer
	//should fail because bug introduced was to increase by only 1,
	//however another persisting bug negates that (discard does not occur)
	//so it actually passes

	if ( !asserttrue(6, state.handCount[player]) )
		printf("fail hand. expected: 6 cards after adventurer, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");


	//test whether 4 cards are removed from deck (two discarded, two treasures)
	if ( !asserttrue(6, state.deckCount[player]) )
		printf("fail deck. expected: 6 cards after adventurer, actual: %d\n", state.deckCount[player]);
	else printf("pass deckCount\n");

	// //reset state
	memcpy(&state, &statecopy, sizeof(struct gameState));  

	//repeat test with other treasures
	for (int i = 0; i < 10; i++){
		if (i == 9 || i == 8)
			state.deck[player][i] = minion;
		else state.deck[player][i] = silver;
	}

	// //now edit state by calling cardEffect
	int s = cardEffect(adventurer, 0, 0, 0, &state, 0, &bonus);

	if ( !asserttrue(6, state.handCount[player]) )
		printf("fail hand. expected: 6 cards after adventurer, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");


	//test whether 4 cards are removed from deck (two discarded, two treasures)
	if ( !asserttrue(6, state.deckCount[player]) )
		printf("fail deck. expected: 6 cards after adventurer, actual: %d\n", state.deckCount[player]);
	else printf("pass deckCount\n");


	//reset state
	memcpy(&state, &statecopy, sizeof(struct gameState));  

	//repeat test with other treasures
	for (int i = 0; i < 10; i++){
		if (i == 9 || i == 8)
			state.deck[player][i] = minion;
		else state.deck[player][i] = gold;
	}

	//now edit state by calling cardEffect
	int g = cardEffect(adventurer, 0, 0, 0, &state, 0, &bonus);

	if ( !asserttrue(6, state.handCount[player]) )
		printf("fail hand. expected: 6 cards after adventurer, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");


	//test whether 4 cards are removed from deck (two discarded, two treasures)
	if ( !asserttrue(6, state.deckCount[player]) )
		printf("fail deck. expected: 6 cards after adventurer, actual: %d\n", state.deckCount[player]);
	else printf("pass deckCount\n");


	//make sure that changes aren't happening to other player
	//handcount
	if ( !asserttrue(5, state.handCount[player+1]) )
		printf("fail hand. expected: 5 cards after adventurer, actual: %d\n", state.handCount[player+1]);
	else printf("pass handCount\n");

	//deckcount
	if ( !asserttrue(10, state.deckCount[player+1]) )
		printf("fail deck. expected: 10 cards after adventurer, actual: %d\n", state.deckCount[player+1]);
	else printf("pass deckCount\n");


	return 0;
}