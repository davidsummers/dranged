#pragma once

#include <functional>
#include <memory>

namespace drange
{

// Forward declarations.
template< typename Container >
class Element;

// Enums
enum class stopable
{
  dont_stop,
  stop
};

/////////////////////////////////////////
///
/// for_each
///
template < typename Func, typename Rng >
void for_each( Rng &rng_, Func &&f_ )
{
  auto fn = std::function{ std::forward< Func >( f_ ) };
  for ( auto itr = rng_.begin( );
        itr != rng_.end( );
        ++itr )
  {
    auto element = itr.element_after( );
    fn( *element );
  }
}

////////////////////////////////////////
///
/// for_each_stopable
///
template < typename Func, typename Rng >
auto for_each_stopable( Rng &rng_, Func &&f_ )
{
  auto fn = std::function{ std::forward< Func >( f_ ) };

  for ( auto itr = rng_.begin( );
        itr != rng_.end( );
        ++itr )
  {
    auto element = itr.element_after( );
    if ( fn( *element ) == stopable::stop )
    {
      element.SetValid( true );
      return element;
    }
  }

  // Element m_Valid will be false which denotes nothing found.
  return rng_.end( ).element_before( );
}

////////////////////////////////////////
///
/// find
///
template < typename Rng, typename Type >
auto find( Rng &rng_, const Type &value_ )
{
  using container = typename Rng::container;

  Element< container > foundElement = for_each_stopable( rng_, [ &value_ ] ( Type &rngValue_ )
  {
    return rngValue_ == value_ ? stopable::stop : stopable::dont_stop;
  } );

  return foundElement;
}

///////////////////////////////////////
///
/// find_if
///
template < typename Rng, typename Func >
auto find_if( Rng &rng_, Func &&f_ )
{
  using container = typename Rng::container;

  auto fn = std::function{ std::forward< Func >( f_ ) };

//  Element< container > foundElement;

  for ( auto itr = rng_.begin( );
        itr != rng_.end( );
        ++itr )
  {
    Element< container > element = itr;
    if ( fn( *element ) )
    {
      element.SetValid ( true );
      return element;
    }
  }

  return rng_.end( ).element_before( );
}

} // end namespace drange
