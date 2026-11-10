#include "vec3.h"
#include <cmath>
#include <iostream>

// 极简自写断言（不依赖外部测试框架，本地即可跑通）
int failures = 0;

void expect_near(double actual, double expected, const char* msg) {
    if (std::fabs(actual - expected) > 1e-9) {
        std::cout << "FAIL: " << msg
                  << " (got " << actual << ", want " << expected << ")\n";
        ++failures;
    }
}

int main() {
    Vec3 a(3, 0, 0), b(0, 4, 0);

    expect_near((a + b).x, 3, "a+b.x");
    expect_near((a + b).y, 4, "a+b.y");
    expect_near(a.dot(b), 0, "a dot b");
    expect_near(normalize(Vec3(1, 2, 2)).length(), 1.0, "normalized length");

    if (failures == 0) {
        std::cout << "全部通过\n";
        return 0;
    }
    std::cout << failures << " 个失败\n";
    return 1;
}
