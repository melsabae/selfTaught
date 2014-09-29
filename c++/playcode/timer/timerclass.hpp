// do these even work
#ifndef TIMERCLASS_HPP
#define TIMERCLASS_HPP
#endif

class Timer
{
	uint16_t start, duration;

	public:
	Timer(){};
	Timer( uint16_t , uint16_t ){};
	void Reset(){};

	void SetDuration( float arg ){}
	uint16_t GetStart() const {}
	uint16_t GetDuration() const {}
	// float for when i want the elapsed time to resolve to units less than a second, otherwise would be a short
	float Elapsed() const {}

};
