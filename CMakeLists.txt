cmake_minimum_required(VERSION 3.8)
project(object_tracking)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        camshift/ObjectTracker.cpp camshift/ObjectTracker.h)

add_executable(object_tracking ${SOURCE_FILES})
target_link_libraries(object_tracking ${OpenCV_LIBS})