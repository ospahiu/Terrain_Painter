//
// Created by Olsi on 2016-11-03.
//

#ifndef A2_BLOB_H
#define A2_BLOB_H


class Blob {

public:
    void setX(double x);

    void setZ(double z);

    void setWidth(double width);

    void setHeight(double height);

    double getX();

    double getZ();

    double getWidth();

    double getHeight();

    bool isEmpty();

    Blob(float a, float b, float x, float z);

private:
    float x_pos;
    float z_pos;
    float width;
    float height;

};


#endif //A2_BLOB_H
