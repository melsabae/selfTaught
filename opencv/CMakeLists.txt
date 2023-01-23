cmake_minimum_required(VERSION 3.0)
project(opencv_things LANGUAGES CXX)


add_executable(sample1 sample1.cpp)
target_include_directories(sample1 PUBLIC "/usr/include/opencv4")
target_link_libraries(sample1 opencv_core opencv_highgui opencv_imgcodecs)

