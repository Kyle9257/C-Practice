# 测试可执行：test_vec3
add_executable(test_vec3 test_vec3.cpp)
target_link_libraries(test_vec3 PRIVATE vec3)

# 注册给 CTest
add_test(NAME vec3_tests COMMAND test_vec3)
