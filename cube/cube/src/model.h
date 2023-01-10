#ifndef MODEL_H
#define MODEL_H
#include "shader.h"
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "objLoader.h"
#include "materialLoader.h"

class Model {
public:
	std::vector<Vectors> vectices;
	std::vector<Material> materials;
	std::string materialPath;
	std::vector<int> faceIndex;
	Model(const char* objectPathIn, const char* texturePathIn) {
		objLoader(objectPathIn, vectices, materialPath, faceIndex);
		materialLoader(materialPath, materials);
		texturePath = texturePathIn;
		setupModel();
	}
	void Draw(Shader& shader) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vectices.size());
		glBindVertexArray(0);
	}
private:
	GLuint VBO_object, VAO, EBO;
	// texture
	int txWidth, txHeight, nrChannels;
	unsigned int texture;
	const char* texturePath;
	void setupModel() {
		// texture
		unsigned char* texture_data = stbi_load(texturePath, &txWidth, &txHeight, &nrChannels, 0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, txWidth, txHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(texture_data);
		// set vertex buffer object
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO_object);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_object);
		glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(Vectors), &vectices.front(), GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
};
#endif
