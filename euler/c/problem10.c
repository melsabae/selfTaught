#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime( int arg ){
	if( arg == 2 )
		return true;

	if( arg % 2 == 0 )
		return false;

	for( int i = 3; i <= sqrt( arg ) + 1; i += 2 ){
		/*
		if( !isPrime( i ))
			continue; 
			*/

		if( arg % i == 0 )
			return false;
	}

	return true;
}

int main(){
	long sum = 2;

	for( int i = 3; i < 2000000; i += 2 )
		if( isPrime( i ))
			sum += i;

	printf( "sum: %ld\n", sum );

	return 0;
}
