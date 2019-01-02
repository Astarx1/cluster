#ifndef OPERATION_POOL_HPP
#define OPERATION_POOL_HPP

class Task;
class TaskStatus;
class Networker;

#include "resource_manager.hpp"

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
		resource_cursor_type resource_input, resource_cursor_type resource_output,
		std::deque<task_cursor_type> dependencies, bool pending=false) = 0;
	virtual task_cursor_type add_task(std::string operation_name, 
		resource_cursor_type resource_input, resource_cursor_type resource_output, bool pending=false) = 0;
	virtual task_status_type get_status_task(task_cursor_type task) const = 0;
	virtual void connect_mailbox(Networker * w) = 0;
};

#endif