/* A program for sorting arrays
 * Takes no command line arguments
 * User will enter each array element (int)
 * and after sorting, the arrays will be printed out */

#include <stdio.h>
#include "ch8_Dc_include.c"

/* mayhaps allow a user to pass CLI argument for number of
 * elements they wish to use, making this more useful generally
 * as well as the type of sort they wish to use instead of
 * dumping 2 to the screen */
int main(void)
{
	unsigned short numElmnts = 25;
	long long int copy0[numElmnts], copy1[numElmnts];

	for (unsigned register short i = 0; i < numElmnts; i++) {
		/* add 1 to array index, because user will use natural
		 *	counting, not index0 counting */
		printf("Enter number to store: %d\n", i+1);
		scanf("%lld", &copy0[i]);

		/* duplicate */
		copy1[i] = copy0[i];
	}

	printf("\n\n\tSelection Sort:\n");
	arraySelectionSort(&copy0[0], numElmnts);
	printArray(&copy0[0], numElmnts);

	
	printf("\n\n\tBubble Sort:\n");
	arrayBubbleSort(&copy1[0], numElmnts);
	printArray(&copy1[0], numElmnts);

	return 0;
}
