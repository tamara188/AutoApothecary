// classes.h
#ifndef CLASSES_H
#define CLASSES_H
#include <glm/glm.hpp>             // Make sure this is the first include statement
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include <cmath>
class Camera {
public:
    Camera();
    void apply() const;
    void moveForward(float distance);

    void moveBackward(float distance);

    void moveLeft(float distance);

    void moveRight(float distance);

    void moveUp(float distance);

    void moveDown(float distance);

    void rotateYaw(float angle);

    void rotatePitch(float angle);

    void setAspectRatio(int w,int h);
private:
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;
    float nearClip;
    float farClip;
    float fov;
    float aspectRatio;

    glm::vec3 forwardVector() const;

    glm::vec3 backwardVector() const;

    glm::vec3 leftVector() const;

    glm::vec3 rightVector() const;

    void move(const glm::vec3& offset);

    void rotate(float angle, const glm::vec3& axis);
};
class SurfaceObject{
    public:
    SurfaceObject();
};

class Scene {
public:
   Camera camera;
    Scene();


    void draw();
};
class LightSource {
public:
    LightSource() : radius(5.0), speed(0.1) {};

    void updatePosition();

private:
    GLfloat radius;
    GLfloat speed;
    GLfloat currentTime = 0.0;
};
#endif // CLASSES_H