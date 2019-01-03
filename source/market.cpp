#include <zmq.hpp>
#include <iostream>

#include "market/market.hpp"

int main (int argc, char *argv[]){
    Market shops;

    shops.open_market();

    while(true);
    
    return 0;
}
