#pragma once

namespace dranged
{

struct PipelineBase
{
};

template< typename HeadPipe, typename TailPipeline >
class GenericPipeline : public PipelineBase
{
  public:

    GenericPipeline( HeadPipe headPipe_, TailPipeline tailPipeline_ )
      : m_HeadPipe( headPipe_ )
      , m_TailPipeline( tailPipeline_ )
    {
    }

    template< typename ValueType >
    bool OnReceive( ValueType && value_, bool end_ )
    {
      return m_HeadPipe.template OnReceive< ValueType >( value_, m_TailPipeline, end_ );
    }

  private:

    HeadPipe m_HeadPipe;
    TailPipeline m_TailPipeline;
};

template< typename HeadPipe, typename TailPipeline >
auto MakeGenericPipeline( HeadPipe && headPipe_, TailPipeline && tailPipeline_ )
{
    return GenericPipeline< std::decay_t< HeadPipe >, std::decay_t< TailPipeline > >{ FWD( headPipe_ ), FWD( tailPipeline_ ) };
}

} // end namespace dranged
