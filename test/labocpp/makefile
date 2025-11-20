all: CPP-etape3

CPP-etape3: Test3.cpp Model.o Option.o Car.o
	g++ Test3.cpp Model.o Option.o Car.o -o CPP-etape3

Model.o: Model.cpp Model.h
	g++ -c Model.cpp

Option.o: Option.cpp Option.h
	g++ -c Option.cpp

Car.o: Car.cpp Car.h Model.h Option.h
	g++ -c Car.cpp
