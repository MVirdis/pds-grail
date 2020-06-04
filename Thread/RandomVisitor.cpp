#include "Thread.h"
#include "Grail.h"

RandomVisitor::RandomVisitor() {
	this->G = NULL;
}

RandomVisitor& RandomVisitor::set_graph(Graph *G) {
	this->G = G;
	return *this;
}

RandomVisitor& RandomVisitor::set_offset(uint i) {
	this->offset = i;
	return *this;
}

RandomVisitor& RandomVisitor::set_start_node(Node* x) {
	this->x = x;
	return *this;
}

RandomVisitor& RandomVisitor::set_barrier(Barrier *barrier) {
	this->barrier = barrier;
	return *this;
}

RandomVisitor& RandomVisitor::set_visited_set(std::unordered_set<uint> *set) {
	this->visited_set = set;
	return *this;
}

RandomVisitor& RandomVisitor::set_rank(uint *rank) {
	this->rank = rank;
	return *this;
}

RandomVisitor& RandomVisitor::run() {
#if !PARALLEL_VISITS
	this->t = std::thread(start_routine, G, offset, barrier, rank, visited_set);
	this->t.detach();
	return *this;
#endif
}

void RandomVisitor::start_routine(Graph *G, uint offset, Barrier *barrier, uint* rank, std::unordered_set<uint> *visited_set) {
	std::vector<Node*> roots = G->get_roots(true);
		for (int i = 0; i < roots.size(); ++i)
			randomized_visit(roots[i], offset, *G, *rank, *visited_set);
		barrier->wait();
}

