#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>

#include "Types.h"
#include "Index.h"
#include "Graph.h"

class QueryProcessor {
	Query* queries;
	bool* results;
	uint num_queries;
public:
	/* Constructors */
	QueryProcessor(void);
	QueryProcessor(std::string file_path);

	/* Methods */
	QueryProcessor& from_file(std::string file_path);
	QueryProcessor& solve(Graph& G, Index* indexes, uint d, int menu);
	QueryProcessor& clear(void);
	QueryProcessor& precision_test(void);

	/* Getters */
	uint get_num_queries(void) const;

	~QueryProcessor();
};

#endif
