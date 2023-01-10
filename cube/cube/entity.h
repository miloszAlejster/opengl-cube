#ifndef ENTITY_H
#define ENTITY_H
#include <list>
#include <memory>
#include "src/linmath.h"
class Transform {
protected:
    vec3 pos = { 0.0f, 0.0f, 0.0f };
    vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
    vec3 scale = { 1.0f, 1.0f, 1.0f };
    mat4x4 modelMatrix = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
};
class Entity {
public:
	//Scene graph
	std::list<std::unique_ptr<Entity>> children;
	Entity* parent = nullptr;
};
#endif
