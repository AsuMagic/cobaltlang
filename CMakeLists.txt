cmake_minimum_required(VERSION 2.8)

project(cobalt)
add_executable(${PROJECT_NAME}
	"main.cpp"
	"cobalt/token.hpp"
	"cobalt/lexer.hpp"
	"cobalt/lexer.cpp")

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
