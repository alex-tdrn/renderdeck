#pragma once

#include "rsp/base/port.hpp"

#include <string>
#include <vector>

namespace rsp
{
class algorithm
{
public:
	algorithm(const algorithm&) = delete;
	algorithm(algorithm&&) = delete;
	auto operator=(const algorithm&) = delete;
	auto operator=(algorithm&&) = delete;
	virtual ~algorithm() = default;

	virtual auto get_name() const noexcept -> std::string const& = 0;
	virtual void update() = 0;
	auto get_input_ports() const noexcept -> std::vector<rsp::input_port*> const&;
	auto get_output_ports() const noexcept -> std::vector<rsp::output_port*> const&;

protected:
	algorithm() = default;

	void register_port(rsp::input_port& port);
	void register_port(rsp::output_port& port);

private:
	std::vector<rsp::input_port*> input_ports;
	std::vector<rsp::output_port*> output_ports;
};

inline auto algorithm::get_input_ports() const noexcept -> std::vector<rsp::input_port*> const&
{
	return input_ports;
}

inline auto algorithm::get_output_ports() const noexcept -> std::vector<rsp::output_port*> const&
{
	return output_ports;
}

inline void algorithm::register_port(rsp::input_port& port)
{
	if(std::find(input_ports.begin(), input_ports.end(), &port) != input_ports.end())
		return;
	input_ports.emplace_back(&port);
}

inline void algorithm::register_port(rsp::output_port& port)
{
	if(std::find(output_ports.begin(), output_ports.end(), &port) != output_ports.end())
		return;
	output_ports.emplace_back(&port);
}
} // namespace rsp