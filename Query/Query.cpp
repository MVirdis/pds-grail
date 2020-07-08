#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <string.h>

#include "Query.h"
#include "Grail.h"

using namespace std;

QueryProcessor& QueryProcessor::from_file(string file_path, Index *indexes, uint d) {
	Query q;
	ifstream file;

	if (this->queries.size() != 0)
		this->clear();
		
	file.open(file_path);
	
	while(file >> q.first >> q.second) {
		this->queries.push_back(q);
	}

	file.close();

	return *this;
}

static void solve_queries(uint offset, uint i, vector<Query>& queries, Graph& G, Index *indexes, uint d, Barrier& barr) {

	uint num_queries = queries.size();
	bool last = (i == (NUM_QUERY_WORKERS-1));
	uint tot = (offset)*(i+1) + (last ? (num_queries%NUM_QUERY_WORKERS) : 0 );
	for (uint j = (offset*i); j < tot; ++j) {
		uint u = queries[j].first;
		uint v = queries[j].second;
		queries[j].result = reachable(u, v, indexes, d, G, false);
	}
	
	barr.wait();
	
}

QueryProcessor& QueryProcessor::solve(Graph& G, Index* indexes, uint d, int menu) {
	uint num_queries = this->queries.size();
	switch(menu) {
		case 0: {
			for (uint i = 0; i < num_queries; ++i) {
				this->queries[i].result = reachable(queries[i].first, queries[i].second, indexes, d, G);
			#if DEBUG
				cout << "Node " << queries[i].first << (this->results[i] == true ? " reach node " : " doesn't reach node ") << queries[i].second << endl;
			#endif
			}
			break;
		}
		
		case 1: {
			
			Barrier barrier(NUM_QUERY_WORKERS+1);
			mutex m;
			uint offset = (num_queries)/NUM_QUERY_WORKERS;
			
			for (uint i = 0; i < NUM_QUERY_WORKERS; ++i) {
				thread t (solve_queries, offset, i, ref(this->queries), ref(G), indexes, d, ref(barrier));
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
	
	for(uint i=0u; i<num_queries; ++i) {
		if(this->queries[i].result) cout<<"REACHABLE"<<endl;
		else cout<<"NOT REACHABLE"<<endl;
	}

	return *this;
}

void QueryProcessor::clear(void) {
	queries.clear();
}
