#include <string>
#include <fstream>
#include <iostream>

#include "Query.h"
#include "Grail.h"

using namespace std;

QueryProcessor::QueryProcessor() {
	this->clear();
}

QueryProcessor::QueryProcessor(string file_path) {
	this->from_file(file_path);
}

QueryProcessor& QueryProcessor::from_file(string file_path) {
	Interval interval;
	ifstream file;

	if (this->queries != NULL)
		this->clear();
		
	if (this->results != NULL)
		this->clear();
		
	file.open(file_path);
	
	while(file >> interval.first >> interval.second)
		this->num_queries++;
	
	this->queries = new Query[this->num_queries];
	this->results = new bool[this->num_queries];
	
	fseek(file, 0, SEEK_SET);
	
	for(uint i = 0; i < this->num_queries; ++i) {
		file >> this->queries[i].first >> this->queries[i].second;
		this->results[i] = false;
	}

	return *this;
}

QueryProcessor& QueryProcessor::solve(Graph& G, Index* indexes, uint d) {
	for (uint i = 0; i < this->num_queries; ++i)
		this->results[i] = reachable(queries[i].first, queries[i].second, indexes, d, G);
	return *this;
}

QueryProcessor& QueryProcessor::clear(void) {
	this->queries = NULL;
	this->results = NULL;
	this->num_queries = 0;
}

uint QueryProcessor::get_num_queries(void) const {
	return this->num_queries;
}

QueryProcessor::~QueryProcessor() {
	delete[] queries;
	delete[] results;
}
