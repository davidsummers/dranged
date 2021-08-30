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

#include "dranged/core/border.h"
#include "dranged/core/element.h"

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

  return NO_ERROR;
}


/* The test table.  */

struct test_descriptor_t test_funcs[] =
{
  TEST_NULL,
  TEST_PASS( test_border, "Basic Border Tests" ),
  TEST_NULL
};
