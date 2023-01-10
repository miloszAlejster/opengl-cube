#ifndef ENTITY_H
#define ENTITY_H
#include <list>
#include <memory>
#include "linmath.h"
#include "model.h"
float toRadians(float degree) {
    float pi = (float)3.14159265359;
    return (degree * (pi / 180.0f));
}
struct mat4 {
    mat4x4 mat;
};
class Transform {
protected:
    vec3 pos = { 0.0f, 0.0f, 0.0f };
    vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
    vec3 scale = { 1.0f, 1.0f, 1.0f };
    mat4 modelMatrix;
    mat4 getLocalModelMatrix() {
        mat4x4 mat;
        mat4x4_identity(mat);
        mat4x4 transformX;
        mat4x4 transformY;
        mat4x4 transformZ;
        mat4x4_rotate(transformX, mat, 1.0f, 0.0f, 0.0f, toRadians(eulerRot[0]));
        mat4x4_rotate(transformY, mat, 0.0f, 1.0f, 0.0f, toRadians(eulerRot[1]));
        mat4x4_rotate(transformZ, mat, 0.0f, 0.0f, 1.0f, toRadians(eulerRot[2]));
        mat4x4 rotationMatrix;
        mat4x4_mul(rotationMatrix, transformZ, transformY);
        mat4x4_mul(rotationMatrix, rotationMatrix, transformX);
        mat4x4 translationMatrix;
        mat4x4_identity(translationMatrix);
        mat4x4_translate(translationMatrix, pos[0], pos[1], pos[2]);
        mat4x4 scaleMatrix;
        mat4x4_scale_aniso(scaleMatrix, scaleMatrix, scale[0], scale[1], scale[2]);
        mat4x4_mul(rotationMatrix, scaleMatrix, rotationMatrix);
        mat4x4_mul(translationMatrix, rotationMatrix, translationMatrix);
        mat4 translationMatrixOut;
        translationMatrixOut.mat[0][0] = translationMatrix[0][0];
        translationMatrixOut.mat[0][1] = translationMatrix[0][1];
        translationMatrixOut.mat[0][2] = translationMatrix[0][2];
        translationMatrixOut.mat[0][3] = translationMatrix[0][3];

        translationMatrixOut.mat[1][0] = translationMatrix[1][0];
        translationMatrixOut.mat[1][1] = translationMatrix[1][1];
        translationMatrixOut.mat[1][2] = translationMatrix[1][2];
        translationMatrixOut.mat[1][3] = translationMatrix[1][3];

        translationMatrixOut.mat[2][0] = translationMatrix[2][0];
        translationMatrixOut.mat[2][1] = translationMatrix[2][1];
        translationMatrixOut.mat[2][2] = translationMatrix[2][2];
        translationMatrixOut.mat[2][3] = translationMatrix[2][3];

        translationMatrixOut.mat[3][0] = translationMatrix[3][0];
        translationMatrixOut.mat[3][1] = translationMatrix[3][1];
        translationMatrixOut.mat[3][2] = translationMatrix[3][2];
        translationMatrixOut.mat[3][3] = translationMatrix[3][3];
        return translationMatrixOut;
    }
public:
    void computeModelMatrix() {
        modelMatrix = getLocalModelMatrix();
    }
    void computeModelMatrix(mat4 parentModelMatrix) {
        mat4x4_mul(modelMatrix.mat, parentModelMatrix.mat, getLocalModelMatrix().mat);
    }
    mat4 getModelMatrix() {
        return modelMatrix;
    }
    float getLocalRotation(int choice) {
        if (choice < 3 && choice >= 0) {
            return eulerRot[choice];
        }else {
            return 0.0f;
        }
    }
    void setLocalPosition(vec3 newPosition) {
        pos[0] = newPosition[0];
        pos[1] = newPosition[1];
        pos[2] = newPosition[2];
    }
    void setLocalScale(vec3 newScale) {
        scale[0] = newScale[0];
        scale[1] = newScale[1];
        scale[2] = newScale[2];
    }
    void setLocalRotation(vec3 newRotation) {
        eulerRot[0] = newRotation[0];
        eulerRot[1] = newRotation[1];
        eulerRot[2] = newRotation[2];
    }
};
class Entity {
public:
	//Scene graph
	std::list<std::unique_ptr<Entity>> children;
	Entity* parent = nullptr;
    Transform transform;
    Model* model = nullptr;

    Entity(Model& inModel) : model{ &inModel } {

    }
    template<typename... TArgs>
    void addChild(TArgs&... args){
        children.emplace_back(std::make_unique<Entity>(args...));
        children.back()->parent = this;
    }
    void updateSelfAndChild(){
        forceUpdateSelfAndChild();
    }
    void forceUpdateSelfAndChild(){
        if (parent){
            transform.computeModelMatrix(parent->transform.getModelMatrix());
        }else{
            transform.computeModelMatrix();
        }
        for (auto&& child : children){
            child->forceUpdateSelfAndChild();
        }
    }
    void drawSelfAndChild(Shader& ourShader){
        ourShader.setMat4("model", transform.getModelMatrix().mat);
        model->Draw(ourShader);
        for (auto&& child : children){
            child->drawSelfAndChild(ourShader);
        }
    }
};
#endif
