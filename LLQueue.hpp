#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
	struct Node {

		Node(Object v, Node * n) : val(v), next(n) {};
		Object val;
		Node * next;

	};
	Node * head = nullptr;
	Node * rear = nullptr;
	int numElements = 0;

public:
	LLQueue(){};

//	In principle, you should have copy constructors and 
// assignment operators implemented.
// I am not going to require it for this assignment.

	~LLQueue()
	{
		while (head != nullptr) {
			Node * other = head;
			head = head -> next;
			delete other;
		}
	};

	int size() const noexcept;
	bool isEmpty() const noexcept;

	Object & front();
	const Object & front() const;

	void enqueue(const Object & elem);

// does not return anything.  Just removes. 
	void dequeue();

	void printQueue();

	LLQueue(const LLQueue & st) {
		Node * tmp = st.head;

		while (tmp != nullptr) {
			enqueue(tmp->val);
			tmp = tmp -> next;
		}
	};

	LLQueue & operator=(const LLQueue & st) {
		Node * tmp = st.head;

		while (tmp != nullptr) {
			enqueue(tmp->val);
			tmp = tmp -> next;
		}
		return *this;
	};
};


template<typename Object>
int LLQueue<Object>::size() const noexcept{
	return numElements;
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept{
	return numElements == 0;
}

template<typename Object>
Object & LLQueue<Object>::front() {
	if (head == nullptr) throw QueueEmptyException("No front of queue");
	return head->val;
}

template<typename Object>
const Object & LLQueue<Object>::front() const {
	if (head == nullptr) throw QueueEmptyException("No front of queue");
	return head->val;
}

template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem) {

	Node* newNode = new Node(elem, nullptr);

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node * tmp = head;
		while (tmp -> next != nullptr) {
			tmp = tmp -> next;
		}
		tmp -> next = newNode;
	}
	rear = newNode;
	numElements++;
}


template<typename Object>
void LLQueue<Object>::dequeue() {

	if (head == nullptr) throw QueueEmptyException("Cannot dequeue empty queue");
	else {

		Node * tmp = head;
		head = head -> next;
		if (head == nullptr) {
			rear = nullptr;
		}
		delete tmp;
		numElements--;
	}
}

template<typename Object>
void LLQueue<Object>::printQueue() {

	Node * tmp = head;

	while (tmp != nullptr) {
		Object o =  (tmp -> val);
		std::cout << o << " ";
		tmp = tmp -> next;
	}

	std::cout << std::endl;
}





#endif 
