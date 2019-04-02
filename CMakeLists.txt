cmake_minimum_required(VERSION 3.9)
project(Space_Adventure)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
#set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Space_Adventure main.cpp Obiekty.cpp Pomocnicze.cpp Menu.cpp AI.h AI.cpp)
target_link_libraries(Space_Adventure sfml-graphics sfml-audio)




