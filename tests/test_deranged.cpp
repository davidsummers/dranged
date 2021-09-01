//
// test_dranged.cpp --- test DRANGED library.
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

#include "dranged/generators/generator.h"
#include "dranged/pipes/pipe_operator.h"
#include "dranged/pipes/pipe_push_back.h"
#include "dranged/pipes/pipe_take.h"
#include "dranged/pipes/pipe_transform.h"
#include "dranged/ranges/algorithms.h"
#include "dranged/ranges/border.h"
#include "dranged/ranges/element.h"
#include "dranged/ranges/range.h"

using namespace dranged;

using IntVec = std::vector< int >;

Generator< int > Integers( int start_ = 0, uint64_t max_ = 0 )
{
    for ( int i = start_; max_ == 0 || i <= max_; i++ )
    {
      co_yield i;
    }
}

// Test generator
Generator< uint64_t > Counter( )
{
  for ( uint64_t i = 0; i < 3; )
  {
    co_yield i++;
  }
}

template< typename TYPE >
std::string PrintVector( const TYPE &vector_ )
{
  std::stringstream ss;

  ss << "{ ";

  bool first = true;

  for ( const auto &item : vector_ )
  {
    if ( first )
    {
      first = false;
    }
    else
    {
      ss << ", ";
    }

    ss << item;
  }

  ss << " }";
  return ss.str( );
}

#ifdef FUTURE

// Test prime generator
Generator< int > Primes( int max_ )
{
  return GenRange( 2, max_ - 1 )
       | Where( [ ] ( int i_ )
         {
           return GenRange( 2, (int) sqrt( i_ ) ) |
                  All( [ i_ ] ( int j_ )
                  {
                    return ( i_ % j_ ) != 0;
                  } );
         } );
}

#endif

// The tests.

static ErrorT test_border( )
{

  {
    // Test Border.
    // Just make sure we can instantiate it.
    IntVec myVec { 1, 2, 3, 4, 5 };
    [[maybe_unused]] Range range = myVec;

    Border< IntVec > border0;
    Border< IntVec > bBegin( myVec.begin( ) );
    Border< IntVec > bEnd( myVec.end(   ) );

    if ( *( bBegin.element_after( ) ) != 1 )
    {
      TEST_ERROR( "Expected element after begin border to be '1' but it was something else." );
    }

    if ( *( bEnd.element_before( ) ) != 5 )
    {
      TEST_ERROR( "Expected last element beofre end border to be '5' but it was something else." );
    }
  }

  // Test iterator on border iterators.
  {
    IntVec myVec { 1, 2, 3, 4, 5 };
    IntVec expected { 1, 2, 3, 4, 5 };
    IntVec result;
    Range range = myVec;

    for ( Border itr = range.begin( );
          itr != range.end( );
          ++itr
        )
    {
      int value = *( itr.element_after( ) );
      result.push_back( value );
    }

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}


static ErrorT test_element( )
{
  {
    // Test Element.
    // At the moment, just make sure we can instantiate it.
    IntVec myVec { 1, 2, 3, 4, 5 };

    Element< IntVec > element0;
    Element< IntVec > element1( myVec.begin( ) );
    Element< IntVec > element2( myVec.end(   ) );
  }

  // Test iterator on element iterators.
  {
    IntVec myVec { 1, 2, 3, 4, 5 };
    IntVec expected { 1, 2, 3, 4, 5 };
    IntVec result;
    Range range = myVec;

    for ( Element itr = range.begin( );
          itr != range.end( );
          ++itr
        )
    {
      int value = *itr;
      result.push_back( value );
    }

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

static ErrorT test_range_for_each( )
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
    std::stringstream ss;
    ss << "Expected result " << PrintVector( myVec ) << " but got " << PrintVector( result );
    TEST_ERROR( ss.str( ).c_str( ) );
  }

  return TEST_NO_ERROR;
}

static ErrorT test_range_find( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );
  int expected = 3;

  // Test 'find'.
  if ( auto element = find( myRange, expected ); *element != expected )
  {
    std::stringstream ss;
    ss << "Expected result " << expected << " but got " << *element;
    TEST_ERROR( ss.str( ).c_str( ) );
  }

  return TEST_NO_ERROR;
}

static ErrorT test_range_find_if( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );

  // Test found.
  if ( auto element = find_if( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 4;
                      } ); *element != 4 )
  {
    TEST_ERROR( "Element '4' was not at position 4." );
  }

  // Test not found.
  if ( auto element = find_if( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 6;
                      } ) )
  {
    TEST_ERROR( "Error: Element value 6 was found but should not have been found." );
  }

  return TEST_NO_ERROR;
}

static ErrorT test_range_find_if_not( )
{
  IntVec myVec { 1, 2, 3, 4, 5 };
  Range myRange( myVec );

  if ( auto element = find_if_not( myRange, [ ] ( int &value_ )
                      {
                        return value_ == 7;
                      } ); !element )
  {
    TEST_ERROR( "Error: Element '7' found when it should not have been." );
  }

  return TEST_NO_ERROR;
}

