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
    //     double Ex = -2*dim*Sin(th)*Cos(ph);
    //     double Ey = +2*dim        *Sin(ph);
    //     double Ez = +2*dim*Cos(th)*Cos(ph);
    //   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, aspectRatio, nearClip, farClip);

        glMatrixMode(GL_MODELVIEW);
    }
    
Camera::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Capture the mouse
            isMouseCaptured = true;
            mouseX = x;
            mouseY = y;
        } else if (state == GLUT_UP) {
            // Release the mouse
            isMouseCaptured = false;
        }
    }
}

Camera::motion(int x, int y) {
    if (isMouseCaptured) {
        // Calculate the change in mouse position
        int deltaX = x - mouseX;
        int deltaY = y - mouseY;

        // Update camera orientation or other logic based on mouse movement

        // Keep the mouse at the center of the window
        glutWarpPointer(windowWidth / 2, windowHeight / 2);

        // Update global mouse coordinates
        mouseX = windowWidth / 2;
        mouseY = windowHeight / 2;

        glutPostRedisplay();
    }
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
            glBegin(GL_QUADS);
            //  Front
            glColor3f(1,0,0);
            glNormal3f( 0, 0, 1);
            glVertex3f(-1,-1, 1);
            glVertex3f(+1,-1, 1);
            glVertex3f(+1,+1, 1);
            glVertex3f(-1,+1, 1);
            //  Back
            glColor3f(0,0,1);
            glNormal3f( 0, 0,-1);
            glVertex3f(+1,-1,-1);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,+1,-1);
            glVertex3f(+1,+1,-1);
            //  Right
            glColor3f(1,1,0);
            glNormal3f(+1, 0, 0);
            glVertex3f(+1,-1,+1);
            glVertex3f(+1,-1,-1);
            glVertex3f(+1,+1,-1);
            glVertex3f(+1,+1,+1);
            //  Left
            glColor3f(0,1,0);
            glNormal3f(-1, 0, 0);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,-1,+1);
            glVertex3f(-1,+1,+1);
            glVertex3f(-1,+1,-1);
            //  Top
            glColor3f(0,1,1);
            glNormal3f( 0,+1, 0);
            glVertex3f(-1,+1,+1);
            glVertex3f(+1,+1,+1);
            glVertex3f(+1,+1,-1);
            glVertex3f(-1,+1,-1);
            //  Bottom
            glColor3f(1,0,1);
            glNormal3f( 0,-1, 0);
            glVertex3f(-1,-1,-1);
            glVertex3f(+1,-1,-1);
            glVertex3f(+1,-1,+1);
            glVertex3f(-1,-1,+1);
            //  End
            glEnd();
            break;
        case cylinder:
            //draw cylinder
            //properties height,radius,sides
            topCircle = Primitive.createPolygon(0,properties[0]/2,0,properties[1],properties[2]);
            bottomCircle = Primitive.createPolygon(0,-properties[0]/2,0,properties[1],properties[2]);
            glBegin(GL_TRIANGLE_FAN);
            for(int i = 0; i < sides; i++){
                topCircle[i];
                glNormal3f( 0,properties[0], 0);
            }
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            for(int i = 0; i < sides; i++){
                bottomCircle[i];
                glNormal3f( 0,-properties[0], 0);
            }
            glEnd();
            //TODO normals
            glBegin(GL_QUADS);
            for(int i = 0; i < sides; i++){
                topCircle[i];
                bottomCircle[i];
                if(i+1 = sides){
                    bottomCircle[0];
                    topCircle[0];
                }else{
                    bottomCircle[i+1];
                    topCircle[i+1];
                }
                glNormal3f( 0,-properties[0], 0);
            }
            glEnd();
            break;
        case sphere:
            //draw sphere
            //properties radius steps, sides
            float currHeight = -properties[0];
            float stepHeight = (2 * properties[0])/properties[1];
            //do bottom
            
            currHeight += stepHeight; 
            float crossSectionRadius = sqrt((properties[0]*properties[0])-(currHeight*currHeight))
            bottomCircle = Primitive.createPolygon(0,currHeight,0,crossSectionRadius,properties[2]);
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0,currHeight,0);
            for(int i = 0; i < sides; i++){
                bottomCircle[i];
                //TODO: normals
                glNormal3f( 0,currHeight, 0);
            }
            bottomCircle[0];
            glEnd();
            for(int i = 0; i < steps, i++){

            }
            
            break;
        case roof:
            //draw roof
            //parameters height,width,length
            //bottom

            //east

            //west

            //north
            glBegin(GL_TRIANGLES);
            glVertex3f(-properties[1]/2,-properties[0]/2,-properties[2]/2);
            glVertex3f(properties[1]/2,-properties[0]/2,-properties[2]/2);
            glVertex3f(0,properties[0]/2,-properties[2]/2);
            glEnd();
            //south
            glBegin(GL_TRIANGLES);
            glVertex3f(-properties[1]/2,-properties[0]/2,properties[2]/2);
            glVertex3f(properties[1]/2,-properties[0]/2,properties[2]/2);
            glVertex3f(0,properties[0]/2,properties[2]/2);
            glEnd();
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
Primitive::createPolygon(float Cx, float Cy, float Cz, float radius, float sides){

    glVertex3d points[sides];
    theta = 0;
    for(int i = 0; i < sides; i++){
        switch (theta)
        {
        case theta<=90:
            x = r * Cos(90-theta);
            z = r * Sin(90-theta);
            points[i] = glVertex3d(x,Cy,z);
            break;

        case theta<=180 && theta>90 :
            x = r * Cos(theta-90);
            z = r * Sin(theta - 90);
            points[i] = glVertex3d(x,Cy,z);
            break;
        case theta<=270 && theta>180 :
            x = r * Cos(270-theta);
            z = r * Sin(270-theta);
            points[i] = glVertex3d(x,Cy,z);
            break;
        case theta>270 :
            x = r * Cos(theta-270);
            z = r * Sin(theta-270);
            points[i] = glVertex3d(x,Cy,z);
            break;
        }
        theta += ((2*3.14159)/sides);
    }
    return points;
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
        float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
         //  Cube
   
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
