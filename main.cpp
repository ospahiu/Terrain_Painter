#include <iostream>
#include <GL/freeglut.h>  // GLUT, includes glu.h and
#include <cmath>
#include "main.h"
#include "QuadMesh.h"
#include "VECTOR3D.h"
#include "stdio.h"

using namespace std;

//QuadMesh groundMesh;

void draw_xyz();

// Default Mesh Size
int meshSize = 64;
VECTOR3D mousePos;
vector<Blob> vec;
bool leftMouseClicked = false;
float height = 1.5;
float width = 1.5;

VECTOR3D origin  = VECTOR3D(-16.0f,0.0f,16.0f);
VECTOR3D dir1v   = VECTOR3D(1.0f, 0.0f, 0.0f);
VECTOR3D dir2v   = VECTOR3D(0.0f, 0.0f,-1.0f);
VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
float shininess = 0.2;
float cameraRotate = 0.0;
QuadMesh groundMesh(meshSize, 16.0);


void clearTerrain() {
    vec.clear();
}

void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            clearTerrain();
            break;
        default:
            break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); // Set the window's initial width & height.
    glutInitWindowPosition(WINDOW_SPAWN_X, WINDOW_SPAWN_Y); // Position the window's initial top-left corner.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Assignment 1"); // Create a window with the given title.
    initOpenGl(); // Initialize scene settings.
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);

    glutPassiveMotionFunc(mouse_func);
    glutMouseFunc(onMouseButton);
    // I/O and Animation.
//    glutSpecialFunc(specialInput);
    glutSpecialUpFunc(specialInputUp);
    glutKeyboardFunc(keyPressed);
//    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(0, timer, 0);
    glutMainLoop(); // Enter the infinitely event-processing loop
    return 0;
}

void mouse_func(int x, int y)
{

    mousePos = getOGLPos(x, y);
//    cout<<mousePos.x;
//    cout<<mousePos.y;
//    cout<<mousePos.z<<endl;
    glutPostRedisplay();
}

void specialInputUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (height < 3.0) {
                height += 0.5;
                cout<<"up pressed"<<endl;
            }
            break;
        case GLUT_KEY_DOWN:
            if (height > - 3.0) {
                height -= 0.5;
                cout<<"down pressed"<<endl;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void onMouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        leftMouseClicked = !leftMouseClicked;
        //vec.push_back(Blob(3.0, height, mousePos.x, mousePos.z));
        groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(3.0, height, mousePos.x, mousePos.z));
    }

    glutPostRedisplay();
}

/// Display function constructs all elements in the scene, including the plane,
/// as well as camera. Scene is colourized and scaled in this function.
/// @return void
void display() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color to grey and opaque
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity();
    setupCamera();

    // Set plane material properties
    glColor3d(1.0, 0.627, 0); // Yellow Surface.
    // Set up ground quad mesh

//    groundMesh(meshSize, 16.0);
//    groundMesh.SetMaterial(ambient,diffuse,specular,shininess);
//    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, vec);
    groundMesh.ComputeNormals();
    groundMesh.DrawMesh(meshSize);


    // Misc drawing
    //draw_xyz();
    renderText();

    // Apply transformations to construct submarine
    glFlush();  // Render now
    glutSwapBuffers();
    //delete groundMesh;
}




/// Draw XYZ axis lines.
/// @return void
void draw_xyz() {// Quad mesh
    glPushMatrix();
    // apply rotations
    glRotatef(0, 1.0, 0.0, 0.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glRotatef(0, 0.0, 0.0, 1.0);
    // move the axes to the screen corner
    glTranslatef(0.0, 0.0, 0.0);
    // draw our axes
    glBegin(GL_LINES);
    // draw line for x axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(20.0, 0.0, 0.0);
    // draw line for y axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -20.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    // draw line for Z axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -20.0);
    glVertex3f(0.0, 0.0, 20.0);
    glEnd();
    // load the previous matrix
    glPopMatrix();
}

/// Setup camera attributes.
/// @return void
void setupCamera() {
    gluLookAt(CAMERA_X, CAMERA_Y, CAMERA_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(0.75, 0.75, 0.75);
    glTranslatef(0, -7, -7);
    glRotatef(cameraRotate, 0.0, 1.0, 0.0);
}

/// Function is passed as a callable to resize geometry according to
/// screen width and height. Essentially decoupling all object scale
/// from window canvas.
/// @return void
void reshape(int width, int height) {
    // Prevent divide by zero error if window size is too small.
    if (height == 0)
        height = 1;
    double ratio = 1.0 * width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

/// Renders text overlay as orthographic mapping 'on-top' of the 3D
/// scene. Text Render should occur after scene is drawn.
/// @return void
void renderText() {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(20, 600);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char *> (HELP_MENU_STRING));
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

/// Initialize opengl lighting settings along with projection settings.
/// @return void
void initOpenGl() {// Setup viewport/projection.
    glViewport(0, 0, (GLsizei) CAMERA_X, (GLsizei) CAMERA_Y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.2, 80.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Setup and enable lighting.
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Other OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    // This one is important - renormalize normal vectors
    glEnable(GL_NORMALIZE);

    //Nice perspective.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    groundMesh.SetMaterial(ambient,diffuse,specular,shininess);
    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(0.0,0.0,0.0,0.0));

}

/// Timer function callable used to animate GLUT scene. Variable incrementing
/// occurs in this function to animate scene information. This function
/// parameterizes scene information over time.
/// @param int value
/// @return void
void timer(int value) {

    glutTimerFunc(16, timer, 0);
    cameraRotate+= 0.1;
    if (cameraRotate > 360) {
        cameraRotate = 0.0;
    }
    glutPostRedisplay();
}



VECTOR3D getOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    return VECTOR3D(posX, posY, posZ);
}