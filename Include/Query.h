#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <vector>

#include "Types.h"
#include "Index.h"
#include "Graph.h"

class QueryProcessor {
	std::vector<Query> queries;
	bool* results;
	uint num_queries;
	uint after_select;
public:
	/* Constructors */
	QueryProcessor(void);

	/* Methods */
	QueryProcessor& from_file(std::string file_path, Index *indexes, uint d);
	QueryProcessor&	select_queries(uint u, uint v, Index *indexes, uint d, bool& res);
	QueryProcessor& solve(Graph& G, Index* indexes, uint d, int menu);
	QueryProcessor& clear(void);
	QueryProcessor& precision_test(Graph& G, Index *indexes, uint d);

	~QueryProcessor();
};

#endif
