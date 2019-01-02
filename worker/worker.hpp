#ifndef MARKET_HPP
#define MARKET_HPP

#include <zmq.hpp>
#include <unistd.h>
#include <deque> 
#include <thread>
#include <string>
#include <iostream>
#include <map>

#include "interfaces/networker.hpp"
#include "network_operations/network_operations_list.hpp"

class MailBox : public Networker {
public:
	MailBox() : context(1), m_me("tcp://localhost:5552") {
		std::string read_market("tcp://localhost:5550");
		sockets.insert(std::pair<std::string,zmq::socket_t>(read_market, zmq::socket_t(context, ZMQ_SUB)));
		(sockets.find(read_market)->second).connect(read_market);
		(sockets.find(read_market)->second).setsockopt(ZMQ_SUBSCRIBE, "", 0);
		std::cout << "Port 5550 is ready to read offers in the market" << std::endl;

		std::string send_market("tcp://localhost:5551");
		sockets.insert(std::pair<std::string,zmq::socket_t>(send_market, zmq::socket_t(context, ZMQ_PUSH)));
		(sockets.find(send_market)->second).connect(send_market);
		std::cout << "Port 5551 is ready to send handshakes" << std::endl;
		
		std::string publish_deliveries("tcp://localhost:5552");
		sockets.insert(std::pair<std::string,zmq::socket_t>(publish_deliveries, zmq::socket_t(context, ZMQ_PUB)));
		(sockets.find(publish_deliveries)->second).bind("tcp://*:5552");
		std::cout << "Port 5552 is ready to deliver" << std::endl;

		open_shop();

		std::cout << "Sending handshake to localhost:5551" << std::endl;
	    send(Address("localhost:5551", send_market), Message(std::string("tcp://localhost:5552")));
	    std::cout << "Handsake sent" << std::endl;

	    wait_ms = 10;
	}

	~MailBox() {
		close_shop();
	}
	
	void open_shop() {
		std::cout << "Getting into the market" << std::endl;
		read_offers = true;
		market_mng_thread = std::thread(&MailBox::answer_offers, this);
	}

	void close_shop() {
		read_offers = false;
		if (market_mng_thread.joinable())
			market_mng_thread.join();
	}

	void answer_offers() {
		std::string read_market("tcp://localhost:5550");
		int val = -1;
	  	zmq::message_t introduction;

	  	std::cout << "Answering offers" << std::endl;

		while(read_offers) {
	        try {
		        val = (sockets.find(read_market)->second).recv(&introduction, ZMQ_NOBLOCK);
		    }
		    catch (...) {
		    	val = -1;
		    }
	        if (val >= 0 && introduction.size() > 0) {
	        	std::cout << "Reading market offers" << std::endl;
	        	try {
			        Message smessage(introduction);
			        network_operation_functor * op2do = net_op_list.get_operation(smessage.operation);
			        (*op2do)(&smessage, this, m_operation_pool, m_operation_pool->get_resource_manager(), &net_op_list);
			        std::cout << "Actions done" << std::endl;
			        //std::string smessage(static_cast<char*>(introduction.data()), introduction.size());
	        		//std::cout << "New worker : " << smessage << std::endl;
			    }
			    catch (...) {
			    	std::cout << "Error when adding new tasks" << std::endl;
			    }
		  	}
			usleep(wait_ms);
		}		
	}

	Message send(Address adr, Message msg, bool pub_delivery=false) {
		if (msg.type == MsgReturnType::NoAnswerNeeded) {
			msg.author = m_me;
			msg.destination = adr;
			std::string msg2send = msg.construct_message();
		    zmq::message_t message(msg2send.size());
		    memcpy(message.data(), msg2send.c_str(), msg2send.size());
		    std::cout << "Mailbox : Sending '" << msg2send << "' to '" << adr.name << "'" << std::endl;
			(sockets.find(adr.name)->second).send(message);
			return Message();
		}
	}

	void connect_operation_pool(OperationPool * operation_pool) {
		m_operation_pool = operation_pool;
	}

private:
	std::map<std::string, zmq::socket_t> sockets;
	zmq::context_t context;

	OperationPool * m_operation_pool;
	std::thread market_mng_thread;
	bool read_offers;
	int wait_ms;

	NetworkOperationList net_op_list;

	Address m_me;
};

#endif