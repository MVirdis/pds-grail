#include <iostream>
#include <string>

#include "Types.h"
#include "Grail.h"
#include "Graph.h"
#include "Query.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc != 4) {
        cout<<"Need to know .gra file, d value and .que file"<<endl;
        cout<<"grail graph.gra d queries.que"<<endl;
        return -1;
    }

    uint d;
    Graph G;
    QueryProcessor QP;
    Index* indexes;
    
#ifdef VERBOSE
    cout<<"Building graph..."<<endl<<flush;
#endif
    G.from_file(argv[1]);
    d = stoi(string(argv[2]));
#ifdef VERBOSE
    cout<<"Building indexes..."<<endl<<flush;
#endif
    indexes = randomized_labelling(G, d);
#ifdef VERBOSE
    cout<<"Processing query file..."<<endl<<flush;
#endif
    QP.from_file(argv[3],indexes, d, true);
#ifdef VERBOSE
    cout<<"Solving queries..."<<endl<<flush;
#endif
    QP.solve(G, indexes,d,1);
    cout<<(1.0f-QP.after_selection_ratio())*100<<"% of queries done during I/O"<<endl;
    return 0;
}
