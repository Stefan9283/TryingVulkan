# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stefan/GIT/TryingVulkan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stefan/GIT/TryingVulkan

# Include any dependencies generated for this target.
include CMakeFiles/VULKAN_Tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VULKAN_Tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VULKAN_Tests.dir/flags.make

CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o: CMakeFiles/VULKAN_Tests.dir/flags.make
CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o: Dependencies/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stefan/GIT/TryingVulkan/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o -c /home/stefan/GIT/TryingVulkan/Dependencies/src/main.cpp

CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stefan/GIT/TryingVulkan/Dependencies/src/main.cpp > CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.i

CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stefan/GIT/TryingVulkan/Dependencies/src/main.cpp -o CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.s

# Object files for target VULKAN_Tests
VULKAN_Tests_OBJECTS = \
"CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o"

# External object files for target VULKAN_Tests
VULKAN_Tests_EXTERNAL_OBJECTS =

VULKAN_Tests/VULKAN_Tests: CMakeFiles/VULKAN_Tests.dir/Dependencies/src/main.cpp.o
VULKAN_Tests/VULKAN_Tests: CMakeFiles/VULKAN_Tests.dir/build.make
VULKAN_Tests/VULKAN_Tests: Dependencies/vendor/glfw/src/libglfw3.a
VULKAN_Tests/VULKAN_Tests: /usr/lib/x86_64-linux-gnu/libvulkan.so
VULKAN_Tests/VULKAN_Tests: /usr/lib/x86_64-linux-gnu/librt.so
VULKAN_Tests/VULKAN_Tests: /usr/lib/x86_64-linux-gnu/libm.so
VULKAN_Tests/VULKAN_Tests: CMakeFiles/VULKAN_Tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stefan/GIT/TryingVulkan/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VULKAN_Tests/VULKAN_Tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VULKAN_Tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VULKAN_Tests.dir/build: VULKAN_Tests/VULKAN_Tests

.PHONY : CMakeFiles/VULKAN_Tests.dir/build

CMakeFiles/VULKAN_Tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VULKAN_Tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VULKAN_Tests.dir/clean

CMakeFiles/VULKAN_Tests.dir/depend:
	cd /home/stefan/GIT/TryingVulkan && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stefan/GIT/TryingVulkan /home/stefan/GIT/TryingVulkan /home/stefan/GIT/TryingVulkan /home/stefan/GIT/TryingVulkan /home/stefan/GIT/TryingVulkan/CMakeFiles/VULKAN_Tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VULKAN_Tests.dir/depend
