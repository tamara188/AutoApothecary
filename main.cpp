#include <glm/glm.hpp>             // Make sure this is the first include statement
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include <cmath>




class Camera {
public:
    Camera() : position({0.0, 0.0, 10.0}), lookAt({0.0, 0.0, 0.0}), up({0.0, 1.0, 0.0}),
               nearClip(1.0), farClip(100.0), fov(45.0), aspectRatio(1.0) {}

    void apply() const {
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
   void moveForward(float distance) {
        move(distance * forwardVector());
    }

    void moveBackward(float distance) {
        move(distance * backwardVector());
    }

    void moveLeft(float distance) {
        move(distance * leftVector());
    }

    void moveRight(float distance) {
        move(distance * rightVector());
    }

    void moveUp(float distance) {
        move(distance * up);
    }

    void moveDown(float distance) {
        move(distance * -up);
    }

    void rotateYaw(float angle) {
        rotate(angle, up);
    }

    void rotatePitch(float angle) {
        glm::vec3 right = glm::normalize(glm::cross(lookAt - position, up));
        rotate(angle, right);
    }

    // Add other camera movement and adjustment functions here
   void setAspectRatio(int w,int h){
      aspectRatio = static_cast<float>(w) / h;
   }
private:
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;
    float nearClip;
    float farClip;
    float fov;
    float aspectRatio;

    glm::vec3 forwardVector() const {
        return glm::normalize(lookAt - position);
    }

    glm::vec3 backwardVector() const {
        return -forwardVector();
    }

    glm::vec3 leftVector() const {
        return glm::normalize(glm::cross(up, forwardVector()));
    }

    glm::vec3 rightVector() const {
        return -leftVector();
    }

    void move(const glm::vec3& offset) {
        position += offset;
        lookAt += offset;
    }

    void rotate(float angle, const glm::vec3& axis) {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
        glm::vec4 newLookAt = rotationMatrix * glm::vec4(lookAt - position, 1.0f);
        lookAt = position + glm::vec3(newLookAt);
    }
};
// class SurfaceObject(){
//     public:
//     SurfaceObject(){
        
//     }
// }

class Scene {
public:
   Camera camera;
    Scene() {
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


    void draw() {
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


};
class LightSource {
public:
    LightSource() : radius(5.0), speed(0.1) {}

    void updatePosition() {
        // Light movement logic (circular path)
        currentTime += speed;

        GLfloat lightX = radius * cos(currentTime);
        GLfloat lightY = radius * sin(currentTime);
        GLfloat lightZ = 0.0;

        GLfloat lightPosition[] = {lightX, lightY, lightZ, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }

private:
    GLfloat radius;
    GLfloat speed;
    GLfloat currentTime = 0.0;
};

//globals
Scene scene;
LightSource lightSource;
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    scene.camera.setAspectRatio(w,h);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   scene.camera.apply();
    // Draw the scene
    scene.draw();
    // Update the light position
    lightSource.updatePosition();


    glutSwapBuffers();
}

void specialKeyInput(int key, int x, int y) {
    const float moveSpeed = 0.01f;
    const float rotateSpeed = 0.2f;

    switch (key) {
        case GLUT_KEY_UP:
            scene.camera.moveForward(moveSpeed);
            break;
        case GLUT_KEY_DOWN:
            scene.camera.moveBackward(moveSpeed);
            break;
        case GLUT_KEY_LEFT:
            scene.camera.rotateYaw(rotateSpeed);
            break;
        case GLUT_KEY_RIGHT:
            scene.camera.rotateYaw(-rotateSpeed);
            break;
    }

    glutPostRedisplay();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL Scene");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();

    return 0;
}
