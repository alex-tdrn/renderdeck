#pragma once

#include "rsp/base/Node.hpp"
#include "rsp/gui/nodes/Node.h"
#include "rsp/gui/panels/Panel.h"

#include <imgui_node_editor.h>
#include <memory>
#include <vector>

namespace rsp::gui
{
class NodeEditor final : public Panel
{
private:
	ax::NodeEditor::EditorContext* context;
	std::vector<std::unique_ptr<rsp::Node>>* store = nullptr;
	std::vector<std::unique_ptr<Node>> nodes;
	bool showInputWidgets = true;
	bool showOutputWidgets = true;

public:
	NodeEditor();
	NodeEditor(NodeEditor const&) = delete;
	NodeEditor(NodeEditor&&) = default;
	auto operator=(NodeEditor const&) -> NodeEditor& = delete;
	auto operator=(NodeEditor&&) -> NodeEditor& = delete;
	~NodeEditor() override;

private:
	void toggleInputWidgets();
	void toggleOutputWidgets();
	void toggleAllWidgets();
	void drawContents() override;

public:
	void setStore(std::vector<std::unique_ptr<rsp::Node>>* store);
};

} // namespace rsp::gui