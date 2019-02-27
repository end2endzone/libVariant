set(LIBVARIANT_HEADER_FILES ""
  ${LIBVARIANT_INCLUDE_DIR}/libvariant/variant.h
  ${LIBVARIANT_INCLUDE_DIR}/libvariant/variant_types.h
  ${LIBVARIANT_INCLUDE_DIR}/libvariant/typeinfo.h
)

if (NOT LIBVARIANT_USE_STD_STRING)
  set(LIBVARIANT_STRING_FILES ${LIBVARIANT_INCLUDE_DIR}/libvariant/variant_string.h
                              ${CMAKE_CURRENT_SOURCE_DIR}/variant_string.cpp
  )
endif()

add_library(libvariant
  ${LIBVARIANT_HEADER_FILES}
  ${LIBVARIANT_EXPORT_HEADER}
  ${LIBVARIANT_VERSION_HEADER}
  ${LIBVARIANT_CONFIG_HEADER}
  ${LIBVARIANT_STRING_FILES}
  FloatLimits.h
  StringEncoder.h
  StringParser.h
  Variant.cpp
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(libvariant PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# Define include directories for exported code.
target_include_directories(libvariant
  PUBLIC
    $<INSTALL_INTERFACE:${LIBVARIANT_INSTALL_INCLUDE_DIR}>  # for clients using the installed library.
)

install(TARGETS libvariant
        EXPORT libvariant-targets
        ARCHIVE DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${LIBVARIANT_INSTALL_BIN_DIR}
)
