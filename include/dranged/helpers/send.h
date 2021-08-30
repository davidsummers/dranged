#pragma once

template< typename T, typename Pipeline >
void Send( T && value_, Pipeline && pipeline_ )
{
  pipeline_.OnReceive( value_ );
}
