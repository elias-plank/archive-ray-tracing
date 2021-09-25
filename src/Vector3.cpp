//
// Created by Elias on 9/24/2021.
//

#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) : e{x, y, z} {

}

double &Vector3::operator[](int i) {

    return e[i];
}

double Vector3::operator[](int i) const {

    return e[i];
}

Vector3 Vector3::operator-() const {

    return { -X(), -Y(), -Z() };
}

Vector3& Vector3::operator+=(const Vector3 &rhs) {

    e[0] += rhs.e[0];
    e[1] += rhs.e[1];
    e[2] += rhs.e[2];
    return *this;
}

Vector3& Vector3::operator*=(double t) {

    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vector3& Vector3::operator/=(double t) {

    return *this *= 1.0 / t;
}

Vector3 Vector3::operator+(const Vector3 &right) const {

    return { X() + right.X(), Y() + right.Y(), Z() + right.Z() };
}

Vector3 Vector3::operator-(const Vector3 &right) const {

    return { X() - right.X(), Y() - right.Y(), Z() - right.Z() };
}

Vector3 Vector3::operator*(const Vector3 &right) const {

    return { X() * right.X(), Y() * right.Y(), Z() * right.Z() };
}

Vector3 Vector3::operator*(double t) const {

    return { X() * t, Y() * t, Z() * t };
}

Vector3 Vector3::operator/(double t) const {

    return { X() / t, Y() / t, Z() / t };
}
