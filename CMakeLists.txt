cmake_minimum_required(VERSION 3.25)
project(zpg)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(libs/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

link_libraries(${GLEW_LIBRARIES})

add_executable(zpg src/main.cpp src/application.cpp src/application.h src/model.cpp src/model.h src/shader_programs.cpp src/shader_programs.h src/shader.cpp src/shader.h src/observer.h)
#add_executable(zpg src/old_main.cpp)
target_link_libraries(zpg ${OPENGL_LIBRARIES} glfw glm::glm GLEW::GLEW)