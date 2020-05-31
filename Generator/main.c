#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Generator.h"

int main(int argc, char *argv[]) {
  int i;
  if (argc != 5) {
    fprintf (stderr, "Run as: %s p1 p2 p3 p4\n", argv[0]);
    fprintf (stderr, "Where : p1 = number of vertex\n");
    fprintf (stderr, "        p2 = max number of edges\n");
    fprintf (stderr, "        p3 = number of queries\n" );
    fprintf (stderr, "        p4 = output file with no extension\n" );
    fprintf (stderr, "             generate graph file (.gra) and query file (.que)\n" );
    exit (1);
  }

  for (i=0; i<argc; i++) {
    printf ("%s ", argv[i]);
  }
  printf ("\n");

  seed_ran ();

  make_graph(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4]);

  return 0;
}
