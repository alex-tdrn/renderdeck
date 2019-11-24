#include "rshp/gui/nodes/InputDataPort.h"
#include "rshp/base/port/DataPort.hpp"
#include "rshp/gui/ImGuiUtilities.hpp"
#include "rshp/gui/Stylesheet.hpp"
#include "rshp/gui/nodes/OutputPort.h"

namespace rshp::gui
{
InputDataPort::InputDataPort(rshp::base::DataPort* port) : InputPort(port), port(port)
{
}

void InputDataPort::draw()
{
	ax::NodeEditor::BeginPin(id, ax::NodeEditor::PinKind::Input);

	ImGui::Text(port->getName().c_str());

	dataRequested = port->getRequestCount() > dataRequests;
	dataRequests = port->getRequestCount();
	if(dataRequested && !port->isConnected())
		anchorOffset.play();

	auto anchorPosition = calculateAnchorPosition();
	auto anchorColor = ImGui::ColorFromHash(port->getDataTypeHash());

	if(port->isConnected())
		ImGui::DrawCircle(anchorPosition, 5, anchorColor);
	else
		ImGui::DrawCircle(anchorPosition, 5, {0, 0, 0, 1}, anchorColor);

	ax::NodeEditor::PinPivotRect(anchorPosition, anchorPosition);

	ax::NodeEditor::EndPin();
}

ImVec2 InputDataPort::calculateSize() const
{
	return ImGui::CalcTextSize(port->getName().c_str());
}

void InputDataPort::drawLink()
{
	if(connection != nullptr)
	{
		auto portColor = ImGui::ColorFromHash(port->getDataTypeHash());
		ax::NodeEditor::Link(linkID, connection->getID(), id, portColor, Stylesheet::getCurrentSheet().linkThickness);

		if(dataRequested)
		{
			ax::NodeEditor::Flow(linkID, portColor);
			dataRequested = false;
		}
	}
}

} // namespace rshp::gui