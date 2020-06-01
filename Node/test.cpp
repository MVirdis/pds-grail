#include <iostream>

#include "Node.h"
using namespace std;


int main() {

Interval i(5,9);
Interval in;
vector<Node*> node;
Node child (4);

Node N (56);
cout << "id: " << N.get_id() << endl;
N.add_interval(i, 5);
in = N.get_interval(5);
cout << "added interval: " << in.first << "," << in.second << endl;
node = N.get_children();
cout << "size should be 0 --> is: " << node.size() << endl;
N.add_child(&child);
node = N.get_children();
cout << "size should be 1 --> is: " << node.size() << endl;

cout << "complete node: " << endl << N << endl;
return 0;
}
