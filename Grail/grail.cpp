#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <string.h>
#include <algorithm>
#include <random>
#include <chrono>

#include "Types.h"
#include "Graph.h"
#include "Thread.h"
#include "Grail.h"
#include "Index.h"

using namespace std;

float index_diversity(Index* indexes, uint d) {
    uint total = indexes[0].get_size();
    uint different = 0u;
    for(uint i=0; i<total; ++i) {
        uint uniqueness = 0u;
        set<Interval> seen;
        for(uint j=0u; j<d; ++j) {
            if (seen.count( indexes[j].get_interval(i) )) continue;
            seen.insert(indexes[j].get_interval(i));
            ++uniqueness;
        }
        different += uniqueness;
    }
    return ((float)different)/(d*total);
}

static uint find_min_rank(uint* children, uint nchildren, Index& index) {
    uint minval;
    uint val;

    if (nchildren == 0u) {
        return 1u;
    }

    minval = index.get_interval(children[0]).first;

    for(uint i=1u; i<nchildren; ++i) {
        val = index.get_interval(children[i]).first;
        if (val == 0u) {
            cerr<<"ERROR THIS SHOULD NOT HAPPEN: find_min_rank "<<children[i]<<" has L[1] == 0, but was already visited"<<endl;
            return 1u;
        }
        if ( val < minval) {
            minval = val;
        }
    }

    return minval;
}

Index* randomized_labelling(Graph& G, const uint d) {
    // One visitor for each dimension
    RandomVisitor visitors[d];
    // One rank variable for each thread
    // One visited set for each thread
    uint ranks[d];
    unordered_set<uint> visited_sets[d];
    // One index for each thread
    Index* indexes = new Index[d];

    Barrier barr(d + 1);

    // Start all threads
    for(uint i=0; i<d; ++i) {
        ranks[i] = 1u;
        indexes[i].set_size(G.get_num_nodes());
        visitors[i].set_graph(&G)
                    .set_rank(&ranks[i])
                    .set_visited_set(&visited_sets[i])
                    .set_index(&indexes[i])
                    .set_barrier(&barr)
                    .run();
    }

    // for all threads
    barr.wait();

    return indexes;
}

Index* sequential_labelling(Graph& G, const uint d) {
    Index* indexes = new Index[d];
    for(uint i=0; i<d; ++i) {
        indexes[i].set_size(G.get_num_nodes());
        const uint* roots = G.get_roots();
        unordered_set<uint> visited_nodes;
        uint rank=1u;
        for(uint j=0; j<G.get_num_roots(); ++j){
            randomized_visit(roots[j], G, rank, visited_nodes, indexes[i]);
        }
    }

    return indexes;
}

uint* reorder(uint* children, uint nchildren) {
    if (children == NULL || nchildren == 0u) {
        cerr<<"ERROR REORDER SHOULD NOT BE CALLED ON NULL"<<endl;
        return NULL;
    }

    try {
        uint* ret = new uint[nchildren];
        memcpy(ret, children, sizeof(uint)*nchildren);
        shuffle(ret, ret+nchildren, default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
        return ret;
    } catch(const bad_alloc& e) {
        cerr<<"REORDER FINISHED MEMORY"<<endl;
        return NULL;
    }
}

bool randomized_visit(uint x, Graph& G, uint& rank, unordered_set<uint>& visited, Index& index) {
    if (visited.count(x) > 0) // Node already visited
        return false;
    
    visited.insert(x); // Add this node to already visited

#ifdef DEBUG
    cout<<"Visiting node "<<x<<endl<<flush;
#endif

    // Call on children in random order
    uint* ch_data = G.get_children(x);
    uint nchildren = ch_data[0];
    ch_data = ch_data+1;
    
    if (nchildren == 0u) {
        Interval ll(rank, rank);
        index.set_interval(ll, x);
    } else {
        uint min_rank;
        if (nchildren == 1u) {
            randomized_visit(ch_data[0], G, rank, visited, index);
            min_rank = find_min_rank(ch_data, 1u, index);
        } else {
            ch_data = reorder(ch_data, nchildren);
            for(uint j=0; j<nchildren; ++j) {
                randomized_visit(ch_data[j], G, rank, visited, index);
            }

            // Compute minimum rank across children
            min_rank = find_min_rank(ch_data, nchildren, index);
            
            if (ch_data) delete[] ch_data;
            else cerr<<"RETURN OF REORDER IS NULL"<<endl;
        }
        Interval ll(min(rank, min_rank), rank);
#ifdef DEBUG
        cout<<"Min rank below me is "<<min_rank;
        cout<<"; my rank is "<<rank<<endl;
#endif
        // Set this node's interval
        index.set_interval(ll, x);
    }

    ++rank;

    return true;
}
