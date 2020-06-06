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

static uint find_min_rank(vector<Node*> children, Index& index) {
    uint minval;
    uint val;

    if (children.size() == 0) {
        return 0u;
    }

    minval = index.get_interval(children[0]->get_id()).first;

    for(uint i=1; i<children.size(); ++i) {
        val = index.get_interval(children[i]->get_id()).first;
        if ( val < minval) {
            minval = val;
        }
    }

    return minval;
}

Index* randomized_labelling(Graph& G, const uint d) {
    vector<Node*> roots = G.get_roots(true);
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
        vector<Node*> roots = G.get_roots(true);
        unordered_set<uint> visited_nodes;
        uint rank=1u;
        for(uint j=0; j<roots.size(); ++j){
            randomized_visit(roots[j], G, rank, visited_nodes, indexes[i]);
        }
    }

    return indexes;
}

bool randomized_visit(Node* x, Graph& G, uint& rank, unordered_set<uint>& visited, Index& index) {
    if (x == NULL) return false;
    if (visited.count(x->get_id()) > 0) // Node already visited
        return false;
    
    visited.insert(x->get_id()); // Add this node to already visited

#ifdef DEBUG
    cout<<"[Thread "<<i<<"] Visiting node "<<x->get_id()<<endl;
    usleep( ( rand()%100 +1 ) *100); // Sleep from 1ms to 100ms
#endif

    // Call on children in random order
    vector<Node*> children = G.get_children(x, true);
    for(uint j=0; j<children.size(); ++j)
        randomized_visit(children[j], G, rank, visited, index);
    
    if (children.size() == 0u) {
        Interval ll(rank, rank);
        index.set_interval(ll, x->get_id());
    } else {

        // Compute minimum rank across children
        uint min_rank = find_min_rank(children, index);

#ifdef DEBUG
        cout<<"[Thread "<<i<<"] Min rank below me is "<<min_rank;
        cout<<"; my rank is "<<rank<<endl;
#endif

        Interval ll(min(rank, min_rank), rank);

        // Set this node's interval
        index.set_interval(ll, x->get_id());
    }

#ifdef DEBUG
    cout<<"[Thread "<<i<<"] Updated my node:"<<endl;
    cout<<*x<<endl<<endl;
#endif

    ++rank;

    return true;
}
