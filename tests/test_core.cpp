//
// test_date.cpp --- test FavorDate class.
//

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <vector>

#ifndef WIN32
#include <unistd.h>
#endif

#include "test.h"

#include "dranged/core/algorithms.h"
#include "dranged/core/border.h"
#include "dranged/core/element.h"
#include "dranged/core/range.h"

using namespace dranged;

using IntVec = std::vector< int >;

// The tests.

static error_t test_border( )
{
  // Test Border.
  // Just make sure we can instantiate it.
  IntVec myVec { 1, 2, 3, 4, 5 };

  Border< IntVec > border0;
  Border< IntVec > border1( myVec.begin( ) );
  Border< IntVec > bordef2( myVec.end(   ) );

  return NO_ERROR;
}


static error_t test_element( )
{
  // Test Element.
  // At the moment, just make sure we can instantiate it.
  IntVec myVec { 1, 2, 3, 4, 5 };

  Element< IntVec > element0;
  Element< IntVec > element1( myVec.begin( ) );
  Element< IntVec > element2( myVec.end(   ) );

  return NO_ERROR;
}

static error_t test_range_for_each( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );
  IntVec result;

  // Test 'for_each'.
  for_each( myRange, [ & ] ( int &val_ )
  {
    result.push_back( val_ );
  } );

  if ( myVec != result )
  {
    ERROR( "Result vector didn't match original vector." );
  }

  return NO_ERROR;
}

static error_t test_range_find( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );

  // Test 'find'.
  if ( auto element = find( myRange, 3 ); *element != 3 )
  {
    ERROR( "Element '3' was not at position 3." );
  }

  return NO_ERROR;
}

static error_t test_range_find_if( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );

  // Test found.
  if ( auto element = find_if( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 4;
                      } ); *element != 4 )
  {
    ERROR( "Element '4' was not at position 4." );
  }

  // Test not found.
  if ( auto element = find_if( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 6;
                      } ) )
  {
    ERROR( "Error: Element value 6 was found but should not have been found." );
  }

  return NO_ERROR;
}

static error_t test_range_find_if_not( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );

  if ( auto element = find_if_not( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 7;
                      } ); !element )
  {
    ERROR( "Error: Element '7' found when it should not have been." );
  }

  return NO_ERROR;
}

/* The test table.  */

struct test_descriptor_t test_funcs[] =
{
  TEST_NULL,
  TEST_PASS( test_border,            "Basic Border Tests" ),
  TEST_PASS( test_element,           "Basic Element Tests" ),
  TEST_PASS( test_range_for_each,    "Basic Range for_each Tests" ),
  TEST_PASS( test_range_find,        "Basic Range find Tests" ),
  TEST_PASS( test_range_find_if,     "Basic Range find_if Tests" ),
  TEST_PASS( test_range_find_if_not, "Basic Range find_if_not Tests" ),
  TEST_NULL
};
