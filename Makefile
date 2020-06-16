grail:
	mkdir -p build
	cp Include/Grail.h build
	cp Include/Graph.h build
	cp Include/Index.h build
	cp Include/Query.h build
	cp Include/Sync.h build
	cp Include/Thread.h build
	cp Include/Types.h build
	cp Grail/prod.cpp build
	cp Grail/grail.cpp build
	cp Grail/reach.cpp build
	cp Graph/Graph.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	cp Index/Index.cpp build
	cp Query/Query.cpp build
	g++ -Wall -pthread -g -o build/grail -std=c++11 build/*.cpp
	rm -rf build/*.h build/*.cpp build/*.c

sequential:
	mkdir -p build
	cp Include/Grail.h build
	cp Include/Graph.h build
	cp Include/Index.h build
	cp Include/Query.h build
	cp Include/Sync.h build
	cp Include/Thread.h build
	cp Include/Types.h build
	cp Grail/sequential.cpp build
	cp Grail/grail.cpp build
	cp Grail/reach.cpp build
	cp Graph/Graph.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	cp Index/Index.cpp build
	cp Query/Query.cpp build
	g++ -Wall -pthread -g -o build/sequential -std=c++11 build/*.cpp
	rm -rf build/*.h build/*.cpp build/*.c

grail_verbose:
	mkdir -p build
	cp Include/Grail.h build
	cp Include/Graph.h build
	cp Include/Index.h build
	cp Include/Query.h build
	cp Include/Sync.h build
	cp Include/Thread.h build
	cp Include/Types.h build
	cp Grail/prod.cpp build
	cp Grail/grail.cpp build
	cp Grail/reach.cpp build
	cp Graph/Graph.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	cp Index/Index.cpp build
	cp Query/Query.cpp build
	g++ -Wall -pthread -DVERBOSE -g -o build/grail -std=c++11 build/*.cpp
	rm -rf build/*.h build/*.cpp build/*.c

sequential_verbose:
	mkdir -p build
	cp Include/Grail.h build
	cp Include/Graph.h build
	cp Include/Index.h build
	cp Include/Query.h build
	cp Include/Sync.h build
	cp Include/Thread.h build
	cp Include/Types.h build
	cp Grail/sequential.cpp build
	cp Grail/grail.cpp build
	cp Grail/reach.cpp build
	cp Graph/Graph.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	cp Index/Index.cpp build
	cp Query/Query.cpp build
	g++ -Wall -pthread -DVERBOSE -g -o build/sequential -std=c++11 build/*.cpp
	rm -rf build/*.h build/*.cpp build/*.c

grail_tester:
	mkdir -p build
	cp Include/*.h build
	cp Grail/main.cpp build
	cp Grail/grail.cpp build
	cp Grail/reach.cpp build
	cp Graph/Graph.cpp build
	cp Thread/Sync.cpp build
	cp Thread/RandomVisitor.cpp build
	cp Generator/dag_generator.c build
	cp Index/Index.cpp build
	cp Query/Query.cpp build
	g++ -Wall -pthread -g -o build/grail_tester -std=c++11 build/*.cpp build/*.c
	rm -rf build/*.h build/*.cpp build/*.c

node_test:
	mkdir -p build
	cp Include/*.h build
	cp Node/Node.cpp build
	cp Node/test.cpp build
	g++ -Wall -g -std=c++11 -o build/node_test build/*.cpp -DDEBUG
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
	g++ -Wall -g -std=c++11 -o build/graph_test build/dag_generator.c build/*.cpp -DDEBUG
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
