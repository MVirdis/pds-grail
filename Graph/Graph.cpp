#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>

#include "Graph.h"

using namespace std;

Graph::Graph(void) {
    this->num_nodes = 0u;
    this->num_roots = 0u;
}

Graph& Graph::from_file(const char* filepath) {
    ifstream file;
    uint num;
    vector<uint> node_children;

    if (num_nodes > 0) this->clear();

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
    adj_list = new uint*[num];

    this->num_roots = this->num_nodes = num;

    for(uint i=0; i<num; ++i) {
            is_root[i] = true;
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
            node_children.push_back(childid);
            is_root[childid] = false;
            --num_roots;
        }
#ifdef DEBUG
        cout<<endl;
#endif
        adj_list[nodeid] = new uint[node_children.size()+1];
        adj_list[nodeid][0] = node_children.size();
        memcpy(adj_list[nodeid]+1, node_children.data(), node_children.size()*sizeof(uint) );
        node_children.clear();
    }

    // Save root nodes
    roots = new uint[num_roots];
    for(uint i=0, j=0; i<num; ++i)
        if(is_root[i]) {
#ifdef DEBUG
            cout<<"Node "<<i<<" is root"<<endl;
#endif
            roots[j++] = i;
        }

    delete[] is_root;
    file.close();
    return *this;
}

uint* Graph::get_roots(void) const {
    return this->roots;
}

uint Graph::get_num_nodes(void) const {
    return this->num_nodes;
}

uint Graph::get_num_roots(void) const {
    return this->num_roots;
}

ostream& operator <<(ostream& ostr, const Graph& graph) {
#ifndef DEBUG
    // TODO
#else
    // TODO
#endif
    return ostr;
}

uint Graph::compute_size(void) const {
    uint size = 0u;

    size += sizeof(*this) + sizeof(uint*) * this->num_nodes + sizeof(uint)* this->num_roots;
    for(uint i=0; i<this->num_nodes; ++i) {
        size += sizeof(uint) * this->adj_list[i][0];
    }

    return size;
}

void Graph::clear(void) {
    for(uint j=0; j<num_nodes; ++j) {
        delete[] adj_list[j];
    }
    delete[] adj_list;
    delete[] roots;
}

Graph::~Graph() {
    this->clear();
}

uint* Graph::get_children(uint x) const {
    return this->adj_list[x];
}
