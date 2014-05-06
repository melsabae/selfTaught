/* todo, implement actual display of heatmap - the purpose of this project
   allow replacement of BUFFER with a command line input
   heatmap for files? that would be cool to see what your file consists of
   continue encapsulating and strip main down to a handful of functions
   */
#include <stdio.h>
#include "colors.c"

// these are all printable ascii characters
// 32 is a space, 126 is ~      these are the upper/lower bounds
#define MIN_ASCII 32
#define MAX_ASCII 126
// defines a size for an array based on the bounds above
#define ASCII_RANGE 95
#define BUFFER 1000

// fill charsMap with counters for ascii chars used
/* (letter - MIN_ASCII) shifts the outputs to the front of the array
   because the first 32 ascii codes (numbers 0-31) are not printable */
void fillMap( int *map, char *input ) {
	// letter takes char and stores its ascii code as int
	unsigned short letter;

	// only deals with ascii codes 32 to 126 inclusive
	// silently ignores other values until we see the null terminator
	for ( unsigned register int i = 0; input[i] != '\0'; i++ ) {
		letter = input[i];
		if ( MIN_ASCII <= letter && MAX_ASCII >= letter ) {
			map[( letter - MIN_ASCII )]++;
		}
	}
}

// make sure your stuff is null terminated or literal
void dumpString( char *description, char *input ) {
	printf( "%s: %s\n", description, input );
}

// dumps charmap, any array really, in tabular format
void dumpArray( const int length, int *map ) {
	for ( unsigned register int i = 0; i < length; i++ ) {
		printf( "%d\t", map[i] );
	}

	printf( "\n" );
}

int main( int argc, char *argv[] ) {
	int bufferSize = BUFFER;

	/*
	// if we passed a string on the CLI we will use that
	if ( 1 < argc && 1 <= sizeof(argv) ) {
	bufferSize = sizeof(argv)/sizeof(char);
	printf( "%d\n", bufferSize );
	} else {
	bufferSize = BUFFER;
	}
	*/

	// charsMap holds number of times character is used
	// string is a buffer for putting input into
	int charsMap[ASCII_RANGE] = {0};
	char string[bufferSize];

	// i prefer this method in case you change sizes later
	unsigned int charsLength = ( sizeof( charsMap )/sizeof( int ));

	// pull whatever we type to stdin into string variable
	// bufferSize is also the length of string array
	fgets( string, bufferSize, stdin );

	fillMap( charsMap, string );
	dumpString( "you entered", string );
	dumpArray( charsLength, charsMap );

	pcolor( string, red );
	pcolor( string, green );
	pcolor( string, blue );
	pcolor( string, cyan );
	pcolor( string, magenta );
	pcolor( string, yellow );

	return 0;
}

