#ifndef _INDEX_H_
#define _INDEX_H_

#include "Types.h"

class Index {
    Interval* labels;
    uint num_nodes;
  public:
    /* Constructors */
    Index();

    /* Methods */
    Index& set_interval(Interval& label, uint node_id);
    Index& set_size(uint size);

    /* Getters */
    uint get_size(void) const;
    Interval get_interval(uint node_id) const;

    ~Index();
};

#endif
