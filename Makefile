CCFLAGS= -Wall -ansi -pedantic -g
CC= g++ 

all: tp1 clean
KDTree: TestKDTree clean
	

tp1: main.o cmdline.o utils.o KDTree.o
	$(CC) $(CCFLAGS) -o tp1 main.o cmdline.o utils.o KDTree.o

main.o: main.cpp Array.h cmdline.h utils.h main.h KDTree.h
	$(CC) $(CCFLAGS) -c main.cpp -o main.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

utils.o: utils.cpp utils.h Array.h
	$(CC) $(CCFLAGS) -c utils.cpp -o utils.o 

KDTree.o: KDTree.cpp KDTree.h Array.h utils.h
	$(CC) $(CCFLAGS) -c KDTree.cpp -o KDTree.o

DataGenerator: datagenerator.o cmdline.o
	$(CC) $(CCFLAGS) -o DataGenerator cmdline.o datagenerator.o

datagenerator.o: datagenerator.cpp Array.h cmdline.h
	$(CC) $(CCFLAGS) -c datagenerator.cpp -o datagenerator.o 
	
TestKDTree: KDTree.o utils.o
	$(CC) $(CCFLAGS) -o TestKDTree utils.o KDTree.o

runtest:
	./TEST.sh

BasicTest:
	./tp1 -p TestEntrada -i TestConsultas  -s promedio
	sleep 1
	valgrind --leak-check=yes ./tp1 -p TestEntrada -i TestConsultas -o TestSalida -s mitad

Debug:
	gdb --args tp1 -p TestEntrada -i TestConsultas -o - -s promedio

clean:
	$(RM) *.o 
