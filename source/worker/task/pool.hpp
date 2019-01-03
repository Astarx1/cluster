#ifndef POOL_HPP
#define POOL_HPP

#include <deque>
#include <map>
#include <thread>
#include <mutex>

#include "operation_pool.hpp"
#include "operation_functions.hpp"
#include "task.hpp"
#include "../resource/interface/resource_manager.hpp"
#include "../network/interfaces/networker.hpp"


namespace Operation {
class ThreadPool : OperationPool {
public:
	ThreadPool(Resource::ResourceManager& resource_manager) :
		m_resource_manager(resource_manager) {
		m_cursor = 0;
		mailbox_connected = false;
	}

	~ThreadPool() {
		is_running = false;
		for(std::size_t i = 0; i < m_threads.size(); ++i) {
			if(m_threads[i].joinable())
				m_threads[i].join();
		}
	}

	task_cursor_type add_task(Task t, bool pending=false) {
		task_cursor_type cur = get_unique_id();
		preserve_task_order.lock();
		m_tasks.insert(std::pair<task_cursor_type, Task>(cur, t));
		m_order_tasks.push_back(cur);
		preserve_task_order.unlock();
		return cur;
	}
	
	task_cursor_type add_task(std::string operation_name, 
		Resource::resource_cursor_type resource_input, Resource::resource_cursor_type resource_output,
		std::deque<task_cursor_type> dependencies, bool pending=false) {
		return add_task(Task(operation_name, resource_input, resource_output, dependencies));
	}

	task_cursor_type add_task(std::string operation_name, Resource::resource_cursor_type resource_input, 
		Resource::resource_cursor_type resource_output, bool pending=false) {
		return add_task(Task(operation_name, resource_input, resource_output));
	}

	void get_task_into_pool(task_cursor_type t) {
		m_order_tasks.push_back(t);
	}

	void run(const int nb_workers) {
		is_running = true;

		if(!mailbox_connected) {
			Misc::ProtectedOut::out(std::string("Please connect mailbox"));
			throw std::string("Error !");
		}
		for(int i = 0; i < nb_workers; i++) {
			m_threads.push_back(std::thread(&ThreadPool::runner, this));
		}
	}

	task_status_type get_status_task(task_cursor_type task) const {
		return ((m_tasks.find(task))->second).current_status();
	}

	void connect_mailbox(Network::Networker * w) {
		mailbox_connected = true;
		m_mailbox = w;
		w->connect_operation_pool(this);
	}

	Resource::ResourceManager * get_resource_manager() {
		return & m_resource_manager;
	}

private:
	TaskList m_tl;
	Resource::ResourceManager& m_resource_manager;
	std::map<task_cursor_type, Task> m_tasks;
	std::deque<task_cursor_type> m_order_tasks;
	std::deque<std::thread> m_threads;

	bool mailbox_connected;
	Network::Networker * m_mailbox;

	task_cursor_type get_unique_id() {
		m_cursor++;
		return m_cursor - 1;
	}
	task_cursor_type m_cursor;

	void runner() {
		bool has_found = false;
		task_cursor_type ct;
		std::deque<task_cursor_type>::iterator it;

		while(is_running) {
			preserve_task_order.lock();
			if(!m_order_tasks.empty()) {
				it = m_order_tasks.begin();
				while (it != m_order_tasks.end()) {
					if (! ((m_tasks.find(*it))->second.current_status()).ended()) {
						ct = *it;
						m_order_tasks.erase(it);
						has_found = true;
					}

				}
			}
			preserve_task_order.unlock();

			if(has_found) {
				Task& t = (m_tasks.find(ct))->second;
				operation_functor * f = m_tl.get_operation(t.get_operation_name());

				(*f)(t.get_input(), t.get_output(), &m_resource_manager, m_mailbox, this);
				t.end();

				has_found = false;
			}
			else {
				// TODO: Add sleeping time !
				;
			}
		}
	}
	std::mutex preserve_task_order;
	bool is_running;
};
};

#endif