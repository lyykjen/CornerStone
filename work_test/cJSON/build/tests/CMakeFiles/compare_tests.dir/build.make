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
include tests/CMakeFiles/compare_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/compare_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/compare_tests.dir/flags.make

tests/CMakeFiles/compare_tests.dir/compare_tests.c.o: tests/CMakeFiles/compare_tests.dir/flags.make
tests/CMakeFiles/compare_tests.dir/compare_tests.c.o: ../tests/compare_tests.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lvyayun/test/work_test/cJSON/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object tests/CMakeFiles/compare_tests.dir/compare_tests.c.o"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/compare_tests.dir/compare_tests.c.o   -c /home/lvyayun/test/work_test/cJSON/tests/compare_tests.c

tests/CMakeFiles/compare_tests.dir/compare_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compare_tests.dir/compare_tests.c.i"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lvyayun/test/work_test/cJSON/tests/compare_tests.c > CMakeFiles/compare_tests.dir/compare_tests.c.i

tests/CMakeFiles/compare_tests.dir/compare_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compare_tests.dir/compare_tests.c.s"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lvyayun/test/work_test/cJSON/tests/compare_tests.c -o CMakeFiles/compare_tests.dir/compare_tests.c.s

tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.requires:
.PHONY : tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.requires

tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.provides: tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.requires
	$(MAKE) -f tests/CMakeFiles/compare_tests.dir/build.make tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.provides.build
.PHONY : tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.provides

tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.provides.build: tests/CMakeFiles/compare_tests.dir/compare_tests.c.o

# Object files for target compare_tests
compare_tests_OBJECTS = \
"CMakeFiles/compare_tests.dir/compare_tests.c.o"

# External object files for target compare_tests
compare_tests_EXTERNAL_OBJECTS =

tests/compare_tests: tests/CMakeFiles/compare_tests.dir/compare_tests.c.o
tests/compare_tests: tests/CMakeFiles/compare_tests.dir/build.make
tests/compare_tests: libcjson.so.1.5.8
tests/compare_tests: tests/libunity.so
tests/compare_tests: tests/libtest-common.so
tests/compare_tests: tests/CMakeFiles/compare_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable compare_tests"
	cd /home/lvyayun/test/work_test/cJSON/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compare_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/compare_tests.dir/build: tests/compare_tests
.PHONY : tests/CMakeFiles/compare_tests.dir/build

tests/CMakeFiles/compare_tests.dir/requires: tests/CMakeFiles/compare_tests.dir/compare_tests.c.o.requires
.PHONY : tests/CMakeFiles/compare_tests.dir/requires

tests/CMakeFiles/compare_tests.dir/clean:
	cd /home/lvyayun/test/work_test/cJSON/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/compare_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/compare_tests.dir/clean

tests/CMakeFiles/compare_tests.dir/depend:
	cd /home/lvyayun/test/work_test/cJSON/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lvyayun/test/work_test/cJSON /home/lvyayun/test/work_test/cJSON/tests /home/lvyayun/test/work_test/cJSON/build /home/lvyayun/test/work_test/cJSON/build/tests /home/lvyayun/test/work_test/cJSON/build/tests/CMakeFiles/compare_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/compare_tests.dir/depend
