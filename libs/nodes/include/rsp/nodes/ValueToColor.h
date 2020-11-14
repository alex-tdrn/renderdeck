#pragma once

#include "rsp/base/Node.hpp"
#include "rsp/util/ColorRGB.hpp"

#include <array>

namespace rsp::nodes
{
class ValueToColor final : public Node
{
private:
	InputPort<float> value{"Value"};
	OutputPort<ColorRGB> color{"Color"};

public:
	ValueToColor()
	{
		registerPort(value);
		registerPort(color);
	}

private:
	void update() override;

public:
	std::string const& getName() const override
	{
		static std::string name = "Value To Color";
		return name;
	}
};

} // namespace rsp::nodes