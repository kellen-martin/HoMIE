# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/homie/HoMIE/Image Reconstruction"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/homie/HoMIE/Image Reconstruction"

# Include any dependencies generated for this target.
include CMakeFiles/loop_recon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/loop_recon.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/loop_recon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/loop_recon.dir/flags.make

CMakeFiles/loop_recon.dir/loop_recon.cpp.o: CMakeFiles/loop_recon.dir/flags.make
CMakeFiles/loop_recon.dir/loop_recon.cpp.o: loop_recon.cpp
CMakeFiles/loop_recon.dir/loop_recon.cpp.o: CMakeFiles/loop_recon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/homie/HoMIE/Image Reconstruction/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/loop_recon.dir/loop_recon.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/loop_recon.dir/loop_recon.cpp.o -MF CMakeFiles/loop_recon.dir/loop_recon.cpp.o.d -o CMakeFiles/loop_recon.dir/loop_recon.cpp.o -c "/home/homie/HoMIE/Image Reconstruction/loop_recon.cpp"

CMakeFiles/loop_recon.dir/loop_recon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/loop_recon.dir/loop_recon.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/homie/HoMIE/Image Reconstruction/loop_recon.cpp" > CMakeFiles/loop_recon.dir/loop_recon.cpp.i

CMakeFiles/loop_recon.dir/loop_recon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/loop_recon.dir/loop_recon.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/homie/HoMIE/Image Reconstruction/loop_recon.cpp" -o CMakeFiles/loop_recon.dir/loop_recon.cpp.s

# Object files for target loop_recon
loop_recon_OBJECTS = \
"CMakeFiles/loop_recon.dir/loop_recon.cpp.o"

# External object files for target loop_recon
loop_recon_EXTERNAL_OBJECTS =

loop_recon: CMakeFiles/loop_recon.dir/loop_recon.cpp.o
loop_recon: CMakeFiles/loop_recon.dir/build.make
loop_recon: /usr/local/lib/libopencv_core.so.4.7.0
loop_recon: /usr/local/lib/libopencv_features2d.so.4.7.0
loop_recon: /usr/local/lib/libopencv_flann.so.4.7.0
loop_recon: /usr/local/lib/libopencv_highgui.so.4.7.0
loop_recon: /usr/local/lib/libopencv_imgcodecs.so.4.7.0
loop_recon: /usr/local/lib/libopencv_imgproc.so.4.7.0
loop_recon: /usr/local/lib/libopencv_photo.so.4.7.0
loop_recon: /usr/local/lib/libopencv_video.so.4.7.0
loop_recon: /usr/local/lib/libopencv_videoio.so.4.7.0
loop_recon: /usr/local/lib/libopencv_imgcodecs.so.4.7.0
loop_recon: /usr/local/lib/libopencv_imgproc.so.4.7.0
loop_recon: /usr/local/lib/libopencv_core.so.4.7.0
loop_recon: CMakeFiles/loop_recon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/homie/HoMIE/Image Reconstruction/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable loop_recon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/loop_recon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/loop_recon.dir/build: loop_recon
.PHONY : CMakeFiles/loop_recon.dir/build

CMakeFiles/loop_recon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/loop_recon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/loop_recon.dir/clean

CMakeFiles/loop_recon.dir/depend:
	cd "/home/homie/HoMIE/Image Reconstruction" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/homie/HoMIE/Image Reconstruction" "/home/homie/HoMIE/Image Reconstruction" "/home/homie/HoMIE/Image Reconstruction" "/home/homie/HoMIE/Image Reconstruction" "/home/homie/HoMIE/Image Reconstruction/CMakeFiles/loop_recon.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/loop_recon.dir/depend

