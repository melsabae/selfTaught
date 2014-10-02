#ifndef TIMERCLASS_HPP
#define TIMERCLASS_HPP
#include <cstdint>

class Timer
{
	uint16_t start, duration;

	public:
		Timer();
		Timer( uint16_t , uint16_t );
		void Reset();

		void SetDuration( float arg );
		uint16_t GetStart() const;
		uint16_t GetDuration() const;
		float Elapsed() const;
};

#endif
