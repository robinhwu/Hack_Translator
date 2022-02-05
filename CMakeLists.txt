cmake_minimum_required(VERSION 3.17)
project(Hack_Translator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hack_Translator main.cpp Parser.cpp Parser.h CodeWriter.cpp CodeWriter.h)