Do not forget to install libzmq3-dev before running


TODO :
- Data sharing between workers protocole ("data sales")
	- In link with the file transfer protocole
	- Need to chose a format to exchange data
- Dynamic deployement : workers must get defined by a YAML-like file
	- If possible, workers must be launchable from master
	- Ports should at least be decided by the user after CLI launching
- Unit Testing !!!
- Python Bindings (MLFactory)
- Refactoring :
	- more namespaces !!!
	- Separation declarations/definitions
	- Inclusions refactoring (it is a HUGE mess)
	- CMake build
- Task dependencies management (in progress) > Essential for load management
- Memory management :
	- Virtual/Physical Memory management > Near-to Essential for real load management
	- Collision prevention between workers for data shared > Essential 
- Better network management/resilience
	- Acknowledgement support
	- Message answer support
- Better non-concurrency between workers support ? Master should have the last word but nonetheless, it seems quite shaky
	- Paxos-like algorithm for decision ? (seems overkill)
- Mailbox shared between multiple thread to add more if needed (like during a data transfer)
- File Transfer : 
	- Use a shared file system like HDFS with a shared hashTable
	- The API used must be transparent with ResourceManager
- More operations : 
	- MapReduce (+ aggreg, combine, flatmap...)
	- Database management, at least Postgre & Cassandra
	- Usual math operations
- Communication securisation
- Reward protocole (in link with "better non-concurrency" and "task topology analysis")
- Possession of resources by tasks : 
	- A resource must be destroyed when it is not used anymore
	- A task must be able to delay resource destruction if
		- It is handed to another task
		- It is shared between several parallel tasks
		- It is an output that can be used by another task
- Lighten messages
	- E.g : version is currently defined by an integer between message beginning and first comma > Reduce int to the n first bits
	- Identifiers are still the URL of the worker > an ID should be attributed at handshake in order just to send some bits
- Make possible for a worker to jump from a task to another even if the task is not over
	- E.g : When receiving data, it may be slower than the processing of the data. Therefore performance could be gained by giving a "worker back" in while(not_over) kind of loop if the loop has iterated many times without receiving anything 
- UTF-8 message support
- Multi OS Support
- System commands launching from operations
- Command launching from message (in progress) > Essential for cluster management
	- In the way with the pending task protocole
- Heartbeats for workers
- Task progress as float and not just ended or not
- Result transfer improvement
- Task Topology analysis
	- Attribution of a weight to each tasks to improve task repartition
	- Why not rewrite the TaskPool runner with a directed acyclic graph manager like Taskflowcpp  
- Support other network protocole
	- UDP seems important
	- IPCs seem to offer great performance opportunities (ZMQ natively handles it)



Message sent :

Message Template version v1 : 
"[MessageVersion],[AuthorID],[ReceiverID],[MessageID],[AckNumber],[OperationID],[Data]"
[MessageID] :
A (hopefully) unique number among all messages to identify the message. Collision being not vary harmful in the long term but being potentially harmful in the short term, a random integer in the whole range of integer is recommanded. 
[Acknumber] :
0 or 1 if the author expects a confirmation of the message reception, in which case the receiver will send the same message with an acknowledge number of 2, with the operation ID and the data. A value of 0 means that no response is expected.
[OperationID] :
A value of the operation concerned. A few are reserved :
- 0 : kill computations
- 1 : start computations
- 2 : a new shop has been opened :
	- 20 : A shop ask for market authorization
	- 21 : Market welcomes a new open shop
- 4 : Shop Status to send :
	- 40 : Liveliness heartbeat
- 5 : Data :
	- 50 : A shop is selling data
	- 51 : A shop is buying data
- 6 : Operations :
	- 60 : A new task is offered
	- 61 : A shop has accepted a task
- 7 : Secure message
	- 70 : Secure Handshake (authentification + key exchange)
	- 71 : [Data] contains the message to decrypt 