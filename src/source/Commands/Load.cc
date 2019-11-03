#include "Commands/Load.h"

void Load::execute(Scene& facade)
{
    FileManager manager = facade.getFileManager();
    std::shared_ptr< Model > model = manager.load(loader, builder);
    facade.getObjects().add(model);

    std::shared_ptr< Position > pos;
    pos.reset(new Position(model->getPoints()));
    facade.getObjects().addPosition(pos);
}
