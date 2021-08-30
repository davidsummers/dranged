//
// C++ experimental code takend from a couple of blogs, see the include files.
//

#include <cmath>
#include <iostream>
#include <vector>

#include "dranged/core/algorithms.h"
#include "dranged/core/element.h"
#include "dranged/core/generator.h"
#include "dranged/pipes/pipe_operator.h"
#include "dranged/pipes/pipe_push_back.h"
#include "dranged/pipes/pipe_source.h"
#include "dranged/pipes/pipe_transform.h"

using namespace dranged;

Generator< int > Integers( int max_ = 0 )
{
    for ( int i = 0; max_ == 0 || i <= max_; i++ )
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


#if LAZY_C_GENERATORS

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

int main( )
{
   std::cout << "Hello, DRANGED world!" << std::endl;

   using IntVec = std::vector< int >;

   IntVec myVec { 1, 2, 3, 4, 5 };

  // Test normal generator.
  auto gen = Counter( );
  while ( gen )
  {
    std::cout << "CoRoutine output: " << gen( ) << std::endl;
  }

  // Test range_for generator.
  auto gen1 = Counter( );
  for ( auto nextItem : gen1  )
  {
    std::cout << "CoRoutine output: " << nextItem << std::endl;
  }

  // Test range_for on bare generator.
  for ( auto nextItem : Counter( ) )
  {
    std::cout << "CoRoutine output: " << nextItem << std::endl;
  }

  // Test Range >>= result.
  {
    std::vector< int > myInts { 1, 2, 3, 4, 5 };
    std::vector< int > result;
    myInts >>= PushBack( result );
    for ( auto item : result )
    {
      std::cout << "Item: " << item << std::endl;
    }
  }

  // Test Transform >>= result.
  {
    std::vector< int > result;
    auto pipe = Transform( [ ] ( int i_ ) { return i_ * 2; } ) >>= PushBack( result );
  }

  // Test simple transform.
  {
    std::vector< int > myInts { 1, 2, 3, 4, 5 };
    std::vector< int > result;
    myInts >>= Transform( [ ] ( int i_ ) { return i_ * 2; } )
           >>= PushBack( result );
    for ( auto item : result )
    {
      std::cout << "Transformed: " << item << std::endl;
    }
  }

#if LAZY_C_GENERATORS
  auto evenIntegers = Integers( 20 ) | Where( [ ] ( int n_ ) { return ( n_ % 2 ) == 0; } );
#endif

  // Test pipeable code.
#if LAZY_C_GENERATORS
  auto nextPrime = Primes( 1000 );
  while ( nextPrime )
  {
    std::cout << "Prime number: " << nextPrime( ) << std::endl;
  }
#endif
  return 0;
}
