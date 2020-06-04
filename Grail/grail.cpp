#include <iostream>
#include <vector>
#include <unordered_set>
#include <unistd.h>
#include <cstdlib>

#include "Types.h"
#include "Graph.h"
#include "Thread.h"
#include "Grail.h"

using namespace std;

bool randomized_labelling(Graph& G, const uint d) {
#if PARALLEL_VISITS
    vector<Node*> roots = G.get_roots(true);
    // Visitor matrix: rows for roots, columns for offsets
    RandomVisitor visitors[d*roots.size()];
    // All threads with equal offset value have same rank var
    // and same visited set
    uint ranks[d];
    unordered_set<uint> visited_sets[d];

    Barrier barr(d*roots.size() + 1);

    // Start all threads
    for(uint i=0; i<d; ++i) {
        ranks[i] = 1u;
        for(uint j=0; j<roots.size(); ++j)
            visitors[i+j*d].set_graph(G)
                           .set_offset(i)
                           .set_start_node(roots[j])
                           .set_rank(ranks[i])
                           .set_visited_set(visited_sets[i])
                           .set_barrier(barr)
                           .run();
    }

    // Wait for all threads
    barr.wait();
#else
    vector<Node*> roots = G.get_roots(true);
    // One visitor for each dimension
    RandomVisitor visitors[d];
    // One rank variable for each thread
    // One visited set for each thread
    uint ranks[d];
    unordered_set<uint> visited_sets[d];

    Barrier barr(d + 1);

    // Start all threads
    for(uint i=0; i<d; ++i) {
        ranks[i] = 1u;
        visitors[i].set_graph(G)
                    .set_offset(i)
                    .set_rank(&ranks[i])
                    .set_visited_set(&visited_sets[i])
                    .set_barrier(&barr)
                    .run();
    }

    // for all threads
    barr.wait();
#endif
    return true;
}

static uint find_min_rank(vector<Node*> children, uint dimension) {
    uint minval;
    uint val;

    if (children.size() == 0) {
        return 0u;
    }

    minval = children[0]->get_interval(dimension).first;

    for(uint i=1; i<children.size(); ++i) {
        val = children[i]->get_interval(dimension).first;
        if ( val < minval) {
            minval = val;
        }
    }

    return minval;
}

bool randomized_visit(Node* x, uint i, Graph& G, uint& rank, unordered_set<uint>& visited) {
    if (x == NULL) return false;
    if (visited.count(x->get_id()) > 0) // Node already visited
        return false;
    
    visited.insert(x->get_id()); // Add this node to already visited

#ifdef DEBUG
#if !PARALLEL_VISITS
    cout<<"[Thread "<<i<<"] Visiting node "<<x->get_id()<<endl;
    usleep( ( rand()%100 +1 ) *100); // Sleep from 1ms to 100ms
#endif
#endif

    // Call on children in random order
    vector<Node*> children = G.get_children(x, true);
    for(uint j=0; j<children.size(); ++j)
        randomized_visit(children[j], i, G, rank, visited);
    
    // Compute minimum rank across children
    uint min_rank = find_min_rank(children, i);

#ifdef DEBUG
#if !PARALLEL_VISITS
    cout<<"[Thread "<<i<<"] Min rank below me is "<<min_rank;
    cout<<"; my rank is "<<rank<<endl;
#endif
#endif

    // Set this node's interval
    x->lock();
    x->add_interval(Interval(min(rank, min_rank), rank), i);
    x->unlock();

#ifdef DEBUG
#if !PARALLEL_VISITS
    cout<<"[Thread "<<i<<"] Updated my node:"<<endl;
    cout<<*x<<endl<<endl;
#endif
#endif

    ++rank;

    return true;
}
