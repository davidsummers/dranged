#pragma once

#include "dranged/helpers/fwd.h"

namespace dranged
{

  // A PipeBase is the base class for any pipe object.
  struct PipeBase
  {
  };

  namespace detail
  {
#ifdef FUTURE
    template< typename Pipe1, typename Pipe2 >
    struct CompositePipe : public PipeBase
    {
      template< typename Pipe1p, typename Pipe2p >
      CompositePipe( Pipe1p && pipe1_, Pipe2p && pipe2_ )
        : m_Pipe1( FWD( pipe1_ ) )
        , m_Pipe2( FWD( pipe2_ ) )
      {
      }

      Pipe1 m_Pipe1;
      Pipe2 m_Pipe2;
    };
#endif
  } // end namespace detail

} // end namespace dranged
