#pragma once

#include "rsp/base/Meta.hpp"
#include "rsp/base/Timestamp.hpp"
#include "rsp/base/node/AbstractSource.hpp"
#include "rsp/base/port/OutputDataPort.hpp"

namespace rsp
{
template <typename... O>
struct OutputList
{
	std::tuple<OutputDataPort<O>...> list;
};

template <typename ConcreteSource, typename OutputList>
class Source : public virtual AbstractSource
{
private:
	mutable OutputList outputs;

public:
	Source()
	{
		meta::static_for_index(outputs.list, [&](auto& outputDataPort, int index) {
			AbstractSource::abstractOutputDataPorts.push_back(&outputDataPort);
			outputDataPort.setName(ConcreteSource::OutputPorts::names[index]);
			outputDataPort.setParent(this);
		});
	}

	Source(Source const&) = delete;
	Source(Source&&) = default;
	Source& operator=(Source const&) = delete;
	Source& operator=(Source&&) = default;
	virtual ~Source() = default;

protected:
	void outputsUpdated()
	{
		notifyObserverFlags(AbstractNode::ObserverFlags::onRun);
		trigger(AbstractNode::OutputEvents::Ran);
		timestamp.update();
	}

public:
	[[nodiscard]] bool update() override
	{
		if(isRunQueued())
		{
			run();
			outputsUpdated();
		}
		return true;
	}

	std::string const& getName() const override
	{
		return ConcreteSource::name;
	}

	template <int outputIndex>
	auto& getOutputDataPort() const
	{
		return std::get<outputIndex>(outputs.list);
	}

	template <int outputIndex>
	auto& getOutputData() const
	{
		return getOutputDataPort<outputIndex>().getData();
	}
};

} // namespace rsp