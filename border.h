#pragma once

// Border - Like iterator but can't be deferenced.

namespace drange
{

// Forward declare Element
template< typename Container >
class Element;

template < typename Container >
class Border
{
  public:

    using iterator = typename Container::iterator;

    Border( )
      : m_Itr( )
    {
    }

    Border( iterator itr_ )
      : m_Itr( itr_ )
    {
    }

    Element< Container > element_before( ) const
    {
      Border itr = m_Itr;
      --itr;
      Element< Container > element( itr );
      return element;
    }

    Element< Container > element_after( ) const
    {
      Element< Container > element( m_Itr );
      return element;
    }

    // Prefix
    Border &operator ++( )
    {
      ++m_Itr;
      return *this;
    }

    // Postfix
    Border operator ++( int )
    {
      Border old = *this;
      m_Itr++;
      return old;
    }

    // Prefix
    Border &operator --( )
    {
      --m_Itr;
      return *this;
    }

    // Postfix
    Border operator --( int )
    {
      Border old = *this;
      m_Itr--;
      return old;
    }

    bool operator ==( const Border &rhs_ )
    {
      return m_Itr == rhs_.m_Itr;
    }
   
    bool operator !=( const Border &rhs_ )
    {
      return !( *this == rhs_ );
    }

  private:

    iterator m_Itr;
};

} // end namespace drange
