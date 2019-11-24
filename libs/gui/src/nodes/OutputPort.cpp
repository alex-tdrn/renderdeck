#include "rshp/gui/nodes/OutputPort.h"
#include "rshp/gui/nodes/InputPort.h"
#include "rshp/gui/Stylesheet.hpp"

namespace rshp::gui
{
		
	OutputPort::OutputPort(rshp::base::Port* port)
		: AbstractPort(port)
	{
		for(auto connection : port->getConnections())
			if(auto pin = getPinForPort(connection); pin != nullptr)
				connect(pin);
	}

	ImVec2 OutputPort::calculateAnchorPosition() const
	{
		auto& currentStyle = Stylesheet::getCurrentSheet();
		auto min = ImGui::GetItemRectMin();
		auto max = ImGui::GetItemRectMax();
		auto h = max.y - min.y;
		auto x = max.x + anchorOffset.get(currentStyle.animatedAnchorOffset,
			currentStyle.anchorOffset, currentStyle.animatedAnchorOffsetDuration, AnimationCurve::spring);
		auto y = min.y + h / 2;
		return {x, y};
	}

	bool OutputPort::canConnect(AbstractPort* inputPort)
	{
		if(!dynamic_cast<InputPort*>(inputPort))
			return false;
		return inputPort->canConnect(this);
	}

	void OutputPort::connect(AbstractPort* inputPort)
	{
		assert(dynamic_cast<InputPort*>(inputPort));

		dynamic_cast<InputPort*>(inputPort)->connect(this);
	}

}