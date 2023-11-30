#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "queue.h"
#include "list_queue.h"
#include <iostream>
#include <stdlib.h>

template <class T>
class ArrayQueue : public Queue<T>
{
	private:
		int arr_size;
		T *array;

		inline bool array_is_full();
		void resize_array(int new_size, int cp_size);

	public:
		ArrayQueue();
		ArrayQueue(int arr_size);
		ArrayQueue(const ArrayQueue& a);
		ArrayQueue(bool a);
		~ArrayQueue();

		virtual void enqueue(T elem);
		virtual T dequeue(); 
		virtual T peek() const;
		virtual void print(std::ostream& os) const;
		virtual ArrayQueue<T> *clone() const;
};

template <class T>
ArrayQueue<T>::ArrayQueue() : 
	arr_size(4), array(new T[arr_size])
{ }

template <class T>
ArrayQueue<T>::ArrayQueue(int arr_size) : 
	Queue<T>(arr_size), arr_size(arr_size), array(new T[arr_size])
{ }

template <class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& a) : 
	Queue<T>(a), arr_size(a.arr_size), array(new T[arr_size])
{
	for(int i = 0; i < this->len; i++)
		array[i] = a.array[i];
}

template <class T>
ArrayQueue<T>::~ArrayQueue()
{
	delete[] array;
}

template <class T>
inline bool ArrayQueue<T>::array_is_full()
{
	return arr_size == this->len;
}

template <class T>
void ArrayQueue<T>::resize_array(int new_size, int cp_size)
{
	T *tmp = new T[new_size];
	for(int i = 0; i < cp_size; i++)
		tmp[i] = array[i];

	delete[] array;
	array = tmp;
}

template <class T>
void ArrayQueue<T>::enqueue(T elem)
{
	if(array_is_full())
	{
		arr_size *= 2;
		resize_array(arr_size, this->len);
	}

	array[this->len] = elem;
	this->len++;
}

template <class T>
T ArrayQueue<T>::peek() const
{
	return this->is_empty() ? 0 : array[0];
}

template <class T>
T ArrayQueue<T>::dequeue()
{
	if(this->is_empty())
		throw "ArrayQueue is empty.\n";

	T tmp = array[0];

	for(int i = 1; i < this->len; i++)
		array[i - 1] = array[i];
	this->len--;

	if(this->len < arr_size / 4)
	{
		arr_size /= 2;
		resize_array(arr_size, this->len);
	}

	return tmp;
}

template <class T>
void ArrayQueue<T>::print(std::ostream& os) const
{
	for(int i = 0; i < this->len; i++)
		os << array[i] << ' ';
	os << '\n';
}

template <class T>
ArrayQueue<T> *ArrayQueue<T>::clone() const
{
	return new ArrayQueue(*this);
}

#endif
