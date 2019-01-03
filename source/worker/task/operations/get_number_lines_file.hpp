#ifndef OPERATION_GET_NB_LINE_FILE_HPP
#define OPERATION_GET_NB_LINE_FILE_HPP
#include "interface/operation_function.hpp"
#include "../../resource/resource_manager.hpp"
#include "../../network/interfaces/networker.hpp"

#include <iostream>
#include <fstream>
#include <string>


namespace Operation {
class GetNumberLineFile : public operation_functor {
public:
	void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output, 
		Resource::ResourceManager * rm, Network::Networker * communications, 
		OperationPool * operation_pool) {
		std::string s;
		std::cout << "Operation GetNumberLineFile : Starting processing" << std::endl;
		int& sTotal = rm->get_int_resource(output);

		std::ifstream in;
		in.open(rm->get_str_resource(input));

		while(!in.eof()) {
			std::getline(in, s);
			sTotal ++;	
		}
	}
};
};

#endif