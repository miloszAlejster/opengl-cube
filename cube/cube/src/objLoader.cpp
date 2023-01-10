#include <vector>
#include "linmath.h"
#include "objLoader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

// for faces in the future
static int count_ascii(std::string s, char c) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) count++;
    }
    return count;
}
static bool isContiguous(std::string s, char c) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            if (++count == 2) return true;
        } else count = 0;
    }
    return false;
}
// _CRT_SECURE_NO_WARNINGS
void objLoader(const char* path, std::vector<Vectors>& out_vecrites, std::string &matPath, std::vector<int>& faceIndex){
    // TODO: add inexes for ebo
    std::vector<std::vector<float>> position;
    std::vector<std::vector<float>> texture;
    std::vector<std::vector<float>> normals;
    std::vector<float> tempPositon;
    std::vector<float> tempTexture;
    std::vector<float> tempNormal;
    int counter = 0;
    // allocate memory in vectors
    tempPositon.push_back(float());
    tempPositon.push_back(float());
    tempPositon.push_back(float());
    tempTexture.push_back(float());
    tempTexture.push_back(float());
    tempNormal.push_back(float());
    tempNormal.push_back(float());
    tempNormal.push_back(float());

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        std::cout << "Failed to open object file: " << path << std::endl;
        return;
    }

    while (1) {
        char lineHeader[256] = {0};
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            break;
        }
        if (strcmp(lineHeader, "v") == 0) {
            if (fscanf(file, "%f %f %f\n", &tempPositon[0], &tempPositon[1], &tempPositon[2])) {
                position.push_back(tempPositon);
            }
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            if (fscanf(file, "%f %f\n", &tempTexture[0], &tempTexture[1])) {
                texture.push_back(tempTexture);
            }
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            if (fscanf(file, "%f %f %f\n", &tempNormal[0], &tempNormal[1], &tempNormal[2])) {
                normals.push_back(tempNormal);
            }
        }
        else if (strcmp(lineHeader, "f") == 0) {
            faceIndex.push_back(counter++);
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            // TODO: change it to other options
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("Error in objects faces\nChange file\n");
                return;
            }
            unsigned int temp[3][3];
            for (int i = 0; i < 3; i++) {
                temp[i][0] = vertexIndex[i];
                temp[i][1] = uvIndex[i];
                temp[i][2] = normalIndex[i];
            }
            for (int j = 0; j < 3; j++) {
                Vectors tempVectors;
                for (int i = 0; i < 3; i++) {
                    tempVectors.position[i] = position[temp[j][0] - 1][i];
                    if (i < 2) tempVectors.texture[i] = texture[temp[j][1] - 1][i];
                    tempVectors.normals[i] = normals[temp[j][2] - 1][i];
                }
                out_vecrites.push_back(tempVectors);
            }
        }
        else if (strcmp(lineHeader, "mtllib") == 0) {
            char tempPath[128] = "";
            if (fscanf(file, "%s", tempPath) != 1) {
                std::cout << "Error in object mtllib\nnChange object file\n" << std::endl;
            }
            else {
                matPath = tempPath;
            }
        }
    }
}
