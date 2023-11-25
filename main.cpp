#include <glm/glm.hpp>             // Make sure this is the first include statement
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include <cmath>
#include "classes.h"





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
