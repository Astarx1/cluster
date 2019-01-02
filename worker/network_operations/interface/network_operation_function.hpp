#ifndef NETWORK_OPERATION_FUNCTOR_INTERFACE_HPP
#define NETWORK_OPERATION_FUNCTOR_INTERFACE_HPP

#include "../../interfaces/networker.hpp"
#include "../../interfaces/message.hpp"
#include "../../resource_manager.hpp"
#include "../../operation_pool.hpp"

class NetworkOperationList;

class network_operation_functor {
public:
	virtual void operator() (Message * msg, Networker * mailbox, OperationPool * op_pool, 
		ResourceManager * rm, NetworkOperationList * nol) = 0;
};

#endif