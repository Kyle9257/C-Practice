#include "vec3.h"
#include <iostream>

int main() {
    Vec3 a(3, 0, 0);
    Vec3 b(0, 4, 0);

    Vec3 c = a + b;
    std::cout << "a+b = (" << c.x << ", " << c.y << ", " << c.z << ")\n";
    std::cout << "a dot b = " << a.dot(b) << "\n";

    Vec3 n = normalize(Vec3(1, 2, 2));
    std::cout << "normalize(1,2,2) length = " << n.length() << "\n";
}
