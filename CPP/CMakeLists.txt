cmake_minimum_required(VERSION 3.12)
set(CMAKE_GENERATOR "Unix Makefiles")

# enabling openCV
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


project( Recon )
set(SOURCES_rec main.cpp)
add_executable(Recon ${SOURCES_rec})
target_link_libraries(Recon ${OpenCV_LIBS})

project( start_commands )
set(SOURCES_command loop_main.cpp)
add_executable(start_commands ${SOURCES_command})
target_link_libraries(start_commands ${OpenCV_LIBS})

project( take_commands )
set(SOURCES_take take_commands.cpp)
add_executable(take_commands ${SOURCES_take})

# enabling openMP
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
