/*****
* Author: Keane Lim
* Date: 07/22/18
* Description: Unit Test for smithy - REFACTORED FOR PRATICOK
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

//testing smithy
//current player should receive exactly 3 cards then discard one

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

	printf("BEGINNING CARD TEST 1 - SMITHY\n");
	printf("----------------------\n");

	//now edit state by calling cardEffect
	int r = cardEffect(smithy, 0, 0, 0, &state, 0, &bonus);

	//check to see if person playing card gained +3 cards
	//5 original, +3 smithy, -1 discard
	//shouldn't pass, bug detected.
	if ( !asserttrue(7, state.handCount[player]) )
		printf("fail hand. expected: 7 cards after smithy, actual: %d\n", state.handCount[player]);
	else printf("pass handCount\n");

	//check to see if 3 cards were removed from his deck
	//shouldn't pass, bug detected.
	if ( !asserttrue(7, state.deckCount[player]) )
		printf("fail deck. expected: 7 cards after smithy, actual: %d\n", state.deckCount[player]);
	else printf("pass\n");
	
	//check to see if other players had a state change (handCount)
	//should pass
	if ( !asserttrue(5, state.handCount[player+1]) )
		printf("fail other player hand. expected: 5 cards after smithy, actual: %d\n", state.handCount[player+1]);
	else printf("pass\n");

	//check to see if other players had a state change (deckCount)
	//should pass
	if ( !asserttrue(10, state.deckCount[player+1]) )
		printf("fail other player deck. expected: 10 cards after smithy, actual: %d\n", state.deckCount[player+1]);
	else printf("pass\n");

	return 0;
}