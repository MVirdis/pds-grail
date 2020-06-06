#include <iostream>
#include <vector>

#include "Node.h"
using namespace std;

int main() {
    Node N(76);
	cout << "My id is: " << N.get_id() << endl;
	vector<Node*> nodes;
	nodes.push_back(&N);
	nodes.push_back(&N);
	N.set_children(nodes);
	nodes.clear();
	nodes = N.get_children();
	for (long unsigned int i = 0; i < nodes.size(); ++i)
		cout << *nodes[i] << endl;
    return 0;
}
