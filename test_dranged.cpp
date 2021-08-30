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


  return 0;
}
