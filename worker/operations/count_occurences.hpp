#ifndef COUNT_OCCURENCES_WORD_HPP
#define COUNT_OCCURENCES_WORD_HPP
#include <string>
#include <map>

#include "interface/operation_function.hpp"
#include "../resource_manager.hpp"
#include "../interfaces/networker.hpp"
#include "../interfaces/message.hpp"

class LaunchCountOccurencesWord : public operation_functor {
public:
	void operator() (resource_cursor_type input, resource_cursor_type output, ResourceManager * rm,
		Networker * communications, OperationPool * operation_pool) {
		std::cout << "Operation LaunchCountOccurencesWord : Starting processing" << std::endl;
		
		Message& msg = rm->get_message_resource(input);
		std::cout << "found message : " << msg.message << std::endl;
		int a = msg.message.find(" ");
		std::string word = msg.message.substr(0, a);
		std::string text = msg.message.substr(a+1);
		std::string destination = msg.author.name;

		std::cout << "Operation LaunchCountOccurencesWord : Looking for '" << word << "' in : " << text << std::endl;
		resource_cursor_type rct_word = rm->add_value(word);
		resource_cursor_type rct_text = rm->add_value(text);
		resource_cursor_type rct_dest = rm->add_value(destination);
		resource_cursor_type rct_occu = rm->add_value(0);

		resource_grape_type grape;
		grape.insert(std::pair<std::string, resource_cursor_type>("word", rct_word));
		grape.insert(std::pair<std::string, resource_cursor_type>("text", rct_text));
		grape.insert(std::pair<std::string, resource_cursor_type>("occu", rct_occu));
		grape.insert(std::pair<std::string, resource_cursor_type>("dest", rct_dest));
		resource_cursor_type inputs = rm->add_value(grape);

		operation_pool->add_task("CountOccurencesWord", inputs, output);
	}
};

class CountOccurencesWord : public operation_functor {
public:
	void operator() (resource_cursor_type input, resource_cursor_type output, ResourceManager * rm,
		Networker * communications, OperationPool * operation_pool) {
		std::cout << "Operation CountOccurencesWord : Starting processing" << std::endl;
		int& sTotal = rm->get_int_resource(output);

		resource_grape_type& grape = rm->get_grape_resource(input);
		std::string& text = rm->get_str_resource(grape.find("text")->second);
		std::string& word = rm->get_str_resource(grape.find("word")->second);
		int& occu = rm->get_int_resource(grape.find("occu")->second);
		std::cout << "Operation CountOccurencesWord : Looking for '" << word << "' in : " << text << std::endl;

		int pos = text.find(word);
		if (pos != std::string::npos) {
			while(pos != std::string::npos) {
				++occu;
				pos = text.find(word, pos+1);
			}
		}
		std::cout << "Operation CountOccurencesWord : " << occu << std::endl;
		operation_pool->add_task("SendOccurencesWordCount", input, output);
	}
};

class SendOccurencesWordCount : public operation_functor {
public:
	void operator() (resource_cursor_type input, resource_cursor_type output, ResourceManager * rm,
		Networker * communications, OperationPool * operation_pool) {
		std::cout << "Operation SendOccurencesWordCount : Starting processing" << std::endl;
		resource_grape_type& grape = rm->get_grape_resource(input);

		std::cout << "Operation SendOccurencesWordCount : Finding variables" << std::endl;
		int& occu = rm->get_int_resource(grape.find("occu")->second);
		std::string& dest = rm->get_str_resource(grape.find("dest")->second);
		
		std::cout << "Operation SendOccurencesWordCount : sending result" << std::endl;
		communications->send(Address(dest), Message(std::to_string(occu)));
		std::cout << "Operation SendOccurencesWordCount : over" << std::endl;
	}
};

#endif