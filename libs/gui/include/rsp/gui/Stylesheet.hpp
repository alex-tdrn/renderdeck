#pragma once

#include "rsp/gui/Animation.hpp"
#include "rsp/util/Bounded.hpp"
#include "rsp/util/ColorRGBA.hpp"

#include <chrono>
#include <imgui.h>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std::chrono_literals;

namespace rsp::gui
{
class Stylesheet
{
public:
	rsp::ColorRGBA nodeEditorBackgroundColor{60, 60, 70, 200};
	rsp::ColorRGBA nodeEditorGridColor{120, 120, 120, 40};
	rsp::ColorRGBA nodeSelectionRectColor{5, 130, 255, 64};
	rsp::ColorRGBA nodeSelectionRectBorderColor{5, 130, 255, 128};
	rsp::ColorRGBA linkSelectionRectColor{5, 130, 255, 64};
	rsp::ColorRGBA linkSelectionRectBorderColor{5, 130, 255, 128};
	rsp::ColorRGBA nodeBackgroundColor{32, 32, 32, 200};
	rsp::ColorRGBA nodeBorderColor{255, 255, 255, 96};
	rsp::ColorRGBA hoveredNodeBorderColor{50, 176, 255, 255};
	rsp::ColorRGBA selectedNodeBorderColor{255, 176, 50, 255};
	Bounded<float> nodeBorderWidth{0.0f, 0.0f, 10.0f};
	Bounded<float> hoveredNodeBorderWidth{3.5f, 1.0f, 10.0f};
	Bounded<float> selectedNodeBorderWidth{3.5f, 1.0f, 10.0f};
	Bounded<float> nodeRounding{0.0f, 0.0f, 100.0f};
	Bounded<glm::vec4> nodePadding{glm::vec4{8}, glm::vec4{0.0f}, glm::vec4{100.0f}};
	rsp::ColorRGBA pinRectColor{60, 180, 255, 100};
	rsp::ColorRGBA pinRectBorderColor{60, 180, 255, 128};
	rsp::ColorRGBA eventColor{1.0f};
	rsp::ColorRGBA eventTextColor{1.0f, 0.9f, 0.68f, 1.0f};
	Bounded<float> anchorOffset{0.0f, 0.0f, 100.0f};
	Bounded<float> animatedAnchorOffset{10, 0.0f, 100.0f};
	std::chrono::nanoseconds animatedAnchorOffsetDuration = 1s;
	Bounded<float> pinBorderWidth{0.0f, 0.0f, 100.0f};
	Bounded<float> pinRounding{0.0f, 0.0f, 100.0f};
	Bounded<float> pinRadius{0.0f, 0.0f, 100.0f};
	Bounded<float> pinArrowSize{0.0f, 0.0f, 100.0f};
	Bounded<float> pinArrowWidth{0.0f, 0.0f, 100.0f};
	rsp::ColorRGBA hoveredLinkBorderColor{50, 176, 255, 255};
	rsp::ColorRGBA selectedLinkBorderColor{255, 176, 50, 255};
	Bounded<float> linkStrength{1000.0f, 0.0f, 1000.0f};
	Bounded<float> linkThickness{2.0f, 1.0f, 10.0f};
	Bounded<glm::vec2> targetDirection{glm::vec2{-1.0f, 0.0f}, glm::vec2{-1.0f}, glm::vec2{1.0f}};
	Bounded<glm::vec2> sourceDirection{glm::vec2{1.0f, 0.0f}, glm::vec2{-1.0f}, glm::vec2{1.0f}};
	glm::vec2 pivotAlignment = {0.5f, 0.5f};
	glm::vec2 pivotSize = {-1.0f, -1.0f};
	glm::vec2 pivotScale = {1.0f, 1.0f};
	Bounded<float> flowMarkerDistance{50.0f, 0.0f, 100.0f};
	Bounded<float> flowSpeed{200.0f, 0.0f, 1000.0f};
	Bounded<float> flowDuration{1.0f, 0.0f, 10.0f};

	explicit Stylesheet(std::string name = "default");
	Stylesheet(Stylesheet&&) = default;
	Stylesheet(Stylesheet const&) = default;
	auto operator=(Stylesheet&&) -> Stylesheet& = default;
	auto operator=(Stylesheet const&) -> Stylesheet& = default;
	~Stylesheet() = default;

	static void addSheet(std::unique_ptr<Stylesheet>&& sheet);
	static auto getSheet(const std::string& name) -> Stylesheet&;
	static void setCurrentSheet(const std::string& name);
	static auto getCurrentSheet() -> Stylesheet&;
	auto getName() const -> std::string;

private:
	static inline std::unordered_map<std::string, std::unique_ptr<Stylesheet>> sheets;
	static inline std::string currentSheetName;
	static inline Stylesheet* currentSheet = nullptr;
	std::string name = "default";
};

inline Stylesheet::Stylesheet(std::string name) : name(std::move(name))
{
}

inline void Stylesheet::addSheet(std::unique_ptr<Stylesheet>&& sheet)
{
	assert(sheets.find(sheet->getName()) == sheets.end());
	sheets[sheet->getName()] = std::move(sheet);
	if(currentSheet == nullptr)
		setCurrentSheet(sheets.begin()->first);
}

inline auto Stylesheet::getSheet(const std::string& name) -> Stylesheet&
{
	assert(sheets.find(name) != sheets.end());
	return *sheets[name];
}

inline void Stylesheet::setCurrentSheet(const std::string& name)
{
	currentSheetName = name;
	currentSheet = &getSheet(name);
}

inline auto Stylesheet::getCurrentSheet() -> Stylesheet&
{
	assert(currentSheet != nullptr);
	return *currentSheet;
}

inline auto Stylesheet::getName() const -> std::string
{
	return name;
}
} // namespace rsp::gui