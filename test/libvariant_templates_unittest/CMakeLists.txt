add_executable(libvariant_templates_unittest
  ${LIBVARIANT_EXPORT_HEADER}
  ${LIBVARIANT_VERSION_HEADER}
  ${LIBVARIANT_CONFIG_HEADER}
  gtesthelper.cpp
  gtesthelper.h
  main.cpp
  TestFloatLimits.cpp
  TestFloatLimits.h
#  TestStringEncoder.cpp
#  TestStringEncoder.h
  TestTypeCastSaturation.cpp
  TestTypeCastSaturation.h
  TestTypeInfo.cpp
  TestTypeInfo.h
  TestTypeUnion.cpp
  TestTypeUnion.h
)

# Unit test projects requires to link with pthread if also linking with gtest
if(NOT WIN32)
  set(PTHREAD_LIBRARIES -pthread)
endif()

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(libvariant_templates_unittest PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(libvariant_templates_unittest 
  PRIVATE
    ${GTEST_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/libVariant # for templates files (Type*.h)
)
add_dependencies(libvariant_templates_unittest libvariant)
target_link_libraries(libvariant_templates_unittest ${PTHREAD_LIBRARIES} ${GTEST_LIBRARIES} )

install(TARGETS libvariant_templates_unittest
        EXPORT libvariant-targets
        ARCHIVE DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${LIBVARIANT_INSTALL_BIN_DIR}
)
