#pragma once

#include <vector>

#include "pipe.h"

namespace dranged
{

template< typename VALUE_TYPE >
class ReversePipe : public PipeBase
{
  public:

    using ContainerType = std::vector< VALUE_TYPE >;

    explicit ReversePipe( )
    {
    }

    template< typename TailPipeline >
    bool OnReceive( VALUE_TYPE && value_, TailPipeline && tailPipeline_, bool end_ )
    {
      if ( !end_ )
      {
        m_Container.push_back( value_ );
        return true; // Continue;
      }

      for ( auto itr = m_Container.rbegin( );
            itr != m_Container.rend( );
            ++itr )
      {
        auto const &item = *itr;
        if ( !Send( m_Function( item ), tailPipeline_, false ) ) // false means "this is not the end".
        {
          Send( m_Function( item ), tailPipeline_, true ); // true means "this is the end".
          break;
        }
      }

      return end_;
    }

  private:

     ContainerType m_Container;
};

template< typename VALUE_TYPE >
ReversePipe< VALUE_TYPE > Reverse( )
{
  return ReversePipe< VALUE_TYPE >( );
}

} // end namespace dranged
