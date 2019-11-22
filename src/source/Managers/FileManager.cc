#include "Managers/FileManager.h"

std::shared_ptr< Model > FileManager::load(File& loader, ModelBuilder& builder)
{
    return loader.loadModel(builder);
}

void FileManager::save(ObjectIterator begin, ObjectIterator end, File& saver)
{
    ObjectIterator iter = begin;
    for (; iter != end; ++iter) {
        std::shared_ptr< Object > obj = *iter;
        Model model = *(Model*)obj.get();
        saver.saveModel(model);
    }
}
