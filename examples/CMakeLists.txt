file(GLOB examples_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.example.cpp)

foreach(example_source ${examples_sources})
    get_filename_component(example ${example_source} NAME_WE)
    add_executable(${example} ${example_source})
    set_target_properties(${example}
        PROPERTIES
            CXX_STANDARD_REQUIRED ON
            CXX_STANDARD 14
            CXX_EXTENSIONS OFF
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
    )
    target_link_libraries(${example} PRIVATE ${CMAKE_PROJECT_NAME})
endforeach()
