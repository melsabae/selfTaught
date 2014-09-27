#include <stdio.h>
#include <math.h>

int main(){
	int sum_square = 0, square_sum = 0;

	for( int i = 1; i <= 100; i++ ){
		sum_square += pow( i, 2 );
		square_sum += i;
	}

	square_sum = pow( square_sum, 2 );

	printf("sum of squares: %d\n", sum_square );
	printf("square of sums: %d\n", square_sum );
	printf("difference: %d\n", square_sum - sum_square );
}
