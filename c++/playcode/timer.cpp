#include <iostream> // testing in console cout and cin
#include <ctime> // clock() and CLOCKS_PER_SEC
#include <cstdint> // specific width integer types

using namespace std;

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

int main(){
	Timer t;
	// checking the size of object, want to be small so we can make a bunch on the stack
	//cout << sizeof( t ) << endl;
	t.SetDuration( 5.1 );

	/*
	   unsigned var = 0 ;
	   cout << "Enter timer amount in seconds" << endl;
	   cin >> var;
	   cout << "Setting timer to " << var << " seconds" << endl;
	   t.SetDuration( var );
	   */

	while(1)
		if( t.Elapsed() >= t.GetDuration() ){
			cout << t.Elapsed() << endl;
			break;
		}

	return 0;
}
