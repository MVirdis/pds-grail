#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <utility>

#include "Types.h"

/*
*	A node of the directed Graph.
*	It has a unique id, and points to all reachable nodes.
*
*	Nodes are all handled through pointers because they are allocated
*	into heap.
*/
class Node {
	uint id;						// Node number
	Node** adj_nodes;				// Reachable nodes
	uint neigh;
	Node(const Node& node);			// Copy constructor blocked

  public:
	/* Constructors */
	Node(uint id);

	/* Getters */
	uint get_id(void) const;
	Node** get_children(void) const;
	uint get_num_children(void) const;

	/* Methods */
	Node& set_children(std::vector<Node*>& children);

	/* Operators */
	friend std::ostream& operator <<(std::ostream& ostr, const Node& node);

	~Node();
};

#endif
