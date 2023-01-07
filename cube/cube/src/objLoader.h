#include <vector>
#include "linmath.h"
#include <string>

struct Vectors {
    vec3 position;
    vec2 texture;
    vec3 normals;
};
void static objLoader(const char* path, std::vector<Vectors>& out_vertices, std::string &matPath, std::vector<int>& faceIndex);
