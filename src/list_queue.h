#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

template <class>
class ArrayQueue;

#include "queue.h"
#include <stdlib.h>
#include <iostream>

template <class T>
struct Node
{
	T data;
	Node *next;

	Node(T data);
};

template <class T>
Node<T>::Node(T data) : data(data), next(0)
{  }

template <class T>
class ListQueue : public Queue<T>
{
	private:
		Node<T> *first;
		Node<T> *last;
	public:
		ListQueue();
		ListQueue(const ListQueue& l);
		ListQueue(ArrayQueue<T> a);
		~ListQueue();

		virtual void enqueue(T elem);
		virtual T peek() const;
		virtual T dequeue(); 
		virtual void print(std::ostream& os) const;
		virtual ListQueue<T> *clone() const;
};

template <class T>
ListQueue<T>::ListQueue() : first(0), last(first)
{  }

template <class T>
ListQueue<T>::ListQueue(const ListQueue& l) :
	Queue<T>(l), first(l.first ? new Node(l.first->data) : 0)
{
	Node<T> *tmp = first;

	for(Node<T> *node = l.first->next; node; node = node->next, tmp = tmp->next)
		tmp->next = new Node<T>(node->data);

	last = tmp;
}

template <class T>
ListQueue<T>::~ListQueue<T>()
{
	Node<T> *next;
	for(Node<T> *node = first; node; node = next)
	{
		next = node->next;
		delete node;
	}
}

template <class T>
void ListQueue<T>::enqueue(T elem)
{
	Node<T> *node = new Node<T>(elem);
	if(!first)
		first = last = node;
	else 
	{
		last->next = node;
		last = node;
	}

	this->len++;
}

template <class T>
T ListQueue<T>::peek() const
{
	return first != 0 ? first->data : 0;
}

template <class T>
T ListQueue<T>::dequeue()
{
	if(this->is_empty())
		throw "ListQueue is empty.\n";

	Node<T> *tmp = first;
	T data_tmp = tmp->data;

	first = first->next;
	delete tmp;

	this->len--;
	return data_tmp;
}

template <class T>
void ListQueue<T>::print(std::ostream& os) const
{
	for(Node<T> *node = first; node; node = node->next)
		os << node->data << ' ';
	os << '\n';
}

template <class T>
ListQueue<T> *ListQueue<T>::clone() const
{
	return new ListQueue(*this);
}

#endif
