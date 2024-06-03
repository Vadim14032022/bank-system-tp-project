cmake_minimum_required(VERSION 3.5)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

set(CMAKE_CXX_COMPILER "clang++")

project(BankSystem LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BankSystem_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BankSystem_SOURCE_DIR}/build//lib)

set(CMAKE_CXX_STANDARD 17)


include_directories(${PROJECT_SOURCE_DIR})

add_executable(BankSystem BankSystemMain/BankSystemMain.cpp)

target_include_directories(BankSystem PRIVATE ${PROJECT_SOURCE_DIR})

add_subdirectory("Account")
add_subdirectory("Bank")
add_subdirectory("UserInterface")
add_subdirectory("DataTypes")
add_subdirectory("Facade")
add_subdirectory("Connection")
add_subdirectory("Transaction")
add_subdirectory("User")

if(BUILD_WITH_TESTS)
    add_subdirectory(${CMAKE_BINARY_DIR}/../3rdparty/$ENV{GOOGLE_TEST_DIR})
    add_subdirectory("tests")
endif()

target_link_libraries(BankSystem PRIVATE Account Bank UserInterface DataTypes Facade Connection Transaction User)

install(
    TARGETS BankSystem Account Bank UserInterface DataTypes Facade Connection Transaction User
    RUNTIME DESTINATION exe/bin
    LIBRARY DESTINATION exe/lib
)