# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.5\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simple_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simple_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simple_example.dir/flags.make

CMakeFiles/simple_example.dir/main.cpp.obj: CMakeFiles/simple_example.dir/flags.make
CMakeFiles/simple_example.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simple_example.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_example.dir\main.cpp.obj -c C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\main.cpp

CMakeFiles/simple_example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_example.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\main.cpp > CMakeFiles\simple_example.dir\main.cpp.i

CMakeFiles/simple_example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_example.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\main.cpp -o CMakeFiles\simple_example.dir\main.cpp.s

# Object files for target simple_example
simple_example_OBJECTS = \
"CMakeFiles/simple_example.dir/main.cpp.obj"

# External object files for target simple_example
simple_example_EXTERNAL_OBJECTS =

simple_example.exe: CMakeFiles/simple_example.dir/main.cpp.obj
simple_example.exe: CMakeFiles/simple_example.dir/build.make
simple_example.exe: CMakeFiles/simple_example.dir/linklibs.rsp
simple_example.exe: CMakeFiles/simple_example.dir/objects1.rsp
simple_example.exe: CMakeFiles/simple_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable simple_example.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simple_example.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simple_example.dir/build: simple_example.exe

.PHONY : CMakeFiles/simple_example.dir/build

CMakeFiles/simple_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\simple_example.dir\cmake_clean.cmake
.PHONY : CMakeFiles/simple_example.dir/clean

CMakeFiles/simple_example.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3 C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3 C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug C:\Users\Coworking\source\repos\itmo_master\1\algorithms\lab3\cmake-build-debug\CMakeFiles\simple_example.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple_example.dir/depend
