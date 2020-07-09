#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <vector>

#include "Types.h"
#include "Index.h"
#include "Graph.h"

class QueryProcessor {
	std::vector<Query> queries;

public:

	/* Methods */
	QueryProcessor& from_file(std::string file_path, Index *indexes, uint d);
	QueryProcessor& solve(Graph& G, Index* indexes, uint d, int menu, bool output=true);
	void clear(void);

	uint get_num_queries(void) const;

	//~QueryProcessor();
};

#endif
