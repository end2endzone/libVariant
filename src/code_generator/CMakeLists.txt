set(LIBVARIANT_HEADER_FILES ""
  ${LIBVARIANT_INCLUDE_DIR}/libvariant/variant.h
)

add_executable(code_generator
  ${LIBVARIANT_HEADER_FILES}
  ${LIBVARIANT_EXPORT_HEADER}
  ${LIBVARIANT_VERSION_HEADER}
  ${LIBVARIANT_CONFIG_HEADER}
  BaseTypes.cpp
  BaseTypes.h
  CodeGenerator.cpp
  CodeGenerator.h
  main.cpp
  TestAllBaseTypes.cpp
  TestAllBaseTypes.h
  utils.cpp
  utils.h
  VariantDefinition.cpp
  VariantDefinition.h
)

# Force CMAKE_DEBUG_POSTFIX for executables
set_target_properties(code_generator PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_dependencies(code_generator libvariant)

install(TARGETS code_generator
        EXPORT libvariant-targets
        ARCHIVE DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        LIBRARY DESTINATION ${LIBVARIANT_INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${LIBVARIANT_INSTALL_BIN_DIR}
)
