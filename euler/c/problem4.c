#include <stdio.h>
#include <stdbool.h>

// 6 is maximum number of digits possible for this problem, 5 the least
// comes from 999*999 = 998,001, and 100*100 = 10,000
#define MAXDIGITS 6
#define FIVEDIGITS 99999
#define MAX 999
#define MIN 100

// maximum for int division for this problem
#define DIVISOR 100000

int digits[ MAXDIGITS ];
int divisor = DIVISOR, i = 0;
bool fivedigits = false;

bool isPalindromic( int arg ){
	// reset vars and array
	divisor = DIVISOR;
	fivedigits = false;
	i = 0;
	for( int index = 0; index < MAXDIGITS; index++ ){
		digits[ index ] = 0;
	}

	// start the array on the next element, first element will be 0, does not affect sum or
	// if returns true or false
	// lowers divisor to an appropriate amount for division
	if( arg <= FIVEDIGITS ){
		i = 1;
		divisor /= 10;
		fivedigits = true;
	} else {
		i = 0;
	}

	// fill array with single digits from arg
	for(; i < MAXDIGITS; i++ ){	

		// pop off first number into array
		digits[ i ] = arg / divisor;

		// remove first digit
		arg -= digits[ i ] * divisor;

		// reduce divisor for next run
		divisor /= 10;
	}

	// selects appropriate comparisons for problem
	if( fivedigits ){
		return (( digits[ 1 ] == digits[ 5 ] ) &&
				( digits[ 2 ] == digits[ 4 ] ));
	} else {
		return (( digits[ 0 ] == digits[ 5 ] ) &&
				( digits[ 1 ] == digits[ 4 ] ) &&
				( digits[ 2 ] == digits[ 3 ] ));
	}
}

int main(){
	/* this method did not work
	// try x down to 100 from 999, while y = 999
	for(; x > 99; x-- ){
	if( isPalindromic( x * y )){
	break;
	}
	}

	x = MIN;

	// try y down to 100 from 999, while x = 100
	for(; y > 99; y--){
	if( isPalindromic( x * y )){
	break;
	}
	}

	// reset x and y
	x = y = MAX;

	this method produced a good result, but not the correct one
	// try stepping each number down at the same time
	while( !isPalindromic( x * y )){
	x--;
	if( isPalindromic( x * y )){
	break;
	}

	y--;
	}
	*/

	int test, x, y = MAX;
	int answer = 0;

	for(; y >= MIN; y-- ){

		// x gains y's value to remove calculations that have already been done
		for( x = y; x >= MIN; x-- ){
			test = x * y;
			printf("%d %d\n", x, y);
			if( isPalindromic( test )){
				if(( test ) > answer ){
					answer = test;
				}
			}
		}
	}
	printf("largest palindromic number: %d\n", answer );
}
