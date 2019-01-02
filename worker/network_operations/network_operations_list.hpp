#ifndef NETWORK_OPERATIONS_LIST_HPP
#define NETWORK_OPERATIONS_LIST_HPP

#include "interface/network_operation_function.hpp"
#include "netop_new_worker.hpp"

class NetworkOperationList {
public:
	NetworkOperationList() { 
		network_operation_functor * new_worker = new netop_new_worker();
		m_operations.insert(std::pair<std::string, network_operation_functor *>("0", new_worker));
	}
	~NetworkOperationList() { 
		// TODO : I have a small memory leak there, I should free functors before exiting program
		;
	}

	network_operation_functor * get_operation(std::string operation_name) {
		return (m_operations.find(operation_name))->second;
	}

private:
	std::map<std::string, network_operation_functor *> m_operations;
};

#endif