#include <iostream>
#include "Graph.h"

int main(int argc, char** argv) {
    Graph G;

    G.from_file(argv[1]);

    return 0;
}
