#ifndef NETWORK_OPERATION_FUNCTOR_INTERFACE_HPP
#define NETWORK_OPERATION_FUNCTOR_INTERFACE_HPP

#include "../../interfaces/networker.hpp"
#include "../../interfaces/message.hpp"
#include "../../../resource/resource_manager.hpp"
#include "../../../task/operation_pool.hpp"


namespace Network {
class NetworkOperationList;

class network_operation_functor {
public:
	virtual void operator() (Message * msg, Networker * mailbox, Operation::OperationPool * op_pool, 
		Resource::ResourceManager * rm, NetworkOperationList * nol) = 0;
};
};

#endif