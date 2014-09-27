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

// these functions do not add CRLF, you need to add them yourself
// takes 1 string at a time and spits it out in this color

// callback pointer for these colors
typedef void (*p_color)( char *string );

void bold (char *string) {
	printf( BOLD "%s" RESET, string);
}

void black (char *string) {
	printf( BLACK "%s" RESET, string);
}

void white (char *string) {
	printf( WHITE "%s" RESET, string);
}

void red( char *string ) {
	printf(RED "%s" RESET, string);
}

void green( char *string ) {
	printf(GREEN "%s" RESET, string);
}

void blue( char *string ) {
	printf(BLUE "%s" RESET, string);
}

void cyan( char *string ) {
	printf(CYAN "%s" RESET, string);
}

void magenta( char *string ) {
	printf(MAGENTA "%s" RESET, string);
}

void yellow( char *string ) {
	printf(YELLOW "%s" RESET, string);
}

// wrapper function for all above functions
int *pcolor( char *string, p_color color ) {
	color( string );
	return 0;
}
