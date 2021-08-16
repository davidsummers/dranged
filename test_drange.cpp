#include <iostream>
#include <vector>

#include "algorithms.h"
#include "range.h"

using namespace drange;

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

  return 0;
}
