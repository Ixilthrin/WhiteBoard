#include "frustum.h"

#include <iostream>
using namespace std;

void Frustum::multiplyBack(const vector<float> &transform, const vector<float> &inverse) {
    this->transform = matrixMult(transform, this->transform);
    this->inverse = matrixMult(this->inverse, inverse);
}

void Frustum::multiplyFront(const vector<float> &transform, const vector<float> &inverse) {
    this->transform = matrixMult(this->transform, transform);
    this->inverse = matrixMult(inverse, this->inverse);
}

void Frustum::rotateY(float angle) {
    totalRotationY += angle;
    multiplyFront(getRotationY(-angle), getRotationY(angle));
}

void Frustum::moveForward(float distance) {
        multiplyBack(getTranslation(distance * sin(totalRotationY), 0, distance * cos(totalRotationY)), getTranslation(-distance * sin(totalRotationY), 0, -distance * cos(totalRotationY)));
}

void Frustum::moveRight(float distance) {
        multiplyBack(getTranslation(-distance * cos(totalRotationY), 0, -distance * sin(-totalRotationY)), getTranslation(distance * cos(totalRotationY), 0, distance * sin(-totalRotationY)));
}
