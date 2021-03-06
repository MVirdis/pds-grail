#ifndef _GRAIL_H_
#define _GRAIL_H_

#include <unordered_set>

#include "Sync.h"
#include "Index.h"
#include "Graph.h"
#include "Query.h"
#define NUM_QUERY_WORKERS 4

Index* randomized_labelling(Graph&, const uint);

Index* sequential_labelling(Graph& G, const uint d);

void randomized_visit(uint x, Graph& G, uint& rank, std::unordered_set<uint>& visited, Index& index);

bool reachable(uint u, uint v, Index *indexes, uint d, Graph& G, bool needs_check=true);

float index_diversity(Index* indexes, uint d);

#endif
