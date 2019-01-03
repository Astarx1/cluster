#ifndef COUNT_OCCURENCES_WORD_HPP
#define COUNT_OCCURENCES_WORD_HPP
#include <string>
#include <map>

#include "interface/operation_function.hpp"
#include "../../resource/interface/resource_manager.hpp"
#include "../../network/interfaces/networker.hpp"
#include "../../network/interfaces/message.hpp"


namespace Operation {
class LaunchCountOccurencesWord : public operation_functor {
public:
	void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output, 
		Resource::ResourceManager * rm, Network::Networker * communications, OperationPool * operation_pool) {
		Misc::ProtectedOut::out(std::string("Operation LaunchCountOccurencesWord : Starting processing"));
		
		Network::Message& msg = rm->get_message_resource(input);
		Misc::ProtectedOut::out(std::string("found message : " + msg.message));
		int a = msg.message.find(" ");
		std::string word = msg.message.substr(0, a);
		std::string text = msg.message.substr(a+1);
		std::string destination = msg.author.name;

		Misc::ProtectedOut::out(std::string("Operation LaunchCountOccurencesWord : Looking for '" + word + "' in : " + text));
		Resource::resource_cursor_type rct_word = rm->add_value(word);
		Resource::resource_cursor_type rct_text = rm->add_value(text);
		Resource::resource_cursor_type rct_dest = rm->add_value(destination);
		Resource::resource_cursor_type rct_occu = rm->add_value(0);

		Resource::resource_grape_type grape;
		grape.insert(std::pair<std::string, Resource::resource_cursor_type>("word", rct_word));
		grape.insert(std::pair<std::string, Resource::resource_cursor_type>("text", rct_text));
		grape.insert(std::pair<std::string, Resource::resource_cursor_type>("occu", rct_occu));
		grape.insert(std::pair<std::string, Resource::resource_cursor_type>("dest", rct_dest));
		Resource::resource_cursor_type inputs = rm->add_value(grape);

		operation_pool->add_task("CountOccurencesWord", inputs, output);
	}
};

class CountOccurencesWord : public operation_functor {
public:
	void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output, 
		Resource::ResourceManager * rm, Network::Networker * communications, OperationPool * operation_pool) {
		Misc::ProtectedOut::out(std::string("Operation CountOccurencesWord : Starting processing"));

		Resource::resource_grape_type& grape = rm->get_grape_resource(input);
		std::string& text = rm->get_str_resource(grape.find("text")->second);
		std::string& word = rm->get_str_resource(grape.find("word")->second);
		int& occu = rm->get_int_resource(grape.find("occu")->second);
		Misc::ProtectedOut::out(std::string("Operation CountOccurencesWord : Looking for '" + word + "' in : " + text));

		std::size_t pos = text.find(word);
		if (pos != std::string::npos) {
			while(pos != std::string::npos) {
				++occu;
				pos = text.find(word, pos+1);
			}
		}
		Misc::ProtectedOut::out(std::string("Operation CountOccurencesWord : " + occu));
		operation_pool->add_task("SendOccurencesWordCount", input, output);
	}
};

class SendOccurencesWordCount : public operation_functor {
public:
	void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output, 
		Resource::ResourceManager * rm, Network::Networker * communications, OperationPool * operation_pool) {
		Misc::ProtectedOut::out(std::string("Operation SendOccurencesWordCount : Starting processing"));
		Resource::resource_grape_type& grape = rm->get_grape_resource(input);

		Misc::ProtectedOut::out(std::string("Operation SendOccurencesWordCount : Finding variables"));
		int& occu = rm->get_int_resource(grape.find("occu")->second);
		std::string& dest = rm->get_str_resource(grape.find("dest")->second);
		
		Misc::ProtectedOut::out(std::string("Operation SendOccurencesWordCount : sending result"));
		communications->send(Network::Address(dest), Network::Message(std::to_string(occu)));
		Misc::ProtectedOut::out(std::string("Operation SendOccurencesWordCount : over"));
	}
};
};

#endif