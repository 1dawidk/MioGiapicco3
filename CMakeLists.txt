cmake_minimum_required(VERSION 3.7)
project(MioGiapicco)

set(CMAKE_CXX_STANDARD 11)

# Find reqired libs
find_library(bcm2835_lib bcm2835 REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(dkulpaclibs REQUIRED)
find_package(PkgConfig)
set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED)

# Include libs directories
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(MioGiapicco main.cpp UI.cpp UI.h ImagePusher.cpp ImagePusher.h SunController.cpp SunController.h Devices/DHT22.cpp Devices/DHT22.h Devices/HD44780.cpp Devices/HD44780.h Peripherals/I2C.cpp Peripherals/I2C.h Devices/PCA9685.cpp Devices/PCA9685.h ButtonsManager.cpp ButtonsManager.h WateringController.cpp WateringController.h WindController.cpp WindController.h Devices/Camera.cpp Devices/Camera.h DataPusher.cpp DataPusher.h Devices/MCP3208.cpp Devices/MCP3208.h Peripherals/SPI.cpp Peripherals/SPI.h Devices/SEN0193.cpp Devices/SEN0193.h)
target_link_libraries(MioGiapicco ${CMAKE_THREAD_LIBS_INIT}  ${CURL_LIBRARIES} ${OpenCV_LIBS} ${dkulpaclibs_misc_LIB} ${bcm2835_lib} ${raspicam_CV_LIBS})