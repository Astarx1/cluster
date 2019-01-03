#ifndef NETWORKER_HPP
#define NETWORKER_HPP
#include <string>
#include <cstdint>

#include "structures/answer.hpp"
#include "structures/address.hpp"
#include "message.hpp"

namespace Operation {
class OperationPool;
};

namespace Network {
class Networker {
public:
	Networker() { ; }
	~Networker() { ; }

	virtual Message send(Address adr, Message msg, bool pub_delivery=false) = 0;
	virtual void connect_operation_pool(Operation::OperationPool * operation_pool) = 0;
};
};

#endif