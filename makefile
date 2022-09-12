default: all

all:
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task1 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp sourcefiles/Task1.cpp
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task2 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task2.cpp -pthread
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task3 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task3.cpp -pthread
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task4 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task4.cpp -pthread

clean:
	rm -f objectfiles/Task1
	rm -f objectfiles/Task2
	rm -f objectfiles/Task3
	rm -f objectfiles/Task4

task1: 
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task1 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp sourcefiles/Task1.cpp
task2: 
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task2 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp  Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task2.cpp -pthread
task3: 
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task3 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp  Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task3.cpp -pthread
task4: 
	g++ -Wall -Werror -std=c++14 -O -o  objectfiles/Task4 Helperfiles/Helpers.cpp Helperfiles/TaskFilter.cpp  Helperfiles/Map.cpp Helperfiles/Reduce.cpp sourcefiles/Task4.cpp -pthread
