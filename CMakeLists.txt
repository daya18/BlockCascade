# CMakeList.txt : CMake project for BlockCascade, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BlockCascade")

set ( BUILD_SHARED_LIBS FALSE )
add_subdirectory ( external/SFML )

add_executable ( BlockCascade )

# Add sources to this project's executable.
target_sources ( BlockCascade
	PRIVATE
	"source/Main.cpp"
	"source/Application.cpp"
	"source/World.cpp"
)

target_include_directories ( BlockCascade
	PRIVATE
	"external/SFML/include"
)

target_link_libraries ( BlockCascade
	PRIVATE
	sfml-system sfml-graphics sfml-window
)

target_precompile_headers ( BlockCascade
	PRIVATE
	<SFML/Window.hpp>
	<SFML/Graphics.hpp>
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BlockCascade PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
