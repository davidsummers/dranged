#pragma once

#include "dranged/pipes/pipe.h"
#include "dranged/core/range.h"
#include "dranged/helpers/send.h"

namespace dranged
{
#ifdef FUTURE
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
#endif
} // end namespace dranged
