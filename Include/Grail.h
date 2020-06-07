#ifndef _GRAIL_H_
#define _GRAIL_H_

#include <unordered_set>

#include "Index.h"
#include "Graph.h"

Index* randomized_labelling(Graph&, const uint);

Index* sequential_labelling(Graph& G, const uint d);

bool randomized_visit(uint x, Graph& G, uint& rank, std::unordered_set<uint>& visited, Index& index);

#endif
