/*****
* Author: Keane Lim
* Date: 07/22/18
* Description: Unit Test for councilRoom
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

	// copy the game state to a test case
	memcpy(&statecopy, &state, sizeof(struct gameState));   

	//test that player gets 4 cards
	printf("BEGINNING CARD TEST 3 - COUNCIL ROOM\n");
	printf("----------------------\n");

	int r = cardEffect(council_room, 0, 0, 0, &state, 0, &bonus);

	//should gain 4 cards - 1 from after discard
	//should fail because of bug that adds one extra card to hand
	if ( !asserttrue(8, state.handCount[player]) )
		printf("fail hand. expected: 8 cards after council, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");

	//check to see if 4 cards were removed from his deck
	//should fail because of extra draw
	if ( !asserttrue(6, state.deckCount[player]) )
		printf("fail. expected: 6 cards after council, actual: %d\n", state.deckCount[player]);

	//check that other player got a card
	if ( !asserttrue(6, state.handCount[player+1]) )
		printf("fail hand. expected: 6 cards after council, actual: %d\n", state.handCount[player+1]);
	else printf("pass handCount\n");

	//check numBuys was incremented
	if ( !asserttrue(3, state.numBuys) )
		printf("fail numBuys. expected: 3 buys after council, actual: %d\n", state.numBuys);
	else printf("pass numBuys\n");

	return 0;
}