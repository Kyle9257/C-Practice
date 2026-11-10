#include "vec3.h"
#include <cmath>

double Vec3::length() const {
    return std::sqrt(dot(*this));
}

Vec3 normalize(const Vec3& v) {
    double len = v.length();
    return {v.x / len, v.y / len, v.z / len};
}
