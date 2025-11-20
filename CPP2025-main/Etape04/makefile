all: Test4

Test4: Test4.o Person.o Actor.o Client.o Employee.o
	g++ -o Test4 Test4.o Person.o Actor.o Client.o Employee.o -g

Test4.o: Test4.cpp Person.h Client.h Employee.h
	g++ -c Test4.cpp -std=c++11 -Wall -g

Person.o: Person.cpp Person.h
	g++ -c Person.cpp -std=c++11 -Wall -g

Actor.o: Actor.cpp Actor.h
	g++ -c Actor.cpp -std=c++11 -Wall -g

Client.o: Client.cpp Client.h
	g++ -c Client.cpp -std=c++11 -Wall -g

Employee.o: Employee.cpp Employee.h
	g++ -c Employee.cpp -std=c++11 -Wall -g

clean:
	rm -f *.o Test4