#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "queue.h"
#include <iostream>
#include <stdlib.h>

template <class T>
class ArrayQueue : public Queue<T>
{
	private:
		int arr_size;
		int expend_mod;
		T *array;

		inline bool array_is_full();
		void resize_array(int new_size, int cp_size);

	public:
		ArrayQueue();
		ArrayQueue(int arr_size);
		ArrayQueue(const ArrayQueue& a);
		~ArrayQueue();

		virtual void enqueue(T elem);
		virtual T dequeue(); 
		virtual T peek() const;
		virtual void print(std::ostream& os) const;

		template <class U>
		friend ArrayQueue<U> operator+(const ArrayQueue<U> &a, const ArrayQueue<U> &b);
};

template <class T>
ArrayQueue<T>::ArrayQueue() : 
	arr_size(4), expend_mod(2), array(new T[arr_size])
{ }

template <class T>
ArrayQueue<T>::ArrayQueue(int arr_size) : 
	Queue<T>(arr_size), arr_size(arr_size), 
	expend_mod(2), array(new T[arr_size])
{ }

template <class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& a) : 
	Queue<T>(a.len), arr_size(a.arr_size), array(new T[arr_size])
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
		arr_size *= expend_mod;
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
		exit(1);
	T tmp = array[0];

	for(int i = 1; i < this->len; i++)
		array[i - 1] = array[i];
	this->len--;

	if(this->len < arr_size / expend_mod / 2)
	{
		arr_size /= expend_mod;
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
ArrayQueue<T> operator+(const ArrayQueue<T> &a, const ArrayQueue<T> &b)
{
	int size = b.len + a.len;
	ArrayQueue<T> queue(size);
	for(int i = 0; i < size; i++)
		queue.array[i] = a.len > i ? a.array[i] : b.array[i - size + b.len];

	return queue;
}

#endif
 
