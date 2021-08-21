#pragma once

// CoRoutine Hello World
// Example from: https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html

#include <concepts>
#if defined( __linux__ ) || defined( WIN32 )
#define STD std
#include <coroutine>
#else
#define STD std::experimental
#include <experimental/coroutine>
#endif
#include <exception>
#include <iostream>

template < typename T >
struct Generator
{
  public:

    // Declarations

    struct promise_type;
    using HandleType = STD::coroutine_handle< promise_type >;

    struct promise_type
    {
      // Methods

      Generator get_return_object( )
      {
        return Generator( HandleType::from_promise( *this ) );
      }

      STD::suspend_always initial_suspend( )
      {
        return { };
      }

      STD::suspend_always final_suspend( ) noexcept
      {
        return { };
      }

      void unhandled_exception( )
      {
        m_Exception = std::current_exception( );
      }

#if defined( __linux__ ) || defined( WIN32 )
      template < std::convertible_to< T > From > // C++20 concept
      std::suspend_always yield_value( From &&from_ )
#else
      template < typename From > // C++20 concept
      STD::suspend_always yield_value( From &&from_ )
#endif
      {
        m_Value = std::forward< From >( from_ );
        return { };
      }

      void return_void( )
      {
      }

      // Data

      T m_Value = 0;

      std::exception_ptr m_Exception;

    };

    // Methods

    Generator( HandleType h_ )
      : m_HandleType( h_ )
    {
    }

    ~Generator( )
    {
      m_HandleType.destroy( );
    }

    explicit operator bool( )
    {
      Fill( );
      return !m_HandleType.done( );
    }

    T operator ( )( )
    {
      Fill( );
      m_Full = false;
      return std::move( m_HandleType.promise( ).m_Value );
    }

  private:

    // Method

    void Fill( )
    {
      if ( !m_Full )
      {
        m_HandleType( );

        if ( m_HandleType.promise( ).m_Exception )
        {
          std::rethrow_exception( m_HandleType.promise( ).m_Exception );
        }

        m_Full = true;
      }
    }

    // Data

    bool m_Full = false;

    HandleType m_HandleType;
};

#ifdef __CPP20_GENERATOR_EXAMPLE_CODE__

Generator< uint64_t > Counter( )
{
  for ( uint64_t i = 0; i < 3; )
  {
    co_yield i++;
  }
}


int main( )
{
  auto gen = Counter( );
  while ( gen )
  {
    std::cout << "CoRoutine output: " << gen( ) << std::endl;
  }
}

#endif // __CPP20_GENERATOR_EXAMPLE_CODE__

