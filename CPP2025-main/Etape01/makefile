all: Test1

Test1: Test1.o Model.o
	g++ -o Test1 Test1.o Model.o

Test1.o: Test1.cpp Model.h
	g++ -c Test1.cpp -std=c++11 -Wall -g

Model.o: Model.cpp Model.h
	g++ -c Model.cpp -std=c++11 -Wall -g

clean:
	rm -f *.o Test1