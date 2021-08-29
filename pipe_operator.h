#pragma once

#include <type_traits>

#include "concepts.h"
#include "fwd.h"
#include "pipe.h"
#include "pipeline.h"
#include "range.h"
#include "send.h"

namespace dranged
{
#if 0
  // range >>= pipeline (rvalue ranges)
  template< typename Range, typename Pipeline, detail::IsARange< Range > = true, detail::IsAPipeline< Pipeline > = true >
  std::enable_if_t< !std::is_lvalue_reference< Range>::value > operator >>=( Range && range_, Pipeline && pipeline_ )
  {
    for ( auto &item : range_ )
    {
      Send( item, pipeline_ );
    }
  }
#endif
#if 1 // Used on line 181
  // range >>= pipeline (lvalue ranges)
  template< typename Range, typename Pipeline, detail::IsARange< Range > = true, detail::IsAPipeline< Pipeline > = true >
  std::enable_if_t< std::is_lvalue_reference< Range >::value > operator >>=( Range && range_, Pipeline && pipeline_ )
  {
    for ( auto &item : range_ )
    {
      Send( item, pipeline_ );
    }
  }
#endif
#if 1 // Used on line 163
  // range >>= pipe (lvalue ranges)
  template< typename Range, typename Pipe, detail::IsARange< Range > = true, detail::IsAPipe< Pipe > = true >
  std::enable_if_t< std::is_lvalue_reference< Range >::value > operator >>=( Range && range_, Pipe && pipe_ )
  {
    for ( auto &item : range_ )
    {
      Send( item, pipe_ );
    }
  }
#endif
#if 0
  // range >>= pipeline (lvalue ranges)
  template< typename Range, typename Pipeline, detail::IsARange< Range > = true, detail::IsAPipeline< Pipeline > = true >
  void operator >>=( Range && range_, Pipeline && pipeline_ )
  {
    for ( auto &item : range_ )
    {
      Send( item, pipeline_ );
    }
  }
#endif
#if 1 // Used on 173 and 182.
  // pipe >>= pipe

  template< typename Pipe1, typename Pipe2, detail::IsAPipe< Pipe1 > = true, detail::IsAPipe< Pipe2 > = true >
  auto operator >>=( Pipe1 && pipe1_, Pipe2 && pipe2_ )
  {
    return MakeGenericPipeline( pipe1_, pipe2_ ); // detail::CompositePipe< std::decay_t< Pipe1 >, std::decay_t< Pipe2 > >( FWD( pipe1_ ), FWD( pipe2_ ) );
  }
#endif
#if 1
  // pipe >>= pipeline

  template< typename Pipe, typename Pipeline, detail::IsAPipe< Pipe > = true, detail::IsAPipeline< Pipeline > = true >
  auto operator>>=( Pipe && pipe_, Pipeline && pipeline_ )
  {
    return MakeGenericPipeline( pipe_, pipeline_ );
  }
#endif
#if 0
  // pipeline >>= pipe

  template< typename Pipeline, typename Pipe, detail::IsAPipeline< Pipeline > = true, detail::IsAPipe< Pipe > = true >
  auto operator>>=( Pipeline && pipeline_, Pipe && pipe_ )
  {
    return MakeGenericPipeline( pipeline_, pipe_ );
  }
#endif
#if 0
  template< typename Pipe, typename Pipeline, typename = std::enable_if_t< std::is_base_of< PipelineBase, Pipeline >::value > >
  auto operator >>=( Pipe &&pipe_, Pipeline &&pipeline_ )
  {
    return GenericPipeline( pipe_, pipeline_ );
  }

  template< typename EndPipe, typename Pipeline, typename = std::enable_if_t< std::is_base_of< PipeSinkBase, EndPipe >::value > >
  auto operator >>=( Pipeline &&pipeline_, EndPipe &&pipe_ )
  {
    return GenericPipeline( pipe_, pipeline_ );
  }
#endif
} // end namespace dranged
