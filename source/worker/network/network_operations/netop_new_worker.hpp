#ifndef NETOP_NEW_WORKER_HPP
#define NETOP_NEW_WORKER_HPP

#include "interface/network_operation_function.hpp"

namespace Network {
class netop_new_worker : public network_operation_functor {
public:
	void operator() (Message * msg, Networker * mailbox, Operation::OperationPool * op_pool, 
		Resource::ResourceManager * rm, NetworkOperationList * nol) {
		Misc::ProtectedOut::out(std::string("New Worker !"));
	}
};
};

#endif