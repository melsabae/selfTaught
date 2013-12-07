#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* once i figure out how to evaluate performance of these algorithms
 * ill spend days figuring out what is better in terms of speed, or
 * in terms of memory usage, but my OCD will be sated */


/* spills array to screen, in 5 columns, tab delimited
 * things get weird, however the structure is mostly correct,
 * 	when using long numbers */
void printArray(long long *array, unsigned short arrayLen)
{
	printf("array[*] = {\n");
	for (unsigned register short i = 0; i < arrayLen; i++, array++) {

		/* 1 is added to i in the if condition
		 *	so that natural counting is what happens when
		 *	the columns are printing  */
		if  ((i + 1) % 5 == 0) {
			printf("%lld,\n", *array);
		} else {
			printf("%lld,\t", *array);
		}
	}

	printf("}\n");
}

// im leaving this one in here for comparison purposes
/* selection sort implementation, using nested for-loops
 * brings smallest numbers to the top */
void arraySelectionSort(long long *array, unsigned short arrayLen)
{
	long long temp;

	/* i and arrayIndex are used differently,
	 *	arrayIndex moves up to the next element in the array
	 *	and starts each iteration from that point
	 *	in each iteration of the outer loop
	 * i absorbs that value, moving through each element
	 *	incrementally on the inner loop */
	for (unsigned register short arrayIndex = 0;
			arrayIndex < arrayLen; arrayIndex++)
		for (unsigned register short i = arrayIndex;
				i < arrayLen; i++)
			if (array[i] < array[arrayIndex]) {
				temp = array[i];
				array[i] = array[arrayIndex];
				array[arrayIndex] = temp;
			}

	assert (array[0] < array[arrayLen - 1]);
}

/* slightly modified for quicker execution */
void arraySelectionSort2(long long *array, unsigned short arrayLen)
{
	long long temp;
	bool modified = false;
	
	for (unsigned register short arrayIndex = 0; arrayIndex < arrayLen; arrayIndex++) {
		for (unsigned register short i = arrayIndex; i < arrayLen; i++) {
			if (array[i] < array[arrayIndex]) {
				temp = array[i];
				array[i] = array[arrayIndex];
				array[arrayIndex] = temp;
				modified = true;
			}
			
			/* after finding a smaller value, no need to
			 * go through the rest of the array
			 * at least according to this logic */

			 /* should be noted that SO FAR this works
			  * and has passed many times flawlessly */
		}

		if (modified)
			continue;
		else
			printf("%d\n", arrayIndex);
			break;
	}
}

/* the description of bubblesort appeared to be the same as the
 * selection sort, but further readings into the algorightm
 * show they are only conceptually similar
 *
 * i was convinced of my own genius, and do not understand the problem
 *
 * leaving this here so i have a way of reverse sorting an array
 * however it is not a true bubble sort
 *
 * i will likely not implement a true bubble sort, the algorithm
 * suggests inefficiency in terms of IO */
void arrayBubbleSort(long long *array, unsigned short arrayLen)
{
	long long temp; 

	for (unsigned register short arrayIndex = 0;
			arrayIndex < arrayLen; arrayIndex++)
		for (unsigned register short i = arrayIndex;
				i < arrayLen; i++, arrayLen--)
			if (array[i] > array[arrayIndex]) {
				temp = array[arrayIndex];
				array[arrayIndex] = array[i];
				array[i] = temp;
			}
	
	assert (array[0] > array[arrayLen - 1]);
}
