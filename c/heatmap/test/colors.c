#include <string.h>

#define BLACK		"\x1b[30m"
#define RED    		"\x1b[31m"
#define GREEN  		"\x1b[32m"
#define YELLOW 		"\x1b[33m"
#define BLUE   		"\x1b[34m"
#define MAGENTA		"\x1b[35m"
#define CYAN   		"\x1b[36m"
#define WHITE		"\x1b[37m"
#define BG_BLACK	"\x1b[40m"
#define BG_RED		"\x1b[41m"
#define BG_GREEN	"\x1b[42m"
#define BG_YELLOW	"\x1b[43m"
#define BG_BLUE		"\x1b[44m"
#define BG_MAGENTA	"\x1b[45m"
#define BG_CYAN		"\x1b[46m"
#define BG_WHITE	"\x1b[47m"
#define BOLD		"\x1b[1m"
#define RESET  		"\x1b[0m"
#define SIZE		7

// attempting to implement a method that returns proper strings
// instead of handling print actions for the user, so that
// these can be nested for bold(color(bgcolor(string))) usage scenarios
char *bold ( char *string2 ) {
	char return_string[ strlen( string2 ) + SIZE ];
	strcat( return_string, BOLD );
	strcat( return_string, string2 );
	return return_string;
}

char *bold2( void ) {
	return BOLD;
}

char *resetFmt( void ) {
	return RESET;
}

// callback pointer for following colors
typedef void ( *p_color )( char *string );

void black ( char *string ) {
	printf( BLACK "%s" RESET, string );
}

void white ( char *string ) {
	printf( WHITE "%s" RESET, string );
}

void red( char *string ) {
	printf(RED "%s" RESET, string );
}

void green( char *string ) {
	printf(GREEN "%s" RESET, string );
}

void blue( char *string ) {
	printf(BLUE "%s" RESET, string );
}

void cyan( char *string ) {
	printf(CYAN "%s" RESET, string );
}

void magenta( char *string ) {
	printf(MAGENTA "%s" RESET, string );
}

void yellow( char *string ) {
	printf(YELLOW "%s" RESET, string );
}

// wrapper function for all above functions
int *pcolor( char *string, p_color color ) {
	color( string );
	return 0;
}

