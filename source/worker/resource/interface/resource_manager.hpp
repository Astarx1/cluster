#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <map>

#include "../../network/interfaces/message.hpp"

namespace Resource {
typedef int resource_cursor_type;
typedef std::map<std::string, resource_cursor_type> resource_grape_type;

enum internal_type {
	Int = 0,
	String = 1,
	Grape = 2,
	IntArray = 3,
	NetMessage = 4,
	None = 5
};

class ResourceManager {
public:
	ResourceManager() { ; }
	~ResourceManager() { ; }

	virtual resource_cursor_type add_value(int value) = 0;
	virtual resource_cursor_type add_value(std::string value) = 0;
	virtual resource_cursor_type add_value(resource_grape_type value) = 0;
	virtual resource_cursor_type add_value(Network::Message value) = 0;

	virtual int& get_int_resource(resource_cursor_type cursor) = 0;
	virtual std::string& get_str_resource(resource_cursor_type cursor) = 0;
	virtual resource_grape_type& get_grape_resource(resource_cursor_type cursor) = 0;
	virtual Network::Message& get_message_resource(resource_cursor_type cursor) = 0;
};
};
#endif