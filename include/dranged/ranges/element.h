#pragma once

// Element - Like iterator but is nullable and can't point past begin/end.

#include "border.h"

namespace dranged
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

    Element( const Border< Container > &itr_, const bool valid_ = false )
      : m_Itr( itr_.element_after( ).m_Itr )
      , m_Valid( valid_ )
    {
    }

    explicit operator bool( )
    {
      return m_Valid;
    }

    void SetValid( const bool val_ )
    {
      m_Valid = val_;
    }

    Border< Container > border_before( )
    {
      Border< Container > itr = m_Itr;
      --itr;
      return itr;
    }

    Border< Container > border_after( )
    {
      Border< Container > itr = m_Itr;
      return itr;
    }

    // Prefix
    Element &operator ++( )
    {
      ++m_Itr;
      return *this;
    }

    // Postfix
    Element operator ++( int )
    {
      Element old = m_Itr;
      m_Itr++;
      return old;
    }

    // Prefix
    Element &operator --( )
    {
      --m_Itr;
      return *this;
    }

    // Postfix
    Element operator --( int )
    {
      Element old = m_Itr;
      m_Itr--;
      return old;
    }

    value_type &operator *( )
    {
      return *m_Itr;
    }

    bool operator ==( const Element &rhs_ ) const
    {
      return m_Itr == rhs_.m_Itr;
    }

    bool operator !=( const Element &rhs_ ) const
    {
      return !( *this == rhs_ );
    }

  private:

    bool     m_Valid = false;
    iterator m_Itr;
};

} // end namespace dranged
