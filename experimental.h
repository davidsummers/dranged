#pragma once

// Taken from a BLOG at
// https://paoloseverini.wordpress.com/2015/03/15/range-comprehensions-with-c-lazy-generators

#include <type_traits>

#include "generator.h"

// Experimental Pipeable classes

template< typename Binder >
struct pipeable
{
    // A forwarding call wrapper generated by std::bind.
    Binder m_binder;
 
    pipeable( Binder pipeableBinder_ )
        : m_binder( std::move( pipeableBinder_ ) )
    {
    }
 
    // Executes the call operator of a bound method, passing a generator
    // as placeholder argument.
    template< typename T, typename Pipe >
    static auto pipe( Generator< T > && gen_, Pipe && pipe_ )
    {
      return pipe_.m_binder( std::forward< Generator< T > >( gen_ ) );
    } 
};

template< typename Op >
struct pipeable_factory
{
    // an invokable object of an operator class.
    Op m_op;
 
    // Binds _op to its arguments, using a placeholder for the first argument.
    template< typename ... Args >
    auto operator( )( Args && ... args_ ) const
    {
        return make_pipeable( std::bind( m_op,
                                         std::placeholders::_1,
                                         std::move( args_ ) ... ) );
    }
 
private:
    template< typename Binder >
    static pipeable< Binder> make_pipeable( Binder pipeableBinder_ )
    {
        return { std::move( pipeableBinder_ ) };
    }
};

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
    static Generator< typename std::invoke_result< Fun( T ) >::type >
    exec( Generator< T > gen_, Fun fun_ )
    {
        for ( auto n : gen_)
        {
          co_yield( fun_( n ) );
        }
    }
};

constexpr pipeable_factory< select_op > Select { };


// Where
class where_op : public generator_operator< where_op >
{
  friend struct generator_operator< where_op >;

  template< typename T, typename Fun >
  static Generator< T > exec( Generator< T > gen_, Fun fun_ )
  {
    for ( auto n : gen_ )
    {
      if ( fun_( n ) )
      {
        co_yield n;
      }
    }
  }
};

constexpr pipeable_factory< where_op > Where { };

Generator< int > GenRange( int from_, int count_ )
{
  for ( int i = 0; i < count_; ++i )
  {
    co_yield( from_ + i );
  }
}


class all_op : public generator_operator< all_op >
{
    friend struct generator_operator< all_op >;
 
    template< typename T, typename Fun >
    static bool exec( Generator< T > gen_, Fun fun_ )
    {
        for ( auto n : gen_ )
        {
            if ( !fun_( n ) )
            {
                return false;
            }
        }

        return true;
    }
};

constexpr pipeable_factory< all_op > All{ };

template< typename T, typename Pipeable >
auto operator |( Generator< T> && src_, Pipeable && pipe_ )
{
    return Pipeable::pipe( std::forward< Generator< T> >( src_ ),
                           std::forward< Pipeable >( pipe_ ) );
}
