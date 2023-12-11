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

		virtual void print(std::ostream& os) const
		{
			for(Node<T> *node = first; node; node = node->next)
				os << node->data << ' ';
			os << '\n';
		}

		virtual ListQueue<T> *clone() const
		{
			return new ListQueue(*this);
		}

	public:

		ListQueue() : first(0), last(first)
		{  }

		ListQueue(const ListQueue& l) :
			Queue<T>(l), first(l.first ? new Node(l.first->data) : 0)
		{
			Node<T> *tmp = first;

			for(Node<T> *node = l.first->next; node; node = node->next, tmp = tmp->next)
				tmp->next = new Node<T>(node->data);

			last = tmp;
		}

		~ListQueue()
		{
			Node<T> *next;
			for(Node<T> *node = first; node; node = next)
			{
				next = node->next;
				delete node;
			}
		}

		virtual void enqueue(T elem)
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

		virtual T peek() const
		{
			return first != 0 ? first->data : 0;
		}

		virtual T dequeue() 
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
};

#endif
