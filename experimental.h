#pragma once

// Experimental Pipeable classes


// A generator operator is an invokable object templatized on
// an operator class. The template type Op represents a LINQ-like
// operator that works on lazy generators.
template < typename Op >
struct generator_operator
{
  template< typename Gen, typename... Rest >
  auto operator( )( Gen &&gen_, Rest &&...rest_ ) const
  {
    return Op::exec( std::move( gen_ ), std::move( rest_ )... );
  }
};

// Select
class select_op : public generator_operator< select_op >
{
    friend struct generator_operator< select_op >;

    template< typename T, typename Fun >
    static generator< typename std::result_of< Fun( T ) >::type >
    exec( generator< T > gen_, Fun fun_ )
    {
        for ( auto n : gen_)
        {
          __yield_value fun_( n );
        }
    }
};

constexpr pipeable_factory< select_op > Select { };


// Where
class where_op : public generator_operator< where_op >
{
  friend struct generator_operator< where_op >;

  template< typename T, typename Fun >
  static generator< T > exec( generator< T > gen_, Fun fun_ )
  {
    for ( auto n : gen_ )
    {
      if ( fun_( n ) )
      {
        __yield_value n;
      }
    }
  }
};

constexpr pipeable_factory< where_op > Where { };
