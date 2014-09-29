#include <ctime> // clock() and CLOCKS_PER_SEC
#include <cstdint> // specific width integer types

class Timer
{
	uint16_t start, duration;

	public:
	Timer(){
		start = clock();
		duration = 0;
	}

	Timer( uint16_t arg, uint16_t arg2 ){
		start = arg;
		duration = arg2;
	}

	void Reset(){
		start = clock();
		duration = 0;
	}

	void SetDuration( float arg ){ duration = arg; }
	uint16_t GetStart() const { return start; }
	uint16_t GetDuration() const { return duration; }
	// float for when i want the elapsed time to resolve to units less than a second, otherwise would be a short
	float Elapsed() const { return ( float )( clock() - start ) / CLOCKS_PER_SEC; }

};
