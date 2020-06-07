#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <mutex>
#include <new>

#include "Graph.h"

using namespace std;

Graph::Graph(void) {
    this->num_nodes = 0u;
}

Graph& Graph::from_file(const char* filepath) {
    ifstream file;
    uint num;
    vector<Node*> node_children;

    if (nodes.size() > 0) this->clear();

    file.open(filepath);
    file >> num;

#ifdef DEBUG
    cout<<"Read num: "<<num<<endl;
#endif

#ifdef DEBUG
    cout<<"Allocating all nodes... ";
#endif

    // Allocate flags for root nodes
    bool* is_root = new bool[num];

    // Allocate num empty nodes
    for(uint i=0; i<num; ++i) {
            Node* new_node = new Node(i);
            is_root[i] = true;
            nodes.push_back(new_node);
    }

#ifdef DEBUG
    cout<<"  OK"<<endl<<"Start reading lines:"<<endl;
#endif

    // For each new node make connections
    string line;
    int id=0;
    while (getline(file, line))
    {
        istringstream iss(line);
        int nodeid, childid;

#ifdef DEBUG
        cout<<"LINE("<<id<<"): \""<<line<<"\""<<endl;
#endif

        if (!(iss >> nodeid)) {
#ifdef DEBUG
            cout<<" this line doesn't start with a number. Skipping..."<<endl;
#endif
            continue;
        }

#ifdef DEBUG
        cout<<"Node "<<nodeid;
#endif

        if (nodeid != (id++)) {
#ifdef DEBUG
            // Kindof assert
            cout<<"Mismatch read "<<nodeid<<" for line "<<id-1<<endl;
#endif
        }

        iss.clear();

        // Skip ": " characters that disturb reading of children ids
        iss.seekg(2, ios_base::cur);

#ifdef DEBUG
        cout<<" Has children: ";
#endif
        // Read remaining numbers in line
        while((iss>>childid)) {
#ifdef DEBUG
            cout<<childid<<" ";
#endif
            node_children.push_back(nodes[childid]);
            is_root[childid] = false;
        }
#ifdef DEBUG
        cout<<endl;
#endif
        nodes[nodeid]->set_children(node_children);
        node_children.clear();
    }

    // Save root nodes
    for(uint i=0; i<num; ++i)
        if(is_root[i]) {
#ifdef DEBUG
            cout<<"Node "<<i<<" is root"<<endl;
#endif
            roots.push_back(nodes[i]);
        }

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
    if (this->nodes.size() == 0u || this->nodes.size() <= (uint)nid) return NULL;
    return this->nodes[nid];
}

uint Graph::get_num_nodes(void) const {
    return this->nodes.size();
}

ostream& operator <<(ostream& ostr, const Graph& graph) {
#ifndef DEBUG
    ostr<<"Nodes: [ ";
    for (uint i=0; i<graph.nodes.size()-1; ++i) {
        ostr<<*(graph.nodes[i])<<", ";
    }
    ostr<<*(*graph.nodes.end())<<" ]";
    return ostr;
#else
    ostr<<"Nodes:"<<endl;
    for (uint i=0; i<graph.nodes.size(); ++i) {
        ostr<<*(graph.nodes[i])<<": ";
    }
    return ostr;
#endif
}

uint Graph::compute_size(uint d) const {
    uint size = 0u;

    // Graph dependent size
    size += sizeof(nodes);
    size += sizeof(roots);
    size += sizeof(num_nodes);

    // Node dependent size
    size += sizeof(Node)*nodes.size();
    for(uint i=0; i<nodes.size(); ++i) {
        size += sizeof(Node*)*(nodes[i]->get_num_children());
    }

    return size;
}

void Graph::clear(void) {
    for(uint j=0; j<nodes.size(); ++j) {
        delete nodes[j];
    }
    nodes.clear();
    roots.clear();
}

Graph::~Graph() {
    this->clear();
}
