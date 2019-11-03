#ifndef __LOAD_H
#define __LOAD_H

#include "Command.h"

class Load : Command
{
public:
    Load(File& loader, ModelBuilder& builder)
         : loader(loader), builder(builder) { }

    void execute(Scene& facade) override;

private:
    File& loader;
    ModelBuilder& builder;
};

#endif // __LOAD_H
