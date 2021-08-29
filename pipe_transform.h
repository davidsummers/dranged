#pragma once

#include "pipe.h"

namespace dranged
{

template< typename FUNCTION >
class TransformPipe : public PipeBase
{
  public:

    explicit TransformPipe( FUNCTION fun_ )
      : m_Function( fun_ )
    {
    }

    template< typename VALUE, typename TailPipeline >
    void OnReceive( VALUE && value_, TailPipeline && tailPipeline_ )
    {
      Send( m_Function( value_ ), tailPipeline_ );
    }

  private:

    FUNCTION m_Function;
};

template< typename Function >
TransformPipe< Function > Transform( Function && function_ )
{
  return TransformPipe< Function >{ function_ };
}

} // end namespace dranged
