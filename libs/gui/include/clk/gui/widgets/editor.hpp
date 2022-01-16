#pragma once

#include "clk/gui/widgets/data_writer.hpp"
#include "clk/gui/widgets/widget.hpp"

#include <imgui.h>

namespace clk::gui
{
class editor : public widget
{
public:
	editor() = default;
	editor(editor const&) = delete;
	editor(editor&&) = delete;
	auto operator=(editor const&) -> editor& = delete;
	auto operator=(editor&&) -> editor& = delete;
	~editor() override = default;
};

template <typename data_type>
class editor_of : public editor
{
public:
	editor_of() = default;
	editor_of(editor_of const&) = delete;
	editor_of(editor_of&&) = delete;
	auto operator=(editor_of const&) -> editor_of& = delete;
	auto operator=(editor_of&&) -> editor_of& = delete;
	~editor_of() override = default;

	auto clone() const -> std::unique_ptr<widget> override;
	void copy(widget const& other) override;

	void set_data_writer(data_writer<data_type> data);
	virtual auto draw_contents(data_type& data) const -> bool;

private:
	data_writer<data_type> _data;

	void draw_contents() const final;
};

template <typename data_type>
auto editor_of<data_type>::clone() const -> std::unique_ptr<widget>
{
	auto clone = std::make_unique<editor_of<data_type>>();
	clone->copy(*this);
	return clone;
}

template <typename data_type>
void editor_of<data_type>::copy(widget const& other)
{
	auto const& casted = dynamic_cast<editor_of<data_type> const&>(other);
	_data = casted._data;
	editor::copy(other);
}

template <typename data_type>
void editor_of<data_type>::set_data_writer(data_writer<data_type> data)
{
	_data = std::move(data);
}

template <typename data_type>
void editor_of<data_type>::draw_contents() const
{
	if(auto* data = _data.read(); data != nullptr)
	{
		if(draw_contents(*data))
		{
			_data.write(data); // TODO pass in new data
		}
	}
	else
	{
		ImGui::Text("NO DATA");
	}
}

template <typename data_type>
auto editor_of<data_type>::draw_contents(data_type& /*data*/) const -> bool
{
	ImGui::Text("NO EDITOR IMPLEMENTATION");
	return false;
}

} // namespace clk::gui