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

bool QueryProcessor::select_queries(uint u, uint v, Index *indexes, uint d) {
	for(uint i = 0; i < d; ++i) {
		if ((indexes[i].get_interval(v).first < indexes[i].get_interval(u).first) || (indexes[i].get_interval(v).second > indexes[i].get_interval(u).second)) {
			return false;
		}
	}
	return true;
}

QueryProcessor& QueryProcessor::from_file(string file_path, Index *indexes, uint d, bool parallel) {
	Query q;
	ifstream file;

	if (this->queries.size() != 0 || this->results != NULL)
		this->clear();
		
	file.open(file_path);
	
	while(file >> q.first >> q.second) {
		if (parallel) {
			bool res;
			this->num_queries++;
			res = this -> select_queries(q.first, q.second, indexes, d);
			if (res) {
				this->queries.push_back(q);
				++after_select;
			} else {
				cout<<q.first<<"  "<<q.second<<": ";
				cout<<"NOT REACHABLE"<<endl;
			}
		} else {
			this->num_queries++;
			this->queries.push_back(q);
			this->after_select++;
		}
	}

	file.close();

	return *this;
}



QueryProcessor& QueryProcessor::solve(Graph& G, Index* indexes, uint d, int menu) {
	switch(menu) {
	
	case 0: {
		for (uint i = 0; i < this->after_select; ++i) {
			bool result = reachable(queries[i].first, queries[i].second, indexes, d, G);
		#if DEBUG
			cout << "Node " << queries[i].first << (this->results[i] == true ? " reach node " : " doesn't reach node ") << queries[i].second << endl;
		#endif

			cout<<queries[i].first<<"  "<<queries[i].second<<":    ";
			if(result) cout<<"REACHABLE"<<endl;
			else cout<<"NOT REACHABLE"<<endl;
		}
		break;
	}
		
	case 1: {
		
		Barrier barrier(NUM_QUERY_WORKERS+1);
		mutex m;
		int offset = (this -> after_select)/NUM_QUERY_WORKERS;
		
		for (uint i = 0; i < NUM_QUERY_WORKERS; ++i) {
			thread t (pre_process, offset, i, queries, ((i == (NUM_QUERY_WORKERS-1))? true:false), ref(G), indexes, d, this->after_select, ref(barrier), &m);
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
	if (results) delete[] results;
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

float QueryProcessor::after_selection_ratio() const {
	return (float)this->after_select/this->num_queries;
}

QueryProcessor::~QueryProcessor() {
	delete[] results;
}
