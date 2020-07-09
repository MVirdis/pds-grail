# How to compile and execute

All targets in *Makefile* will generate a build folder and generate there the executable.
All make commands have to be issued from inside the project root folder.

Before compiling tune the constant *NUM_QUERY_WORKERS* in *Include/Grail.h* that we found to work best with value 4 on our machine.

Here are reported a few interesting available targets:
* **make** / **make grail**: generates the final program for the project. Multi-thread version of grail, takes .gra file, d, .que files and outputs the 
            query solutions in order.
* **make sequential**: generates the sequential version of grail used when comparing execution times with the parallel version.
                       single-thread version takes .gra file, d, .que file and outputs query solutions.
* **make grail_verbose**: generates the verbose version of the Multi-thread grail. Same usage.
* **make sequential_verbose**: generates the verbose version of the single-thread grail. Same usage.
* **make grail_tester**: generates an interactive program with menu that is able to create/load a graph multiple times, test
                         building times separately of index building and query processing parts, analyzing an index.
                         Very handy when measuring wall-clock performances. See more details on the grail tester below.
* **make gra2que**: simple utility to generate queries from a .gra file. Very basic fast.
* **make generator**: compiles the standalone graph generator available from the start; it was already implemented and given with the project.
* **make clean**: DELETES the build folder permanently.

# Project Structure

Folders:
* **Include**: contains all header files.
* **GRA2QUE**: contains source code of the small utility
* **Grail**: contains source code of the various different mains, depending on which version one compiles (grail tester, sequential, grail)
             and also of the algorithms from the paper such as reachable and randomized labelling.
* **Graph**: Contains source code for the Graph class
* **Index**: index class that contains a label pair for each vertex of the graph
* **Query**: contains source codes for the QueryProcessor class as well as other functions that allow parallel processing of queries
* **Thread**: contains source code both for the Barrier synch object implemented and the RandomVisitor class.

# Grail Performance Tester

Compiled by means of *make grail_tester*.
Started from inside *build/* folder with *./grail_tester* no params.

The following menu appears:
<q>
[GRAIL Performance Tester]
Select one of the following options:
  -1. Quit
   0. Print MENU
   1. Create a Graph
   2. Load a Graph
   3. Build Index with Sequential GRAIL
   4. Build Index with Parallel GRAIL
   5. Process Queries Sequential
   6. Process Queries Parallel
   7. Analyze index diversity

[STATUS]
Empty
</q>

The first 4 options are self-explanatory.

Options 3,4,5,6 ask for the appropriate file path and then do the corresponding action; afterwards some stats are printed.

Option 7 counts the overall number of different label pairs in the whole index. It gives a measure of how effective the random
traversal was in creating different labels.

# Large graphs benchmarks

We used d=5 as done in the grail paper and tried to compare times obtained on our machine with the ones obtained by the grail researchers.

Our machine is an Ubuntu 16.04LTS (64 bit) with 4.9GB RAM and 4 cores running on VirtualBox hosted by Windows 10.

For some large graphs we measured the index building times of the sequential version on our machine in order to estimate the difference in performance
between the machine used in the paper vs our own machine.

**cit-Patents**:
* Index building time from the paper: 61911ms
* Index building time on our machine with sequential implementation: 73532ms (avg on 5 tests)
* On this graph our machine has 100*61911/73532 ~ 84.2% the speed of the researcher's machine
* Index building time on our machine with parallel implementation: 25961ms (avg on 5 tests)
  * Our parallel time is better w.r.t. their performance; even without accounting for the difference in the machine power
* Index building time on our machine with parallel implementation at 84.2%: 21859ms

**uniprot22m**:
* Index building time from the paper: 5192ms
* Index building time on our machine with sequential implementation: 13127ms (avg on 5 tests)
* On this graph our machine has 100*5192/13127 ~ 39.55% the speed of the researcher's machine
* Index building time on our machine with parallel implementation: 4713ms (avg on 5 tests)
  * Our parallel time is better w.r.t. their performance; even without accounting for the difference in the machine power
* Index building time on our machine with parallel implementation at 39.55%: 1863ms

**uniprot100m**:
* Index building time from the paper: 58858ms
* Index building time on our machine with sequential implementation: 136300ms (avg on 5 tests)
* On this graph our machine has 100*58858/136300 ~ 43.18% the speed of the researcher's machine
* Index building time on our machine with parallel implementation: 72441ms (avg on 5 tests)
* Index building time on our machine with parallel implementation at 43.18%: 31280ms
