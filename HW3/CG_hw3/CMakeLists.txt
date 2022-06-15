cmake_minimum_required(VERSION 3.18)
project(hw3)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
set(glm_DIR ${PROJECT_SOURCE_DIR}/glm/cmake/glm)
find_package(glm REQUIRED)

#GLEW
include_directories(glew-2.2.0/include)
link_directories(glew-2.2.0/lib/Release/x64)
add_custom_target(glew_dll COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/glew-2.2.0/bin/Release/x64/glew32.dll ${CMAKE_BINARY_DIR})

#FreeGlut
include_directories(freeglut/include)
link_directories(freeglut/lib/x64)
add_custom_target(freeglut_dll COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/freeglut/bin/x64/freeglut.dll ${CMAKE_BINARY_DIR})

#FreeImage
include_directories(FreeImage-3.18/include)
link_directories(FreeImage-3.18/lib)
add_custom_target(FreeImage_dll COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/FreeImage-3.18/bin/FreeImage.dll ${CMAKE_BINARY_DIR})

#glm
include_directories(${GLM_INCLUDE_DIRS})

include_directories(include)
set(HEADER_FILES include)
set(SOURCE_FILES main.cpp Object.cpp stb_image.cpp)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} libfreeglut.a glew32.lib FreeImage.lib)

add_dependencies(${PROJECT_NAME} freeglut_dll glew_dll FreeImage_dll)
set(CMAKE_CXX_STANDARD 11)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)