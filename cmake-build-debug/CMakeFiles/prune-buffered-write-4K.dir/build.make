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

# Utility rule file for prune-buffered-write-4K.

# Include the progress variables for this target.
include CMakeFiles/prune-buffered-write-4K.dir/progress.make

CMakeFiles/prune-buffered-write-4K:
	bash /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/trace-transfer-methods/prune.sh /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/trace-transfer-methods buffered-write-4K

prune-buffered-write-4K: CMakeFiles/prune-buffered-write-4K
prune-buffered-write-4K: CMakeFiles/prune-buffered-write-4K.dir/build.make

.PHONY : prune-buffered-write-4K

# Rule to build all files generated by this target.
CMakeFiles/prune-buffered-write-4K.dir/build: prune-buffered-write-4K

.PHONY : CMakeFiles/prune-buffered-write-4K.dir/build

CMakeFiles/prune-buffered-write-4K.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prune-buffered-write-4K.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prune-buffered-write-4K.dir/clean

CMakeFiles/prune-buffered-write-4K.dir/depend:
	cd /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug/CMakeFiles/prune-buffered-write-4K.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prune-buffered-write-4K.dir/depend

