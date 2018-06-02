EXECUTABLE = $(shell realpath . | rev | cut -f1 -d/ | rev)
GEXECUTABLE = g$(EXECUTABLE)
CEXECUTABLE = c$(EXECUTABLE)
FLAGS = -lrt -O3

all: generator consumer

generator:
	gcc -c generator.c
	gcc -o $(GEXECUTABLE) generator.o $(FLAGS)

consumer:
	gcc -c consumer.c
	gcc -o $(CEXECUTABLE) consumer.o $(FLAGS)


clean:
	$(RM) *.o $(GEXECUTABLE) $(CEXECUTABLE)
