
set( TEST_SOURCE
     test_main.cpp
     test_deranged.cpp
   )

set( TEST_INCLUDES 
     test.h
     test_helpers.h
    )

add_executable( test_dranged
                ${TEST_SOURCE}
                ${TEST_INCLUDES}
                ${INCLUDE_GENERATOR_FILES}
                ${INCLUDE_HELPER_FILES}
                ${INCLUDE_PIPE_FILES}
                ${INCLUDE_RANGE_FILES}
              )

target_include_directories( test_dranged PUBLIC
                            ${CMAKE_SOURCE_DIR}/include
                          )
