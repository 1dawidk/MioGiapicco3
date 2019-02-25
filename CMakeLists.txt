cmake_minimum_required(VERSION 3.13)
project(MioGiapicco)

set(CMAKE_CXX_STANDARD 11)

# Find reqired libs
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(dkulpaclibs REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

# Include libs directories
include_directories(${GTKMM_INCLUDE_DIRS})

# Link libs directories
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(MioGiapicco main.cpp UI.cpp UI.h ImagePusher.cpp ImagePusher.h)
target_link_libraries(MioGiapicco ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} ${CURL_LIBRARIES} ${dkulpaclibs_misc_LIB} ${dkulpaclibs_hw_LIB})