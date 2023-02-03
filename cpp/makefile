CC = g++
LFLAGS = -lfmt -ltbb
OPTS = -std=c++17 -fprofile-arcs --coverage -pg
FILE = parallelo_world.cpp
BINARIES = seq par_unseq unseq par
OBJECTS = $(BINARIES:%=%.o)

all: $(BINARIES)

$(BINARIES): $(OBJECTS)

par.o: $(FILE)
	$(CC) -c -o par.o -DPOLICY=std::execution::par $(OPTS) $(FILE)

seq.o: $(FILE)
	$(CC) -c -o seq.o -DPOLICY=std::execution::seq $(OPTS) $(FILE)

unseq.o: $(FILE)
	$(CC) -c -o unseq.o -DPOLICY=std::execution::unseq $(OPTS) $(FILE)

par_unseq.o: $(FILE)
	$(CC) -c -o par_unseq.o -DPOLICY=std::execution::par_unseq $(OPTS) $(FILE)

par: par.o
	$(CC) par.o -o par $(OPTS) $(LFLAGS)

seq: seq.o
	$(CC) seq.o -o seq $(OPTS) $(LFLAGS)

unseq: unseq.o
	$(CC) unseq.o -o unseq $(OPTS) $(LFLAGS)

par_unseq: par_unseq.o
	$(CC) par_unseq.o -o par_unseq $(OPTS) $(LFLAGS)

clean:
	$(RM) $(OBJECTS) *.gcda *.gcno *gmon* $(BINARIES) *.txt

