#include <stdio.h>
#include "colors.c"

int main() {
	printf( "%s%s%s\n", BOLD, "hi", RESET);
	return 0;
}
