# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /snap/cmake/1070/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1070/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anna/Repositories/4th_semester/Studying_templates/Container

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anna/Repositories/4th_semester/Studying_templates/Container

# Include any dependencies generated for this target.
include CMakeFiles/Dynamic_mem.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Dynamic_mem.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Dynamic_mem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Dynamic_mem.dir/flags.make

CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o: CMakeFiles/Dynamic_mem.dir/flags.make
CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o: src/Container/Dynamic_mem.cpp
CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o: CMakeFiles/Dynamic_mem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anna/Repositories/4th_semester/Studying_templates/Container/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o -MF CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o.d -o CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o -c /home/anna/Repositories/4th_semester/Studying_templates/Container/src/Container/Dynamic_mem.cpp

CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anna/Repositories/4th_semester/Studying_templates/Container/src/Container/Dynamic_mem.cpp > CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.i

CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anna/Repositories/4th_semester/Studying_templates/Container/src/Container/Dynamic_mem.cpp -o CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.s

# Object files for target Dynamic_mem
Dynamic_mem_OBJECTS = \
"CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o"

# External object files for target Dynamic_mem
Dynamic_mem_EXTERNAL_OBJECTS =

libDynamic_mem.a: CMakeFiles/Dynamic_mem.dir/src/Container/Dynamic_mem.cpp.o
libDynamic_mem.a: CMakeFiles/Dynamic_mem.dir/build.make
libDynamic_mem.a: CMakeFiles/Dynamic_mem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anna/Repositories/4th_semester/Studying_templates/Container/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libDynamic_mem.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Dynamic_mem.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Dynamic_mem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Dynamic_mem.dir/build: libDynamic_mem.a
.PHONY : CMakeFiles/Dynamic_mem.dir/build

CMakeFiles/Dynamic_mem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Dynamic_mem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Dynamic_mem.dir/clean

CMakeFiles/Dynamic_mem.dir/depend:
	cd /home/anna/Repositories/4th_semester/Studying_templates/Container && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anna/Repositories/4th_semester/Studying_templates/Container /home/anna/Repositories/4th_semester/Studying_templates/Container /home/anna/Repositories/4th_semester/Studying_templates/Container /home/anna/Repositories/4th_semester/Studying_templates/Container /home/anna/Repositories/4th_semester/Studying_templates/Container/CMakeFiles/Dynamic_mem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Dynamic_mem.dir/depend
