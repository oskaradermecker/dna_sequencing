all:ProgressBar.o database.o query.o matrix.o main.cpp
	g++ ProgressBar.o database.o query.o matrix.o main.cpp -lpthread -o main
	
database.o:database.cpp
	g++ -c database.h
	g++ -c database.cpp
	
query.o:query.cpp
	g++ -c query.h
	g++ -c query.cpp

matrix.o:matrix.cpp
	g++ -c matrix.h
	g++ -c matrix.cpp
	
ProgressBar.o:ProgressBar.cpp
	g++ -c ProgressBar.h
	g++ -c ProgressBar.cpp	
	
clean:
	rm *.o
