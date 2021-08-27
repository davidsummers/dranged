#pragma once

// A Range is a pair of begin/end Border.

#include "border.h"
#include "element.h"

namespace dranged
{

template < class Container >
class Range
{
  public:

    using container = Container;

    Range( container &container_ )
      : m_BeginIndex( Border< container >( container_.begin( ) ) )
      , m_EndIndex(   Border< container >( container_.end(   ) ) )
    {
    }

    Border< container > begin( )
    {
      return m_BeginIndex;
    }
    
    Border< container > end( )
    {
      return m_EndIndex;
    }

  private:

    Border< container > m_BeginIndex;
    Border< container > m_EndIndex;
};


} // End namespace dranged
