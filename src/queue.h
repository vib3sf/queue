#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
	protected:
		int len;

	public:
		virtual void enqueue(T elem) = 0;
		virtual T dequeue() = 0; 
		virtual T peek() const = 0;

		Queue();
		Queue(int len);

		inline int size() const;
		inline bool is_empty() const;
		Queue& operator+=(const T& t);
};

template <typename T>
Queue<T>::Queue() : len(0)
{  }

template <typename T>
Queue<T>::Queue(int len) : len(len)
{  }

template <typename T>
inline int Queue<T>::size() const
{
	return len;
}

template <typename T>
inline bool Queue<T>::is_empty() const
{
	return len == 0;
}

template <typename T>
Queue<T>& Queue<T>::operator+=(const T& t)
{
	enqueue(t);
	return *this;
}


#endif
