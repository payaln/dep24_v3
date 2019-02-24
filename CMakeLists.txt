cmake_minimum_required(VERSION 3.12)
project(dep24_v3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH D:/new/Geant_17)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(dep24_v3 main.cpp ${sources} ${headers})
target_link_libraries(dep24_v3 ${Geant4_LIBRARIES})
