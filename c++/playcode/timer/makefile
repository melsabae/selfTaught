headers:
	g++ -c timerclass.hpp -std=gnu++11 -march=native
objcode:
	g++ -c main.cpp timerclass.cpp -std=gnu++11 -march=native
timer:
	g++ main.o timerclass.o -std=gnu++11 -o timer -march=native
clean:
	rm timer *.o *.gch
