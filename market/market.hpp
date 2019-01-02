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

class Market : public Networker {
public:
	Market() : context(1) {
		publish_offers = std::string("publish_offers");
		sockets.insert(std::pair<std::string,zmq::socket_t>(publish_offers, zmq::socket_t(context, ZMQ_PUB)));
		(sockets.find(publish_offers)->second).bind("tcp://*:5550");
		std::cout << "Port 5550 ready to make offers" << std::endl;

		receive_deliveries = std::string("receive_deliveries");
		sockets.insert(std::pair<std::string,zmq::socket_t>(receive_deliveries, zmq::socket_t(context, ZMQ_PULL)));
		(sockets.find(receive_deliveries)->second).bind("tcp://*:5551");
		std::cout << "Port 5551 ready to receive handshakes" << std::endl;
	}

	~Market() {
	}

	void open_market() {
		std::cout << "Opening market" << std::endl;
		accept_new_workers = true;
		market_mng_thread = std::thread(&Market::market_management, this);
	}

	void close_market() {
		accept_new_workers = false;
		if (market_mng_thread.joinable())
			market_mng_thread.join();
	}

	void make_offer() {
		std::string offer("buyer0/extract_column/");
	}

	void market_management() {
		int val = -1;
	  	zmq::message_t introduction;

		while(accept_new_workers) {
	        try {
		        val = (sockets.find(receive_deliveries)->second).recv(&introduction, ZMQ_NOBLOCK);
		    }
		    catch (...) {
		    	val = -1;
		    }
	        if (val >= 0 && introduction.size() > 0) {
	        	try {
			        //std::string smessage(static_cast<char*>(introduction.data()), introduction.size());
			        Message smessage(introduction);
			        workers.push_back(smessage.message);
	        		std::cout << "New worker : " << smessage.author.adr << std::endl;
	        		send(Address(publish_offers), Message(std::string("New worker !")));
			    }
			    catch (...) {
			    	std::cout << "Error when adding new worker" << std::endl;
			    }
		  	}
			usleep(wait_ms);
		}
	}

	Message send(Address adr, Message msg) {
		if (msg.type == 0) {
		    zmq::message_t message(msg.message.size());
		    memcpy(message.data(), msg.message.c_str(), msg.message.size());
		    std::cout << "Sending message " << msg.message << " to socket " << adr.adr << std::endl;
			(sockets.find(adr.adr)->second).send(message);
			return Message();
		}
	}

	void connect_operation_pool(OperationPool * operation_pool) {
		;
	}

	std::deque<std::string> get_ips_workers() {
		return workers;
	}
	
	std::map<std::string, zmq::socket_t> sockets;
	zmq::context_t context;

	std::string publish_offers;
	std::string receive_deliveries;
	
	bool accept_new_workers;
	int wait_ms = 10;
	std::thread market_mng_thread;
	std::deque<std::string> workers;
};

#endif