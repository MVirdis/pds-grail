#include "Index.h"
#include <cstdlib>

Index::Index() {
	this->labels = NULL;
	this->num_nodes = 0;
}

Index& Index::set_size(uint size) {
	this->num_nodes = size;
	this->labels = new Interval[this->num_nodes];
	return *this;
}

Index& Index::set_interval(Interval& label, uint node_id) {
	this->labels[node_id] = label;
	return *this;
}

uint Index::get_size(void) const {
	return this->num_nodes;
}

Interval Index::get_interval(uint node_id) const {
	return this->labels[node_id];
}

Index::~Index() {
	delete this->labels;
}	
