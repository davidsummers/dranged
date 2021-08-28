#pragma once

#include "range.h"

namespace dranged
{

template< typename PIPELINE, typename RANGE >
void operator >>=( RANGE && rng_, PIPELINE && pipeline_ )
{
  for ( auto &item : rng_ )
  {
    Send( item, pipeline_ );
  }
};

} // end namespace dranged
