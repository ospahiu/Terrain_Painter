//
// Created by Olsi on 2016-11-02.
//

#include "VECTOR3D.h"

#ifndef A2_MAIN_H
#define A2_MAIN_H

const GLfloat light_position0[] = {6.0, 12.0, 0.0, 1.0};

const GLfloat light_position1[] = {6.0, 12.0, 0.0, 1.0};

const GLfloat mat_ambient[] = {0.4, 0.2, 0.0, 1.0};

const GLfloat mat_specular[] = {0.1, 0.1, 0.0, 1.0};

const GLfloat mat_diffuse[] = {0.9, 0.5, 0.0, 1.0};

const GLfloat mat_shininess[] = {0.0};

static const double CAMERA_Y = 15.0;

static const double CAMERA_Z = 22.0;

static const double CAMERA_X = 0.0;

static const int SCREEN_WIDTH = 1120;

static const int SCREEN_HEIGHT = 630;

static const int WINDOW_SPAWN_Y = 10;

static const int WINDOW_SPAWN_X = 10;



void setupCamera();

void renderText();

void initOpenGl();

void display();

void mouse_func(int x, int y);

void onMouseButton(int button, int state, int x, int y);

void specialInputUp(int key, int x, int y);

VECTOR3D getOGLPos(int x, int y);

void reshape(int width, int height);

void timer(int value);

#endif //A2_MAIN_H
