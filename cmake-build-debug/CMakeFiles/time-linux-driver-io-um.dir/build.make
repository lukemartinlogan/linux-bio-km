# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/time-linux-driver-io-um.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/time-linux-driver-io-um.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/time-linux-driver-io-um.dir/flags.make

CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o: CMakeFiles/time-linux-driver-io-um.dir/flags.make
CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o: ../test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o   -c /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c

CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c > CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.i

CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c -o CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.s

# Object files for target time-linux-driver-io-um
time__linux__driver__io__um_OBJECTS = \
"CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o"

# External object files for target time-linux-driver-io-um
time__linux__driver__io__um_EXTERNAL_OBJECTS =

libtime-linux-driver-io-um.so: CMakeFiles/time-linux-driver-io-um.dir/test/time-transfer-methods/submit-bio-driver/time-linux-driver-io-um.c.o
libtime-linux-driver-io-um.so: CMakeFiles/time-linux-driver-io-um.dir/build.make
libtime-linux-driver-io-um.so: CMakeFiles/time-linux-driver-io-um.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libtime-linux-driver-io-um.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/time-linux-driver-io-um.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/time-linux-driver-io-um.dir/build: libtime-linux-driver-io-um.so

.PHONY : CMakeFiles/time-linux-driver-io-um.dir/build

CMakeFiles/time-linux-driver-io-um.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/time-linux-driver-io-um.dir/cmake_clean.cmake
.PHONY : CMakeFiles/time-linux-driver-io-um.dir/clean

CMakeFiles/time-linux-driver-io-um.dir/depend:
	cd /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug/CMakeFiles/time-linux-driver-io-um.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/time-linux-driver-io-um.dir/depend

