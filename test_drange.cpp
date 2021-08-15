#include <iostream>
#include <vector>

#include "drange.h"

using namespace drange;

int main( )
{
   std::cout << "Hello, DRANGE world!" << std::endl;

   std::vector< int > myVec { 1, 2, 3, 4, 5 };

   std::vector< int > myRange( myVec );

   for ( auto itr = myVec.begin( );
         itr != myVec.end( );
         ++itr )
   {
     std::cout << "myVec: " << *itr << std::endl;
   }

   for ( auto itr = myRange.begin( );
         itr != myRange.end( );
         ++itr )
   {
     std::cout << "myRange: " << *itr << std::endl;
   }

#if 0
   drange::for_each_item( myVec, [ ] ( int &val_ )
   {
     std::cout << val_ << std::endl;
   } );
#endif
//   Element< int > element;
//   Border< int > border;


   return 0;
}
