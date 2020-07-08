# How to compile and execute

All targets in *Makefile* will generate a build folder and generate there the executable.
All make commands have to be issued from inside the project root folder.

Here are reported a few interesting available targets:
* **make** / **make grail**: generates the final program for the project. Multi-thread version of grail, takes .gra file, d, .que files and outputs the 
            query solutions in order.
* **make sequential**: generates the sequential version of grail used when comparing execution times on the machine.
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
* **Index**: index class
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

Options 3,4,5,6 ask for the appropriate file path and then do the corresping action; afterwards some stats are printed.

Option 7 counts the overall number of different label pairs in the whole index. It gives a measure of how effective the random
traversal was in creating different labels.
