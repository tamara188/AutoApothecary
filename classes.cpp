// classes.cpp
#include "classes.h"


   Camera::Camera() : position({0.0, 0.0, 10.0}), lookAt({0.0, 0.0, 0.0}), up({0.0, 1.0, 0.0}),
               nearClip(1.0), farClip(100.0), fov(45.0), aspectRatio(1.0) {};

    void Camera::apply() const {
        gluLookAt(
            position[0], position[1], position[2],
            lookAt[0], lookAt[1], lookAt[2],
            up[0], up[1], up[2]
        );

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, aspectRatio, nearClip, farClip);

        glMatrixMode(GL_MODELVIEW);
    }
   void Camera::moveForward(float distance) {
        move(distance * forwardVector());
    }

    void Camera::moveBackward(float distance) {
        move(distance * backwardVector());
    }

    void Camera::moveLeft(float distance) {
        move(distance * leftVector());
    }

    void Camera::moveRight(float distance) {
        move(distance * rightVector());
    }

    void Camera::moveUp(float distance) {
        move(distance * up);
    }

    void Camera::moveDown(float distance) {
        move(distance * -up);
    }

    void Camera::rotateYaw(float angle) {
        rotate(angle, up);
    }

    void Camera::rotatePitch(float angle) {
        glm::vec3 right = glm::normalize(glm::cross(lookAt - position, up));
        rotate(angle, right);
    }

    // Add other camera movement and adjustment functions here
   void Camera::setAspectRatio(int w,int h){
      aspectRatio = static_cast<float>(w) / h;
   }

    glm::vec3 Camera::forwardVector() const {
        return glm::normalize(lookAt - position);
    }

    glm::vec3 Camera::backwardVector() const {
        return -forwardVector();
    }

    glm::vec3 Camera::leftVector() const {
        return glm::normalize(glm::cross(up, forwardVector()));
    }

    glm::vec3 Camera::rightVector() const {
        return -leftVector();
    }

    void Camera::move(const glm::vec3& offset) {
        position += offset;
        lookAt += offset;
    }

    void Camera::rotate(float angle, const glm::vec3& axis) {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
        glm::vec4 newLookAt = rotationMatrix * glm::vec4(lookAt - position, 1.0f);
        lookAt = position + glm::vec3(newLookAt);
    }

    Primitive::Primitive(shape shapein,float *prop){
        shapein;
        properties = prop;
    }
    Primitive::setProperties(float *prop){
        properties = prop;
    }
    Primitive::draw(){
        //all primitives - box, cylinder, sphere, roof, cone, roundRoof, wedge, pyramid, halfSphere, polygon, parabloid, torus, tube
        switch(shape){
            case box:
                //draw a box
                break;
            case cylinder:
                //draw cylinder
                break;
            case sphere:
                //draw sphere
                break;
            case roof:
                //draw roof
                break;
            case cone:
                //draw cone
                break;
            case roundRoof:
                //draw half cylinder
                break;
            case wedge:
                //draw wedge
                break;
            case pyramid:
                //draw pyramid
                break;
            case halfSphere:
                //draw half sphere
                break;
            case polygon:
                //draw polygon
                break;
            case parabloid:
                //draw parabloid
                break;
            case torus:
                //draw torus
                break;
            case tube:
                //draw tube
                break;
        }
    }
    SurfaceObject::SurfaceObject(){
        
    }


    Scene::Scene() {
      // Set up lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
      // Set light properties
        GLfloat lightPosition[] = {0.0, 0.0, 1.0, 1.0}; // Light at the center
        GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
        GLfloat diffuseLight[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

        // Set material properties
        GLfloat materialAmbient[] = {0.5, 0.5, 0.5, 1.0};
        GLfloat materialDiffuse[] = {0.8, 0.8, 0.8, 1.0};
        GLfloat materialSpecular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat shininess = 50.0;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

        // Set up the initial camera
        
        camera.setAspectRatio(600,800);
    }


    void Scene::draw() {
        // Draw the room, ceiling, walls, floor, etc.
        // ...
         // Draw the four walls
         glColor3f(1.0, 0.0, 0.0);  // Red
         // Front face
        glBegin(GL_QUADS);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);

        glColor3f(0.0, 1.0, 0.0);  // Green
      //Back face
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        
        glColor3f(0.0, 0.0, 1.0);  // Blue
        // Left face
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        
        glColor3f(0.0, 1.0, 1.0);  // green + blue
        // Right face
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        
        glColor3f(1.0, 0.0, 1.0);  // purple
        // Top face
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        
        glColor3f(0.1, 0.1, 0.1);  // grey
        // Bottom face
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glEnd();
    }

    void LightSource::updatePosition() {
        // Light movement logic (circular path)
        currentTime += speed;

        GLfloat lightX = radius * cos(currentTime);
        GLfloat lightY = radius * sin(currentTime);
        GLfloat lightZ = 0.0;

        GLfloat lightPosition[] = {lightX, lightY, lightZ, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }
