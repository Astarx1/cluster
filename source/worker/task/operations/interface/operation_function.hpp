#ifndef OPERATION_FUNCTOR_INTERFACE_HPP
#define OPERATION_FUNCTOR_INTERFACE_HPP

namespace Operation {
class operation_functor {
public:
	virtual void operator() (Resource::resource_cursor_type input, Resource::resource_cursor_type output,
		Resource::ResourceManager * rm, Network::Networker * communications, OperationPool * operation_pool) = 0;
};
};
#endif