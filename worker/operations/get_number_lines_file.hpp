#ifndef OPERATION_GET_NB_LINE_FILE_HPP
#define OPERATION_GET_NB_LINE_FILE_HPP
#include "interface/operation_function.hpp"
#include "../resource_manager.hpp"
#include "../interfaces/networker.hpp"

#include <iostream>
#include <fstream>
#include <string>

class GetNumberLineFile : public operation_functor {
public:
	void operator() (resource_cursor_type input, resource_cursor_type output, ResourceManager * rm,
		Networker * communications, OperationPool * operation_pool) {
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

#endif