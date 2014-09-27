#define NUMBER 600851475143
#include <stdbool.h>
#include <stdio.h>

long long largestFactor( long long arg );
int isPrime( long long arg );

long long largestFactor( long long arg ){
	for ( long long i = 2; i < arg ; i++ ){
		if( arg % i == 0 ){
			arg /= i;
			break;
		}
	}

	return arg;
}

int isPrime( long long arg ){
	for ( long i = 2; i < arg ; i++ ){
		if( arg % i == 0 ){
			return false;
		}
	}
	
	return true;
}

int main(){
	long long number = NUMBER;
	long long test = largestFactor( number );

	while( !( isPrime( test ))){
			test = largestFactor( test );
	}

	printf( "largest prime factor: %lld\n", test );

	return 0;
}
