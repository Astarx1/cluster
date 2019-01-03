#include <iostream>
#include "worker/network/MailBox.hpp"
#include "worker/task/pool.hpp"


int main (int argc, char *argv[]){
    std::string master_pub;
    std::string master_pull;
    std::string local_port;

    if (argc < 3) {
        std::cout << "Auto-config" << std::endl;
        master_pub = std::string("tcp://localhost:5550");
        master_pull = std::string("tcp://localhost:5551");
        local_port = std::string("5552");
    }
    else {
        master_pub = std::string(argv[1]);
        master_pull = std::string(argv[2]);
        local_port = std::string(argv[3]);
    }

    Network::MailBox shop(master_pub, master_pull, local_port);
    Resource::ResourceManager rm;
    Operation::ThreadPool tp(rm);
    tp.connect_mailbox(&shop);

    tp.run(2);

    while(true);

    return 0;
}
