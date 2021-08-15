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

     for_each( myRange, [ ] ( int &val_ )
     {
       std::cout << "myRng Result: " << val_ << std::endl;
     } );

     if ( auto element = find( myRange, 3 ) )
     {
       std::cout << "Element found: " << *element << std::endl;
     }
     else
     {
       std::cout << "Error No element '3' found." << std::endl;
     }

     if ( auto element = find_if( myRange, [ ] ( int &value_ )
          {
            return value_ == 4;
          } ) )
     {
       std::cout << "Element found: " << *element << std::endl;
     }
     else
     {
       std::cout << "Element '4' not found." << std::endl;
     }

     if ( auto element = find_if( myRange, [ ] ( int &value_ )
          {
            return value_ == 6;
          } ) )
     {
       std::cout << "Element found: " << *element << std::endl;
     }
     else
     {
       std::cout << "Element '6' not found." << std::endl;
     }

  }

  return 0;
}
