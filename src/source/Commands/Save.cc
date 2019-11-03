#include "Commands/Save.h"

void Save::execute(Scene& facade)
{
    FileManager manager = facade.getFileManager();
    manager.save(begin, end, saver);
}
