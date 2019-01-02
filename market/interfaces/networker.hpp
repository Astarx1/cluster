#ifndef NETWORKER_HPP
#define NETWORKER_HPP
#include <string>
#include <cstdint>

#include "structures/answer.hpp"
#include "structures/address.hpp"
#include "message.hpp"

class OperationPool;

class Networker {
public:
	Networker() { ; }
	~Networker() { ; }

	virtual Message send(Address adr, Message msg) = 0;
	virtual void connect_operation_pool(OperationPool * operation_pool) = 0;
};

#endif