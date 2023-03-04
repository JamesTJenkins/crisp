#pragma once
#include <string>

namespace Crisp {
	class EntityProperties {
	public:
		EntityProperties() = default;
		EntityProperties(const EntityProperties&) = default;
		EntityProperties(const std::string& name, const std::string& tag) : name(name), tag(tag) {}
	public:
		std::string name;
		std::string tag;
	};
}