#ifndef QUEUE_H
#define QUEUE_H

#include <ostream>
template <class T>
class Queue
{
	protected:
		int len;

		virtual Queue<T> *clone() const = 0;
		virtual void print(std::ostream& os) const = 0;

	public:
		virtual void enqueue(T elem) = 0;
		virtual T dequeue() = 0; 
		virtual T peek() const = 0;

		Queue() : len(0)
		{  }

		Queue(int len) : len(len)
		{  }

		Queue(const Queue& q) : len(q.len)
		{  }

	 	virtual ~Queue() 
		{  }

		inline int size() const
		{
			return len;
		}

		inline bool is_empty() const
		{
			return len == 0;
		}

		const Queue& operator+=(const T& t)
		{
			enqueue(t);
			return *this;
		}

		const Queue& operator+=(const Queue<T> &q)
		{
			Queue<T> *copy = q.clone();
			while(!copy->is_empty())
				enqueue(copy->dequeue());

			return *this;
		}
		
		const Queue& operator*=(int mul)
		{
			Queue<T> *copy = clone();
			const int prev_len = len;
			T *data_cp = new T[prev_len];

			for(int i = 0; i < len; i++)
				data_cp[i] = copy->dequeue();

			for(int i = 0; i < mul - 1; i++)
				for(int j = 0; j < prev_len; j++)
					enqueue(data_cp[j]);

			delete[] data_cp;

			return *this;
		}

		template <class U>
		friend std::ostream& operator<< (std::ostream& os, const Queue<U>& q)
		{
			q.print(os);
			return os;
		}
};

#endif
