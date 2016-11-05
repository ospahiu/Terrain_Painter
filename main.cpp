#include <iostream>
#include <GL/freeglut.h>  // GLUT, includes glu.h and
#include <cmath>
#include "main.h"
#include "QuadMesh.h"
#include "VECTOR3D.h"
#include "stdio.h"

using namespace std;

//QuadMesh groundMesh;

float CAMERA_X_COORD = 0.0;
float CAMERA_Y_COORD = 0.0;
float CAMERA_Z_COORD = 0.0;
VECTOR3D camera;
void draw_xyz();

// Default Mesh Size
int meshSize = 64;
VECTOR3D mousePos;
float height = 1.5;
float width = 1.5;
float theta = 0;
float phi = 45;
float zoom = 0.0;


QuadMesh groundMesh(meshSize, 16.0);

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

void angleToCartesian(double rho, double phi, double theta) {

    CAMERA_X_COORD = rho * sin(phi) * cos(theta);
    CAMERA_Y_COORD = rho * cos(phi);
    CAMERA_Z_COORD = rho * sin(phi) * sin(theta);

}

/// Mouse position event handler. Parameters are the current
/// cartesian positiion of the mouse cursor over the glut window.
void mouse_func(int x, int y)
{

    mousePos = getOGLPos(x, y);
//    cout<<mousePos.x;
//    cout<<mousePos.y;
//    cout<<mousePos.z<<endl;
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
    cout<<zoom<<endl;
    // Misc drawing
    //draw_xyz();
    renderText();
    glFlush();  // Render now
    glutSwapBuffers();
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
    //double phi = 90* PI / 180;
    //theta = 0* PI / 180;
    angleToCartesian(30.00, getRad(phi), getRad(theta));
    gluLookAt(CAMERA_X_COORD, CAMERA_Y_COORD, CAMERA_Z_COORD, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(0.75+zoom, 0.75+zoom, 0.75+zoom);
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

    //First Plane Mesh initialization.
    groundMesh.SetMaterial(ambient,diffuse,specular,shininess);
    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(0,0,0,0));

}

/// Clears terrain of all Blobs. All previously drawn on information
/// is cleared, and original mesh is restored.
/// @return void
void clearTerrain() {
    groundMesh.resetPlane();
    groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, Blob(0,0,0,0));
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

/// Normal key pressed event handler.
/// @param int key The key pressed.
/// @param int x
/// @param int y
/// @return void
void keyPressed(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w':
            if (phi > 5) {
                phi -= 5;
            }
            break;
        case 's':
            if (phi < 90) {
                phi+=5;
            }
            break;
        case 'a':
            theta+=1;
            break;
        case 'd':
            theta-=1;
            break;
        case 'e':
            if (zoom < 1.5) {
                zoom += 0.05;
            }
            break;
        case 'q':
            if (zoom > -0.5) {
                zoom -= 0.05;
            }
            break;
        case 27:
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
        Blob blobToDeposit(width, height, mousePos.x, mousePos.z);
        groundMesh.InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v, blobToDeposit);
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
        case GLUT_LEFT_BUTTON:
            if (width > - 12.0) {
                width -= 3;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (width < 12.0) {
                width += 3;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
