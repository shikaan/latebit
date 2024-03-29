# Install target (needed by CPack)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/${PROJECT_NAME})
install(DIRECTORY ${SDL2_INCLUDE_DIR} DESTINATION include)

# Package with CPack
set(CPACK_PACKAGE_VENDOR "Manuel Spagnolo")
set(CPACK_PACKAGE_CONTACT "manuelspagnolo@duck.com")
set(CPACK_PACKAGE_DESCRIPTION "A game engine integrated in your IDE for pixel art games.")

if (WASM)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${VERSION_TAG}-wasm")
else()
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${VERSION_TAG}-${CMAKE_SYSTEM_NAME}")
endif()

include(CPack)