# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/camm_rose/Documents/CGRA251/Assignment 4/work"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug"

# Include any dependencies generated for this target.
include vendor/glew/CMakeFiles/glew.dir/depend.make

# Include the progress variables for this target.
include vendor/glew/CMakeFiles/glew.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/glew/CMakeFiles/glew.dir/flags.make

vendor/glew/CMakeFiles/glew.dir/src/glew.c.o: vendor/glew/CMakeFiles/glew.dir/flags.make
vendor/glew/CMakeFiles/glew.dir/src/glew.c.o: ../vendor/glew/src/glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/glew/CMakeFiles/glew.dir/src/glew.c.o"
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glew.dir/src/glew.c.o   -c "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/vendor/glew/src/glew.c"

vendor/glew/CMakeFiles/glew.dir/src/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glew.dir/src/glew.c.i"
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/vendor/glew/src/glew.c" > CMakeFiles/glew.dir/src/glew.c.i

vendor/glew/CMakeFiles/glew.dir/src/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glew.dir/src/glew.c.s"
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/vendor/glew/src/glew.c" -o CMakeFiles/glew.dir/src/glew.c.s

vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.requires:

.PHONY : vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.requires

vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.provides: vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.requires
	$(MAKE) -f vendor/glew/CMakeFiles/glew.dir/build.make vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.provides.build
.PHONY : vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.provides

vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.provides.build: vendor/glew/CMakeFiles/glew.dir/src/glew.c.o


# Object files for target glew
glew_OBJECTS = \
"CMakeFiles/glew.dir/src/glew.c.o"

# External object files for target glew
glew_EXTERNAL_OBJECTS =

bin/libglew.a: vendor/glew/CMakeFiles/glew.dir/src/glew.c.o
bin/libglew.a: vendor/glew/CMakeFiles/glew.dir/build.make
bin/libglew.a: vendor/glew/CMakeFiles/glew.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../bin/libglew.a"
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && $(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean_target.cmake
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glew.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/glew/CMakeFiles/glew.dir/build: bin/libglew.a

.PHONY : vendor/glew/CMakeFiles/glew.dir/build

vendor/glew/CMakeFiles/glew.dir/requires: vendor/glew/CMakeFiles/glew.dir/src/glew.c.o.requires

.PHONY : vendor/glew/CMakeFiles/glew.dir/requires

vendor/glew/CMakeFiles/glew.dir/clean:
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" && $(CMAKE_COMMAND) -P CMakeFiles/glew.dir/cmake_clean.cmake
.PHONY : vendor/glew/CMakeFiles/glew.dir/clean

vendor/glew/CMakeFiles/glew.dir/depend:
	cd "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/camm_rose/Documents/CGRA251/Assignment 4/work" "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/vendor/glew" "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug" "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew" "/Users/camm_rose/Documents/CGRA251/Assignment 4/work/cmake-build-debug/vendor/glew/CMakeFiles/glew.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : vendor/glew/CMakeFiles/glew.dir/depend

