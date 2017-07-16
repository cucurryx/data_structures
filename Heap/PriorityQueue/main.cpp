#include"PriorityQueue.h"

int main()
{
	priority_queue<int> myQueue;

	for(int i = 0; i < 100; ++i)
		myQueue.push(i);
	//myQueue.show();
	for(int i = 0; i < 100; ++i)
	{
		cout<<myQueue.top()<<" ";
		myQueue.pop();
	}

	return 0;
}
