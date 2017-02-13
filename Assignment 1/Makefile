# declare the variables
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

output: main.o Node.o InputManager.o ResourceManager.o
	$(CC) -o $(OUTFILE) main.o Node.o InputManager.o ResourceManager.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Node.o: Classes/Node.cpp
	$(CC) $(CFLAGS) Classes/Node.cpp

InputManager.o: Classes/InputManager.cpp
	$(CC) $(CFLAGS) Classes/InputManager.cpp

ResourceManager.o: Classes/ResourceManager.cpp
	$(CC) $(CFLAGS) Classes/ResourceManager.cpp

# will clean all created .o files and output
clean:
	rm -rf *o output
