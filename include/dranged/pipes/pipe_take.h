#pragma once

#include "pipe.h"

namespace dranged
{

template< typename TYPE >
class TakePipe : public PipeBase
{
  public:

    explicit TakePipe( const uint64_t total_ )
      : m_Total( total_ )
    {
    }

    template< typename VALUE_TYPE, typename TailPipeline >
    bool OnReceive( VALUE_TYPE && value_, TailPipeline && tailPipeline_, bool end_ )
    {
      if ( end_ )
      {
        return Send( value_, tailPipeline_, end_ );
      }

      if ( m_CurrentCount >= m_Total )
      {
        return false; // Stop pipe.
      }

      m_CurrentCount++;

      return Send( value_, tailPipeline_, end_ );
    }

  private:

    uint64_t m_CurrentCount = 0;
    uint64_t m_Total = 0;
};

template< typename TYPE >
TakePipe< TYPE > Take( const uint64_t total_ )
{
  return TakePipe< TYPE >{ total_ };
}

} // end namespace dranged
