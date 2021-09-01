#
# DRANGE
#

cmake_minimum_required( VERSION 3.17 )

project( dranged )

set( CMAKE_CXX_STANDARD          20  )
set( CMAKX_CXX_STANDARD_REQUIRED ON  )
set( CMAKE_CXX_EXTENSIONS        OFF )

if ( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( )

message( "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )

message( "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}" )

if ( CMAKE_VERSION VERSION_GREATER_EQUAL "3.14.0" )
  cmake_policy( SET CMP0077 NEW )
endif( )

if ( APPLE )

  message( "*** Configuring for MacOS" )

  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=1" )

elseif( MSVC )

  message( "*** Configuring for Windows" )

  # Enable C++ standards conformance mode.
  add_compile_options( /permissive- )

else( )

  message( "*** Configuring for Linux" )

  add_definitions( -fcoroutines )

endif( )


if ( APPLE )

  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.10" )
  set( CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -lc++" )

  # Standard library.
  add_definitions( -stdlib=libc++ )

  # Warnings as errors.
  add_definitions( -Werror        )

elseif ( MSVC )

  # Force setting correct C++ macros.
  add_definitions( /Zc:__cplusplus )

  # Warnings as errors.
  add_definitions( /WX )

  # No deprecated standard functions.
  add_definitions( -D_CRT_SECURE_NO_WARNINGS  )

else( )

  # Warnings as errors.
  add_definitions( -Werror )

endif( )

set( INCLUDE_GENERATOR_FILES
     ${CMAKE_SOURCE_DIR}/include/dranged/generators/generator.h
   )

set( INCLUDE_HELPER_FILES
     ${CMAKE_SOURCE_DIR}/include/dranged/helpers/concepts.h
     ${CMAKE_SOURCE_DIR}/include/dranged/helpers/detect.h
     ${CMAKE_SOURCE_DIR}/include/dranged/helpers/fwd.h
     ${CMAKE_SOURCE_DIR}/include/dranged/helpers/send.h
   )

set( INCLUDE_PIPE_FILES
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe_operator.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe_push_back.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe_source.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe_take.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe_transform.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipe.h
     ${CMAKE_SOURCE_DIR}/include/dranged/pipes/pipeline.h
   )

set( INCLUDE_RANGE_FILES
     ${CMAKE_SOURCE_DIR}/include/dranged/ranges/algorithms.h
     ${CMAKE_SOURCE_DIR}/include/dranged/ranges/border.h
     ${CMAKE_SOURCE_DIR}/include/dranged/ranges/element.h
     ${CMAKE_SOURCE_DIR}/include/dranged/ranges/range.h
   )

set( TARGET_BUILD_NAME test_dranged )

add_subdirectory( "tests" )
