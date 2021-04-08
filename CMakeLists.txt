project(CS312-Raytracer)
cmake_minimum_required(VERSION 2.8.11)

if (WIN32) # Include win64 platforms

  find_package(OpenGL REQUIRED)
  find_library(GLEW NAMES glew32s PATHS external/lib/x64)
  find_library(GLFW NAMES glfw3 PATHS external/lib)

  set(INCLUDE_DIRS
     external/include )

  set(LIBRARY_DIRS
    lib
    external/lib)

  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_FLAGS 
     "/wd4018 /wd4244 /wd4305 
     /D_CRT_SECURE_NO_WARNINGS 
     /D_CRT_NONSTDC_NO_DEPRECATE 
     /D NOMINMAX /DGLEW_STATIC
     /EHsc")

  set(VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
  set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:\"MSVCRT\" /NODEFAULTLIB:\"LIBCMT\"")

  set(CORE ${GLEW} ${GLFW} opengl32.lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

elseif (APPLE)

  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-reorder -Wno-deprecated-declarations -g -stdlib=libc++ -std=c++14")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  find_library(GL_LIB OpenGL)
  find_library(GLFW glfw)
  add_definitions(-DAPPLE)

  set(INCLUDE_DIRS
    /System/Library/Frameworks
    external/include
    /usr/local/include)

  set(CORE ${GLFW} ${GL_LIB})

elseif (UNIX)

  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11 -Wno-comment")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

  FIND_PACKAGE(OpenGL REQUIRED) 
  FIND_PACKAGE(GLEW REQUIRED)

  set(INCLUDE_DIRS
    external/include)

  set(LIBRARY_DIRS
    external/lib
    /usr/X11R6/lib
    /usr/local/lib
    lib)

  add_definitions(-DUNIX)
  set(CORE GLEW glfw glut GL GLU X11)

endif()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})


set(SOURCES 
    src/AGL.h
    src/AGLM.h
    src/AGLM.cpp
    src/ppm_image.h
    src/ppm_image.cpp
    src/sphere.cpp
    src/material.cpp
    src/triangle.cpp
    src/plane.cpp)

set(RT_SOURCES
    src/hittable.h
    src/hittable_list.h
    src/material.h
    src/camera.h
    src/ray.h
    src/plane.h
    src/box.h
    src/triangle.h
    src/sphere.h)

add_executable(gradient src/gradient.cpp src/Ray.h src/main.cpp ${SOURCES})
target_link_libraries(gradient ${CORE})

add_executable(silhouette src/silhouette.cpp src/Ray.h src/main.cpp ${SOURCES})
target_link_libraries(silhouette ${CORE})

add_executable(normals src/normals.cpp src/main.cpp src/Ray.h ${SOURCES})
target_link_libraries(normals ${CORE})

add_executable(basic src/basic.cpp src/main.cpp ${RT_SOURCES} ${SOURCES})
target_link_libraries(basic ${CORE})

add_executable(intesection_tests src/intesection_tests.cpp ${SOURCES} ${RT_SOURCES}) 
target_link_libraries(intesection_tests ${CORE})

add_executable(raytracer src/raytracer.cpp src/main.cpp ${RT_SOURCES} ${SOURCES})
target_link_libraries(raytracer ${CORE})

add_executable(materials src/materials.cpp src/main.cpp ${RT_SOURCES} ${SOURCES})
target_link_libraries(materials ${CORE})


