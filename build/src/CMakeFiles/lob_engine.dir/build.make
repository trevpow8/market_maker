# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /opt/anaconda3/lib/python3.11/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /opt/anaconda3/lib/python3.11/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/trevorpowell/market_maker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/trevorpowell/market_maker/build

# Include any dependencies generated for this target.
include src/CMakeFiles/lob_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/lob_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lob_engine.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lob_engine.dir/flags.make

src/CMakeFiles/lob_engine.dir/codegen:
.PHONY : src/CMakeFiles/lob_engine.dir/codegen

src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o: src/CMakeFiles/lob_engine.dir/flags.make
src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o: /Users/trevorpowell/market_maker/src/lob_engine/OrderBook.cpp
src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o: src/CMakeFiles/lob_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trevorpowell/market_maker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o"
	cd /Users/trevorpowell/market_maker/build/src && /opt/anaconda3/bin/arm64-apple-darwin20.0.0-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o -MF CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o.d -o CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o -c /Users/trevorpowell/market_maker/src/lob_engine/OrderBook.cpp

src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.i"
	cd /Users/trevorpowell/market_maker/build/src && /opt/anaconda3/bin/arm64-apple-darwin20.0.0-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trevorpowell/market_maker/src/lob_engine/OrderBook.cpp > CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.i

src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.s"
	cd /Users/trevorpowell/market_maker/build/src && /opt/anaconda3/bin/arm64-apple-darwin20.0.0-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trevorpowell/market_maker/src/lob_engine/OrderBook.cpp -o CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.s

# Object files for target lob_engine
lob_engine_OBJECTS = \
"CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o"

# External object files for target lob_engine
lob_engine_EXTERNAL_OBJECTS =

src/liblob_engine.a: src/CMakeFiles/lob_engine.dir/lob_engine/OrderBook.cpp.o
src/liblob_engine.a: src/CMakeFiles/lob_engine.dir/build.make
src/liblob_engine.a: src/CMakeFiles/lob_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/trevorpowell/market_maker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblob_engine.a"
	cd /Users/trevorpowell/market_maker/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lob_engine.dir/cmake_clean_target.cmake
	cd /Users/trevorpowell/market_maker/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lob_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lob_engine.dir/build: src/liblob_engine.a
.PHONY : src/CMakeFiles/lob_engine.dir/build

src/CMakeFiles/lob_engine.dir/clean:
	cd /Users/trevorpowell/market_maker/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lob_engine.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lob_engine.dir/clean

src/CMakeFiles/lob_engine.dir/depend:
	cd /Users/trevorpowell/market_maker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/trevorpowell/market_maker /Users/trevorpowell/market_maker/src /Users/trevorpowell/market_maker/build /Users/trevorpowell/market_maker/build/src /Users/trevorpowell/market_maker/build/src/CMakeFiles/lob_engine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/lob_engine.dir/depend

