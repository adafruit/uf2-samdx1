cmake_minimum_required(VERSION 3.22.0)

message(STATUS "----------------------")
message(STATUS "Configuring uf2-samdx1")
message(STATUS "----------------------")
message(STATUS "CMake version: ${CMAKE_VERSION}")

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "In-source builds are not supported. Please use separate folder for build.")
endif()

enable_language(C)
enable_language(CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Git REQUIRED)
find_package(Python3 REQUIRED)

if(GIT_EXECUTABLE)
	# Generate a git-describe version string from Git repository tags
	execute_process(
		COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
		RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	if(NOT GIT_DESCRIBE_ERROR_CODE)
		set(UF2_VERSION_SHORT ${GIT_DESCRIBE_VERSION})
	endif()

	execute_process(
		COMMAND ${GIT_EXECUTABLE} describe --tags --dirty
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
		RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	if(NOT GIT_DESCRIBE_ERROR_CODE)
		set(UF2_VERSION_LONG ${GIT_DESCRIBE_VERSION})
	endif()
endif()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if(NOT DEFINED UF2_VERSION_SHORT)
	set(UF2_VERSION_SHORT v0.0.0)
  	message(WARNING "Failed to determine UF2_VERSION_SHORT from Git tags. Using default version \"${UF2_VERSION_SHORT}\".")
endif()

if(NOT DEFINED UF2_VERSION_LONG)
  	set(UF2_VERSION_LONG v0.0.0-unknown)
  	message(WARNING "Failed to determine UF2_VERSION_LONG from Git tags. Using default version \"${UF2_VERSION_LONG}\".")
endif()

configure_file(${CMAKE_SOURCE_DIR}/Version.h.in ${CMAKE_BINARY_DIR}/Version.h @ONLY)

message(STATUS "Short Version: ${UF2_VERSION_SHORT}")
message(STATUS "Long Version: ${UF2_VERSION_LONG}")

string(SUBSTRING ${UF2_VERSION_SHORT} 1 -1 UF2_PROJECT_VERSION)
string(REPLACE "-draft" "" UF2_PROJECT_VERSION ${UF2_PROJECT_VERSION})

message(STATUS "Project Version: ${UF2_PROJECT_VERSION}")

project(uf2 VERSION ${UF2_PROJECT_VERSION})