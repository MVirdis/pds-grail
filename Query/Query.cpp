#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <string.h>

#include "Query.h"
#include "Grail.h"

using namespace std;

QueryProcessor::QueryProcessor() {
	this->results = NULL;
	this->num_queries = 0;
	this->after_select = 0;
}

QueryProcessor& QueryProcessor::select_queries(uint u, uint v, Index *indexes, uint d, bool& res) {
	for(uint i = 0; i < d; ++i) {
		if ((indexes[i].get_interval(v).first < indexes[i].get_interval(u).first) || (indexes[i].get_interval(v).second > indexes[i].get_interval(u).second)) {
			res = false;
			return *this;
		}
		
		else 
			res = true;
	}
	return *this;
}

QueryProcessor& QueryProcessor::from_file(string file_path, Index *indexes, uint d) {
	Interval interval;
	ifstream file;

	if (this->queries.size() != 0 || this->results != NULL)
		this->clear();
		
	file.open(file_path);
	
	while(file >> interval.first >> interval.second)
		this->num_queries++;
	
	file.clear();
	file.seekg(0);
	
	for(uint i = 0; i < this->num_queries; ++i) {
		bool res;
		Query q;
		file >> q.first >> q.second;
		this -> select_queries(q.first, q.second, indexes, d, res);
		if (res) {
			this->queries.push_back(q);
			++after_select;
		}
	}

	this->results = new bool[this->after_select];
	double percentage = (double)(100*((double)after_select/(double)num_queries));
	cout << "after the selection we have " << percentage << "% " << "of queries" << endl;

	return *this;
}



QueryProcessor& QueryProcessor::solve(Graph& G, Index* indexes, uint d, int menu) {
	switch(menu) {
	
	case 0: {
	
		for (uint i = 0; i < this->after_select; ++i) {
			this->results[i] = reachable(queries[i].first, queries[i].second, indexes, d, G);
		#if DEBUG
			cout << "Node " << queries[i].first << (this->results[i] == true ? " reach node " : " doesn't reach node ") << queries[i].second << endl;
		#endif

			//cout<<queries[i].first<<"  "<<queries[i].second<<":    ";
			//if(this->results[i]) cout<<"REACHABLE"<<endl;
			//else cout<<"NOT REACHABLE"<<endl;
		}
		break;
	}
		
	case 1: {
		
		Barrier barrier(HOW_MANY_BUFF+1);
		int offset = (this -> after_select)/HOW_MANY_BUFF;
		
		for (uint i = 0; i < HOW_MANY_BUFF; ++i) {
			thread t (pre_process, offset, i, queries, results, ((i == (HOW_MANY_BUFF-1))? true:false), ref(G), indexes, d, this->after_select, ref(barrier));
			t.detach();
		}
		
		barrier.wait();
		
		break;
	}
		
	default: {
	
		cerr << "menu value not supported\n" << endl;
		return *this;
	}
	}
	
	return *this;
}

QueryProcessor& QueryProcessor::clear(void) {
	queries.clear();
	delete[] results;
	this->results = NULL;
	this->num_queries = 0;
	this->after_select = 0;
	return *this;
}


QueryProcessor& QueryProcessor::precision_test(Graph& G, Index *indexes, uint d) {
	int count = 0;
	bool *parallel_results = new bool[this->after_select];
	memcpy(parallel_results, this->results, sizeof(bool)*this->after_select);
	this->solve(G, indexes, d, 0);
	for (uint i = 0; i < this->num_queries; ++i) {
		if (parallel_results[i] == this->results[i])
			count++;
	}
	
	cout << "Precision: " << (count/this->after_select)*100 << "%" << endl;

	delete[] parallel_results;
	return *this;
}

QueryProcessor::~QueryProcessor() {
	delete[] results;
}
