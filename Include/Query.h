#ifndef _QUERY_H_
#define _QUERY_H_

#include "Types.h"

class Query {
	Interval query;
	bool result;
public:
	Query(Interval interval);
	Query& read_query(const char *path);
};


#endif
