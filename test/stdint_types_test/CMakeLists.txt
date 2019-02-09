add_executable(stdint_types_test
  main.cpp
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(stdint_types_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
