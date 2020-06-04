#define L    100

typedef struct e_s {
  int e_n;
  int v_depth;
  int *e_p;
} n_t;

int make_graph(int num_nodes, int max_num_edges, int num_queries, const char* fname);
void print_graph (n_t *, int, int, int, char *);
void generate_query (int, int, char *);
void seed_ran (void);
int ran (int, int);
