add_executable(AccountTest AccountTestCase.hpp AccountTestCase.cpp)

target_link_libraries(AccountTest gtest_main gtest gmock Account DataTypes)