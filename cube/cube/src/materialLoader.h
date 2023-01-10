#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H 
#include "linmath.h"
#include <vector>
#include <string>

struct Material {
    char name[128];
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
void materialLoader(std::string path, std::vector<Material>& materials);
#endif // !MATERIALLOADER_H
