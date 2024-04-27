cmake_minimum_required(VERSION 3.26.4)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(data)

add_executable(data data.cpp)

# Buscar y enlazar la biblioteca CURL
find_package(CURL CONFIG REQUIRED)
target_link_libraries(data PRIVATE CURL::libcurl)

# También necesitas agregar los siguientes includes si deseas usar las funciones de libcurl
target_include_directories(data PRIVATE ${CURL_INCLUDE_DIRS})

# Buscar y enlazar la biblioteca JSONCPP
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(data PRIVATE jsoncpp_lib)

# Agregar los directorios de inclusión de JSONCPP
target_include_directories(data PRIVATE ${JSONCPP_INCLUDE_DIRS})