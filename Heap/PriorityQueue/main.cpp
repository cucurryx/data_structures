#include"PriorityQueue.h"

int main()
{
	Priority_queue myQueue;
	for(int i = 0; i < 100; ++i)
		myQueue.push(double(i));

	for(int i = 0; i < 100; ++i)
	{
		cout<<myQueue.top()<<" ";
		myQueue.pop();
	}

	return 0;
}
