grail_test:
	mkdir -p build
	cp Include/*.h build
	cp Grail/*.cpp build
	cp Graph/Graph.cpp build
	cp Node/Node.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	g++ -Wall -g -o build/grail -DDEBUG -std=c++11 -lpthread build/*.cpp
	rm -rf build/*.h build/*.cpp

node_test:
	mkdir -p build
	cp Include/*.h build
	cp Node/Node.cpp build
	cp Node/test.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	g++ -Wall -g -std=c++11 -o build/node_test -lpthread build/*.cpp -DDEBUG
	rm -rf build/*.cpp build/*.h

graph_test:
	mkdir -p build
	cp Include/*.h build
	cp Graph/Graph.cpp build
	cp Node/Node.cpp build
	cp Graph/test.cpp build
	cp Generator/dag_generator.c build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	g++ -Wall -g -std=c++11 -o build/graph_test -lpthread build/dag_generator.c build/*.cpp -DDEBUG
	rm -rf build/*.c build/*.cpp build/*.h

generator:
	mkdir -p build
	cp Include/Generator.h build
	cp Generator/dag_generator.c build
	cp Generator/main.c build
	gcc -Wall -g -o build/dag_generator build/*.c -lm
	rm -rf build/*.c build/*.cpp build/*.h

clean:
	rm -rf build
