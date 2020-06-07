#include <string>
#include <fstream>
#include <iostream>

#include "Query.h"
#include "Grail.h"

using namespace std;

QueryProcessor::QueryProcessor() {
	// TODO init internal arrays
}

QueryProcessor::QueryProcessor(string file_path) {
	// TODO call this->from_file
}

QueryProcessor& QueryProcessor::from_file(string file_path) {
	Interval interval;
	ifstream file;

	// TODO Check if queries and results are already allocated,
	// if they are free them through clear method

	file.open(file_path);
	if (!file.is_open()) {
		cerr << "Errod during the open. Try with another name" << endl;
		// TODO Handle situation where file doesn't exist, e.g. return here
	}
	
	// TODO allocate internal arrays and read queries from_file filling arrays
	// and num_queries appropriately

	return *this;
}

QueryProcessor& QueryProcessor::solve(Graph& G, Index* indexes, uint d) {
	for (uint i = 0; i < this->num_queries; ++i)
		this->results[i] = reachable(queries[i].first, queries[i].second, indexes, d, G);
	return *this;
}

QueryProcessor& QueryProcessor::clear(void) {
	// TODO free resources
}

uint QueryProcessor::get_num_queries(void) const {
	return this->num_queries;
}

QueryProcessor::~QueryProcessor() {
	// TODO call clear
}
