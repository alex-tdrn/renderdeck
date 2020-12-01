#pragma once

#include <chrono>
#include <cmath>

namespace rsp::gui
{
enum class AnimationCurve
{
	linear,
	spring,
};

template <typename T>
class Animation
{
private:
	mutable bool playing = false;
	std::chrono::steady_clock::time_point startTime;

public:
	Animation() = default;
	Animation(Animation&&) noexcept = default;
	Animation(Animation const&) = default;
	auto operator=(Animation&&) noexcept -> Animation& = default;
	auto operator=(Animation const&) -> Animation& = default;
	~Animation() = default;

private:
	auto static inline linear(T const& startValue, T const& endValue, float p) -> T
	{
		T difference = endValue - startValue;
		return startValue + p * difference;
	}

	auto static inline spring(T const& startValue, T const& endValue, float p) -> T
	{
		float f = std::sinf(p * 10 * 3.141f) / (p + 1);
		T difference = endValue - startValue;
		return endValue - f * difference;
	}

public:
	void play()
	{
		startTime = std::chrono::steady_clock::now();
		playing = true;
	}

	auto get(T startValue, T endValue, std::chrono::nanoseconds const& duration, AnimationCurve curveType) const -> T
	{
		if(!playing)
			return endValue;
		auto const endTime = startTime + duration;
		auto const now = std::chrono::steady_clock::now();
		if(now > endTime)
		{
			playing = false;
			return endValue;
		}
		auto currentDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime);

		float p = float(currentDuration.count()) / float(duration.count());

		switch(curveType)
		{
			case AnimationCurve::linear:
				return linear(startValue, endValue, p);
			case AnimationCurve::spring:
				return spring(startValue, endValue, p);
		}
		return endValue;
	}
};

} // namespace rsp::gui