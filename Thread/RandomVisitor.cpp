#include "Thread.h"
#include "Grail.h"

RandomVisitor::RandomVisitor() {
	this->G = NULL;
}

RandomVisitor& RandomVisitor::set_graph(Graph *G) {
	this->G = G;
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

RandomVisitor& RandomVisitor::set_index(Index *index) {
	this->index = index;
	return *this;
}

RandomVisitor& RandomVisitor::run() {
	this->t = std::thread(start_routine, G, barrier, rank, visited_set, index);
	this->t.detach();
	return *this;
}

void RandomVisitor::start_routine(Graph *G, Barrier *barrier, uint* rank, std::unordered_set<uint> *visited_set, Index *index) {
	uint* roots = G->get_roots();
	for (uint i = 0; i < G->get_num_roots(); ++i)
		randomized_visit(roots[i], *G, *rank, *visited_set, *index);
	barrier->wait();
}

