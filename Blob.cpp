/**
 * @file   Blob.cpp
 * @Author Olsi Spahiu
 * @date   November, 2016
 * @brief  Assignment 2 source file.
 *
 * Program constructs and interactively manipulates a plane mesh model, by generating
 * terrain. This was done as part of a programming assignment for CPS 511. Geometric
 * transformations, shape modeling, and simple animation are required aspects of
 * this assignment.
 */

#include "Blob.h"


Blob::Blob(float a, float b, float x, float z) :  width(a), height(b), x_pos(x), z_pos(z)
    {}

void Blob::setHeight(double height) { this->height = height; }

void Blob::setWidth(double width) { this->width = width; }

void Blob::setX(double x) { this->x_pos = x; }

void Blob::setZ(double z) { this->z_pos = z; }

double Blob::getHeight() { return this->height; }

double Blob::getWidth() { return this->width; }

double Blob::getX() { return this->x_pos; }

double Blob::getZ() { return this->z_pos;}

bool Blob::isEmpty() {
    return this->height + this->width + this->x_pos + this->z_pos == 0;
}