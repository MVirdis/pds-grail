#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

#include "Types.h"
#include "Graph.h"

void randomized_visit(Node* x, uint i, Graph&);

/*
*	A handy class that lets start a thread that executes
*	a randomized visit on graph G, starting from node x
*	and labelling in dimension i.
*
*/
class RandomVisitor {
	pthread_t tid;
	Graph& G;
	uint i;

	static void* start_routine(void*);

  public:
	/* Constructors */
	RandomVisitor(Graph& G, int i);

	/* Methods */
	RandomVisitor& run(void);
	int wait(void);

	~RandomVisitor(void);
};

#endif
