cmake_minimum_required(VERSION 3.16)

project(ejercicio_19 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ejercicio_19 main.cpp)

include(GNUInstallDirs)
install(TARGETS ejercicio_19
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
