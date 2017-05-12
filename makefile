project.x : project.o tree.o node.o
	g++ -std=c++11 -g -o project.x project.o tree.o node.o

project.o : project.cpp
	g++ -std=c++11 -g -c project.cpp

tree.o : tree.cpp
	g++ -std=c++11 -g -c tree.cpp

node.o : node.cpp
	g++ -std=c++11 -g -c node.cpp

clean:
	rm *.o
