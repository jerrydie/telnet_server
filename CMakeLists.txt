cmake_minimum_required(VERSION 3.19)

project(hse-telnet LANGUAGES CXX)

set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.74 REQUIRED COMPONENTS chrono container context log thread filesystem program_options system)

include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/server.hpp
                src/session.hpp
                src/server.cpp
                src/session.cpp
)
target_link_libraries(${PROJECT_NAME} pthread boost_system boost_program_options boost_filesystem)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
