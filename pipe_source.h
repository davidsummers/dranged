#pragma once

#include "pipe.h"
#include "range.h"
#include "send.h"

namespace dranged
{

template< typename Container >
class SourcePipe : public PipeBase
{
  public:

    SourcePipe( Container &container_ )
      : m_Container( container_ )
    {
    }

    typename Container::iterator begin( )
    {
      return m_Container.begin( );
    }

    typename Container::iterator end( )
    {
      return m_Container.end( );
    }

  private:

    Container &m_Container;
};

} // end namespace dranged
