#pragma once

#include "rsp/base/Node.hpp"
#include "rsp/util/ColorRGB.hpp"

#include <array>

namespace rsp::nodes
{
class RandomColorSource final : public Node
{
private:
	OutputPort<ColorRGB> color{"Color"};

public:
	RandomColorSource()
	{
		registerPort(color);
	}

private:
	void update() override;

public:
	std::string const& getName() const override
	{
		static std::string name = "Random Color Source";
		return name;
	}
};

} // namespace rsp::nodes