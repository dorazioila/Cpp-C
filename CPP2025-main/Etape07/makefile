all: Test7

Test7: Test7.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o Employee.o Person.o Actor.o Client.o
	g++ -o Test7 Test7.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o Employee.o Person.o Actor.o Client.o -g

Test7.o: Test7.cpp XmlFileSerializer.hpp XmlFileSerializer.ipp
	g++ -c Test7.cpp

Exception.o: Exception.cpp Exception.h
	g++ -c Exception.cpp

OptionException.o: OptionException.cpp OptionException.h Exception.h
	g++ -c OptionException.cpp 

PasswordException.o: PasswordException.cpp PasswordException.h Exception.h
	g++ -c PasswordException.cpp 

Option.o: Option.cpp Option.h OptionException.h
	g++ -c Option.cpp 

Car.o: Car.cpp Car.h Model.h Option.h OptionException.h
	g++ -c Car.cpp 

Model.o: Model.cpp Model.h
	g++ -c Model.cpp 

Employee.o: Employee.cpp Employee.h PasswordException.h Actor.h
	g++ -c Employee.cpp 

Person.o: Person.cpp Person.h
	g++ -c Person.cpp 

Actor.o: Actor.cpp Actor.h Person.h
	g++ -c Actor.cpp

Client.o: Client.cpp Client.h Actor.h
	g++ -c Client.cpp 