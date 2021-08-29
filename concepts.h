#pragma once

#include "detect.h"
#include "pipe.h"
#include "pipeline.h"

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

            // Definition of a SourcePipe
            template< typename SourcePipe >
            using IsASourcePipe = std::enable_if_t< std::is_base_of< PipeSourceBase, SourcePipe >::value, bool >;

            // Definition of a SinkPipe.
            template< typename SinkPipe >
            using IsASinkPipe = std::enable_if_t< std::is_base_of< PipeSinkBase, SinkPipe >::value, bool >;
        }
        
        template< typename Range >
        using IsARange = impl::IsARange< std::remove_reference_t< Range > >;
        
        template< typename Pipe >
        using IsAPipe = impl::IsAPipe< std::remove_reference_t< Pipe> >;

        template< typename Pipeline >
        using IsAPipeline = impl::IsAPipeline< std::remove_reference_t< Pipeline > >;

        template< typename SourcePipe >
        using IsASourcePipe = impl::IsASourcePipe< std::remove_reference_t< SourcePipe > >;

        template< typename SinkPipe >
        using IsASinkPipe = impl::IsASinkPipe< std::remove_reference_t< SinkPipe > >;
    } // end namespace detail
} // end namespace dranged

