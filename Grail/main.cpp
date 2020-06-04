#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "Graph.h"
#include "Grail.h"
#include "Generator.h"

#define PARAMS "Param 1: graph file;\nParam 2: integer d;\nParam 3: query file"
#define MENU_HEADER "[GRAIL Performance Tester]\nSelect one of the following options:"
#define MENU_OPTS "  -1. Quit\n   0. Print MENU\n   1. Create a Graph\n   2. Run Sequencial GRAIL with Graph, Node\n   3. Run GRAIL with Graph, Node on d threads\n   4. Run GRAIL with Graph, Node on R*d threads"

using namespace std;

void graph_creation();
void dgrail_graph();
void seq_grail_graph();

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
                case 2:
                    seq_grail_graph();
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

void seq_grail_graph() {
    Graph G;
    string name;
    ifstream graph_file;
    uint d;

    cout<<endl<<"GRAIL Sequential Test with Graph class"<<endl;
    cout<<"What is the name of the graph file? "; (cin>>name).get();
    graph_file.open(name);
    if (!graph_file.is_open()) {
        cerr<<"Couldn't open the file. Is the name right?"<<endl;
        return;
    }
    graph_file.close();

    cout<<"Loading graph...";
    G.from_file(name.data());
    cout<<"  OK"<<endl;

    cout<<"What is the value of d for the index? "; (cin>>d).get();

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    sequential_labelling(G, d); // Builds Index
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout<<"The index will be shown:"<<endl;
    for(uint j=0; j<min(G.get_num_nodes(), 20u); ++j) {
        Node* x = G.get_node(j);
        cout<<"Node "<<x->get_id()<<": ";
        for(uint i=0; i<d; ++i) {
            Interval label = x->get_interval(i);
            cout<<"["<<label.first<<", "<<label.second<<"]";
            if (i<d-1)
                cout<<", ";
        }
        cout<<endl;
    }
    if (G.get_num_nodes() > 20u) {
        cout<<"..."<<endl;
        for(uint j=G.get_num_nodes()-1u-5u; j<G.get_num_nodes(); ++j) {
            Node* x = G.get_node(j);
            cout<<"Node "<<x->get_id()<<": ";
            for(uint i=0; i<d; ++i) {
                Interval label = x->get_interval(i);
                cout<<"["<<label.first<<", "<<label.second<<"]";
                if (i<d-1)
                    cout<<", ";
            }
            cout<<endl;
        }
    }

    cout<<"Index building took ";
    cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<"[ms]";
    cout<<" / "<<chrono::duration_cast<chrono::seconds>(end - begin).count()<<"[s]" <<endl;

    uint bs = G.compute_size(d);
    cout<<"The whole datastructure requires "<<(bs/1024u)<<"kB ";
    cout<<(bs/(1024u*1024u))<<"MB"<<endl;
}
