cmake_minimum_required(VERSION 3.16)

project(Xor_arreglo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Xor_arreglo main.cpp)

include(GNUInstallDirs)
install(TARGETS Xor_arreglo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
