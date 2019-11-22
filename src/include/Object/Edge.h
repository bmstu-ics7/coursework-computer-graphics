#ifndef __EDGE_H
#define __EDGE_H

#include <stdlib.h>

class Edge
{
public:
    Edge() : Edge(0, 0) { }
    Edge(size_t start, size_t finish) : start(start), finish(finish) { }
    size_t getStart() { return start; }
    size_t getFinish() { return finish; }

private:
    size_t start;
    size_t finish;
};

#endif // __EDGE_H
