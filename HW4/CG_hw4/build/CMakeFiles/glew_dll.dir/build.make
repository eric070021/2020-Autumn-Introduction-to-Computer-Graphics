# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\cmake-3.19.0-rc3-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = C:\cmake-3.19.0-rc3-win64-x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ERIC\Desktop\CG_hw4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ERIC\Desktop\CG_hw4\build

# Utility rule file for glew_dll.

# Include the progress variables for this target.
include CMakeFiles/glew_dll.dir/progress.make

CMakeFiles/glew_dll:
	C:\cmake-3.19.0-rc3-win64-x64\bin\cmake.exe -E copy C:/Users/ERIC/Desktop/CG_hw4/glew-2.2.0/bin/Release/x64/glew32.dll C:/Users/ERIC/Desktop/CG_hw4/build

glew_dll: CMakeFiles/glew_dll
glew_dll: CMakeFiles/glew_dll.dir/build.make

.PHONY : glew_dll

# Rule to build all files generated by this target.
CMakeFiles/glew_dll.dir/build: glew_dll

.PHONY : CMakeFiles/glew_dll.dir/build

CMakeFiles/glew_dll.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glew_dll.dir\cmake_clean.cmake
.PHONY : CMakeFiles/glew_dll.dir/clean

CMakeFiles/glew_dll.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ERIC\Desktop\CG_hw4 C:\Users\ERIC\Desktop\CG_hw4 C:\Users\ERIC\Desktop\CG_hw4\build C:\Users\ERIC\Desktop\CG_hw4\build C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles\glew_dll.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glew_dll.dir/depend

