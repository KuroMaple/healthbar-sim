cmake_minimum_required(VERSION 4.0)
project(healthBarSim)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_MakeAvailable(SFML)

add_executable(healthBarSim
        src/main.cpp
        src/model/HealthModel.cpp
        src/viewmodel/HealthBarViewModel.cpp
        src/view/HealthBarView.cpp
        src/view/RoundedRectangle.cpp
)
target_include_directories(healthBarSim PRIVATE include)
target_compile_features(healthBarSim PRIVATE cxx_std_23)
target_link_libraries(healthBarSim PRIVATE SFML::Graphics)


