#ifndef OPERATION_POOL_HPP
#define OPERATION_POOL_HPP

#include "../resource/resource_manager.hpp"

namespace Network {
class Networker;
};

namespace Operation {
class Task;
class TaskStatus;

typedef int task_cursor_type;
typedef TaskStatus task_status_type;

class OperationPool {
public:	
	OperationPool() {
		;
	}
	~OperationPool() {
		;
	}

	virtual void run(const int nb_workers) = 0;
	virtual task_cursor_type add_task(Task task, bool pending=false) = 0;
	virtual task_cursor_type add_task(std::string operation_name, 
		Resource::resource_cursor_type resource_input, Resource::resource_cursor_type resource_output,
		std::deque<task_cursor_type> dependencies, bool pending=false) = 0;
	virtual task_cursor_type add_task(std::string operation_name, 
		Resource::resource_cursor_type resource_input, Resource::resource_cursor_type resource_output, 
		bool pending=false) = 0;
	virtual task_status_type get_status_task(task_cursor_type task) const = 0;
	virtual void connect_mailbox(Network::Networker * w) = 0;
	virtual Resource::ResourceManager * get_resource_manager() = 0;
};
};

#endif