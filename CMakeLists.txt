cmake_minimum_required(VERSION 3.27)
project(EPQ)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(3rdparty/glm)

add_executable(EPQ src/main.cpp
        src/imageio.h
        src/cameras/camera.cpp
        src/cameras/camera.h
        src/geometry.h
        src/geometry.cpp
        src/geometricOperations/transformations.h
        src/cameras/orthographicCamera.cpp
        src/cameras/orthographicCamera.h
)
target_include_directories(EPQ PRIVATE 3rdparty/stb_image)
target_include_directories(EPQ PRIVATE src)
target_link_libraries(EPQ glm)