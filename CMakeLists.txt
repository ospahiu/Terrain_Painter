cmake_minimum_required(VERSION 3.3)
project(A2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp QuadMesh.cpp Plane.cpp Plane.h Blob.cpp Blob.h)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# Include Files and executable
add_executable(A2 ${SOURCE_FILES} main.h QuadMesh.h VECTOR3D.h QuadMesh.cpp)

# Link
target_link_libraries(A2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )