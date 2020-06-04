#ifndef _GRAIL_H_
#define _GRAIL_H_

#include <unordered_set>

#include "Graph.h"

/*
*	Set to 1 to enable multiple threads to visit
*	the graph at the same time, with equal offset
*	value, starting from different roots.
*	If set to 0, randomized labelling will be done
*	by creating one thread per dimension, with
*	sequential visits for each root node
*
*	Let R be num. of different roots in given DAG,
*	then:
*	If (PARALLEL_VISITS == 0) => Num Threads == d
*	If (PARALLEL_VISITS == 1) => Num Threads == R*d
*/
#define PARALLEL_VISITS 0

bool randomized_labelling(Graph&, const uint);

bool randomized_visit(Node*, uint, Graph&, uint& , std::unordered_set<uint>&);

#endif
