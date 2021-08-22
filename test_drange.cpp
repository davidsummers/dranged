#include <cmath>
#include <iostream>
#include <vector>

#include "algorithms.h"
#include "generator.h"
#include "range.h"
#include "experimental.h"

using namespace drange;

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

int main( )
{
   std::cout << "Hello, DRANGE world!" << std::endl;

   using IntVec = std::vector< int >;

   IntVec myVec { 1, 2, 3, 4, 5 };

   // Test Border.
   {
     Border< IntVec > border0;
     Border< IntVec > border1( myVec.begin( ) );
     Border< IntVec > bordef2( myVec.end(   ) );
   }

   // Test Element.
   {
     Element< IntVec > element0;
     Element< IntVec > element1( myVec.begin( ) );
     Element< IntVec > element2( myVec.end(   ) );
   }

   // Test Range.
   {

     Range myRange( myVec );

     // Test 'for_each'.
     for_each( myRange, [ ] ( int &val_ )
     {
       std::cout << "myRng Result: " << val_ << std::endl;
     } );

     // Test 'find'.
     if ( auto element = find( myRange, 3 ) )
     {
       std::cout << "Element found should be '3'.: " << *element << std::endl;
     }
     else
     {
       std::cout << "Error: No element '3' found." << std::endl;
     }

     // Test 'find_if'.
     if ( auto element = find_if( myRange, [ ] ( int &value_ )
          {
            return value_ == 4;
          } ) )
     {
       std::cout << "Element found should be '4'.: " << *element << std::endl;
     }
     else
     {
       std::cout << "Error: Element '4' not found." << std::endl;
     }

     // Test 'find_if'.
     if ( auto element = find_if( myRange, [ ] ( int &value_ )
          {
            return value_ == 6;
          } ) )
     {
       std::cout << "Error: Element found should be '6'.: " << *element << std::endl;
     }
     else
     {
       std::cout << "Element '6' (correctly) is not found." << std::endl;
     }

     // Test 'find_if_not'.
     if ( auto element = find_if_not( myRange, [ ] ( int &value_ )
          {
            return value_ == 7;
          } ) )
     {
       std::cout << "Element found is not '7'.: " << *element << std::endl;
     }
     else
     {
       std::cout << "Error: Element '7' found." << std::endl;
     }

  }

  // Test normal generator.
  auto gen = Counter( );
  while ( gen )
  {
    std::cout << "CoRoutine output: " << gen( ) << std::endl;
  }

  // Test range_for generator
  auto gen1 = Counter( );
  for ( auto nextItem : gen1  )
  {
    std::cout << "CoRoutine output: " << nextItem << std::endl;
  } 

  auto evenIntegers = Integers( 20 ) | Where( [ ] ( int n_ ) { return ( n_ % 2 ) == 0; } );

  // Test pipeable code.
#if 0
  auto nextPrime = Primes( 1000 );
  while ( nextPrime )
  {
    std::cout << "Prime number: " << nextPrime( ) << std::endl;
  }
#endif
  return 0;
}
