#pragma once

#include "rsp/base/Node.hpp"
#include "rsp/base/Port.hpp"
#include "rsp/util/ColorRGB.hpp"

#include <string>
#include <unordered_set>

namespace rsp::nodes
{
class GrayscaleColorNode final : public Node
{
private:
	InputPort<ColorRGB> inputColor{"Color"};
	OutputPort<ColorRGB> outputColor{"Color"};

public:
	GrayscaleColorNode()
	{
		registerPort(inputColor);
		registerPort(outputColor);
	}

private:
	void update() override;

public:
	auto getName() const -> std::string const& override
	{
		static std::string name = "Grayscale Color Node";
		return name;
	}
};

} // namespace rsp::nodes