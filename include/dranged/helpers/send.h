#pragma once

template< typename T, typename Pipeline >
bool Send( T && value_, Pipeline && pipeline_ )
{
  return pipeline_.OnReceive( value_ );
}
