#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include <deque>
#include <map>
#include <thread>

#include "operation_functions.hpp"
#include "operation_pool.hpp"
#include "resource_manager.hpp"
#include "interfaces/networker.hpp"

class TaskStatus {
public:
	TaskStatus() {
		m_ended = false;
	}
	~TaskStatus() {
		;
	}
	void end() {
		m_ended = true;
	}
	bool ended() const {
		return m_ended; 
	}

private:
	bool m_ended;
};

class TaskList {
public:
	TaskList() { 
		operation_functor * get_nb_line = new GetNumberLineFile();
		m_operations.insert(std::pair<std::string, operation_functor *>("GetNBLine", get_nb_line));

		operation_functor * lcow = new LaunchCountOccurencesWord();
		m_operations.insert(std::pair<std::string, operation_functor *>("LaunchCountOccurencesWord", lcow));

		operation_functor * cow = new CountOccurencesWord();
		m_operations.insert(std::pair<std::string, operation_functor *>("CountOccurencesWord", cow));

		operation_functor * sowc = new SendOccurencesWordCount();
		m_operations.insert(std::pair<std::string, operation_functor *>("SendOccurencesWordCount", sowc));
	}
	~TaskList() { 
		// TODO : I have a small memory leak there, I should free functors before exiting program
		;
	}

	operation_functor * get_operation(std::string operation_name) {
		return (m_operations.find(operation_name))->second;
	}

private:
	std::map<std::string, operation_functor *> m_operations;
};

class Task {
public:
	Task(std::string operation_name, resource_cursor_type resource_input, resource_cursor_type resource_output,
		 std::deque<task_cursor_type> dependencies) :
		m_operation(operation_name),
		m_resource_input(resource_input),
		m_resource_output(resource_output),
		m_dependencies(dependencies) {
		;
	}

	Task(std::string operation_name, resource_cursor_type resource_input, resource_cursor_type resource_output):
		m_operation(operation_name),
		m_resource_input(resource_input),
		m_resource_output(resource_output) {
		;
	}

	std::string get_operation_name() {
		return m_operation;
	}

	resource_cursor_type get_input() {
		return m_resource_input;
	}

	resource_cursor_type get_output() {
		return m_resource_output;
	}

	bool validate_task_dependencies(const OperationPool * op) {
		bool is_valid = true;
		std::deque<task_cursor_type>::iterator it = m_dependencies.begin();

		while (it != m_dependencies.end())
			is_valid = is_valid && (op->get_status_task(*it)).ended();
	}

	void end() {
		m_status.end();
	}

	TaskStatus current_status() const {
		return m_status;
	}

private:
	std::deque<task_cursor_type> m_dependencies;

	std::string m_operation;
	resource_cursor_type m_resource_input;

	TaskStatus m_status;
	resource_cursor_type m_resource_output;
};

#endif