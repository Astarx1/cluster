#ifndef PROTECTED_OUTPUT_HPP
#define PROTECTED_OUTPUT_HPP

#include <mutex>

namespace Misc {
class ProtectedOut {
public:
	static void out(const std::string& in) {
		Misc::ProtectedOut::no_double.lock();
		std::cout << in << std::endl;
		Misc::ProtectedOut::no_double.unlock();
	}

	static std::mutex no_double;
};
std::mutex ProtectedOut::no_double;
};

#endif