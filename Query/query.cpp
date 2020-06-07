
#include "Query.h"
#include "Types.h"

Query::Query(Interval interval) {
	this->query.first = interval.first;
	this->query.second = interval.second;
	this->result = false;
}

