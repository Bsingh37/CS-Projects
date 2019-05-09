#include <iostream>

/*
The purpose of this lab is to be familiar with queues. The lab 
uses the concept of queue as the base. Queue is a data structure 
designed to operate in FIFO (First in First out) context. In queue 
elements are inserted from rear end and get removed from front end. 
Queue class is container adapter. Container is an objects that hold 
data of same type. One common application of a queue is to simulate 
some real-world process in order to better understand it. For this 
lab, we are modeling the management of blocks of storage used to store files.


\newpage
This is the header file that i included in order to store the
maps in a queue. We were given a choice to either store it in 
a circular array or in a linked list. I chose the linked list
way as it seemed the most comprehensible to me.*/
struct Node{
	std::string data = "";
	Node* next = nullptr; //basic Node declaration
};

struct Queue{	 //declaring the queue
	void pop(Node*& head);
	void push(Node*& tail, Node*& head, std::string data);
};
/*the functions that take out the value from the queue*/
void Queue::pop(Node*& head){
    if (head == nullptr) return;
    Node *temp = head;
    head = head -> next;
    delete temp;
}
/*the fucntion that adds into the queue when called*/
void Queue::push(Node*& tail, Node*& head, std::string data){
	Node *newnode = new Node;
	newnode->data = data;
	newnode->next = nullptr;
	if(head==nullptr){head = newnode;}
	else{tail->next=newnode;
		tail=newnode;}
}
