#include <stdio.h>
#include <stdbool.h>

int main(){
	long long i;
	int j;
	bool bools[ 20 ] = { false };
	bool found = false;
	
	// add 20 because the number has to be divisible by 20
	for( i = 20; ; i += 20 ){
		// fill divisble numbers' array slot with true, defaults are false
		for( j = 1; j <= 20; j ++ ){
			if( i % j == 0 ){
				// offset by 1 for array indexing
				bools[ j - 1 ] = true;
			} else {
				break;
			}
		}

		// flag to end looping if all are true, else set false and break
		for( int k = 0; k <= 19; k++ ){
			if( bools[ k ] == true ){
				found = true;
			} else {
				found = false;
				break;
			}
		}

		// dump number and break for exit
		if( found == true ){
			printf("%lld\n", i );
			break;
		}
	}

	return 0;

}
