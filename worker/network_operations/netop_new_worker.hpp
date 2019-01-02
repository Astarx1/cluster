#ifndef NETOP_NEW_WORKER_HPP
#define NETOP_NEW_WORKER_HPP

#include "interface/network_operation_function.hpp"

class netop_new_worker : public network_operation_functor {
public:
	void operator() (Message * msg, Networker * mailbox, OperationPool * op_pool, ResourceManager * rm, 
		NetworkOperationList * nol) {
		std::cout << "New Worker !" << std::endl;
	}
};

#endif