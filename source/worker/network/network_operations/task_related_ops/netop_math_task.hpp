#ifndef NETOP_DO_TASK_HPP
#define NETOP_DO_TASK_HPP

#include "../interface/network_operation_function.hpp"

namespace Network {
class netop_math_task : public network_operation_functor {
public:
	void operator() (Message * msg, Networker * mailbox, Operation::OperationPool * op_pool, 
		Resource::ResourceManager * rm, NetworkOperationList * nol) {
		Misc::ProtectedOut::out(std::string("Network::netop_math_task : Task Related operation!"));
		int fws = (msg->message).find(' ');
		std::string operation = (msg->message).substr(0,fws);

		Misc::ProtectedOut::out(std::string("Network::netop_math_task : Task " + operation));
		if (operation == "Add2Ints") {
			int sws = (msg->message).find(' ', fws + 1);
			Resource::resource_cursor_type i1 = rm->add_value(std::stoi((msg->message).substr(fws+1, sws-fws-1)));
			Resource::resource_cursor_type i2 = rm->add_value(std::stoi((msg->message).substr(sws+1)));

			Resource::resource_grape_type grape;
			grape.insert(std::pair<std::string, Resource::resource_cursor_type>("int1", i1));
			grape.insert(std::pair<std::string, Resource::resource_cursor_type>("int2", i2));

			Resource::resource_cursor_type input = rm->add_value(grape);
			Resource::resource_cursor_type output = rm->add_value(0);

			op_pool->add_task("MathAdd2Ints", input, output);
			Misc::ProtectedOut::out(std::string("Network::netop_math_task : Add2Int Operation order given"));
		}
	}
};
};

#endif