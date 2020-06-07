#include <iostream>

#include "Types.h"
#include "Grail.h"

using namespace std;

bool reachable(uint u, uint v, Index *indexes, uint d, Graph& G) {
	// For each Index check if interval Lv !C Lu and return false
	for(int i = 0; i < d; ++i) {
		if ((indexes[i].get_interval(v).first < indexes[i].get_interval(u).first) || (indexes[i].get_interval(v).second > indexes[i].get_interval(u).second))
			return false;
	}

	//for each u-child check if v is in the set, then return true (we find that u -> v)
	uint* child_data = G.get_children(u);
	for (int i = 1; i <= child_data[0]; ++i)
		if (child_data[i] == v)
			return true;
	
	//for each u-child (call it c) check if Lv C Lc. If it's true call recursively reachable
	for(int i = 1; i <= child_data[0]; ++i) {
		for (int j = 0; j < d; ++i) {
			if ((indexes[j].get_interval(v).first >= indexes[j].get_interval(child_data[i]).first) && 
				(indexes[i].get_interval(v).second <= indexes[i].get_interval(child_data[i]).second)) {
				if(reachable(child_data[i], v, indexes, d, G))
					return true;
			}
		}
	}

	return false;
}
