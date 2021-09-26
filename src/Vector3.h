//
// Created by Elias on 9/24/2021.
//

#ifndef RAYTRACING_VECTOR3_H
#define RAYTRACING_VECTOR3_H

#include "Common.h"
#include <cmath>

class Vector3 {

private:
    double e[3];

public:
    Vector3() = default;
    Vector3(double x, double y, double z);

    [[nodiscard]] inline double X() const { return e[0]; }
    [[nodiscard]] inline double Y() const { return e[1]; }
    [[nodiscard]] inline double Z() const { return e[2]; }

    [[nodiscard]] Vector3 operator - () const;
    [[nodiscard]] double operator[](int i) const;
    [[nodiscard]] double& operator[](int i);

    [[nodiscard]] Vector3 operator + (const Vector3& right) const;
    [[nodiscard]] Vector3 operator - (const Vector3& right) const;
    [[nodiscard]] Vector3 operator * (const Vector3& right) const;
    [[nodiscard]] Vector3 operator * (double t) const;
    [[nodiscard]] Vector3 operator / (double t) const;
    Vector3& operator += (const Vector3& rhs);
    Vector3& operator *= (double t);
    Vector3& operator /= (double t);

    [[nodiscard]] inline bool NearZero() const { const auto s = 1e-8; return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s); }
    [[nodiscard]] inline Vector3 Unit() const { return *this / this->Length(); }
    [[nodiscard]] inline double Length() const { return std::sqrt(Length2()); }
    [[nodiscard]] inline double Length2() const { return (X() * X() + Y() * Y() + Z() * Z()); }
    [[nodiscard]] inline static Vector3 Reflect(const Vector3& vector, const Vector3& normal) { return vector - normal * Dot(vector, normal) * 2; };
    [[nodiscard]] inline static double Dot(const Vector3& left, const Vector3& right) { return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z(); }
    [[nodiscard]] inline static Vector3 Cross(const Vector3& left, const Vector3& right) { return { left.e[1] * right.e[2] - left.e[2] * right.e[1], left.e[2] * right.e[0] - left.e[0] * right.e[2], left.e[0] * right.e[1] - left.e[1] * right.e[0] }; }

    [[nodiscard]] inline static Vector3 Random() { return { RandomDouble(), RandomDouble(), RandomDouble()}; }
    [[nodiscard]] inline static Vector3 Random(double min, double max) { return { RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max) }; }
    [[nodiscard]] inline static Vector3 RandomInUnitSphere() { while(true) { auto p = Vector3::Random(-1, 1); if(p.Length2() >= 1) continue; return p; }}
    [[nodiscard]] inline static Vector3 RandomUnit() { return RandomInUnitSphere().Unit(); }
    [[nodiscard]] inline static Vector3 RandomInHemisphere(const Vector3& normal) { auto inUnit = RandomInUnitSphere(); return Dot(inUnit, normal) > 0.0 ? inUnit : -inUnit; }
};

#endif //RAYTRACING_VECTOR3_H
