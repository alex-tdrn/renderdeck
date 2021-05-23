#include "clk/algorithms/mix_colors.h"

namespace clk::algorithms
{
mix_colors::mix_colors()
{
	register_port(_factor);
	register_port(_color_a);
	register_port(_color_b);
	register_port(_mixed_color);
}

auto mix_colors::get_name() const noexcept -> std::string const&
{
	static std::string name = "Mix Colors";
	return name;
}

void mix_colors::update()
{
	float f = _factor.get() / 100.0f;
	*_mixed_color = f * _color_a.get() + (1 - f) * _color_b.get();
}
} // namespace clk::algorithms