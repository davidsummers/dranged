#pragma once

template< typename T, typename Pipeline >
bool Send( T && value_, Pipeline && pipeline_, bool end_ )
{
  return pipeline_.OnReceive( value_, end_ );
}
