#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <utility>

#include "Types.h"

/*
*	A node of the directed Graph.
*	It has a unique id, and points to all reachable nodes.
*	It also stores a vector of intervals used for the DAG index.
*
*	Nodes are all handled through pointers because they are allocated
*	into heap.
*
*	-add_interval takes also an index and this is important because
*		when different threads will be adding intervals in an out of
*		order fashion, we must ensure that each interval keeps the
*		appropriate position inside the labels array. It's not just a
*		simple push back.
*
*/
class Node {
	std::vector<Interval> labels;
	uint id;						// Node number
	std::vector<Node*> adj_nodes;	// Reachable nodes

	Node(const Node& node);			// Copy constructor blocked

  public:
	/* Constructors */
	Node(uint id);

	/* Getters */
	uint get_id(void) const;
	Interval& get_interval(int index) const;
	std::vector<Node*> get_children(void) const;

	/* Methods */
	Node& add_child(Node* child);
	Node& add_interval(Interval interval, int index);

	/* Operators */
	friend std::ostream& operator <<(std::ostream& ostr, const Node& node);

	~Node(void);
};

#endif
