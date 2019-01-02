#include <iostream>
#include "worker/worker.hpp"
#include "worker/pool.hpp"


int main (int argc, char *argv[]){
    MailBox shop;
	ResourceManager rm;
	ThreadPool tp(rm);
	tp.connect_mailbox(&shop);

	std::string filename("test.txt");
	resource_cursor_type file = rm.add_value(filename);
	resource_cursor_type nblines = rm.add_value(0);

    tp.add_task(Task(std::string("GetNBLine"), file, nblines));
    tp.run(2);

    std::cout << "-----------------" << std::endl;
    Message sent("romain romain romain romain");
    sent.author.name = std::string("tcp://localhost:5551");
	resource_cursor_type hey = rm.add_value(sent);
	resource_cursor_type nbocur = rm.add_value(0);
    std::cout << "Running counting occurences task" << std::endl;
    tp.add_task(Task(std::string("LaunchCountOccurencesWord"), hey, nbocur));
    std::cout << "-----------------" << std::endl;
    while(true);

    return 0;
}
