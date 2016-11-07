//
// Created by Olsi on 2016-11-02.
//

#include "VECTOR3D.h"

#ifndef A2_MAIN_H
#define A2_MAIN_H
#define PI 3.14159265

VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
float shininess = 0.2;


const GLfloat light_position0[] = {6.0, 12.0, 0.0, 1.0};

const GLfloat light_position1[] = {6.0, 12.0, 0.0, 1.0};

static const double CAMERA_Y = 15.0;

static const double CAMERA_X = 0.0;

static const int SCREEN_WIDTH = 1120;

static const int SCREEN_HEIGHT = 630;

static const int WINDOW_SPAWN_Y = 10;

static const int WINDOW_SPAWN_X = 10;

const char *const HELP_MENU_STRING = "Blob Editor:\n"
        "Paint Terrain - Left Mouse Button\n"
        "Blob Height Increase - Up Arrow Key\n"
        "Blob Height Decrease - Down Arrow Key\n"
        "Blob Width Increase - Right Arrow Key\n"
        "Blob Width Decrease - Left Arrow Key\n"
        "Zoom In - E\n"
        "Zoom Out - Q\n"
        "Elevate Up- W\n"
        "Elevate Down- S\n"
        "Pan Left - A\n"
        "Pan Right - D\n"
        "Turn Viewer Mode On - F1\n"
        "Clear Terrain - Esc\n";

const char *const HELP_MENU_STRING_MOUSE_CAMERA = "Blob Viewer:\n"
        "Move Camera - Hold Left Mouse Button\n"
        "Zoom In - E\n"
        "Zoom Out - Q\n"
        "Elevate Up - W\n"
        "Elevate Down - S\n"
        "Pan Left - A\n"
        "Pan Right - D\n"
        "Turn Editor On - F1\n"
        "Clear Terrain - Esc";

void setupCamera();

float getRad(float angle);

void renderText();

void initOpenGl();

void display();

void clearTerrain();

void mouseMove(int x, int y);

void mouse_func(int x, int y);

void onMouseButton(int button, int state, int x, int y);

void specialInputUp(int key, int x, int y);

VECTOR3D getOGLPos(int x, int y);

void reshape(int width, int height);

void timer(int value);

void keyPressed(unsigned char key, int x, int y);

void angleToCartesian(double rho, double phi, double theta);

#endif //A2_MAIN_H
