cmake_minimum_required(VERSION 3.27)
project(EPQ)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(3rdparty/glm)

# set debu
set(CMAKE_BUILD_TYPE Debug)


add_executable(EPQ
        src/imageio.h
        src/geometry.h
        src/geometry.cpp
        src/cameras/camera.cpp
        src/cameras/camera.h
        src/cameras/orthographicCamera.cpp
        src/cameras/orthographicCamera.h
        src/integrators/integrator.cpp
        src/integrators/integrator.h
        src/samplers/sampler.cpp
        src/samplers/sampler.h
        src/utility/RNG.cpp
        src/utility/RNG.h
        src/samplers/stratifiedSampler.cpp
        src/samplers/stratifiedSampler.h
        src/Scene.cpp
        src/Scene.h
        src/Primitives.cpp
        src/Primitives.h
        src/integrators/testIntegerator.cpp
        src/main.cpp
)
target_include_directories(EPQ PRIVATE 3rdparty/stb_image)
target_include_directories(EPQ PRIVATE src)
target_link_libraries(EPQ glm)