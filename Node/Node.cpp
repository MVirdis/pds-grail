#include <vector>

#include "Node.h"

using namespace std;

Node::Node(uint id) {
	this->id = id;
	this->adj_nodes = NULL;
	this->neigh = 0;
}

uint Node::get_id(void) const {
	return this->id;
}

Node** Node::get_children(void) const {
	if (this->neigh == 0)	return NULL;

	return this->adj_nodes;
}

uint Node::get_num_children(void) const {
	return neigh;
}

Node& Node::set_children(vector<Node*>& children) {
	this->neigh = children.size();
	this->adj_nodes = new Node*[neigh];
	for (uint i = 0; i < this->neigh; ++i) 
		this->adj_nodes[i] = children[i];
	return *this;
}

ostream& operator <<(ostream& ostr, const Node& node) {
#ifdef DEBUG
	cout << "Direct linked nodes: ";
	for (int i = 0; i < node.neigh; ++i)
		ostr << "[" << node.adj_nodes[i]->get_id() << "]";
	ostr << endl;
#endif
	ostr << node.id;
	return ostr;
}

Node::~Node() {
		delete[] adj_nodes;
}
