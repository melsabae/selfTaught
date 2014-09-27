#include <stdio.h>

int fibonacci( int first, int second );

int term1 = 0, term2 = 1, newsum = 0;

int fibonacci( int first, int second ){
	newsum = first + second;
	term1 = second;
	term2 = newsum;

	return newsum;
}

int main(){
	int mysum = 0, holder = 0;

	while ( term1 + term2 < 4000001 ){
		holder = fibonacci( term1, term2 );

		if ( holder % 2 == 0 ){
			mysum += holder;
		}
	}

	printf( "%d\n", mysum );
}

