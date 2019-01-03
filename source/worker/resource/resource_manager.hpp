#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include <string>
#include <map>
#include <deque>

#include "../network/interfaces/message.hpp"

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
	ResourceManager() { 
		m_cursor = 0; 
	}

	resource_cursor_type add_value(int value) {
		resource_cursor_type cur = get_unique_id();
		m_int_resources.insert(std::pair<resource_cursor_type, int>(cur, value));
		m_resources.insert(std::pair<resource_cursor_type, internal_type>(cur, internal_type::Int));
		return cur;
	}

	resource_cursor_type add_value(std::string value) {
		resource_cursor_type cur = get_unique_id();
		m_str_resources.insert(std::pair<resource_cursor_type, std::string>(cur, value));
		m_resources.insert(std::pair<resource_cursor_type, internal_type>(cur, internal_type::String));
		return cur;
	}

	resource_cursor_type add_value(resource_grape_type value) {
		resource_cursor_type cur = get_unique_id();
		m_grape_resources.insert(std::pair<resource_cursor_type, resource_grape_type>(cur, value));
		m_resources.insert(std::pair<resource_cursor_type, internal_type>(cur, internal_type::Grape));
		return cur;
	}

	resource_cursor_type add_value(Network::Message value) {
		resource_cursor_type cur = get_unique_id();
		m_message_resources.insert(std::pair<resource_cursor_type, Network::Message>(cur, value));
		m_resources.insert(std::pair<resource_cursor_type, internal_type>(cur, internal_type::NetMessage));
		return cur;
	}

	int& get_int_resource(resource_cursor_type cursor) {
		return m_int_resources.at(cursor);
	} 

	std::string& get_str_resource(resource_cursor_type cursor) {
		return m_str_resources.at(cursor);
	} 

	resource_grape_type& get_grape_resource(resource_cursor_type cursor) {
		return m_grape_resources.at(cursor);
	}

	Network::Message& get_message_resource(resource_cursor_type cursor) {
		return m_message_resources.at(cursor);
	}

private:
	resource_cursor_type get_unique_id() {
		m_cursor++;
		return m_cursor - 1;
	}
	
	std::map<resource_cursor_type, internal_type> m_resources;

	std::map<resource_cursor_type, int> m_int_resources;
	std::map<resource_cursor_type, std::string> m_str_resources;
	std::map<resource_cursor_type, resource_grape_type> m_grape_resources;
	std::map<resource_cursor_type, Network::Message> m_message_resources;

	resource_cursor_type m_cursor;
};
};

#endif
