cmake_minimum_required(VERSION 2.8)
project("OpenCV_Project")


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
SET(OpenCV_DIR "/home/musa/opencv-2.4.13.2/build")
SET( OpenCV_FOUND TRUE)
file(GLOB SOURCES "src/*cpp")
find_package(OpenCV REQUIRED)
add_executable(testas ${SOURCES})


include_directories(include)
target_link_libraries(testas ${OpenCV_LIBS})



