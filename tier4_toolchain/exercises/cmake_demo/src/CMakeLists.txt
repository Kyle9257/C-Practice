# 静态库 target：vec3
add_library(vec3 STATIC
    vec3.cpp
)

# PUBLIC 头文件目录：链接本库的 target 会自动获得这个 include 路径
target_include_directories(vec3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
