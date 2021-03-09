#include <iostream>
#include<string>
#include <exception>
#include <time.h>

#include "SLinkedList.h"

using namespace std;

class RuntimeException : public exception {
private:
	string errorMsg;
public:
	RuntimeException(const string& err) {
		errorMsg = err;
	}
	string getMessage() const { return errorMsg; }
};

class LinkedException : public RuntimeException {
public:
	LinkedException(const string& err) : RuntimeException(err) {}
};

template <typename E>
SLinkedList<E>::SLinkedList() 
{
	head = NULL;
	tail = NULL;
}

template <typename E>
SLinkedList<E>::~SLinkedList() 
{
	SNode<E> *cur = head;
	SNode<E> *next = NULL;
	while(cur != NULL) {
		next = cur->next;
		delete cur;
		cur = next;
	}
}

// O(1)
template <typename E>
bool SLinkedList<E>::empty() const 
{
	return head == NULL;
}

// O(1)
template <typename E>
const E& SLinkedList<E>::front() const
{
	if( head == NULL )
		throw new LinkedException("empty linked list");

	return head->node;
}

// O(1)
template <typename E>
const E& SLinkedList<E>::last() const
{
	if( tail == NULL )
		throw new LinkedException("empty linked list");

	return tail->node;
}

// O(1)
template <typename E>
void SLinkedList<E>::addFront(const E& e)
{
	SNode<E> *s = new SNode<E>();
	s->node = e;

	if( head == NULL )	// empty list
	{
		s->next = NULL;
		s->prev = NULL;
		head = s;
		tail = s;
	}
	else
	{
		s->next = head;
		s->prev = NULL;
		head->prev = s;
		head = s;
	}
}

// O(1)
template <typename E>
void SLinkedList<E>::addLast(const E& e)
{
	SNode<E> *s = new SNode<E>();
	s->node = e;

	if( head == NULL )	// empty list
	{
		s->next = NULL;
		s->prev = NULL;
		head = s;
		tail = s;
	}
	else
	{
		s->next = NULL;
		s->prev = tail;
		tail->next = s;

		tail = s;		
	}
}

// O(1)
template <typename E>
void SLinkedList<E>::removeFront()
{
	if( head == NULL )
		throw new LinkedException("empty linked list");

	SNode<E> *next = head->next;
	delete head;

	if( next == NULL )
	{
		tail = NULL;
		return;
	}

	head = next;		
	head->prev = NULL;	
}

// O(1)
template <typename E>
void SLinkedList<E>::removeLast()
{
	if( tail == NULL )
		throw new LinkedException("empty linked list");

	SNode<E> *prev = tail->prev;
	delete tail;

	if( prev == NULL )
	{
		head = NULL;
		return;
	}

	tail = prev;	
	tail->next = NULL;
}

// O(n)
template <typename E>
void SLinkedList<E>::print()
{
	SNode<E> *cur = head;
	SNode<E> *next = NULL;
	int i = 0;
	while(cur != NULL) {
		next = cur->next;
		if( i > 0 )
			cout << ", ";

		cout << cur->node;
		cur = next;
		i++;
	}

	cout << endl;
}


int main() {
	srand ( time(NULL) );

	try {
		SLinkedList<int> intList;
		cout << intList.empty() << endl;
		//cout << intList.front() << endl;
		//intList.removeFront();
	
		int i = 0; 
		for(i = 0; i < 50; i++)
		{
			int n = rand() % 100 + 1;
			intList.addLast(n);
		}
		intList.print();

		SLinkedList<string> stringList;

		for(i = 0; i < 100; i++)
		{		
			char szBuff[100];	
			sprintf(szBuff, "Customer %d", (i + 1));
			string val = szBuff;
			stringList.addLast(val);
		}
		stringList.print();

		stringList.removeLast();
		stringList.print();

		stringList.removeFront();
		stringList.print();
	} catch(LinkedException& e) {
		cout << e.getMessage() << endl;
	}

	return 0;
}