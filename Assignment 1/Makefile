#declare the variable
CC=g++
CFLAGS=-c -Wall
OUTFILE=output

# creates an output file
all: output
	$(info )
	$(info ----------------------------------------------------)
	$(info | Executable program will be saved in file: $(OUTFILE) | )
	$(info ----------------------------------------------------)
	$(info )

output: main.o Node.o InputManager.o Registry.o
	$(CC) -o $(OUTFILE) main.o Node.o InputManager.o Registry.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Node.o: Classes/Node.cpp
	$(CC) $(CFLAGS) Classes/Node.cpp

InputManager.o: Classes/InputManager.cpp
	$(CC) $(CFLAGS) Classes/InputManager.cpp

Registry.o: Classes/Registry.cpp
	$(CC) $(CFLAGS) Classes/Registry.cpp

clean:
	rm -rf *o output
