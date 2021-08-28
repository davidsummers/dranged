#pragma once

namespace dranged
{

// A PipeBase is the base class for any pipe object.
struct PipeBase
{
};

// A PipeSource is something that can send data into a pipeline without anything previous.
struct PipeSourceBase
{
};

// A PipeSink is something that can receive data from a pipeline and terminate the pipeline.
struct PipeSinkBase
{
};

} // end namespace dranged
