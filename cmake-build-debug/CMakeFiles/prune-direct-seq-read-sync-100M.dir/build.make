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

# Utility rule file for prune-direct-seq-read-sync-100M.

# Include the progress variables for this target.
include CMakeFiles/prune-direct-seq-read-sync-100M.dir/progress.make

CMakeFiles/prune-direct-seq-read-sync-100M:
	bash /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/trace-transfer-methods/prune.sh /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/test/trace-transfer-methods 9

prune-direct-seq-read-sync-100M: CMakeFiles/prune-direct-seq-read-sync-100M
prune-direct-seq-read-sync-100M: CMakeFiles/prune-direct-seq-read-sync-100M.dir/build.make

.PHONY : prune-direct-seq-read-sync-100M

# Rule to build all files generated by this target.
CMakeFiles/prune-direct-seq-read-sync-100M.dir/build: prune-direct-seq-read-sync-100M

.PHONY : CMakeFiles/prune-direct-seq-read-sync-100M.dir/build

CMakeFiles/prune-direct-seq-read-sync-100M.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prune-direct-seq-read-sync-100M.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prune-direct-seq-read-sync-100M.dir/clean

CMakeFiles/prune-direct-seq-read-sync-100M.dir/depend:
	cd /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug /home/lukemartinlogan/Documents/Projects/PhD/linux-bio-km/cmake-build-debug/CMakeFiles/prune-direct-seq-read-sync-100M.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prune-direct-seq-read-sync-100M.dir/depend

