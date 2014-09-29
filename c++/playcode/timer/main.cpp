#include <iostream> // testing in console cout and cin
#include "timerclass.cpp"

using namespace std;

int main(){
	Timer t;
	// checking the size of object, want to be small so we can make a bunch on the stack
	//cout << sizeof( t ) << endl;
	t.SetDuration( 5 );

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
