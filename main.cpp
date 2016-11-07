/**
 * @file   main.cpp
 * @Author Olsi Spahiu
 * @date   November, 2016
 * @brief  Assignment 2 source file.
 *
 * Program constructs and interactively manipulates a plane mesh model, by generating
 * terrain. This was done as part of a programming assignment for CPS 511. Geometric
 * transformations, shape modeling, and simple animation are required aspects of
 * this assignment.
 */

#include <iostream>
#include <GL/freeglut.h>  // GLUT, includes glu.h and
#include <cmath>
#include "main.h"
#include "QuadMesh.h"
#include <string>

using namespace std;

float height = 1.5;
int meshSize = 128; // Default Mesh Size
float width = 1.5;
float theta = 0;
float phi = 45;
float zoom = 0.0;
VECTOR3D camera(0.0, 0.0, 0.0);
VECTOR3D mousePos;
QuadMesh groundMesh(meshSize, 16.0);
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

bool isMouseCameraMode = false;

int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); // Set the window's initial width & height.
    glutInitWindowPosition(WINDOW_SPAWN_X, WINDOW_SPAWN_Y); // Position the window's initial top-left corner.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Assignment 2"); // Create a window with the given title.
    initOpenGl(); // Initialize scene settings.
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouse_func);
    glutMouseFunc(onMouseButton);
    glutMotionFunc(mouseMove);
    glutSpecialUpFunc(specialInputUp);
    glutKeyboardFunc(keyPressed);
    glutTimerFunc(0, timer, 0);
    glutMainLoop(); // Enter the infinitely event-processing loop
    return 0;
}

/// Set camera opengl coordinates given the spherical coordinates.
/// Adjusts camera according to given zenith, and azimuth angles,
/// as well as radius from origin.
/// @param double rho Radius from the origin.
/// @param double phi Zenith angle with respect to origin.
/// @param double rho Azimuth angle with respect to origin.
void angleToCartesian(double rho, double phi, double theta) {

    camera.SetX(rho * sin(phi) * cos(theta));
    camera.SetY(rho * cos(phi));
    camera.SetZ(rho * sin(phi) * sin(theta));

}


/// Mouse position event handler. Parameters are the current
/// cartesian positiion of the mouse cursor over the glut window.
void mouse_func(int x, int y) {
    mousePos = getOGLPos(x, y);
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
    groundMesh.ComputeNormals();
    groundMesh.DrawMesh(meshSize);
    // Misc drawing
    renderText();
    glFlush();  // Render now
    glutSwapBuffers();
}

/// Setup camera attributes.
/// @return void
void setupCamera() {
    angleToCartesian(30.00, getRad(phi), getRad(theta));
    gluLookAt(camera.GetX(), camera.GetY(), camera.GetZ(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(0.75 + zoom, 0.75 + zoom, 0.75 + zoom);
}

/// Convert degree angles to radians for computing radian
/// parameters.
/// @param float angle The angle given in degrees.
/// @return float The angle converted to a Rad degree type.
float getRad(float angle) {
    return angle * PI / 180;
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
    const char *const text = isMouseCameraMode ? HELP_MENU_STRING_MOUSE_CAMERA : HELP_MENU_STRING;
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char *> (text));
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

    //First Plane Mesh initialization.
    groundMesh.SetMaterial(ambient, diffuse, specular, shininess);
    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(0, 0, 0, 0));

}

/// Clears terrain of all Blobs. All previously drawn on information
/// is cleared, and original mesh is restored.
/// @return void
void clearTerrain() {
    groundMesh.resetPlane();
    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(0, 0, 0, 0));
}

/// Timer function callable used to animate GLUT scene. Variable incrementing
/// occurs in this function to animate scene information. This function
/// parameterizes scene information over time.
/// @param int value
/// @return void
void timer(int value) {

    glutTimerFunc(16, timer, 0);
    glutPostRedisplay();
}

/// Converts Mouse x, y glut screen position to OpenGL
/// cartesian coordinates.
/// @param int x The x-position of the active mouse cursor.
/// @param int y The y-position of the active mouse cursor.
VECTOR3D getOGLPos(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (float) x;
    winY = (float) viewport[3] - (float) y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    return VECTOR3D(posX, posY, posZ);
}

/// Normal key pressed event handler.
/// @param int key The key pressed.
/// @param int x
/// @param int y
/// @return void
void keyPressed(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w':
            phi -= phi > 5 ? 5 : 0;
            break;
        case 's':
            phi += phi < 90 ? 5 : 0;
            break;
        case 'a':
            theta += 1;
            break;
        case 'd':
            theta -= 1;
            break;
        case 'e':
            zoom += zoom < 1.5 ? 0.05 : 0;
            break;
        case 'q':
            zoom -= zoom > -0.5 ? 0.05 : 0;
            break;
        case 27: // Escape
            clearTerrain();
            break;
        default:
            break;
    }
}

/// Event handlers for mouse button clicks. A blob is deposited
/// with the user chosen parameters on every single left button
/// mouse click.
void onMouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (!isMouseCameraMode) {
            Blob blobToDeposit(width, height, mousePos.x, mousePos.z);
            groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, blobToDeposit);
        } else {
            if (state == GLUT_UP) {
                xOrigin = -1;
                yOrigin = -1;
            } else {// state = GLUT_DOWN
                xOrigin = x;
                yOrigin = y;
            }

        }
    }
    glutPostRedisplay();
}

/// Special key released event handler.
/// @param int key The key pressed.
/// @param int x
/// @param int y
/// @return void
void specialInputUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            height += height < 3.0 ? 0.5 : 0;
            break;
        case GLUT_KEY_DOWN:
            height -= height > -3.0 ? 0.5 : 0;
            break;
        case GLUT_LEFT_BUTTON:
            width -= width > -50.0 ? 10 : 0;
            break;
        case GLUT_RIGHT_BUTTON:
            width += width < 50.0 ? 10 : 0;
            break;
        case GLUT_KEY_F1:
            isMouseCameraMode = !isMouseCameraMode;
        default:
            break;
    }
    glutPostRedisplay();
}

/// Tracks continuous movement of mouse for camera information.
/// Event handler used for updating phi/theta.
/// @param int x Mouse x coordinate.
/// @param int y Mouse y coordinate.
/// @return void
void mouseMove(int x, int y) {

    // True when the left button is pressed.
    if (xOrigin >= 0) {
        // update delta's.
        deltaAngleX = (x - xOrigin) * 0.01f;
        theta += deltaAngleX;
        deltaAngleY = (y - yOrigin) * 0.01f;
        phi += deltaAngleY;
    }
}
