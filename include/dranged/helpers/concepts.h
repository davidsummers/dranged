#pragma once

#include "dranged/helpers/detect.h"
#include "dranged/pipes/pipe.h"
#include "dranged/pipes/pipeline.h"

namespace dranged
{
    namespace detail
    {
        namespace impl
        {
            // definition of range
            
            namespace adl
            {
                using std::begin;
                using std::end;

                template< typename T >
                using BeginExpression = decltype( begin( std::declval< T & >( ) ) );

                template< typename T >
                using EndExpression = decltype( end( std::declval< T & >( ) ) );
            }
            
            template< typename Range >
            constexpr bool RangeExpressionDetected = detail::IsDetected< adl::BeginExpression, Range > && detail::IsDetected< adl::EndExpression, Range >;
            
            // Definition of a Range.
            template< typename Range >
            using IsARange = std::enable_if_t< RangeExpressionDetected< Range >, bool >;
            
            // Definition of Pipe.
            template< typename Pipe >
            using IsAPipe = std::enable_if_t< std::is_base_of< PipeBase, Pipe >::value, bool >;

            // Definition of Pipeline.
            template< typename Pipeline >
            using IsAPipeline = std::enable_if_t< std::is_base_of< PipelineBase, Pipeline >::value, bool >;
        }
        
        template< typename Range >
        using IsARange = impl::IsARange< std::remove_reference_t< Range > >;
        
        template< typename Pipe >
        using IsAPipe = impl::IsAPipe< std::remove_reference_t< Pipe> >;

        template< typename Pipeline >
        using IsAPipeline = impl::IsAPipeline< std::remove_reference_t< Pipeline > >;

    } // end namespace detail
} // end namespace dranged

