# Force C++11 standard on Linux.
if (NOT WIN32)
  MESSAGE( WARNING "Building project ${PROJECT_NAME}. Increasing minimum requirement of c++ standard from C++98 to C++11." )
  SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_executable(stdint_types_test
  main.cpp
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(stdint_types_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
