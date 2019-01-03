Do not forget to install libzmq3-dev before running


TODO :
Check https://trello.com/b/6DIQHIpM/cluster


Message sent :

Message Template version v1 : 
"[MessageVersion],[AuthorID],[ReceiverID],[MessageID],[AckNumber],[OperationID],[Data]"

[MessageID] :

A (hopefully) unique number among all messages to identify the message. Collision being not vary harmful in the long term but being potentially harmful in the short term, a random integer in the whole range of integer is recommanded. 


[Acknumber] :

0 or 1 if the author expects a confirmation of the message reception, in which case the receiver will send the same message with an acknowledge number of 2, with the operation ID and the data. A value of 0 means that no response is expected.


[OperationID] :

The network operation concerned. A few are reserved (not implemented yet !) :
- 0 : Computations
	- 00 : kill computations
	- 01 : start computations
- 1 : Network life :
	- 10 : Market life
		- 100 : A shop ask for market authorization
		- 101 : Market welcomes a new open shop
	- 11 : Agreement protocole
	- 12 : Liveliness heartbeat
- 2 : Data :
	- 20 : A shop is selling data
	- 21 : A shop is buying data
- 3 : Tasks :
	- 30 : A new task is offered
	- 31 : A shop has accepted a task
	- 32 : A task is no longer available
	- 33 : Do task
		- 330 : Other tasks
		- 331 : Math Task
		- 332 : Data Acquisition Task
		- 333 : Data Structure Task
- 4 : Secure message
	- 40 : Secure Handshake (authentification + key exchange)
	- 41 : [Data] contains the message to decrypt 
	- 42 : [Data] contains the message to authentify 
- 5 : State Agreement
	- 50 : State Description
		- 500 : (Answer) State accepted 
		- 500 : (Answer) State refused 