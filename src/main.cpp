#include "array_queue.h"
#include "list_queue.h"
#include "queue.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <cstring>
#include <string>


void sum(ListQueue<int> a, ListQueue<int> b)
{
	std::cout << a + b;
}

int main()
{
	ArrayQueue<int> queue1;
	ListQueue<int> queue2;
	queue1 += 1;
	queue1 += 2;
	queue1 += 3;
	queue1 += 4;
	
	queue2 += 5;
	queue2 += 6;
	sum(queue1, queue2);
	
	return 0;
}
