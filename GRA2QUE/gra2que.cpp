#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Types.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc == 1) return -1;

    cout<<"Loading file";
    ifstream ifile(argv[1]);
    uint num_nodes;

    if(!ifile.is_open()) {
        cerr<<"Error opening file"<<endl;
        return -1;
    }

    ifile>>num_nodes;

    cout<<"The graph has "<<num_nodes<<" nodes"<<endl;
    uint num_query;

    cout<<"How many query? "; (cin>>num_query).get();

    ifile.close();

    if (num_query<=0u) {
        cerr<<"Invalid value "<<num_query<<endl;
        return -1;
    }

    ofstream ofile;
    string name;
    cout<<".que filename: "; (cin>>name).get();

    ofile.open(name);
    if (!ofile.is_open()) {
        cerr<<"Error creating file !"<<endl;
        return -1;
    }

    double rat;
    for(uint i=0u;i<num_query;++i) {
        rat = ((double)rand())/RAND_MAX;
        ofile<<(uint)(rat*(num_nodes-1))<<" ";
        rat = ((double)rand())/RAND_MAX;
        ofile<<(uint)(rat*(num_nodes-1))<<endl;
    }

    return 0;
}
