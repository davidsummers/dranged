#pragma once

#include "pipe.h"

namespace dranged
{

template< typename Container >
class PushBackPipe : PipeBase
{
  public:

    explicit PushBackPipe( Container &container_ )
      : m_Container( container_ )
    {
    }


    template< typename T >
    void OnReceive( T && value_ )
    {
      m_Container.push_back( value_ );
    }

  private:

    Container &m_Container;
};

template< typename Container >
PushBackPipe< Container > PushBack( Container & container_ )
{
  return PushBackPipe< Container >( container_ );
}

} // end namespace dranged
