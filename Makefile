CCFLAGS= -Wall -ansi -pedantic -g
CC= g++ 

all: tp0 clean
	

tp0: main.o cmdline.o utils.o
	$(CC) $(CCFLAGS) -o tp0 main.o cmdline.o utils.o

main.o: main.cpp Array.h cmdline.h utils.h main.h
	$(CC) $(CCFLAGS) -c main.cpp -o main.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

utils.o: utils.cpp utils.h
	$(CC) $(CCFLAGS) -c utils.cpp -o utils.o 

DataGenerator: datagenerator.o cmdline.o
	$(CC) $(CCFLAGS) -o DataGenerator cmdline.o datagenerator.o

datagenerator.o: datagenerator.cpp Array.h cmdline.h
	$(CC) $(CCFLAGS) -c datagenerator.cpp -o datagenerator.o 
	

runtest:
	./TEST.sh

clean:
	$(RM) *.o 
