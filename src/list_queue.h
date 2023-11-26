#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

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
		~ListQueue();

		virtual void enqueue(T elem);
		virtual T peek() const;
		virtual T dequeue(); 
		virtual void print(std::ostream& os) const;

		template <class U>
		friend ListQueue<U> operator+(const ListQueue<U> &a, const ListQueue<U> &b);
};

template <class T>
ListQueue<T>::ListQueue() : first(0), last(first)
{  }

template <class T>
ListQueue<T>::ListQueue(const ListQueue& l) :
	Queue<T>(l.len), first(l.first ? new Node(l.first->data) : 0)
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

	last->next = node;
	last = node;

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
		exit(1);

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
ListQueue<T> operator+(const ListQueue<T> &a, const ListQueue<T> &b)
{
	ListQueue<T> queue;
	Node<T> *node = a.first, *q_node;
	bool first_passed = false;

	q_node = new Node(node->data);
	queue.first = q_node;

	while(node || !first_passed)
	{
		if(!node)
		{
			node = b.first;
			first_passed = true;
		}

		q_node->next = new Node(node->data);

		node = node->next;
		q_node = q_node->next;
	}
	
	queue.len = a.len + b.len;
	return queue;
}

#endif
