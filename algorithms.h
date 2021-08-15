#pragma once

#include <functional>
#include <memory>

namespace drange
{

template < typename Rng, typename F >
void for_each( Rng &rng_, F && f_ )
{
  auto fn = std::function{ std::forward< F >( f_ ) };
  for ( auto itr = rng_.begin( );
        itr != rng_.end( );
        ++itr )
  {
    auto element = itr.element_after( );
    fn( *element );
  }
}

} // end namespace drange
