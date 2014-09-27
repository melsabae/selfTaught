#include <stdio.h>
#include <stdbool.h>

#define SUM 1000

#define CONDITION1 (( a + b + c ) == SUM )
#define CONDITION2 ((( a * a ) + ( b * b )) == ( c * c ))


int main(){
	int a, b, c;

	for( c = 997; c > b; c-- ){ // 997 comes from b = 2, a = 1 as minimums
		for( b = c - 1; b > a; b-- ){
			if( b + c >= SUM || b + c + b - 1 < SUM ) // dont bother trying a if either are true
				continue;

			for( a = b - 1; a >= 1; a-- ){
				if( a + b + c < SUM ) // a only makes it worse as it goes on
					break;

				if( a + b + c != SUM ) // keep going until it works
					continue;

				if( CONDITION1 && CONDITION2 ){ // winner
					printf( "%d, %d, %d\n", a, b, c );
					printf( "%d\n", a * b * c );
					c = 0; // break parent loops conditions
				}

			}
		}
	}

	return 0;
}
