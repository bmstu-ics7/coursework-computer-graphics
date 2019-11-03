#ifndef __FILEMANAGER_H
#define __FILEMANAGER_H

#include "Manager.h"

class FileManager : public Manager
{
public:
    FileManager() { }

    std::shared_ptr< Model > load(File& loader, ModelBuilder& builder);
    void save(ObjectIterator begin, ObjectIterator end, File& saver);
};

#endif // __FILEMANAGER_H
