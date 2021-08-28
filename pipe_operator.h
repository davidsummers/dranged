#pragma once

#include "range.h"

namespace dranged
{

#if 0
template< typename PIPELINE, typename RANGE >
void operator >>=( RANGE && rng_, PIPELINE && pipeline_ )
{
  for ( auto &item : rng_ )
  {
    Send( item, pipeline_ );
  }
};

#endif

} // end namespace dranged
