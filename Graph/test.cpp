#include <iostream>
#include "Graph.h"
#include "Generator.h"

using namespace std;

int main(int argc, char** argv) {
    Graph G;

    make_graph(10, 5, 2, "test");

    cout<<"Graph.from_file(\"test.gra\"):"<<endl;

    G.from_file("test.gra");

    cout<<endl;
    cout<<"Checking Created Graph:"<<endl;

    cout<<G<<endl;

    return 0;
}
