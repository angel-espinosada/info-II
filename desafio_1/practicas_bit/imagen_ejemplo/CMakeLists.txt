cmake_minimum_required(VERSION 3.16)

project(imagen_ejemplo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(imagen_ejemplo main.cpp)

include(GNUInstallDirs)
install(TARGETS imagen_ejemplo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
