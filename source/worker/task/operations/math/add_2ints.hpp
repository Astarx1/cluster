#ifndef OPERATION_MATH_ADD_2INT_HPP
#define OPERATION_MATH_ADD_2INT_HPP
#include "../interface/operation_function.hpp"
#include "../../../resource/interface/resource_manager.hpp"
#include "../../../network/interfaces/networker.hpp"

#include <iostream>
#include <fstream>
#include <string>


namespace Operation {
namespace Math {
class Add2Ints : public operation_functor {
public:
	void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output, 
		Resource::ResourceManager * rm, Network::Networker * communications, 
		OperationPool * operation_pool) {
		std::string s;
		Misc::ProtectedOut::out(std::string("Operation::Math::Add2Ints : Starting processing"));

		Resource::resource_grape_type& grape = rm->get_grape_resource(input);
		int& int1 = rm->get_int_resource(grape.find("int1")->second);
		int& int2 = rm->get_int_resource(grape.find("int2")->second);
		int& intt = rm->get_int_resource(output);
		intt = int1 + int2;

		Misc::ProtectedOut::out(std::string("Operation::Math::Add2Ints : Output = " + std::to_string(intt)));
	}
};
};
};

#endif