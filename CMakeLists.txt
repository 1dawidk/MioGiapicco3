cmake_minimum_required(VERSION 3.7)
project(MioGiapicco)

set(CMAKE_CXX_STANDARD 11)

# Find reqired libs
find_library(bcm2835_lib bcm2835 REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(dkulpaclibs REQUIRED)
find_package(PkgConfig)
find_package(OpenCV REQUIRED)

# Include libs directories
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(MioGiapicco main.cpp UI.cpp UI.h ImagePusher.cpp ImagePusher.h Logger.cpp Logger.h SunController.cpp SunController.h NJU6450Driver.cpp NJU6450Driver.h DHT11.cpp DHT11.h)
target_link_libraries(MioGiapicco ${CMAKE_THREAD_LIBS_INIT}  ${CURL_LIBRARIES} ${OpenCV_LIBS} ${dkulpaclibs_misc_LIB} ${dkulpaclibs_hw_LIB} ${bcm2835_lib})