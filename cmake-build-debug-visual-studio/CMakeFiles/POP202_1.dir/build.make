# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mabat\CLionProjects\POP202_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio

# Include any dependencies generated for this target.
include CMakeFiles\POP202_1.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\POP202_1.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\POP202_1.dir\flags.make

CMakeFiles\POP202_1.dir\main.cpp.obj: CMakeFiles\POP202_1.dir\flags.make
CMakeFiles\POP202_1.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/POP202_1.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\POP202_1.dir\main.cpp.obj /FdCMakeFiles\POP202_1.dir\ /FS -c C:\Users\mabat\CLionProjects\POP202_1\main.cpp
<<

CMakeFiles\POP202_1.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/POP202_1.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\POP202_1.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mabat\CLionProjects\POP202_1\main.cpp
<<

CMakeFiles\POP202_1.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/POP202_1.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\POP202_1.dir\main.cpp.s /c C:\Users\mabat\CLionProjects\POP202_1\main.cpp
<<

CMakeFiles\POP202_1.dir\Deck.cpp.obj: CMakeFiles\POP202_1.dir\flags.make
CMakeFiles\POP202_1.dir\Deck.cpp.obj: ..\Deck.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/POP202_1.dir/Deck.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\POP202_1.dir\Deck.cpp.obj /FdCMakeFiles\POP202_1.dir\ /FS -c C:\Users\mabat\CLionProjects\POP202_1\Deck.cpp
<<

CMakeFiles\POP202_1.dir\Deck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/POP202_1.dir/Deck.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\POP202_1.dir\Deck.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mabat\CLionProjects\POP202_1\Deck.cpp
<<

CMakeFiles\POP202_1.dir\Deck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/POP202_1.dir/Deck.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\POP202_1.dir\Deck.cpp.s /c C:\Users\mabat\CLionProjects\POP202_1\Deck.cpp
<<

CMakeFiles\POP202_1.dir\GameState.cpp.obj: CMakeFiles\POP202_1.dir\flags.make
CMakeFiles\POP202_1.dir\GameState.cpp.obj: ..\GameState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/POP202_1.dir/GameState.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\POP202_1.dir\GameState.cpp.obj /FdCMakeFiles\POP202_1.dir\ /FS -c C:\Users\mabat\CLionProjects\POP202_1\GameState.cpp
<<

CMakeFiles\POP202_1.dir\GameState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/POP202_1.dir/GameState.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\POP202_1.dir\GameState.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mabat\CLionProjects\POP202_1\GameState.cpp
<<

CMakeFiles\POP202_1.dir\GameState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/POP202_1.dir/GameState.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\POP202_1.dir\GameState.cpp.s /c C:\Users\mabat\CLionProjects\POP202_1\GameState.cpp
<<

CMakeFiles\POP202_1.dir\StateParser.cpp.obj: CMakeFiles\POP202_1.dir\flags.make
CMakeFiles\POP202_1.dir\StateParser.cpp.obj: ..\StateParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/POP202_1.dir/StateParser.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\POP202_1.dir\StateParser.cpp.obj /FdCMakeFiles\POP202_1.dir\ /FS -c C:\Users\mabat\CLionProjects\POP202_1\StateParser.cpp
<<

CMakeFiles\POP202_1.dir\StateParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/POP202_1.dir/StateParser.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe > CMakeFiles\POP202_1.dir\StateParser.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mabat\CLionProjects\POP202_1\StateParser.cpp
<<

CMakeFiles\POP202_1.dir\StateParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/POP202_1.dir/StateParser.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\POP202_1.dir\StateParser.cpp.s /c C:\Users\mabat\CLionProjects\POP202_1\StateParser.cpp
<<

# Object files for target POP202_1
POP202_1_OBJECTS = \
"CMakeFiles\POP202_1.dir\main.cpp.obj" \
"CMakeFiles\POP202_1.dir\Deck.cpp.obj" \
"CMakeFiles\POP202_1.dir\GameState.cpp.obj" \
"CMakeFiles\POP202_1.dir\StateParser.cpp.obj"

# External object files for target POP202_1
POP202_1_EXTERNAL_OBJECTS =

POP202_1.exe: CMakeFiles\POP202_1.dir\main.cpp.obj
POP202_1.exe: CMakeFiles\POP202_1.dir\Deck.cpp.obj
POP202_1.exe: CMakeFiles\POP202_1.dir\GameState.cpp.obj
POP202_1.exe: CMakeFiles\POP202_1.dir\StateParser.cpp.obj
POP202_1.exe: CMakeFiles\POP202_1.dir\build.make
POP202_1.exe: CMakeFiles\POP202_1.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable POP202_1.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\POP202_1.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\POP202_1.dir\objects1.rsp @<<
 /out:POP202_1.exe /implib:POP202_1.lib /pdb:C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\POP202_1.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\POP202_1.dir\build: POP202_1.exe

.PHONY : CMakeFiles\POP202_1.dir\build

CMakeFiles\POP202_1.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\POP202_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles\POP202_1.dir\clean

CMakeFiles\POP202_1.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\mabat\CLionProjects\POP202_1 C:\Users\mabat\CLionProjects\POP202_1 C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio C:\Users\mabat\CLionProjects\POP202_1\cmake-build-debug-visual-studio\CMakeFiles\POP202_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\POP202_1.dir\depend

