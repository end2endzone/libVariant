add_executable(libvariant_unittest
  ${LIBVARIANT_EXPORT_HEADER}
  ${LIBVARIANT_VERSION_HEADER}
  ${LIBVARIANT_CONFIG_HEADER}
  gtesthelper.cpp
  gtesthelper.h
  main.cpp
  TestFloatLimits.cpp
  TestFloatLimits.h
  TestStringEncoder.cpp
  TestStringEncoder.h
  TestTypeInfo.cpp
  TestTypeInfo.h
  TestTypeUnion.cpp
  TestTypeUnion.h
  TestVariant.cpp
  TestVariant.h
  TestVariant.testVbScriptIdenticalBehavior.input.txt
  TestVariantTemplate.cpp
  TestVariantTemplate.h
)

# Unit test projects requires to link with pthread if also linking with gtest
if(NOT WIN32)
  set(PTHREAD_LIBRARIES -pthread)
endif()

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(libvariant_unittest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(libvariant_unittest 
  PRIVATE
    ${GTEST_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/libVariant # for templates files (Type*.h)
)
add_dependencies(libvariant_unittest libvariant)
target_link_libraries(libvariant_unittest PRIVATE libvariant ${PTHREAD_LIBRARIES} ${GTEST_LIBRARIES} )

# Copy test file to target dir
add_custom_command( TARGET libvariant_unittest POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/TestVariant.testVbScriptIdenticalBehavior.input.txt $<TARGET_FILE_DIR:libvariant_unittest>/
                    COMMENT "Copying test files...")

# Copy test files to build dir for local execution (from within the IDE)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/TestVariant.testVbScriptIdenticalBehavior.input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS libvariant_unittest
        EXPORT libvariant-targets
        ARCHIVE DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${LIBVARIANT_INSTALL_BIN_DIR}
)
