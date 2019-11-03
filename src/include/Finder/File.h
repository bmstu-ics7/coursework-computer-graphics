#ifndef __FILE_H
#define __FILE_H

#include <fstream>

#include "Object/Builder.h"
#include "Managers/ExceptionManager.h"

class File
{
public:
    File(const char* name) : fileName(name) { }
    std::shared_ptr< Model > loadModel(ModelBuilder& builder);
    void saveModel(const Model& model);

private:
    void openSave();
    void openLoad();
    void close();

    const char* fileName;
    std::ifstream in;
    std::ofstream out;
};

#endif // __FILE_H
