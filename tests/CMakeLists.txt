
set( TEST_SOURCE
     test_main.cpp
     test_core.cpp
   )

set( TEST_INCLUDES 
     test.h
     test_helpers.h
    )

add_executable( test_dranged1
                ${TEST_SOURCE}
                ${TEST_INCLUDES}
              )

target_include_directories( test_dranged1 PUBLIC
                            ${CMAKE_SOURCE_DIR}/include
                          )
