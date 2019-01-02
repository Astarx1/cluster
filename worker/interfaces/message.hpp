#ifndef MESSAGE_HPP
#define MESSAGE_HPP

enum MsgReturnType {
	NoAnswerNeeded = 0,
	WaitingAnswer = 1,
	Answered = 2,
	Acknowledged = 3,
	WaitingAcknowledgement = 4,
	WaitingAckNAnswer = 5,
	Unknown = 6
};

typedef struct Message {
	Message() { ; }
	Message(MsgReturnType t, std::string msg) : type(t), message_number(0), version(0), message(msg) { ; }
	Message(std::string msg) : type(MsgReturnType::NoAnswerNeeded), message_number(0), version(0), message(msg) { ; }
	Message(zmq::message_t& msg) : type(MsgReturnType::Unknown), message_number(0) { message_from_zmq(msg); }
	
	std::string message;
	
	Address author;
	Address destination;

	int version;
	int message_number;
	MsgReturnType type; // 0 : send without waiting for answer, 1 : wait for answer in the dedicated receiver

	std::string construct_message() {
		int ack = (type == MsgReturnType::NoAnswerNeeded ? 0 : 1);
		if (version == 0) {
			return std::to_string(version) + ',' + author.adr + ',' + destination.adr + ',' + 
				   std::to_string(message_number) + ',' + std::to_string(ack) + ',' + message;
		}
		else {
			return std::to_string(version) + ',' + author.adr + ',' + destination.adr + ',' + 
				   std::to_string(message_number) + ',' + std::to_string(ack) + ',' + message;
		}
	}

	void message_from_zmq(zmq::message_t& msg) {
		std::string smessage(static_cast<char*>(msg.data()), msg.size());
		int a, b, c;
		a = smessage.find(',', 0);
		b = smessage.find(',', a+1);
		c = smessage.find(',', b+1);
		version = std::stoi (smessage.substr(0,a));
		author = Address(smessage.substr(a+1,b-a-1));
		destination = Address(smessage.substr(b+1,c-b-1));
		message = smessage.substr(c+1);
	}
} Message;

#endif