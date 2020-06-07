#include <iostream>
#include <vector>
#include <unordered_set>
#include <unistd.h>
#include <cstdlib>

#include "Types.h"
#include "Graph.h"
#include "Thread.h"
#include "Grail.h"
#include "Index.h"

using namespace std;

static uint find_min_rank(uint* children, uint nchildren, Index& index) {
    uint minval;
    uint val;

    if (nchildren == 0) {
        return 0u;
    }

    minval = index.get_interval(children[0]).first;

    for(uint i=1; i<nchildren; ++i) {
        val = index.get_interval(children[i]).first;
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
        uint* roots = G.get_roots();
        unordered_set<uint> visited_nodes;
        uint rank=1u;
        for(uint j=0; j<G.get_num_roots(); ++j){
            randomized_visit(roots[j], G, rank, visited_nodes, indexes[i]);
        }
    }

    return indexes;
}

bool randomized_visit(uint x, Graph& G, uint& rank, unordered_set<uint>& visited, Index& index) {
    if (visited.count(x) > 0) // Node already visited
        return false;
    
    visited.insert(x); // Add this node to already visited

#ifdef DEBUG
    cout<<"Visiting node "<<x<<endl;
    usleep( ( rand()%100 +1 ) *100); // Sleep from 1ms to 100ms
#endif

    // Call on children in random order
    uint* ch_data = G.get_children(x);
    uint nchildren = ch_data[0];
    // Skip first element!!!!
    for(uint j=1; j<=nchildren; ++j)
        randomized_visit(ch_data[j], G, rank, visited, index);
    
    if (nchildren == 0u) {
        Interval ll(rank, rank);
        index.set_interval(ll, x);
    } else {

        // Compute minimum rank across children
        uint min_rank = find_min_rank(ch_data+1, nchildren, index);

#ifdef DEBUG
        cout<<"Min rank below me is "<<min_rank;
        cout<<"; my rank is "<<rank<<endl;
#endif

        Interval ll(min(rank, min_rank), rank);

        // Set this node's interval
        index.set_interval(ll, x);
    }

#ifdef DEBUG
    cout<<"Updated my node"<<endl;
#endif

    ++rank;

    return true;
}
