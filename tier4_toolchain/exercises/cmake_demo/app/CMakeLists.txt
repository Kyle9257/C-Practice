# 可执行 target：demo
add_executable(demo main.cpp)

# 链接 vec3 库；PRIVATE 表示只本 target 需要
target_link_libraries(demo PRIVATE vec3)
