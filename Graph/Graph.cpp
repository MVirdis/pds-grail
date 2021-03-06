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
    this->adj_list = NULL;
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
    bool* is_root;
    try {
        is_root = new bool[num];
    } catch(const bad_alloc& e) {
        cerr<<"Error allocating is_root array"<<endl<<flush;
        this->num_nodes = this->num_roots = 0u;
        return *this;
    }

    // Allocate num empty nodes
    try {
        adj_list = new uint*[num];
    } catch(const bad_alloc& e) {
        cerr<<"Error allocating adj_list array"<<endl<<flush;
        this->num_nodes = this->num_roots = 0u;
        return *this;
    }

    this->num_roots = num;
    this->num_nodes = num;

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
        }
#ifdef DEBUG
        cout<<endl;
#endif
        try {
            adj_list[nodeid] = new uint[node_children.size()+1];
        } catch(const bad_alloc& e) {
            cerr<<"Error allocating adj_list["<<nodeid<<"] array"<<endl<<flush;
            this->num_nodes = this->num_roots = 0u;
            return *this;
        }

        adj_list[nodeid][0] = node_children.size();
        if (node_children.size())
            memcpy(adj_list[nodeid]+1, node_children.data(), node_children.size()*sizeof(uint) );
        node_children.clear();
    }

    // Save root nodes
    for(uint i=0; i<num; ++i) {
        if(is_root[i]) {
#ifdef DEBUG
            cout<<"Node "<<i<<" is root"<<endl;
#endif
            this->roots.push_back(i);
        }
    }

    this->num_roots = this->roots.size();

    delete[] is_root;
    file.close();
    return *this;
}

const uint* Graph::get_roots(void) const {
    return this->roots.data();
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

void Graph::clear(void) {
    for(uint j=0; j<num_nodes; ++j) {
        if (adj_list[j]) {
            delete[] adj_list[j];
            adj_list[j] = NULL;
        }
    }
    if(adj_list) {
        delete[] adj_list;
        adj_list = NULL;
    }
    roots.clear();
    this->num_nodes = 0u;
    this->num_roots = 0u;
}

Graph::~Graph() {
    this->clear();
}

uint* Graph::get_children(uint x) const {
    return this->adj_list[x];
}
