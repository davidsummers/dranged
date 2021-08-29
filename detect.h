#pragma once

#include <type_traits>

namespace dranged
{
  namespace detail
  {
    template< typename... >
    using TryToInstantiate = void;

    using DisregardThis = void;

    template< template< typename ... > class Expression, typename Attempt, typename ... Ts >
    struct IsDetectedImpl : std::false_type
    {
    };

    template< template< typename ... > class Expression, typename ... Ts >
    struct IsDetectedImpl< Expression, TryToInstantiate< Expression< Ts ... > >, Ts ... > : std::true_type
    {
    };

    template< template< typename ... > class Expression, typename ... Ts >
    constexpr bool IsDetected = IsDetectedImpl< Expression, DisregardThis, Ts ...>::value;

  }
} // end namespace dranged

