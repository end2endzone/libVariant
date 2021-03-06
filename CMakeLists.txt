# CMakeLists.txt
cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)
project(libVariant)

##############################################################################################################################################
# Standard CMake variables
##############################################################################################################################################

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

# Set a default build type if none was specified.
# See https://blog.kitware.com/cmake-and-the-default-build-type/
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  mark_as_advanced(CMAKE_BUILD_TYPE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Export no symbols by default (if the compiler supports it). 
# This makes e.g. GCC's "visibility behavior" consistent with MSVC's.  
# On Windows/MSVC this is a noop. 
if (BUILD_SHARED_LIBS)
  set(CMAKE_C_VISIBILITY_PRESET hidden) 
  set(CMAKE_CXX_VISIBILITY_PRESET hidden) 
endif()

# Set the output folder where your program will be created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(   LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

##############################################################################################################################################
# CMake properties
##############################################################################################################################################
MESSAGE( STATUS "PROJECT_NAME:             " ${PROJECT_NAME} )
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_BINARY_DIR:       " ${PROJECT_BINARY_DIR} )
MESSAGE( STATUS "PROJECT_SOURCE_DIR:       " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH:   " ${EXECUTABLE_OUTPUT_PATH} )
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:      " ${LIBRARY_OUTPUT_PATH} )
MESSAGE( STATUS "CMAKE_MODULE_PATH:        " ${CMAKE_MODULE_PATH} )
MESSAGE( STATUS "CMAKE_COMMAND:            " ${CMAKE_COMMAND} )
MESSAGE( STATUS "CMAKE_ROOT:               " ${CMAKE_ROOT} )
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE:  " ${CMAKE_CURRENT_LIST_FILE} )
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE:  " ${CMAKE_CURRENT_LIST_LINE} )
MESSAGE( STATUS "CMAKE_INCLUDE_PATH:       " ${CMAKE_INCLUDE_PATH} )
MESSAGE( STATUS "CMAKE_LIBRARY_PATH:       " ${CMAKE_LIBRARY_PATH} )
MESSAGE( STATUS "CMAKE_SYSTEM:             " ${CMAKE_SYSTEM} )
MESSAGE( STATUS "CMAKE_SYSTEM_NAME:        " ${CMAKE_SYSTEM_NAME} )
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION:     " ${CMAKE_SYSTEM_VERSION} )
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR:   " ${CMAKE_SYSTEM_PROCESSOR} )

MESSAGE( "Build options:" )
MESSAGE( STATUS "LIBVARIANT_BUILD_TEST: " ${LIBVARIANT_BUILD_TEST} )
MESSAGE( STATUS "LIBVARIANT_USE_STD_STRING: " ${LIBVARIANT_USE_STD_STRING} )
MESSAGE( STATUS "LIBVARIANT_BUILD_STDINT_TYPES_TEST: " ${LIBVARIANT_BUILD_STDINT_TYPES_TEST} )
if (WIN32)
  MESSAGE( STATUS "CMAKE_GENERATOR_PLATFORM: " ${CMAKE_GENERATOR_PLATFORM} )
endif()

##############################################################################################################################################
# Global settings
##############################################################################################################################################

# Product version according to Semantic Versioning v2.0.0 https://semver.org/
SET(LIBVARIANT_VERSION_MAJOR 3)
SET(LIBVARIANT_VERSION_MINOR 0)
SET(LIBVARIANT_VERSION_PATCH 0)
set(LIBVARIANT_VERSION ${LIBVARIANT_VERSION_MAJOR}.${LIBVARIANT_VERSION_MINOR}.${LIBVARIANT_VERSION_PATCH})

# read license file
file(READ ${CMAKE_SOURCE_DIR}/LICENSE.h LICENSE)

# version.h file
set(LIBVARIANT_VERSION_HEADER ${CMAKE_BINARY_DIR}/include/libvariant/version.h)
message("Generating ${LIBVARIANT_VERSION_HEADER}...")
configure_file( ${CMAKE_SOURCE_DIR}/src/libVariant/version.h.in ${LIBVARIANT_VERSION_HEADER} )

# Define installation directories
set(LIBVARIANT_INSTALL_BIN_DIR      "bin")
set(LIBVARIANT_INSTALL_LIB_DIR      "lib/libvariant-${LIBVARIANT_VERSION}")
set(LIBVARIANT_INSTALL_INCLUDE_DIR  "include/libvariant-${LIBVARIANT_VERSION}")
set(LIBVARIANT_INSTALL_CMAKE_DIR    ${LIBVARIANT_INSTALL_LIB_DIR}) # CMake files (*.cmake) should have the same destination as the library files. Some also prefers to use "cmake".

##############################################################################################################################################
# Project settings
##############################################################################################################################################

# Build options
option(LIBVARIANT_BUILD_TEST "Build all libVariant's unit tests" OFF)
option(LIBVARIANT_BUILD_STDINT_TYPES_TEST "Build a code sample for testing stdint types on all platforms" OFF)
option(LIBVARIANT_USE_STD_STRING "Build libVariant using std::string" ON)

# config.h file
set(LIBVARIANT_CONFIG_HEADER ${CMAKE_BINARY_DIR}/include/libvariant/config.h)
message("Generating ${LIBVARIANT_CONFIG_HEADER}...")
set(LIBVARIANT_BUILD_OPTION_DEFINITIONS "//build options")
if (BUILD_SHARED_LIBS)
  string(CONCAT LIBVARIANT_BUILD_OPTION_DEFINITIONS "${LIBVARIANT_BUILD_OPTION_DEFINITIONS}" "\n#define LIBVARIANT_BUILT_AS_SHARED")
else()
  string(CONCAT LIBVARIANT_BUILD_OPTION_DEFINITIONS "${LIBVARIANT_BUILD_OPTION_DEFINITIONS}" "\n#define LIBVARIANT_BUILT_AS_STATIC")
endif()
if (LIBVARIANT_BUILD_TEST)
  string(CONCAT LIBVARIANT_BUILD_OPTION_DEFINITIONS "${LIBVARIANT_BUILD_OPTION_DEFINITIONS}" "\n#define LIBVARIANT_HAS_TESTS")
endif()
if (LIBVARIANT_BUILD_STDINT_TYPES_TEST)
  string(CONCAT LIBVARIANT_BUILD_OPTION_DEFINITIONS "${LIBVARIANT_BUILD_OPTION_DEFINITIONS}" "\n#define LIBVARIANT_HAS_STDINT_TYPES_TEST")
endif()
if (LIBVARIANT_USE_STD_STRING)
  string(CONCAT LIBVARIANT_BUILD_OPTION_DEFINITIONS "${LIBVARIANT_BUILD_OPTION_DEFINITIONS}" "\n#define LIBVARIANT_USE_STD_STRING")
endif()
configure_file( ${CMAKE_SOURCE_DIR}/src/libVariant/config.h.in ${LIBVARIANT_CONFIG_HEADER} )

# Force a debug postfix if none specified.
# This allows publishing both release and debug binaries to the same location
# and it helps to prevent linking with the wrong library on Windows.
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Prevents annoying warnings on MSVC
if (WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Define include directories for source code.
# The specified values will not be exported.
set( LIBVARIANT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
include_directories(${LIBVARIANT_INCLUDE_DIR}          # public header files, for source code.
                    ${CMAKE_BINARY_DIR}/include     # for ${LIBVARIANT_VERSION_HEADER} and ${LIBVARIANT_CONFIG_HEADER} generated files.
                    ${CMAKE_SOURCE_DIR}/src/common  # for common files shared by libVariant and unit tests.
)

##############################################################################################################################################
# Dependencies
##############################################################################################################################################
find_package(GTest REQUIRED) #rapidassist requires GTest

##############################################################################################################################################
# Subprojects
##############################################################################################################################################

if (BUILD_SHARED_LIBS)
  set(LIBVARIANT_EXPORT_HEADER_FILENAME "export.h")
  set(LIBVARIANT_EXPORT_HEADER ${CMAKE_BINARY_DIR}/include/libvariant/${LIBVARIANT_EXPORT_HEADER_FILENAME})
endif()

add_subdirectory(src/libVariant)
add_subdirectory(src/code_generator)

#stdint types test
if(LIBVARIANT_BUILD_STDINT_TYPES_TEST)
  add_subdirectory(test/stdint_types_test)
endif()

# unit tests
if(LIBVARIANT_BUILD_TEST)
  add_subdirectory(test/libvariant_unittest)
endif()

##############################################################################################################################################
# Support for static and shared library
##############################################################################################################################################

if (BUILD_SHARED_LIBS)
  message("Generating ${LIBVARIANT_EXPORT_HEADER_FILENAME} for shared library...")
  include (GenerateExportHeader) 
  GENERATE_EXPORT_HEADER(libvariant 
               BASE_NAME libvariant 
               EXPORT_MACRO_NAME LIBVARIANT_EXPORT 
               EXPORT_FILE_NAME ${LIBVARIANT_EXPORT_HEADER} 
               STATIC_DEFINE LIBVARIANT_BUILT_AS_STATIC
  )
endif()

##############################################################################################################################################
# Install
##############################################################################################################################################

# Install locations:   See https://unix.stackexchange.com/a/36874
#   On UNIX, installs to "/usr/local".
#   On Windows, installs to "C:\Program Files (x86)\${PROJECT_NAME}" or to "C:\Program Files\${PROJECT_NAME}" for 64 bit binaries

# Target config version verification file
configure_file(${CMAKE_SOURCE_DIR}/cmake/libvariant-config-version.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/cmake/libvariant-config-version.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/libvariant-config-version.cmake DESTINATION ${LIBVARIANT_INSTALL_CMAKE_DIR})

# Target config file
configure_file(${CMAKE_SOURCE_DIR}/cmake/libvariant-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/cmake/libvariant-config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/libvariant-config.cmake DESTINATION ${LIBVARIANT_INSTALL_CMAKE_DIR})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${LIBVARIANT_INSTALL_INCLUDE_DIR})
install(FILES ${LIBVARIANT_EXPORT_HEADER}
              ${LIBVARIANT_VERSION_HEADER}
              ${LIBVARIANT_CONFIG_HEADER}
              DESTINATION ${LIBVARIANT_INSTALL_INCLUDE_DIR}/libvariant)
install(EXPORT libvariant-targets DESTINATION ${LIBVARIANT_INSTALL_CMAKE_DIR})

##############################################################################################################################################
# Packaging
##############################################################################################################################################

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${LIBVARIANT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "${LIBVARIANT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${LIBVARIANT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${LIBVARIANT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libVariant is a c++ library which encapsulate any value of variant types.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
