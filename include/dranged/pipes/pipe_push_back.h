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
    bool OnReceive( T && value_, bool end_ )
    {
      if ( end_ )
      {
        return false; // Stop.
      }

      m_Container.push_back( value_ );
      return true; // Continue
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
