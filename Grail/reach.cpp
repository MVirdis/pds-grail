#include <iostream>
#include <thread>

#include "Types.h"
#include "Grail.h"

using namespace std;

bool reachable(uint u, uint v, Index *indexes, uint d, Graph& G) {
	// For each Index check if interval Lv !C Lu and return false
	for(uint i = 0; i < d; ++i) {
		if ((indexes[i].get_interval(v).first < indexes[i].get_interval(u).first) || (indexes[i].get_interval(v).second > indexes[i].get_interval(u).second))
			return false;
	}

	//for each u-child check if v is in the set, then return true (we find that u -> v)
	uint* child_data = G.get_children(u);
	for (uint i = 1; i <= child_data[0]; ++i)
		if (child_data[i] == v)
			return true;
	
	//for each u-child (call it c) check if Lv C Lc. If it's true call recursively reachable
	for(uint i = 1; i <= child_data[0]; ++i) {
		bool is_candidate = true;
		for (uint j = 0; j < d; ++j) {
			if ((indexes[j].get_interval(v).first < indexes[j].get_interval(child_data[i]).first) ||
				(indexes[j].get_interval(v).second > indexes[j].get_interval(child_data[i]).second)) {
				is_candidate = false;
				break;	
			}
		}
		if(is_candidate && reachable(child_data[i], v, indexes, d, G))
			return true;
	}

	return false;
}

void reachable_parallel(uint u, uint v, Index *indexes, uint d, Graph& G, bool& result) {
	result = reachable(u, v, indexes, d, G);
#if DEBUG
	cout << u << ((result == true)? "reach" : "does not reach") << v << endl;
#endif
}

void pre_process(int offset, uint i, Query *queries, bool *results, bool last, Graph& G, Index *indexes, uint d, uint num_queries, Barrier& barr) {
	if (!last) {
		for (uint j = (offset*i); j < ((offset)*(i+1)); ++j) {
			thread t (reachable_parallel, queries[j].first, queries[j].second, indexes, d, ref(G), ref(results[j]));
			t.join();
		}
	}

	if (last) {
		int last_offset = num_queries%HOW_MANY_BUFF;
		for (uint j = (offset*i); j < (((offset)*(i+1))+last_offset); ++j) {
			thread t (reachable_parallel, queries[j].first, queries[j].second, indexes, d, ref(G), ref(results[j]));
			t.join();
		}
	}
	
	barr.wait();
	
}








