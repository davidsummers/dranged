#pragma once

#include <functional>
#include <memory>

namespace drange
{

template < typename T >
class Border
{
  public:

  private:
};

template < typename T >
class Element
{
  public:

    using pointer = T *;

  private:

    pointer m_Ptr = nullptr;
};

template < typename Container >
class Range
{
  public:

    using container = Container;
    using iterator  = typename Container::iterator;

    Range( const container &container_ )
      : m_BeginIndex( container_.begin( ) )
      , m_EndIndex( container_.end( ) )
    {
    }

    iterator begin( )
    {
      return m_BeginIndex;
    }
    
    iterator end( )
    {
      return m_EndIndex;
    }

  private:

    container m_BeginIndex;
    container m_EndIndex;
};

template < typename Rng, typename Type >
void for_each_item( Rng &rng_, std::function< void ( Type &val ) > func_ )
{
  for ( auto itr = rng_.begin( );
        itr != rng_.end( );
        ++itr )
  {
    func_( *itr );
  }
}

} // End namespace drange

