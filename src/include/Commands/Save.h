#ifndef __SAVE_H
#define __SAVE_H

#include "Command.h"

class Save : Command
{
public:
    Save(ObjectIterator begin,
         File& file)
        : Command(begin), saver(file) { }

    Save(ObjectIterator begin, ObjectIterator end,
         File& file)
        : Command(begin, end), saver(file) { }

    void execute(Scene& facade) override;

private:
    File& saver;
};

#endif // __SAVE_H
