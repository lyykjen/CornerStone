# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lvyayun/test/work_test/cJSON

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lvyayun/test/work_test/cJSON/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/parse_number.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/parse_number.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/parse_number.dir/flags.make

tests/CMakeFiles/parse_number.dir/parse_number.c.o: tests/CMakeFiles/parse_number.dir/flags.make
tests/CMakeFiles/parse_number.dir/parse_number.c.o: ../tests/parse_number.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lvyayun/test/work_test/cJSON/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/parse_number.dir/parse_number.c.o"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/parse_number.dir/parse_number.c.o   -c /home/lvyayun/test/work_test/cJSON/tests/parse_number.c

tests/CMakeFiles/parse_number.dir/parse_number.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parse_number.dir/parse_number.c.i"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lvyayun/test/work_test/cJSON/tests/parse_number.c > CMakeFiles/parse_number.dir/parse_number.c.i

tests/CMakeFiles/parse_number.dir/parse_number.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parse_number.dir/parse_number.c.s"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lvyayun/test/work_test/cJSON/tests/parse_number.c -o CMakeFiles/parse_number.dir/parse_number.c.s

tests/CMakeFiles/parse_number.dir/parse_number.c.o.requires:
.PHONY : tests/CMakeFiles/parse_number.dir/parse_number.c.o.requires

tests/CMakeFiles/parse_number.dir/parse_number.c.o.provides: tests/CMakeFiles/parse_number.dir/parse_number.c.o.requires
	$(MAKE) -f tests/CMakeFiles/parse_number.dir/build.make tests/CMakeFiles/parse_number.dir/parse_number.c.o.provides.build
.PHONY : tests/CMakeFiles/parse_number.dir/parse_number.c.o.provides

tests/CMakeFiles/parse_number.dir/parse_number.c.o.provides.build: tests/CMakeFiles/parse_number.dir/parse_number.c.o

# Object files for target parse_number
parse_number_OBJECTS = \
"CMakeFiles/parse_number.dir/parse_number.c.o"

# External object files for target parse_number
parse_number_EXTERNAL_OBJECTS =

tests/parse_number: tests/CMakeFiles/parse_number.dir/parse_number.c.o
tests/parse_number: tests/CMakeFiles/parse_number.dir/build.make
tests/parse_number: libcjson.so.1.5.8
tests/parse_number: tests/libunity.so
tests/parse_number: tests/libtest-common.so
tests/parse_number: tests/CMakeFiles/parse_number.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable parse_number"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parse_number.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/parse_number.dir/build: tests/parse_number
.PHONY : tests/CMakeFiles/parse_number.dir/build

tests/CMakeFiles/parse_number.dir/requires: tests/CMakeFiles/parse_number.dir/parse_number.c.o.requires
.PHONY : tests/CMakeFiles/parse_number.dir/requires

tests/CMakeFiles/parse_number.dir/clean:
	cd /home/lvyayun/test/work_test/cJSON/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/parse_number.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/parse_number.dir/clean

tests/CMakeFiles/parse_number.dir/depend:
	cd /home/lvyayun/test/work_test/cJSON/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lvyayun/test/work_test/cJSON /home/lvyayun/test/work_test/cJSON/tests /home/lvyayun/test/work_test/cJSON/build /home/lvyayun/test/work_test/cJSON/build/tests /home/lvyayun/test/work_test/cJSON/build/tests/CMakeFiles/parse_number.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/parse_number.dir/depend
