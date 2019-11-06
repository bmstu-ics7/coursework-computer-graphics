#ifndef __SCENE_H
#define __SCENE_H

#include "SceneContainer.h"
#include "Managers/FileManager.h"
#include "Managers/DrawManager.h"
#include "Managers/TransformManager.h"
#include "Managers/DeleteManager.h"
#include "Object/Particle.h"

class Scene
{
public:
    Scene() { }

    SceneContainer& getObjects() { return objects; }
    FileManager& getFileManager() { return fileMan; }
    DrawManager& getDrawManager() { return drawMan; }
    TransformManager& getTransformManager() { return transformMan; }
    DeleteManager& getDeleteManager() { return deleteMan; }

private:
    SceneContainer objects;

    FileManager fileMan;
    DrawManager drawMan;
    TransformManager transformMan;
    DeleteManager deleteMan;
};

#endif // __SCENE_H
