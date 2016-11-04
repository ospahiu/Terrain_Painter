//
// Created by Olsi on 2016-11-03.
//

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