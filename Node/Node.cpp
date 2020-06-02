#include <vector>

#include "Node.h"

using namespace std;

Node::Node(uint id) {
	this->id = id;
}

uint Node::get_id(void) const {
	return this->id;
}

Interval Node::get_interval(int index) const {
	Interval i(0,0);
	if ((uint)index >= labels.size())
		return i;
	i.first = labels[index].first;
	i.second = labels[index].second;
	return i;
}

vector<Node*> Node::get_children(void) const {
	return adj_nodes;
}

Node& Node::add_child(Node *child) {
	adj_nodes.push_back(child);
	return *this;
}

Node& Node::add_interval(Interval interval, int ind) {
	Interval in(0,0);
	uint index = (uint)ind;
	int lim = 1+index-labels.size();

	if (labels.size() > 0 && index >= 0 && index <= labels.size()-1) {
#ifdef DEBUG
		cout << "entrato" << endl;
#endif
		labels[index].first = interval.first;
		labels[index].second = interval.second;
	}
	
	else {
		for(int i = 0; i < lim; ++i) {
			labels.push_back(in);
#ifdef DEBUG
			cout << "[Node "<<id<<"] Added empty interval in pos " << i << endl;
#endif
		}
		labels[index].first = interval.first;
		labels[index].second = interval.second;
	}
	return *this;
}

ostream& operator <<(ostream& ostr, const Node& node) {
#ifdef DEBUG
	ostr << "Node id: " << node.id << endl;
	ostr << "Labels: ";
	for (uint i = 0; i < node.labels.size(); ++i) {
		ostr << "(" << node.labels[i].first << "," << node.labels[i].second << ")";
		if (i == node.labels.size()-1)
			ostr << endl;
		else
			ostr << " ; ";
	}
	ostr << "Reachable nodes: {";
	for (uint i = 0; i < node.adj_nodes.size(); ++i) {
		ostr << node.adj_nodes[i]->id;
		if (i == node.adj_nodes.size()-1)
			ostr << "}" << endl;
		else
			ostr << " , ";
	}
	return ostr;
#else
	ostr << node.id;
	return ostr;
#endif
}

Node& Node::lock(void) {
	this->mutex.lock();
	return *this;
}

Node& Node::unlock(void) {
	this->mutex.unlock();
	return *this;
}
