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
		free(cur);
		cur = next;
	}
}

template <typename E>
bool SLinkedList<E>::empty() const
{
	return head == NULL;
}

template <typename E>
const E& SLinkedList<E>::front() const
{
	if( head == NULL )
		throw new LinkedException("empty linked list");

	return head->node;
}

template <typename E>
const E& SLinkedList<E>::last() const 
{
	if( tail == NULL )
		throw new LinkedException("empty linked list");

	return tail->node;
}

template <typename E>
void SLinkedList<E>::addFront(const E& e)
{
	SNode<E> *s = (SNode<E> *) malloc(sizeof(SNode<E>));
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

template <typename E>
void SLinkedList<E>::addLast(const E& e)
{
	SNode<E> *s = (SNode<E> *) malloc(sizeof(SNode<E>));
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

template <typename E>
void SLinkedList<E>::removeFront()
{
	if( head == NULL )
		throw new LinkedException("empty linked list");

	SNode<E> *next = head->next;
	free(head);

	head = next;		
}

template <typename E>
void SLinkedList<E>::removeLast()
{
	if( tail == NULL )
		throw new LinkedException("empty linked list");

	SNode<E> *prev = tail->prev;
	free(tail);

	tail = prev;	
}

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

	SLinkedList<int> intList;
	
	int i = 0; 
	for(i = 0; i < 50; i++)
	{
		int n = rand() % 100 + 1;
		intList.addLast(n);
	}
	intList.print();

	SLinkedList<string> stringList;

	/*for(i = 0; i < 100; i++)
	{		
		char szBuff[100];	
		sprintf(szBuff, "Customer %d", (i + 1));
		string val = szBuff;
		stringList.addLast(val);
	}
	stringList.print();*/

	return 0;
}