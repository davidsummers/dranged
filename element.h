#pragma once

// Element - Like iterator but is nullable and can't point past begin/end.

#include "border.h"

namespace drange
{

template < typename Container >
class Element
{
  public:

    using iterator = typename Container::iterator;
    using value_type = typename Container::value_type;

    Element( )
      : m_Itr( )
    {
    }

    Element( iterator itr_ )
      : m_Itr( itr_ )
    {
    }
#if 0
    explicit operator bool( )
    {
      return m_Valid;
    }

    Border< Container > border_before( )
    {
      return nullptr;
    }

    Border< Container > border_after( )
    {
      return nullptr;
    }

    Border< Container > operator ++( )
    {
      return nullptr;
    }

    Border< Container > operator --( )
    {
      return nullptr;
    }
#endif
    value_type &operator *( )
    {
      return *m_Itr;
    }

  private:

    bool     m_Valid = false;
    iterator m_Itr;
};

} // end namespace drange.
