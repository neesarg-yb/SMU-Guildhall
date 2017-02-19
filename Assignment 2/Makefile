# declare the variables
CC=g++
CFLAGS=-c -Wall
OUTFILE=compressor

# creates an output file
all: output
	$(info )
	$(info --------------------------------------------------------)
	$(info | Executable program will be saved in file: $(OUTFILE) | )
	$(info --------------------------------------------------------)
	$(info )

output: main.o ReadWriteOperations.o Node.o BinaryTree.o
	$(CC) -o $(OUTFILE) main.o ReadWriteOperations.o Node.o BinaryTree.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Node.o: Classes/Node.cpp
	$(CC) $(CFLAGS) Classes/Node.cpp

BinaryTree.o: Classes/BinaryTree.cpp
	$(CC) $(CFLAGS) Classes/BinaryTree.cpp

ReadWriteOperations.o: Classes/ReadWriteOperations.cpp
	$(CC) $(CFLAGS) Classes/ReadWriteOperations.cpp

# will clean all created .o files and output
clean:
	rm -rf *o $(OUTFILE)

keepJustOutput:
	rm -rf *o
