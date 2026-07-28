cmake_minimum_required(VERSION 4.0)
project(healthBarSim)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.1.0
)

set(CMAKE_CXX_STANDARD 26)

FetchContent_MakeAvailable(SFML)

add_executable(healthBarSim main.cpp)
target_compile_features(healthBarSim PRIVATE cxx_std_26)
target_link_libraries(healthBarSim PRIVATE SFML::Graphics)


