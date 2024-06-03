add_executable(UserTest UserTestCase.hpp UserTestCase.cpp)

target_link_libraries(UserTest gtest_main gtest gmock Transaction User Bank Account DataTypes)