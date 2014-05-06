#include <stdio.h>
#include "colors.c"

int main() {
	char *string = "hello, world";
	char *ptr = bold( string );

	/*
	printf("%s%s%s\n", bold2(), string, resetFmt( ));
	*/

	printf( "%s\n", ptr);

	printf("segfault over?\n");

	return 0;
}
