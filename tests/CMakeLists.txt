configure_file(${CMAKE_SOURCE_DIR}/cmake/GTestDownload.txt.in ${CMAKE_BINARY_DIR}/3rd-party/GTests/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/3rd-party/GTests )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/3rd-party/GTests )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/3rd-party/GTests/src
                 ${CMAKE_BINARY_DIR}/3rd-party/GTests/build
                 EXCLUDE_FROM_ALL)

add_executable(${CMAKE_PROJECT_NAME}_tests main.cpp)

set_target_properties(${CMAKE_PROJECT_NAME}_tests
    PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_STANDARD 14
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(${CMAKE_PROJECT_NAME}_tests gtest ${CMAKE_PROJECT_NAME})

include(${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_tests)
