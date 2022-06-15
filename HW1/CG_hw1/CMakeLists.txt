cmake_minimum_required(VERSION 3.18)
project(hw1)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)


#FreeGlut
include_directories(freeglut/include)
link_directories(freeglut/lib/x64)
add_custom_target(freeglut_dll COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/freeglut/bin/x64/freeglut.dll ${CMAKE_BINARY_DIR})



include_directories(include)
set(HEADER_FILES include)
set(SOURCE_FILES main.cpp Object.cpp stb_image.cpp)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} libfreeglut.a )

add_dependencies(${PROJECT_NAME} freeglut_dll)
set(CMAKE_CXX_STANDARD 11)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
