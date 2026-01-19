# ===========================
#   MAKEFILE Labo C++
# ===========================

all: Test8a Test8b

# ===========================
#  EXECUTABLE Test8a
# ===========================

Test8a: Test8a.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o \
        Employee.o Person.o Actor.o Client.o Garage.o
	g++ -o Test8a Test8a.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o \
	Employee.o Person.o Actor.o Client.o Garage.o -g

Test8a.o: Test8a.cpp XmlFileSerializer.hpp XmlFileSerializer.ipp
	g++ -c Test8a.cpp -g

# ===========================
#  EXECUTABLE Test8b
# ===========================

Test8b: Test8b.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o \
        Employee.o Person.o Actor.o Client.o Garage.o
	g++ -o Test8b Test8b.o Exception.o OptionException.o PasswordException.o Option.o Car.o Model.o \
	Employee.o Person.o Actor.o Client.o Garage.o -g

Test8b.o: Test8b.cpp XmlFileSerializer.hpp XmlFileSerializer.ipp
	g++ -c Test8b.cpp -g

# ===========================
#  OBJETS
# ===========================

Exception.o: Exception.cpp Exception.h
	g++ -c Exception.cpp -g

OptionException.o: OptionException.cpp OptionException.h Exception.h
	g++ -c OptionException.cpp -g

PasswordException.o: PasswordException.cpp PasswordException.h Exception.h
	g++ -c PasswordException.cpp -g

Option.o: Option.cpp Option.h OptionException.h
	g++ -c Option.cpp -g

Car.o: Car.cpp Car.h Model.h Option.h OptionException.h
	g++ -c Car.cpp -g

Model.o: Model.cpp Model.h
	g++ -c Model.cpp -g

Employee.o: Employee.cpp Employee.h PasswordException.h Actor.h
	g++ -c Employee.cpp -g

Person.o: Person.cpp Person.h
	g++ -c Person.cpp -g

Actor.o: Actor.cpp Actor.h Person.h
	g++ -c Actor.cpp -g

Client.o: Client.cpp Client.h Actor.h
	g++ -c Client.cpp -g

Garage.o: Garage.cpp Garage.h Client.h Employee.h Model.h Option.h
	g++ -c Garage.cpp -g

# ===========================
#  CLEAN
# ===========================

clean:
	rm -f *.o Test8a Test8b
