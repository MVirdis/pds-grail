#include <fstream>

#include "Graph.h"

using namespace std;

Graph::Graph(void) {
    this->num_nodes = 0u;
}

Graph& Graph::from_file(char* filepath) {
    ifstream file;
    uint num;

    file.open(filepath);
    file >> num;

    cout<<"Read "<<num<<endl;

    return *this;
}
