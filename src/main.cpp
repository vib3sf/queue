#include "list_queue.h"
#include <iostream>

void print(const Queue<int>& queue)
{
	std::cout << queue.peek()  << ' ' <<queue.size() << '\n';
}

int main()
{
	ListQueue<int> queue;
	queue.enqueue(9);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(1);
	queue.dequeue();
	queue += 5;	
	queue += 5;	
	std::cout << queue.peek() << ' ' << queue.size() << '\n';

	ListQueue<int> queue1;
	queue1 += 4;
	queue1 += 3;
	queue1 += 3;
	print(queue1);
	print(queue + queue1);

	return 0;
}
