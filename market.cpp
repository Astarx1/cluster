#include <zmq.hpp>
#include <iostream>

#include "market/market.hpp"

int main (int argc, char *argv[]){
    Market shops;

    shops.open_market();
    std::cout << "Press Enter when the workers are ready: " << std::endl;
    getchar ();
    while(true);
    
    return 0;
}
