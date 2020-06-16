#include <iostream>
#include <string>

#include "Types.h"
#include "Grail.h"
#include "Graph.h"
#include "Query.h"

using namespace std;

uint d;
Graph G;
QueryProcessor QP;
Index* indexes;

int main(int argc, char** argv) {

    if (argc != 4) {
        cout<<"Need to know .gra file, d value and .que file"<<endl;
        cout<<"grail graph.gra d queries.que"<<endl;
        return -1;
    }
    
#ifdef VERBOSE
    cout<<"Building graph..."<<endl<<flush;
#endif
    G.from_file(argv[1]);
#ifdef VERBOSE
    cout<<"Processing query file..."<<endl<<flush;
#endif
    d = stoi(string(argv[2]));
    QP.from_file(argv[3]);
#ifdef VERBOSE
    cout<<"Building indexes..."<<endl<<flush;
#endif
    indexes = randomized_labelling(G, d);
#ifdef VERBOSE
    cout<<"Solving queries..."<<endl<<flush;
#endif
    QP.solve(G, indexes,d,0);

    return 0;
}
