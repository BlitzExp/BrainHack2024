cmake_minimum_required(VERSION 3.26.4)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(data)

add_executable(data data.cpp)

# Buscar y enlazar la biblioteca CURL
find_package(CURL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

# También necesitas agregar los siguientes includes si deseas usar las funciones de libcurl
target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})