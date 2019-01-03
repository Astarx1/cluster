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


Cluster Definition example
machines:
	- name: PC1
	  user: dummy_user
	  password: dummy_pwd
	  ip: 192.168.1.10
	  services:
	  	- name: master
	  	  publish_port: 5550
	  	  port: 5551
	  	  master: true
	    - name: worker1
	  	  port: 5552
	- name: PC2
	  user: dummy_user
	  password: dummy_pwd
	  ip: 192.168.1.11
	  services:
	    - name: worker1
	  	  port: 5552
	    - name: worker2
	  	  port: 5553

