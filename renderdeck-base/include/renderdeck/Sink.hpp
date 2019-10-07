#pragma once

#include "renderdeck/AbstractSink.hpp"
#include "renderdeck/InputDataPort.hpp"
#include "renderdeck/Utility.hpp"

template<typename... I>
struct InputList
{
	std::tuple<InputDataPort<I>...> list;
};

template<typename ConcreteSink, typename InputList>
class Sink : public virtual AbstractSink
{
protected:
	mutable InputList inputs;

public:
	Sink()
	{
		static_for_index(inputs.list, [&](auto& inputDataPort, int index) {
			AbstractSink::abstractInputDataPorts.push_back(&inputDataPort);
			inputDataPort.setName(ConcreteSink::InputPorts::names[index]);
		});
	}
	Sink(Sink const&) = delete;
	Sink(Sink&&) = delete;
	Sink& operator=(Sink const&) = delete;
	Sink& operator=(Sink&&) = delete;
	virtual ~Sink() = default;

protected:
	void updateAllInputs() const override final
	{
		static_for(inputs.list, [](auto const& input) {
			input.update();
			});
	}

public:
	std::string const& getName() const override
	{
		return ConcreteSink::name;
	}

	template<int inputIndex>
	auto& getInputDataPort() const
	{
		return std::get<inputIndex>(inputs.list);
	}

};