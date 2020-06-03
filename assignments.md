MV: Mario
AN: Alessandro

-- Misc --
* **main**: MV
* **randomized_labelling**: MV
* **randomized_visit**: MV
* **find_min_rank**: MV
* **reachable**: AN

-- Graph --
* **Graph()**: MV
* **from_file**: MV
* **get_roots**: MV
* **get_num_nodes**: MV
* **operator <<**: MV
* **~Graph()**: MV
* Tests: MV

-- Node --
* **Node(id)**: AN
* **Node(Node&&)**: AN
* **get_id**: AN
* **get_interval**: AN
* **get_children**: AN
* **add_child**: AN
* **add_interval**: AN
* **lock**: MV
* **unlock**: MV
* **operator <<**: AN
* **~Node()**: AN
* Tests: AN

-- Random Visitor --
* **start_routine**: AN
* **RandomVisitor**: AN
* **run**: AN
* **wait**: AN
* **set_graph**: AN
* **set_offset**: AN
* **set_start_node**: AN
* **set_barrier**: AN
* **set_visited_set**: AN
* **set_rank**: AN
* **~RandomVisitor**: AN
* Tests: AN

-- Mutex --
* **Mutex()**: MV
* **lock**: MV
* **unlock**: MV
* **~Mutex()**: MV

-- Barrier --
* **Barrier(count)**: MV
* **wait**: MV
* **~Barrier**: MV
