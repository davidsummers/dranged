//
// test_date.cpp --- test FavorDate class.
//

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <iostream>

#ifndef WIN32
#include <unistd.h>
#endif

#include "test.h"
//#include "date.h"

// The tests.

static error_t test_1( )
{
#if 0 // TESTS GO HERE
#endif
  return NO_ERROR;
}


/* The test table.  */

struct test_descriptor_t test_funcs[] =
{
  TEST_NULL,
  TEST_PASS( test_1,       "Basic Range Tests" ),
  TEST_NULL
};
