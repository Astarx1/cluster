#ifndef OPERATION_FUNCTOR_INTERFACE_HPP
#define OPERATION_FUNCTOR_INTERFACE_HPP

class operation_functor {
public:
	virtual void operator() (resource_cursor_type input, resource_cursor_type output,
		ResourceManager * rm, Networker * communications, OperationPool * operation_pool) = 0;
};

#endif