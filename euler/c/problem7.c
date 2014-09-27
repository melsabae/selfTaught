#include <stdio.h>
#include <stdbool.h>

bool isPrime( int arg ) {
	for( int i = 2; i < arg; i++ ){
		if( arg % i == 0 ){
			return false;
		}
	}

	return true;
}

int main(){
	int counter = 1;
	printf("%d: 2\n", counter );

	for( int i = 3; ; i += 2 ){
		if( isPrime( i )){
			counter++;
			printf("%d: %d\n", counter, i );
		}

		if( counter == 10001 ){
			break;
		}
	}

}
