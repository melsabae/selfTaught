#include "timerclass.hpp" // header
#include <ctime> // clock() and CLOCKS_PER_SEC

Timer :: Timer(){
	start = clock();
	duration = 0;
};

Timer :: Timer( uint16_t arg, uint16_t arg2 ){
	start = arg;
	duration = arg2;
};

void Timer :: Reset(){
	start = clock();
	duration = 0;
};

void Timer :: SetDuration( float arg ){
	duration = arg;
};

uint16_t Timer :: GetStart() const{
	return start;
};

uint16_t Timer :: GetDuration() const{
	return duration;
};

// float for when i want the elapsed time to resolve to units less than a second, otherwise would be a short
float Timer::Elapsed() const{
	return ( float )( clock() - start ) / CLOCKS_PER_SEC;
};
