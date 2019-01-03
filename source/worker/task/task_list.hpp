#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include <deque>
#include <map>
#include <thread>

#include "operation_functions.hpp"
#include "operation_pool.hpp"
#include "../resource/interface/resource_manager.hpp"


namespace Operation {
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

		operation_functor * add2ints = new Math::Add2Ints();
		m_operations.insert(std::pair<std::string, operation_functor *>("MathAdd2Ints", add2ints));
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
};
#endif