#ifndef _THREAD_H_
#define _THREAD_H_

#include <unordered_set>
#include <thread>

#include "Types.h"
#include "Index.h"
#include "Graph.h"
#include "Sync.h"

/*
*	A handy class that lets start a thread that executes
*	a randomized visit on graph G, starting from node x
*	and labelling in dimension i.
*	This class should adjust accordingly to PARALLEL_VISITS
*/
class RandomVisitor {
	std::thread t;
	Graph *G;
	uint offset;
	Node* x;
	Barrier *barrier;
	uint *rank;
	std::unordered_set<uint> *visited_set;

	// Change this function's signature as needed (should be static)
	static void start_routine(Graph *G, uint offset, Barrier *barrier, uint* rank, std::unordered_set<uint> *visited_set);

  public:
	/* Constructors */
	RandomVisitor();

	/* Methods */
	RandomVisitor& run(void);
	RandomVisitor& set_graph(Graph *G);
	RandomVisitor& set_offset(uint i);
	RandomVisitor& set_start_node(Node* x);
	RandomVisitor& set_barrier(Barrier *barrier);
	RandomVisitor& set_visited_set(std::unordered_set<uint> *set);
	RandomVisitor& set_rank(uint *rank);
	RandomVisitor& set_index(Index* index);

	//~RandomVisitor();
};


#endif
