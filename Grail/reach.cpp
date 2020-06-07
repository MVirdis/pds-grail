#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "Grail.h"
#include "Query.h"

std::vector<Query> read_query(string path) {
	std::vector<Query> queries;
	
	Interval interval;
	ifstream file;
	if (!file.is_open(path))
		cerr << "Errod during the open. Try with another name" << endl;
	
	while (file >> interval.first >> interval.second) {
		Query q(interval);
		queries.push_back(q);
	}

	return queries;
}

void call_reachable(Index *indexes, std::vector<Query>& queries, uint d, Graph& G) {
	for (int i = 0; i < queries.size(); ++i)
		queries[i].result = reachable(queries[i].query.first, queries[i].query.second, indexes, d, G);
}

bool reachable(uint u, uint v, Index *indexes, uint d, Graph& G) {
	//for each Index check if interval Lv !C Lu and return false
	for(int i = 0; i < d; ++i) {
		if ((indexes[i][v].first < indexes[i][u].first) || (indexes[i][v].second > indexes[i][u].second))
			return false;
	}

	//for each u-child check if v is in the set, then return true (we find that u -> v)
	for (int i = 1; i < G.mat[u][0]; ++i)
		if (G.mat[u][i] == v)
			return true;
	
	//for each u-child (call it c) check if Lv C Lc. If it's true call recursively reachable
	for(int i = 1; i < G.mat[u][0]; ++i) {
		for (int j = 0; j < d; ++i) {
			if ((indexes[j][v].first >= indexes[j][G.mat[u][i]].first) && (indexes[i][v].second <= indexes[i][G.mat[u][i]].second)) {
				if(reachable(G.mat[u][i], v, indexes, d, G))
					return true;
			}
			else 
				return false;
		}
	}
}
