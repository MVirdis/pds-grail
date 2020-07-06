#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>

#include "Types.h"

/*
*	A generic directed Graph.
*
*	roots will point to all nodes that don't have any incoming edges.
*	These nodes are used in grail to start the labelling process.
*
*/
class Graph {
	uint** adj_list;
	std::vector<uint> roots;
	uint num_nodes;
	uint num_roots;
  public:
	/* Constructors */
	Graph(void);

	/* Methods */
	Graph& from_file(const char* filepath);
	uint compute_size(void) const;
	void clear(void);

	/* Getters */
	const uint* get_roots(void) const;
	uint get_num_nodes(void) const;
	uint get_num_roots(void) const;
	uint* get_children(uint x) const;

	/* Operators */
	friend std::ostream& operator <<(std::ostream& ostr, const Graph& Graph);

	~Graph();
};

#endif
