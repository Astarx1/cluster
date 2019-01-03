#ifndef OPERATIONS_FUNCTIONS_HPP
#define OPERATIONS_FUNCTIONS_HPP
#include <iostream>
#include <fstream>
#include <string>

#include "operations/get_number_lines_file.hpp"
#include "operations/count_occurences.hpp"
#include "operations/math/add_2ints.hpp"

/*
class operation_functor {
public:
	virtual void operator() (resource_cursor_type input, resource_cursor_type output,
		ResourceManager * rm, Networker * communications, OperationPool * operation_pool) = 0;
};

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
*/

#endif