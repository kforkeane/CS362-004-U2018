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

//testing to see if getCost returns the correct cost

int main(){

	//init cards
	int k[10] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast };
	
	//init theoretical results array
	int expected_costs[10] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 4 };

	printf("BEGINNING UNIT TEST 3\n");
	printf("----------------------\n");

	//getCost result of k[i] should match respective index on expected_costs
	//expected_costs generated by looking at hardcoded values on cards
	int result; 
	int fails = 0, passes = 0, passedAll = 1;
	
	for (int i = 0; i < 10; i++){

		result = asserttrue(expected_costs[i], getCost(k[i]));
		if (result == 0){
			fails++;
			passedAll = 0;
		}
		else passes++;
	}

	//this should fail, because expected_costs will be reduced by 1
	for (int i = 0; i < 10; i++){

		result = asserttrue( (expected_costs[i] - 1) , getCost(k[i]));
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