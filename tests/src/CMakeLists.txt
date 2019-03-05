target_sources(${CMAKE_PROJECT_NAME}_tests
    PRIVATE
       ${CMAKE_CURRENT_LIST_DIR}/sample.cpp
       ${CMAKE_CURRENT_LIST_DIR}/graph_test.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/example_folder/CMakeLists.txt)
