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

# Include any dependencies generated for this target.
include CMakeFiles/hw3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw3.dir/flags.make

CMakeFiles/hw3.dir/main.cpp.obj: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/main.cpp.obj: CMakeFiles/hw3.dir/includes_CXX.rsp
CMakeFiles/hw3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw3.dir/main.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3.dir\main.cpp.obj -c C:\Users\ERIC\Desktop\CG_hw4\main.cpp

CMakeFiles/hw3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/main.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ERIC\Desktop\CG_hw4\main.cpp > CMakeFiles\hw3.dir\main.cpp.i

CMakeFiles/hw3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/main.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ERIC\Desktop\CG_hw4\main.cpp -o CMakeFiles\hw3.dir\main.cpp.s

CMakeFiles/hw3.dir/Object.cpp.obj: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/Object.cpp.obj: CMakeFiles/hw3.dir/includes_CXX.rsp
CMakeFiles/hw3.dir/Object.cpp.obj: ../Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw3.dir/Object.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3.dir\Object.cpp.obj -c C:\Users\ERIC\Desktop\CG_hw4\Object.cpp

CMakeFiles/hw3.dir/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/Object.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ERIC\Desktop\CG_hw4\Object.cpp > CMakeFiles\hw3.dir\Object.cpp.i

CMakeFiles/hw3.dir/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/Object.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ERIC\Desktop\CG_hw4\Object.cpp -o CMakeFiles\hw3.dir\Object.cpp.s

CMakeFiles/hw3.dir/stb_image.cpp.obj: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/stb_image.cpp.obj: CMakeFiles/hw3.dir/includes_CXX.rsp
CMakeFiles/hw3.dir/stb_image.cpp.obj: ../stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw3.dir/stb_image.cpp.obj"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw3.dir\stb_image.cpp.obj -c C:\Users\ERIC\Desktop\CG_hw4\stb_image.cpp

CMakeFiles/hw3.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/stb_image.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ERIC\Desktop\CG_hw4\stb_image.cpp > CMakeFiles\hw3.dir\stb_image.cpp.i

CMakeFiles/hw3.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/stb_image.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ERIC\Desktop\CG_hw4\stb_image.cpp -o CMakeFiles\hw3.dir\stb_image.cpp.s

# Object files for target hw3
hw3_OBJECTS = \
"CMakeFiles/hw3.dir/main.cpp.obj" \
"CMakeFiles/hw3.dir/Object.cpp.obj" \
"CMakeFiles/hw3.dir/stb_image.cpp.obj"

# External object files for target hw3
hw3_EXTERNAL_OBJECTS =

hw3.exe: CMakeFiles/hw3.dir/main.cpp.obj
hw3.exe: CMakeFiles/hw3.dir/Object.cpp.obj
hw3.exe: CMakeFiles/hw3.dir/stb_image.cpp.obj
hw3.exe: CMakeFiles/hw3.dir/build.make
hw3.exe: CMakeFiles/hw3.dir/linklibs.rsp
hw3.exe: CMakeFiles/hw3.dir/objects1.rsp
hw3.exe: CMakeFiles/hw3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable hw3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw3.dir/build: hw3.exe

.PHONY : CMakeFiles/hw3.dir/build

CMakeFiles/hw3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw3.dir/clean

CMakeFiles/hw3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ERIC\Desktop\CG_hw4 C:\Users\ERIC\Desktop\CG_hw4 C:\Users\ERIC\Desktop\CG_hw4\build C:\Users\ERIC\Desktop\CG_hw4\build C:\Users\ERIC\Desktop\CG_hw4\build\CMakeFiles\hw3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw3.dir/depend

