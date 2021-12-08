CC = g++ -std=c++11
exe_file = samosa

$(exe_file): functions.o main.o pizza.o restaurant.o menu.o
	$(CC) functions.o main.o pizza.o restaurant.o menu.o -o $(exe_file)
functions.o: functions.cpp
	$(CC) -c functions.cpp 
main.o: main.cpp
	$(CC) -c main.cpp 
pizza.o: pizza.cpp
	$(CC) -c pizza.cpp 
restaurant.o: restaurant.cpp
	$(CC) -c restaurant.cpp 
menu.o: menu.cpp
	$(CC) -c menu.cpp
clean:
	rm -f *.out *.o $(exe_file)

.PHONY: clean 
