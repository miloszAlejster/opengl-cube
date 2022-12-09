#include <vector>
#include "linmath.h"
#include <string>

int count_ascii(std::string s, char c) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) count++;
    }
    return count;
}
bool isContiguous(std::string s, char c) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            if (++count == 2) return true;
        } else count = 0;
    }
    return false;
}
// _CRT_SECURE_NO_WARNINGS
bool loader(const char* path,
    std::vector < std::vector<float> >& out_vertices,
    std::vector < std::vector<float> >& out_uvs,
    std::vector < std::vector<float> >& out_normals) {

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< std::vector<float> > temp_vertices;
    std::vector< std::vector<float> > temp_uvs;
    std::vector< std::vector<float> > temp_normals;
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }
    while (1) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        if (strcmp(lineHeader, "v") == 0) {
            std::vector<float> vertex;
            fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            std::vector<float> uv;
            fscanf(file, "%f %f\n", &uv[0], &uv[1]);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            std::vector<float> normal;
            fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f")) {
            std::string vertex1, vertex2, vertex3;
            // number of vertexes
            int n = count_ascii(lineHeader, ' ');
            // number of slashes
            int slash = count_ascii(lineHeader, '/');
            // are slahses next to each other
            bool twiceSlash = isContiguous(lineHeader, '/');
            // allocate arrays
            unsigned int* vertexIndex, * uvIndex, * normalIndex;
            vertexIndex = new unsigned int[n];  uvIndex = new unsigned int[n]; normalIndex = new unsigned int[n];
            // delete pointers
            delete[] vertexIndex; delete[] uvIndex; delete[] normalIndex;
            // get data
            if (slash == 0) {
                // Face
                if (n == 3) {
                    fscanf(file, "%d %d %d\n",
                        &vertexIndex[0],
                        &vertexIndex[1],
                        &vertexIndex[2]);
                }
                else if (n == 4) {
                    fscanf(file, "%d %d %d %d\n",
                        &vertexIndex[0],
                        &vertexIndex[1],
                        &vertexIndex[2],
                        &vertexIndex[3]);
                }
                else {
                    printf("error in obj file");
                    return false;
                }
            }
            else if (slash > 0) {
                if (slash == 2 * n) {
                    if (twiceSlash == true) {
                        // Face with norms
                        if (n == 3) {
                            fscanf(file, "%d//%d %d//%d %d//%d\n",
                                &vertexIndex[0], &normalIndex[0],
                                &vertexIndex[1], &normalIndex[1],
                                &vertexIndex[2], &normalIndex[2]);
                        }
                        else if (n == 4) {
                            fscanf(file, "%d//%d %d//%d %d//%d %d//%d\n",
                                &vertexIndex[0], &normalIndex[0],
                                &vertexIndex[1], &normalIndex[1],
                                &vertexIndex[2], &normalIndex[2],
                                &vertexIndex[3], &normalIndex[3]);
                        }
                        else {
                            printf("error in obj file");
                            return false;
                        }
                    }
                    else if (twiceSlash == false) {
                        // Face with txt and norms
                        if (n == 3) {
                            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                        }
                        else if (n == 4) {
                            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                                &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
                        }
                        else {
                            printf("error in obj file");
                            return false;
                        }
                    }
                }
                else if (slash == n) {
                    // Face with txt
                    if (n == 3) {
                        fscanf(file, "%d/%d %d/%d %d/%d\n",
                            &vertexIndex[0], &uvIndex[0],
                            &vertexIndex[1], &uvIndex[1],
                            &vertexIndex[2], &uvIndex[2]);
                    }
                    else if (n == 4) {
                        fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n",
                            &vertexIndex[0], &uvIndex[0],
                            &vertexIndex[1], &uvIndex[1],
                            &vertexIndex[2], &uvIndex[2],
                            &vertexIndex[3], &uvIndex[3]);
                    }
                    else {
                        printf("error in obj file");
                        return false;
                    }
                }
            }
            // pass data
            for (int i = 0; i < n; i++) {
                vertexIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalIndices.push_back(normalIndex[i]);
            }
        }
    }
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        std::vector<float> vertex = temp_vertices[vertexIndex - 1];
        out_vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int uvIndex = uvIndices[i];
        std::vector<float> uv = temp_uvs[uvIndex - 1];
        out_uvs.push_back(uv);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int normalIndex = normalIndices[i];
        std::vector<float> normal = temp_normals[normalIndex - 1];
        out_normals.push_back(normal);
    }
    return true;
}
