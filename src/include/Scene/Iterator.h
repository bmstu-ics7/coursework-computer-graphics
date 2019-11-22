#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <stdlib.h>
#include <vector>
#include <memory>

class Object;
class Position;

typedef std::vector< std::shared_ptr< Object > >::iterator ObjectIterator;
typedef std::vector< std::shared_ptr< Position > >::iterator PositionIterator;

#endif // __ITERATOR_H
