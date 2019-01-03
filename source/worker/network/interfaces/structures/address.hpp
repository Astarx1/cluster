#ifndef ADDRESS_HPP
#define ADDRESS_HPP

namespace Network {
typedef struct Address {
	Address() { ; }
	Address(std::string adress) : adr(adress), name(adress) { ; }
	Address(std::string adress, std::string name_adr) : adr(adress), name(name_adr) { ; }
	
	std::string adr;
	std::string name;
} Address;
};

#endif