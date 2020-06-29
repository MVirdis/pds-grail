#ifndef _GRAIL_H_
#define _GRAIL_H_

#include <unordered_set>

#include "Sync.h"
#include "Index.h"
#include "Graph.h"
#include "Query.h"
#define HOW_MANY_BUFF 8

Index* randomized_labelling(Graph&, const uint);

Index* sequential_labelling(Graph& G, const uint d);

bool randomized_visit(uint x, Graph& G, uint& rank, std::unordered_set<uint>& visited, Index& index);

bool reachable(uint u, uint v, Index *indexes, uint d, Graph& G);

void reachable_parallel(uint u, uint v, Index *indexes, uint d, Graph& G, bool& result);

void pre_process(int offset, uint i, Query *queries, bool *results, bool last, Graph& G, Index *indexes, uint d, uint num_queries, Barrier& barr);

float index_diversity(Index* indexes, uint d);

#endif
