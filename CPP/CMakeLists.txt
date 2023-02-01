cmake_minimum_required(VERSION 3.12)
set(CMAKE_GENERATOR "Unix Makefiles")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ./CMakeFiles)
# set("OpenCV_DIR" /)

project( Recon )

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

# set(SOURCES main.cpp AverageImage.cpp CalculateTemplate.cpp DifferenceStack.cpp ImportImages.cpp linspace.cpp PlotFrame.cpp Reconstructor.cpp)
set(SOURCES main.cpp)
add_executable(Recon ${SOURCES})
target_link_libraries(Recon ${OpenCV_LIBS})