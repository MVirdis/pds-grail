#include <vector>

#include "Node.h"

using namespace std;

Node::Node(uint id) {
	// TODO
}

uint Node::get_id(void) const {
	return this->id;
}

vector<Node*> Node::get_children(void) const {
	// TODO
}

Node& Node::add_child(Node *child) {
	// TODO
}

ostream& operator <<(ostream& ostr, const Node& node) {
#ifdef DEBUG
	// TODO
#else
	ostr << node.id;
	return ostr;
#endif
}
