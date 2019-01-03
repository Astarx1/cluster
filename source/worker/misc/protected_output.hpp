#ifndef PROTECTED_OUTPUT_HPP
#define PROTECTED_OUTPUT_HPP

#include <mutex>

class ProtectedOut {
public:
	static void out(const std::string& in) {
		ProtectedOut::no_double.lock();
		std::cout << in << std::endl;
		ProtectedOut::no_double.unlock();
	}

	static std::mutex no_double;
};

#endif