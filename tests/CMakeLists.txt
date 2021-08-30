
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
              )

target_include_directories( test_dranged PUBLIC
                            ${CMAKE_SOURCE_DIR}/include
                          )
