#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Graph.h"
//#include "Grail.h"
#include "Generator.h"

#define PARAMS "Param 1: graph file;\nParam 2: integer d;\nParam 3: query file"
#define MENU_HEADER "[GRAIL Performance Tester]\nSelect one of the following options:"
#define MENU_OPTS "  -1. Quit\n   0. Print MENU\n   1. Create a Graph\n   2. Run Sequencial GRAIL with Graph, Node\n   3. Run GRAIL with Graph, Node on d threads\n   4. Run GRAIL with Graph, Node on R*d threads"

using namespace std;

void graph_creation();
void dgrail_graph();

int main() {

    int opt;
    while(1) {
        cout<<MENU_HEADER<<endl<<MENU_OPTS<<endl;
        opt = 1;
        while (opt) {
            cout<<">> "; (cin>>opt).get();
            switch(opt) {
                case -1:
                    return 0;
                case 0:
                    break;
                case 1:
                    graph_creation();
                    break;
                case 3:
                    dgrail_graph();
                    break;
                default:
                    cout<<"Not Supported"<<endl;
            }
        }
    }

    return 0;
}

void graph_creation() {
    int nodes, edges, queries;
    string name;
    cout<<"GRAPH Creation"<<endl;
    cout<<"How many nodes? "; (cin>>nodes).get();
    cout<<"How many edges at max.? "; (cin>>edges).get();
    cout<<"How many queries? "; (cin>>queries).get();
    cout<<"What's the graph's name (no spaces)? "; (cin>>name).get();
    
    if (nodes > 1000) cout<<"It will take a few minutes..."<<endl;

    make_graph(nodes, edges, queries, name.data());
    cout<<endl;
}

void dgrail_graph() {
    Graph G;
    string name;
    ifstream graph_file;
    cout<<endl<<"GRAIL Test with D threads and Graph class"<<endl;
    cout<<"What is the name of the graph file? "; (cin>>name).get();
    graph_file.open(name);
    if (!graph_file.is_open()) {
        cerr<<"Couldn't open the file. Is the name right?"<<endl;
        return;
    }
    graph_file.close();
    G.from_file(name.data());
    cout<<G<<endl;
}
