#include <vector>
#include "linmath.h"
#include "materialLoader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

static void materialLoader(std::string path, std::vector<Material>& materials) {
    Material temp_material;
    std::string prePath = "./resources/";
    path = prePath + path;
    FILE* file = fopen(path.c_str(), "r");
    bool isFirst = true;
    if (file == NULL) {
        std::cout << "Failed to open material file: \n" << path << std::endl;
        return;
    }
    while (1) {
        char lineHeader[128] = {0};
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            // last material
            materials.push_back(temp_material);
            break;
        }
        if (strcmp(lineHeader, "newmtl") == 0) {
            if (fscanf(file, "%s", &temp_material.name) != 1) {
                std::cout << "Error in material newmtl\nnChange material file\n" << std::endl;
            }
            else {
                if (isFirst == true) {
                    isFirst = false;
                }
                else if (isFirst == false) {
                    materials.push_back(temp_material);
                }
            }
        }
        else if (strcmp(lineHeader, "Ka") == 0) {
            if (fscanf(file, "%f %f %f\n", &temp_material.ambient[0], &temp_material.ambient[1],
                &temp_material.ambient[2]) != 3) {
                std::cout << "Error in material Ka\nnChange material file\n" << std::endl;
;            }
        }
        else if (strcmp(lineHeader, "Kd") == 0) {
            if (fscanf(file, "%f %f %f\n", &temp_material.diffuse[0], &temp_material.diffuse[1],
                &temp_material.diffuse[2]) != 3) {
                std::cout << "Error in material Kd\nChange material file\n" << std::endl;
            }
        }
        else if (strcmp(lineHeader, "Ks") == 0) {
            if (fscanf(file, "%f %f %f\n", &temp_material.specular[0], &temp_material.specular[1],
                &temp_material.specular[2]) != 3) {
                std::cout << "Error in material Ks\nnChange material file\n" << std::endl;
            }
        }
        else if (strcmp(lineHeader, "Ns") == 0) {
            if (fscanf(file, "%f\n", &temp_material.shininess) != 1) {
                std::cout << "Error in material Ns\nChange material file\n" << std::endl;
            }
        }
    }
}