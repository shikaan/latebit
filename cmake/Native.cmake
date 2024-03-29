set(VCPKG_ROOT $ENV{VCPKG_ROOT})
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

set(CMAKE_CXX_COMPILER $ENV{CXX})

# Declare dependencies
find_package(SDL2 2.30.0 CONFIG REQUIRED)
find_package(SDL2_mixer 2.8.0 CONFIG REQUIRED)
find_package(PNG 1.6.43 REQUIRED)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    PNG::PNG
    SDL2::SDL2-static
    SDL2_mixer::SDL2_mixer-static)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})

# Create test executable
add_executable(test.out test/main.cpp ${TEST_LIB_FILES})
target_link_libraries(test.out PRIVATE ${PROJECT_NAME})
add_custom_target(test
    COMMAND $<TARGET_FILE:test.out>
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)