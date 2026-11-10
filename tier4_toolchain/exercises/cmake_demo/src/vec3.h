#pragma once

struct Vec3 {
    double x = 0, y = 0, z = 0;

    Vec3() = default;
    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    Vec3 operator+(const Vec3& o) const {
        return {x + o.x, y + o.y, z + o.z};
    }

    double dot(const Vec3& o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    double length() const;
};

Vec3 normalize(const Vec3& v);
