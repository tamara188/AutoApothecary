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

class Primitive{
    public:
    //Primitive();
    void addTexture();

    //all primitives - box, cylinder, sphere, roof, cone, roundRoof, wedge, pyramid, halfSphere, polygon, parabloid, torus, tube
    void addBox(float radius, int steps, float length, float width, float height);
    void addCylinder(int sides, float bevel, int segments);
    void addSphere(float radius, int steps, float length, float width, float height);//in tinkercad has only steps? but has implicit w,l,h
    void addRoof();
    void addCone(float topRadius, float baseRadius, float height, int sides);
    void addRoundRoof();
    void addWedge();
    void addPyramid(int sides);
    void addHalfSphere();
    void addPolygon(int sides, float bevel, int segments);
    void addParabloid(int steps);
    void addTorus(float radius, float tube, int sides, int steps);
    void addTube(float radius, float wallThickness, int sides, float bevel, int bevelSegments);
    //create a hole? 
    private:
    GLuint textureID;  // Texture ID
}
//a surface object is a list of primitives
//so is a clutter object now that I think about it. 
class SurfaceObject{
    public:
    SurfaceObject();

    void fillSurfaceArea();
    //this function fills the surface with clutter objects

    void placeInWorld();
    //this functions places the object at some location in the scene

    void addPrim(Primitive obj);
    //this function adds  primitive to the surface object
    //might do this differently?
    //like just using the prims to draw the object in their individual classes?
    private:
    //location in space
    float xPosition = 0;
    float yPosition = 0;
    float zPosition = 0;

    //scale
    float xScale = 1;
    float yScale = 1;
    float zScale = 1;
};
#endif // CLASSES_H