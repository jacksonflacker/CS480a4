# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

ride : Consumer.o Producer.o Buffer.o main.o
	$(CXX) $(CXXFLAGS) -lpthread -o rideshare $^ 

main.o: main.cpp

Buffer.o: Buffer.h Buffer.cpp

Producer.o: Producer.h Producer.cpp

Consumer.o: Consumer.h Consumer.cpp

clean :
	rm *.o
