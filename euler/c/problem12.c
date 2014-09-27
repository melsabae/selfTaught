#include <stdio.h>

int numFactors;

int countFactors( unsigned long long arg ){
	numFactors = 2;

	for( unsigned long long i = 2; i < arg; i++ ) // going up to halfway point saves time
		if( arg % i == 0 )
			numFactors++;

	return numFactors;
}

int main(){
	unsigned long long start, counter;

	for( start = 0, counter = 1; numFactors < 500; start += counter, counter++ )
		printf( "%lld\t%d\n", start, countFactors( start ));

	return 0;
}
