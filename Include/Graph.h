#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <vector>

#include "Node.h"

/*
*	A generic directed Graph.
*
*	roots will point to all nodes that don't have any incoming edges.
*	These nodes are used in grail to start the labelling process.
*
*/
class Graph {
	std::vector<Node*> nodes;
	std::vector<Node*> roots;
	uint num_nodes;

  public:
	/* Constructors */
	Graph(void);

	/* Methods */
	Graph& from_file(char* filepath);

	/* Getters */
	std::vector<Node*> get_roots(bool random=true) const;
	std::vector<Node*> get_children(Node* node, bool random) const;
	Node* get_node(int nid) const;
	uint get_num_nodes(void) const;

	/* Operators */
	friend std::ostream& operator <<(std::ostream& ostr, const Graph& Graph);
};

#endif
