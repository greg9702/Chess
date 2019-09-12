cmake_minimum_required(VERSION 3.10)
project(Chess)

# set everything up for c++ 17 features
set(CMAKE_CXX_STANDARD 17)
# Don't add this line if you will try_compile with boost.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# test that filesystem header actually is there and works

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "include/*.h")

add_executable(chess ${SOURCES})

add_executable(server Network/MainServer.cpp)
add_executable(client Network/OuterClient.cpp)

target_link_libraries(server stdc++fs)
