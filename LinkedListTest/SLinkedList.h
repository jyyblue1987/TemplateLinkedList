#pragma once

template <typename E>
struct SNode {
	E node;
	SNode* next;
	SNode* prev;
};

template <typename E>
class SLinkedList {	// singly linked list
public:
	SLinkedList();	// empty list constructor
	~SLinkedList();
	bool empty() const;
	const E& front() const;
	const E& last() const;
	void addFront(const E& e);
	void addLast(const E& e);
	void removeFront();
	void removeLast();
	void print();

private:
	SNode<E>* head;
	SNode<E>* tail;
};