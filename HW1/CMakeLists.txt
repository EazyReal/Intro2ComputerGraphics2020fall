cmake_minimum_required(VERSION 3.0.0)
project(HW1 VERSION 0.1.0)

# find_package(glm REQUIRED)
find_package(GLFW3 REQUIRED)
# find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GLUT_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    # ${GLEW_INCLUDE_DIRS}
    # ${GLM_INCLUDE_DIRS}
)

add_executable(HW1 main.cpp Object.cpp)
target_link_libraries(
    ${PROJECT_NAME} 
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    glfw
    # ${GLEW_LIBRARIES}
    # glm::glm 
)

set(CMAKE_CXX_STANDARD 11)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
