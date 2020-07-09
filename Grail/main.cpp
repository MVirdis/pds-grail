#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

#include "Graph.h"
#include "Grail.h"
#include "Generator.h"

#define MENU_HEADER "[GRAIL Performance Tester]\nSelect one of the following options:"
#define MENU_OPTS "  -1. Quit\n   0. Print MENU\n   1. Create a Graph\n   2. Load a Graph\n   3. Build Index with Sequential GRAIL\n   4. Build Index with Parallel GRAIL\n   5. Process Queries Sequential\n   6. Process Queries Parallel\n   7. Analyze index diversity"

using namespace std;

Graph G;
uint d = 0u;
Index* indexes = NULL;
QueryProcessor QP;

void graph_creation();
void graph_load();
void grail_graph(int option);
void process_queries(int menu);
void index_quality();

int main() {

    int opt;
    while(1) {
        cout<<MENU_HEADER<<endl<<MENU_OPTS<<endl;
        opt = 1;
        while (opt) {
            // Print Status
            cout<<endl<<"[STATUS]"<<endl;
            if (G.get_num_nodes() > 0u) {
                cout<<"Loaded Graph with "<<G.get_num_nodes()<<" nodes"<<endl;
                if (indexes != NULL && d > 0u)
                    cout<<"Index created with d="<<d<<endl;
            } else
                cout<<"Empty"<<endl;
            // Get command
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
                    graph_load();
                    break;
                case 3:
                    grail_graph(3);
                    break;
                case 4:
                    grail_graph(4);
                    break;
                case 5:
                    process_queries(0);
                    break;
				case 6:
					process_queries(1);
					break;
                case 7:
                    index_quality();
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
    cout<<"What's the graph's name (no spaces, no extension)? "; (cin>>name).get();
    
    if (nodes > 1000) cout<<"It will take a few minutes..."<<endl;

    make_graph(nodes, edges, queries, name.data());
    cout<<endl;
}

void graph_load() {
    string file_path;
    ifstream graph_file;
    chrono::steady_clock::time_point begin, end;
    cout<<"GRAPH Loader"<<endl;
    cout<<"What is the path to the .gra file? "; (cin>>file_path).get();
    graph_file.open(file_path);
    if (!graph_file.is_open()) {
        cerr<<"Couldn't open the file. Is the name right?"<<endl;
        return;
    }
    graph_file.close();

    cout<<"Loading graph..."<<flush;
    begin = chrono::steady_clock::now();
    G.from_file(file_path.data());
    end = chrono::steady_clock::now();
    cout<<"  OK"<<endl<<flush;

    cout<<"Time required: ";
    cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<"[ms]";
    cout<<" / "<<chrono::duration_cast<chrono::seconds>(end - begin).count()<<"[s]" <<endl;

    // Remove previous index
    if(indexes) {
        delete[] indexes;
        indexes = NULL;
    }
}

void grail_graph(int option) {
    if (G.get_num_nodes() == 0u) {
        cout<<"Cannot build an index if you don't load a graph!!"<<endl;
        return;
    }
    cout<<"GRAIL Tester - "<<(option == 3 ? "Sequential" : "Parallel")<<endl;
    cout<<"What is the value of d ? "; (cin>>d).get();

    chrono::steady_clock::time_point begin, end;
	
	if (indexes != NULL)
		delete[] indexes;

    switch (option) {
        case 3:
            begin = chrono::steady_clock::now();
            indexes = sequential_labelling(G, d); // Builds Index
            end = chrono::steady_clock::now();
            break;
        case 4:
            begin = chrono::steady_clock::now();
            indexes = randomized_labelling(G, d); // Builds Index
            end = chrono::steady_clock::now();
            break;
        default:
            cerr<<"Bad Option!"<<endl;
            return;
    }

    cout<<"The index will be shown:"<<endl<<flush;
    for(uint j=0; j<min(G.get_num_nodes(), 20u); ++j) {
        cout<<"Node "<<j<<": ";
        for(uint i=0; i<d; ++i) {
            Interval label = indexes[i].get_interval(j);
            cout<<"["<<label.first<<", "<<label.second<<"]";
            if (i<d-1)
                cout<<", ";
        }
        cout<<endl;
    }
    if (G.get_num_nodes() > 20u) {
        cout<<"..."<<endl;
        for(uint j=max(G.get_num_nodes()-1u-5u, 20u); j<G.get_num_nodes(); ++j) {
            cout<<"Node "<<j<<": ";
            for(uint i=0; i<d; ++i) {
                Interval label = indexes[i].get_interval(j);
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

    cout<<"Index requires "<<2*d*sizeof(uint)*G.get_num_nodes()/(1024u*1024u)<<"MB"<<endl;
}

void index_quality() {
    if (indexes == NULL) {
        cout<<"Error first build an index"<<endl;
        return;
    }
    cout<<"Analyzing index..."<<flush;
    cout<<"\rIndex diversity: "<<(int)(index_diversity(indexes, d)*100)<<"%"<<endl;
}

void process_queries(int menu) {
	string name;
	ifstream file;

    if (G.get_num_nodes() == 0u) {
        cout<<"First load a graph and build an index!"<<endl;
        return;
    }
    if (indexes == NULL && d == 0u) {
        cout<<"First build an index!!"<<endl;
        return;
    }
	
    cout<<"QUERY " << (menu == 0 ? "SEQUENTIAL " : "PARALLEL ") << "TESTER"<<endl;
	cout << "What is the name of the query file? ";
	(cin >> name).get();

	chrono::steady_clock::time_point begin, end;

	file.open(name);
	if (!file.is_open()) {
		cerr << "Error during the open. Try with another name" << endl;
		return;
	}
    file.close();
	begin = chrono::steady_clock::now();
    QP.from_file(name, indexes, d);
	QP.solve(G, indexes, d, menu, false);
	end = chrono::steady_clock::now();

	cout << "All queries processed in ";
	cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count()<<"[ms]";
    cout<<" / "<<chrono::duration_cast<chrono::seconds>(end - begin).count()<<"[s]" <<endl<<flush;

    cout<<"Average time to answer a single query ";
    cout<<chrono::duration_cast<chrono::milliseconds>(end - begin).count() / QP.get_num_queries()<<" [ms]  ";
    cout<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / QP.get_num_queries()<<" [ns]  ";
}
