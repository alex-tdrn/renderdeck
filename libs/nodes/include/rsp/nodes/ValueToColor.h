#pragma once

#include "rsp/base/Node.hpp"
#include "rsp/base/Port.hpp"
#include "rsp/util/ColorRGB.hpp"

#include <string>
#include <unordered_set>

namespace rsp::nodes
{
class ValueToColor final : public Node
{
public:
	ValueToColor();

	auto getName() const -> std::string const& override;

private:
	InputPort<float> value{"Value"};
	OutputPort<ColorRGB> color{"Color"};

	void update() override;
};

} // namespace rsp::nodes