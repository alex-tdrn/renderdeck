#pragma once

#include <set>
#include <string>

namespace rshp::base
{
class Port
{
private:
	std::string name = "Unnamed";

public:
	Port() = default;
	Port(Port const&) = delete;
	Port(Port&&) = default;
	Port& operator=(Port const& that) = delete;
	Port& operator=(Port&&) = default;
	virtual ~Port() = default;

public:
	virtual bool canConnect(Port* port) const = 0;
	virtual bool isConnected() const = 0;
	virtual void connect(Port* port) = 0;
	virtual void disconnect() = 0;
	virtual std::set<Port*> getConnections() const = 0;

	std::string const& getName() const
	{
		return name;
	}

	void setName(std::string const& name)
	{
		this->name = name;
	}
};

} // namespace rshp::base