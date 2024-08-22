cmake_minimum_required(VERSION 3.28)
project(SlotMachineSimulator VERSION 1.0)

set(CMAKE_DEBUG_POSTFIX d)

add_executable(a.out SlotMachineSimulator.cpp src/Point.cpp src/ProgramParameters.cpp src/Reel.cpp src/Report.cpp src/RewardTable.cpp)

find_package(GTest CONFIG REQUIRED)

target_include_directories(a.out PUBLIC include)

target_link_libraries(a.out gtest_main)