#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

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

#ifdef DEBUG
    cout<<"Read num: "<<num<<endl;
#endif

    // Allocate flags for root nodes
    bool* is_root = new bool[num];

    // Allocate num empty nodes
    for(int i=0; i<num; ++i) {
        Node* new_node = new Node(i);
        if (new_node == NULL) {
            cerr<<"Error allocating new node!"<<endl;
            delete[] is_root;
            file.close();
            return *this;
        }
        is_root[i] = true;
        nodes.push_back(new_node);
    }

    // For each new node make connections
    string line;
    int id=0;
    while (getline(file, line))
    {
        istringstream iss(line);
        int nodeid, childid;

        if (!(iss >> nodeid) || nodeid != (id++)) {
            continue;
        }

        // Read remaining numbers in line
        while((iss >> childid)) {
            nodes[nodeid]->add_child(nodes[childid]);
            is_root[childid] = false;
        }
    }

    // Save root nodes
    for(int i=0; i<num; ++i)
        if(is_root[i])
            roots.push_back(nodes[i]);

    delete[] is_root;
    file.close();
    return *this;
}

vector<Node*> Graph::get_roots(bool random) const {
    vector<Node*> vec(this->roots);
    if (!random) return this->roots;
    random_shuffle(vec.begin(), vec.end());
    return vec;
}

vector<Node*> Graph::get_children(Node* node, bool random) const {
    vector<Node*> vec;
    if (node == NULL) return vector<Node*>();
    vec = node->get_children();
    if (random) random_shuffle(vec.begin(), vec.end());
    return vec;
}

Node* Graph::get_node(int nid) const {
    if (this->nodes.size() == 0 || this->nodes.size() <= (int)nid) return NULL;
    return this->nodes[nid];
}

uint Graph::get_num_nodes(void) const {
    return this->nodes.size();
}

ostream& operator <<(ostream& ostr, const Graph& graph) {
    ostr<<"Nodes: [ ";
    for (int i=0; i<graph.nodes.size()-1; ++i) {
        ostr<<*(graph.nodes[i])<<", ";
    }
    ostr<<*(*graph.nodes.end())<<" ]";
    return ostr;
}