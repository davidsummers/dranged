#include <iostream>
#include <vector>

#include "drange.h"

using namespace drange;

int main( )
{
   std::cout << "Hello, DRANGE world!" << std::endl;

   std::vector< int > myVec { 1, 2, 3, 4, 5 };

   std::vector< int > myRange( myVec );

   drange::for_each( myVec, [ ] ( int &val_ )
   {
     std::cout << "myVec Result: " << val_ << std::endl;
   } );

   drange::for_each( myRange, [ ] ( int &val_ )
   {
     std::cout << "myRng Result: " << val_ << std::endl;
   } );

   Element< int > element;
   Border< int > border;


   return 0;
}
