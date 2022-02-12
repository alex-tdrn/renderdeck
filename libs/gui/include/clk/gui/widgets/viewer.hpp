#pragma once

#include "clk/gui/widgets/data_reader.hpp"
#include "clk/gui/widgets/data_widget.hpp"

#include <imgui.h>

namespace clk::gui
{
class viewer : public data_widget
{
public:
	using data_widget::data_widget;
	viewer() = delete;
	viewer(viewer const&) = delete;
	viewer(viewer&&) = delete;
	auto operator=(viewer const&) -> viewer& = delete;
	auto operator=(viewer&&) -> viewer& = delete;
	~viewer() override = default;
};

template <typename data_type>
class viewer_of : public viewer
{
public:
	using viewer::viewer;
	viewer_of() = delete;
	viewer_of(viewer_of const&) = delete;
	viewer_of(viewer_of&&) = delete;
	auto operator=(viewer_of const&) -> viewer_of& = delete;
	auto operator=(viewer_of&&) -> viewer_of& = delete;
	~viewer_of() override = default;

	auto clone() const -> std::unique_ptr<widget> override;
	void copy(widget const& other) override;

	void set_data_reader(data_reader<data_type> data);
	virtual void draw_contents(data_type const& data) const;

private:
	data_reader<data_type> _data;

	void draw_contents() const final;
};

template <>
class viewer_of<void> : public viewer
{
public:
	using viewer::viewer;
	viewer_of() = delete;
	viewer_of(viewer_of const&) = delete;
	viewer_of(viewer_of&&) = delete;
	auto operator=(viewer_of const&) -> viewer_of& = delete;
	auto operator=(viewer_of&&) -> viewer_of& = delete;
	~viewer_of() override = default;

	auto clone() const -> std::unique_ptr<widget> override;
	void copy(widget const& other) override;

private:
	void draw_contents() const final;
};

inline auto viewer_of<void>::clone() const -> std::unique_ptr<widget>
{
	auto clone = std::make_unique<viewer_of<void>>(get_widget_factory(), name());
	clone->copy(*this);
	return clone;
}

inline void viewer_of<void>::copy(widget const& other)
{
	viewer::copy(other);
}

inline void viewer_of<void>::draw_contents() const
{
	ImGui::Text("VOID VIEWER");
}

template <typename data_type>
auto viewer_of<data_type>::clone() const -> std::unique_ptr<widget>
{
	auto clone = std::make_unique<viewer_of<data_type>>(get_widget_factory(), name());
	clone->copy(*this);
	return clone;
}

template <typename data_type>
void viewer_of<data_type>::copy(widget const& other)
{
	auto const& casted = dynamic_cast<viewer_of<data_type> const&>(other);
	_data = casted._data;
	viewer::copy(other);
}

template <typename data_type>
void viewer_of<data_type>::set_data_reader(data_reader<data_type> data)
{
	_data = std::move(data);
}

template <typename data_type>
void viewer_of<data_type>::draw_contents() const
{
	if(auto const* data = _data.read(); data != nullptr)
	{
		draw_contents(*data);
	}
	else
	{
		ImGui::Text("NO DATA");
	}
}

template <typename data_type>
void viewer_of<data_type>::draw_contents(data_type const& /*data*/) const
{
	ImGui::Text("NO VIEWER IMPLEMENTATION");
}

} // namespace clk::gui
