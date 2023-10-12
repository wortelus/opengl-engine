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

add_executable(zpg src/main.cpp
        src/core/application.h src/core/application.cpp
        src/util/const.h
        src/util/event_args.h
        src/util/observer.h
        src/models/model.h src/models/model.cpp
        src/rendering/shader_loader.h src/rendering/shader_loader.cpp
        src/rendering/shader.h src/rendering/shader.cpp
        src/models/drawable.h src/models/drawable.cpp
        src/rendering/transform.h src/rendering/transform.cpp
        src/rendering/transform_composite.h src/rendering/transform_composite.cpp
        src/core/scene.h src/core/scene.cpp
        src/rendering/camera.h src/rendering/camera.cpp)

target_link_libraries(zpg ${OPENGL_LIBRARIES} glfw glm::glm GLEW::GLEW)