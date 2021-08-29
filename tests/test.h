#pragma once

/*
 * test.h:  public interfaces for test programs.
 *
 */

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef char * error_t;

error_t error_create( const char * file, int line, const char *errmsg );

#define NO_ERROR ( ( error_t ) 0 )

#define ERROR( errstr ) return( error_create( __FILE__, __LINE__, errstr ) )

#define WARN( errstr ) { printf( "WARN:  %s(%d): %s\n", __FILE__, __LINE__, errstr ); }

/* Prototype for test driver functions. */
typedef error_t ( *test_driver_t ) ( );

/* All test programs include an array of test descriptors
   (all of our sub-tests) that begins and ends with a TEST_NULL entry. */
struct test_descriptor_t
{
  test_driver_t func;       /* A pointer to the test driver function. */
  int xfail;                /* Is the test marked XFAIL? */
  const char *msg;          /* Human readable name of test */
};

extern struct test_descriptor_t test_funcs[];

/* A null initializer for the test descriptor. */
#define TEST_NULL { nullptr, 0, "" }

/* Initializers for PASS and XFAIL tests */
#define TEST_PASS(  func, msg ) { func, 0, msg }
#define TEST_XFAIL( func, msg ) { func, 1, msg }

/* Return a pseudo-random number based on SEED, and modify SEED.  This
   is a "good" pseudo-random number generator, intended to replace all
   those "bad" rand() implementations out there. */
uint32_t favor_test_rand ( uint32_t *seed );

bool ChangeToTestDataDir( char *testDataDirPtr );

bool EqualWithinTolerance( double val1, double val2, double tol );


#ifdef __cplusplus
}
#endif /* __cplusplus */

