cmake_minimum_required(VERSION 2.8)

project(cobalt)
add_executable(cobalt
	"main.cpp"
	"cobalt/lexer.cpp"
	"cobalt/log.cpp")

target_compile_options(cobalt PRIVATE -Wall -Wextra -std=c++17)