static ErrorT test_generator( )
{
  // Test normal generator.
  {
    IntVec result;
    auto gen = Counter( );
    while ( gen )
    {
      result.push_back( gen( ) );
    }

    IntVec expected { 0, 1, 2 };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test range_for generator.
  {
    IntVec result;
    auto gen1 = Counter( );
    for ( auto nextItem : gen1  )
    {
      result.push_back( nextItem );
    }

    IntVec expected { 0, 1, 2 };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test range_for on bare generator.
  {
    IntVec result;

    for ( auto nextItem : Counter( ) )
    {
      result.push_back( nextItem );
    }

    IntVec expected { 0, 1, 2 };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

static ErrorT test_generator_to_pipe( )
{
  // Test basic generator to pipe.
  {
    IntVec results;
    auto gen = Counter( );

    gen >>= PushBack( results );

    IntVec expected { 0, 1, 2 };
    if ( results != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( results );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test basic generator to pipeline.
  {
    IntVec results;
    auto gen = Counter( );

    gen >>= Transform( [ ] ( int i_ ) { return i_ * 3; } ) >>= PushBack( results );

    IntVec expected { 0, 3, 6 };
    if ( results != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( results );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

static ErrorT test_pipe_range_to_pipe( )
{
  // Test pipes: Range >>= result.
  {
    std::vector< int > myInts { 1, 2, 3, 4, 5 };
    std::vector< int > result;

    myInts >>= PushBack( result );

    std::vector< int > expected { 1, 2, 3, 4, 5 };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

static ErrorT test_pipe_take( )
{
  // Test 'take' pipe with a limited range.
  {
    IntVec myVec { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    IntVec expected { 1, 2, 3, 4, 5 };
    IntVec result;

    myVec >>= Take< int >( 5 ) >>= PushBack( result );

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test 'take' pipe with an 'infinite' generator.
  {
    IntVec expected { 0, 1, 2, 3, 4 };
    IntVec result;
    auto integers = Integers( 0, 100 );

    integers >>= Take< int >( 5 )
             >>= PushBack( result );

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test 'take' pipe with an 'infinite' generator with no lambda.
  {
    IntVec expected { 0, 1, 2, 3, 4 };
    IntVec result;

    Integers( 0 ) >>= Take< int >( 5 )
                  >>= PushBack( result );

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

static ErrorT test_pipe_transform( )
{
  // Test pipes: Transform >>= result.
  // This just tests that we can set up the pipe but it doesn't do anything
  // because there is no source to the pipe.
  {
    std::vector< int > result;

    [[maybe_unused]] auto pipe = Transform( [ ] ( int i_ ) { return i_ * 2; } ) >>= PushBack( result );

    std::vector< int > expected;

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test simple transform.
  {
    std::vector< int > myInts { 1, 2, 3, 4, 5 };
    std::vector< int > result;

    myInts >>= Transform( [ ] ( int i_ ) { return i_ * 2; } )
           >>= PushBack( result );

    std::vector< int > expected { 2, 4, 6, 8, 10 };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  // Test more complex transform, int -> string.
  {
    std::vector< int > myInts { 1, 2, 3, 4, 5 };
    std::vector< std::string > result;

    myInts >>= Transform( [ ] ( int i_ ) { return std::to_string( i_ ); } )
           >>= PushBack( result );

    std::vector< std::string > expected { "1", "2", "3", "4", "5" };

    if ( result != expected )
    {
      std::stringstream ss;
      ss << "Expected result " << PrintVector( expected ) << " but got " << PrintVector( result );
      TEST_ERROR( ss.str( ).c_str( ) );
    }
  }

  return TEST_NO_ERROR;
}

#ifdef FUTURE
  auto evenIntegers = Integers( 20 ) | Where( [ ] ( int n_ ) { return ( n_ % 2 ) == 0; } );
#endif

  // Test pipeable code.
#ifdef FUTURE
  auto nextPrime = Primes( 1000 );
  while ( nextPrime )
  {
    std::cout << "Prime number: " << nextPrime( ) << std::endl;
  }
#endif

/* The test table.  */

struct test_descriptor_t test_funcs[] =
{
  TEST_NULL,
  TEST_PASS( test_border,             "Basic Border Tests" ),
  TEST_PASS( test_element,            "Basic Element Tests" ),
  TEST_PASS( test_range_for_each,     "Basic Range for_each Tests" ),
  TEST_PASS( test_range_find,         "Basic Range find Tests" ),
  TEST_PASS( test_range_find_if,      "Basic Range find_if Tests" ),
  TEST_PASS( test_range_find_if_not,  "Basic Range find_if_not Tests" ),
  TEST_PASS( test_generator,          "Basic Generator Tests" ),
  TEST_PASS( test_generator_to_pipe,  "Basic Generator to Pipe Tests" ),
  TEST_PASS( test_pipe_range_to_pipe, "Basic Pipe Range to Pipe Tests." ),
  TEST_PASS( test_pipe_take,          "Basic Pipe Take Tests." ),
  TEST_PASS( test_pipe_transform,     "Basic Pipe Transform Tests." ),
  TEST_NULL
};
