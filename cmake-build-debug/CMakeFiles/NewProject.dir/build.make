# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = H:\NewProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = H:\NewProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\NewProject.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\NewProject.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\NewProject.dir\flags.make

CMakeFiles\NewProject.dir\main.cpp.obj: CMakeFiles\NewProject.dir\flags.make
CMakeFiles\NewProject.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=H:\NewProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NewProject.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\NewProject.dir\main.cpp.obj /FdCMakeFiles\NewProject.dir\ /FS -c H:\NewProject\main.cpp
<<

CMakeFiles\NewProject.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NewProject.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\NewProject.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E H:\NewProject\main.cpp
<<

CMakeFiles\NewProject.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NewProject.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\NewProject.dir\main.cpp.s /c H:\NewProject\main.cpp
<<

# Object files for target NewProject
NewProject_OBJECTS = \
"CMakeFiles\NewProject.dir\main.cpp.obj"

# External object files for target NewProject
NewProject_EXTERNAL_OBJECTS =

NewProject.exe: CMakeFiles\NewProject.dir\main.cpp.obj
NewProject.exe: CMakeFiles\NewProject.dir\build.make
NewProject.exe: CMakeFiles\NewProject.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=H:\NewProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NewProject.exe"
	"C:\Program Files\JetBrains\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\NewProject.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\NewProject.dir\objects1.rsp @<<
 /out:NewProject.exe /implib:NewProject.lib /pdb:H:\NewProject\cmake-build-debug\NewProject.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\NewProject.dir\build: NewProject.exe

.PHONY : CMakeFiles\NewProject.dir\build

CMakeFiles\NewProject.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NewProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles\NewProject.dir\clean

CMakeFiles\NewProject.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" H:\NewProject H:\NewProject H:\NewProject\cmake-build-debug H:\NewProject\cmake-build-debug H:\NewProject\cmake-build-debug\CMakeFiles\NewProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\NewProject.dir\depend

