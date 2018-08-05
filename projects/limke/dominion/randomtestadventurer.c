/*****
* Author: Keane Lim
* Date: 08/04/18
* Description: Random Test for Adventurer
****/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> //taken from cardtest4.c template

#define NUM_TESTS 2000
#define DISCARD 1 //adventurer should be discarded after being played
#define CARDS_DRAWN 2 //adventurer should draw only 2 cards

//as per HW specs,
//use own asserttrue function to avoid crashing from standard C assert
int asserttrue(int left, int right){
	if (left == right)
		return 1;
	else return 0;
} 

int coinCount(int, struct gameState*); //function prototype
int adventurerEff(struct gameState*); //function prototype

//testing adventurer with randomly generated inputs
int main(){

	int passed = 0, failed = 0;

	int passedAll = 1;

	//cards
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	printf("BEGINNING ADVENTURER RANDOM TEST GENERATOR\n");
	printf("------------------------------------------\n");

	//num tests denotes how many times random test generator is run for
	for (int i = 0; i < NUM_TESTS; i++){

		//adventurerEff takes input of gameState, therefore randomize this.

		struct gameState state; // declare new one each time
		int numPlayers = rand() % 3 + 2; //need +2 to ensure atleast 2 players [2,4]
		int randSeed = rand() % 28 + 36; //arbitrary number for the seed, +36 to ensure positive seed
		initializeGame(numPlayers, k, randSeed, &state);

		//for each randomized game state, test adventurer card


		//saving previous state
		int player = state.whoseTurn; //person who will be playing the card
		int prevHandCount = numHandCards(&state); //preserve handCount

		int numCoins = coinCount(player, &state);

		int r = adventurerEff(&state);

		int postHandCount = numHandCards(&state); //preserve handCount
		int postNumCoins = coinCount(player, &state); //still want same player

		//handCount
		if ( !asserttrue(prevHandCount + CARDS_DRAWN - DISCARD, postHandCount) ){
			failed++;
			printf("failed handCount test\nprev: %d, post: %d\n", prevHandCount, postHandCount);
			passedAll = 0;
		} else passed++;

		//coinCount
		if ( !asserttrue(numCoins + 2, postNumCoins) ||   // copper + copper
			 !asserttrue(numCoins + 3, postNumCoins) ||	  // copper + silver
			 !asserttrue(numCoins + 4, postNumCoins) ||	  // copper + gold, or silver + silver
			 !asserttrue(numCoins + 5, postNumCoins) ||	  // silver + gold 		
			 !asserttrue(numCoins + 6, postNumCoins)  )	  // gold + gold
		{ 

			failed++;
			printf("failed numCoin test\nprev: %d, post: %d\n", numCoins, postNumCoins);
			passedAll = 0;
		}
		else passed++;


	}

	printf("passed tests: %d, failed tests: %d\n", passed, failed);

	return 0;
}

//coinCount():
//snippet taken from updateCoins function,
//helps calculate current coin value of player's hand.
int coinCount(int player, struct gameState* state){

	int val = 0;
	int i;

	//taken from updateCoins
	for (i = 0; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == copper)
    {
      val += 1;
    }
    else if (state->hand[player][i] == silver)
    {
      val += 2;
    }
    else if (state->hand[player][i] == gold)
    {
      val += 3;
    }
  }

  	return val;
}