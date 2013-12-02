#include <stdio.h>
#include <assert.h>

/* spills array to screen, in 5 columns, tab delimited
 * things get weird, however the structure is mostly correct,
 * 	when using long numbers */
void printArray(long long *array, unsigned short arrayLength)
{
	printf("array[*] = {\n");
	for (unsigned register short i = 0; i < arrayLength; i++, array++)
		/* 1 is added to i in the if condition
		 *	so that natural counting is what happens when
		 *	the columns are printing  */
		if  ((i + 1) % 5 == 0) {
			printf("%lld,\n", *array);
		} else {
			printf("%lld,\t", *array);
		}

	printf("}\n");
}

/* selection sort implementation, using nested for-loops
 * brings smallest numbers to the top */
void arraySelectionSort(long long *array, unsigned short arrayLength)
{
	long long temp;

	/* i and arrayPosition are used differently,
	 *	arrayPosition moves up to the next element in the array
	 *	and starts each iteration from that point
	 *	in each iteration of the outer loop
	 * i absorbs that value, moving through each element
	 *	incrementally on the inner loop */
	for (unsigned register short arrayPosition = 0;
			arrayPosition < arrayLength; arrayPosition++)
		for (unsigned register short i = arrayPosition;
				i < arrayLength; i++)
			if (array[i] < array[arrayPosition]) {
				temp = array[i];
				array[i] = array[arrayPosition];
				array[arrayPosition] = temp;
			}

	assert (array[0] < array[arrayLength - 1]);
}

/* the way the book described the bubble sort was the same as the
 *	selection sort, with the comparison reversed
 * this bubblesort is reversed from the book's description
 * 	to bring the largest numbers to the top
 *
 * bubble sort implementation, using nested for-loops */
void arrayBubbleSort(long long *array, unsigned short arrayLength)
{
	long long temp; 

	for (unsigned register short arrayPosition = 0;
			arrayPosition < arrayLength; arrayPosition++)
		for (unsigned register short i = arrayPosition;
				i < arrayLength; i++)
			if (array[i] > array[arrayPosition]) {
				temp = array[arrayPosition];
				array[arrayPosition] = array[i];
				array[i] = temp;
			}
	
	assert (array[0] > array[arrayLength - 1]);
}
