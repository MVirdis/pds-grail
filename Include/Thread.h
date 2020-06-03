#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <unordered_set>

#include "Types.h"
#include "Graph.h"

/*
*	A handy class that handles a pthread_barrier
*
*/
class Barrier {
	pthread_barrier_t tbarrier;
  public:
	/* Constructors */
	Barrier(uint how_many);

	/* Methods */
	Barrier& wait(void);

	~Barrier();
};

/*
*	A handy class that handles a pthread_mutex
*
*/
class Mutex {
	pthread_mutex_t tmutex;
  public:
	/* Constructors */
	Mutex();

	/* Methods */
	Mutex& lock(void);
	Mutex& unlock(void);

	~Mutex();
};

/*
*	A handy class that lets start a thread that executes
*	a randomized visit on graph G, starting from node x
*	and labelling in dimension i.
*	This class should adjust accordingly to PARALLEL_VISITS
*/
class RandomVisitor {
	pthread_t tid;
	Graph& G;
	uint offset;
	Node* x;
	Barrier& barrier;
	uint& rank;
	std::unordered_set<uint>& visited_set;

	static void* start_routine(void*);

  public:
	/* Constructors */
	RandomVisitor();

	/* Methods */
	RandomVisitor& run(void);
	int wait(void);
	RandomVisitor& set_graph(Graph& G);
	RandomVisitor& set_offset(uint i);
	RandomVisitor& set_start_node(Node* x);
	RandomVisitor& set_barrier(Barrier& barrier);
	RandomVisitor& set_visited_set(std::unordered_set<uint>& set);
	RandomVisitor& set_rank(uint& rank);

	~RandomVisitor();
};

#endif
