#include "clk/algorithms/init.hpp"
#include "clk/algorithms/color.hpp"
#include "clk/algorithms/math.hpp"

namespace clk::algorithms
{
void init()
{
	clk::algorithm::register_factory<random_integer>();
	clk::algorithm::register_factory<random_float>();
	clk::algorithm::register_factory<add_integers>();
	clk::algorithm::register_factory<subtract_integers>();
	clk::algorithm::register_factory<multiply_integers>();
	clk::algorithm::register_factory<divide_integers>();
	clk::algorithm::register_factory<modulo>();
	clk::algorithm::register_factory<add_floats>();
	clk::algorithm::register_factory<subtract_floats>();
	clk::algorithm::register_factory<multiply_floats>();
	clk::algorithm::register_factory<divide_floats>();
	clk::algorithm::register_factory<pow>();
	clk::algorithm::register_factory<nth_root>();
	clk::algorithm::register_factory<rad_to_deg>();
	clk::algorithm::register_factory<deg_to_rad>();
	clk::algorithm::register_factory<sin>();
	clk::algorithm::register_factory<cos>();

	clk::algorithm::register_factory<add_colors>();
	clk::algorithm::register_factory<subtract_colors>();
	clk::algorithm::register_factory<multiply_colors>();
	clk::algorithm::register_factory<divide_colors>();
	clk::algorithm::register_factory<decompose_color>();
	clk::algorithm::register_factory<grayscale>();
	clk::algorithm::register_factory<mix_colors>();
	clk::algorithm::register_factory<random_color>();
	clk::algorithm::register_factory<value_to_color>();
	clk::algorithm::register_factory<apply_gamma>();
	clk::algorithm::register_factory<remove_gamma>();
	clk::algorithm::register_factory<tonemap_reinhard>();
	clk::algorithm::register_factory<tonemap_filmic_aces>();
}
} // namespace clk::algorithms