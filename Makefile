graph_test: clean
	mkdir build
	cp Include/Graph.h build
	cp Graph/Graph.cpp build
	cp Include/Node.h build
	cp Node/Node.cpp build
	cp Include/Types.h build
	cp Graph/test.cpp build
	cp Include/Generator.h build
	cp Generator/dag_generator.c build
	g++ -Wall -g -o build/graph_test build/dag_generator.c build/*.cpp -DDEBUG
	rm -rf build/*.c build/*.cpp build/*.h

generator: clean
	mkdir build
	cp Include/Generator.h build
	cp Generator/dag_generator.c build
	cp Generator/main.c build
	gcc -Wall -g -o build/dag_generator build/*.c -lm
	rm -rf build/*.c build/*.cpp build/*.h

clean:
	rm -rf build
