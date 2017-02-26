CC = gcc
CFLAGS = -O3 -Wall -std=gnu11

OBJ_DIR = obj

INC_PATH = -I$(PWD)
LIB_PATH = -L$(PWD)
LFLAGS =

SOURCE += main.c
SOURCE += second_file.c

HEADERS = $(SOURCE:.c=.h)
OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCE))
EXECUTABLE = the_program


all: .PHONY $(EXECUTABLE)

.PHONY: tree_setup 
tree_setup:
	@mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIB_PATH) $(INC_PATH) $(LFLAGS) -o $(EXECUTABLE)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c -o $@ $? $(CFLAGS) $(LIB_PATH) $(INC_PATH) $(LFLAGS)

%.c: %.h

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

