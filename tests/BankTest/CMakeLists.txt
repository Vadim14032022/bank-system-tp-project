add_executable(BankTest BankTestCase.hpp BankTestCase.cpp)

target_link_libraries(BankTest gtest_main gtest gmock Transaction User Bank Account DataTypes)