all: Test2c

Test2c: Test2c.o Car.o Option.o Model.o
	g++ -o Test2c Test2c.o Car.o Option.o Model.o -g

Test2c.o: Test2c.cpp Car.h Option.h Model.h
	g++ -c Test2c.cpp -std=c++11 -Wall -g

Car.o: Car.cpp Car.h Model.cpp Model.h Option.cpp Option.h
	g++ -c Car.cpp -std=c++11 -Wall -g

Model.o: Model.cpp Model.h
	g++ -c Model.cpp -std=c++11 -Wall -g

Option.o: Option.cpp Option.h
	g++ -c Option.cpp -std=c++11 -Wall -g

clean:
	rm -f *.o Test2c