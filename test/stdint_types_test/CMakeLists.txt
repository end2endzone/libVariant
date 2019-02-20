get_filename_component(CURRENT_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Force C++11 standard on Linux.
if (NOT WIN32)
  MESSAGE( WARNING "Building project '${CURRENT_PROJECT_NAME}'. Increasing minimum c++ standard from C++98 to C++11." )
  SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_executable(stdint_types_test
  main.cpp
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(stdint_types_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
