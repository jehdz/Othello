# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jehdz/Desktop/othello

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jehdz/Desktop/othello/build

# Include any dependencies generated for this target.
include CMakeFiles/othello.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/othello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/othello.dir/flags.make

CMakeFiles/othello.dir/board.c.o: CMakeFiles/othello.dir/flags.make
CMakeFiles/othello.dir/board.c.o: ../board.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jehdz/Desktop/othello/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/othello.dir/board.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/othello.dir/board.c.o -c /Users/jehdz/Desktop/othello/board.c

CMakeFiles/othello.dir/board.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/othello.dir/board.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jehdz/Desktop/othello/board.c > CMakeFiles/othello.dir/board.c.i

CMakeFiles/othello.dir/board.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/othello.dir/board.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jehdz/Desktop/othello/board.c -o CMakeFiles/othello.dir/board.c.s

# Object files for target othello
othello_OBJECTS = \
"CMakeFiles/othello.dir/board.c.o"

# External object files for target othello
othello_EXTERNAL_OBJECTS =

bin/othello: CMakeFiles/othello.dir/board.c.o
bin/othello: CMakeFiles/othello.dir/build.make
bin/othello: CMakeFiles/othello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jehdz/Desktop/othello/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/othello"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/othello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/othello.dir/build: bin/othello

.PHONY : CMakeFiles/othello.dir/build

CMakeFiles/othello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/othello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/othello.dir/clean

CMakeFiles/othello.dir/depend:
	cd /Users/jehdz/Desktop/othello/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jehdz/Desktop/othello /Users/jehdz/Desktop/othello /Users/jehdz/Desktop/othello/build /Users/jehdz/Desktop/othello/build /Users/jehdz/Desktop/othello/build/CMakeFiles/othello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/othello.dir/depend

