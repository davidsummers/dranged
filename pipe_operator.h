#pragma once

#include "range.h"
#include "send.h"

namespace dranged
{

template< typename StartPipe, typename Pipeline >
void operator >>=( StartPipe &&startPipe_, Pipeline &&pipeline_ )
{
  for ( auto &item : startPipe_ )
  {
    Send( item, pipeline_ );
  }
}

} // end namespace dranged
