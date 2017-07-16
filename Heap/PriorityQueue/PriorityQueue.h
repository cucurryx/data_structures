#include<iostream>
#include<vector>
#include<algorithm>
#define Child(i) (2*i);
using namespace std;
//priorty_queue 需要实现 empty(), size(), top(), push(const T&), pop()方法


template <typename T>
class priority_queue
{
public:
	priority_queue();
	priority_queue(size_t , T);
	~priority_queue(){}

	bool empty();
	size_t size();
	T top();
	void push(const T&);
	void pop();

	void show()
	{
		for(auto x: elements)
			cout<<x<<" "<<endl;
	}
private:
	void resizeQueue();
	vector<T> elements;
	size_t queueSize;
};

template <typename T>
void priority_queue<T>::resizeQueue()
{
	if(elements.size() == 0)
		elements.resize(1);
	if(elements.size()-1 == queueSize)
		elements.resize(2 * elements.size());
}

template <typename T>
priority_queue<T>::priority_queue():
	elements(), queueSize(0){}

template <typename T>
priority_queue<T>::priority_queue(size_t _queueSize, T element):
	elements(queueSize, element), queueSize(_queueSize){}

template <typename T>
bool priority_queue<T>::empty()
{
	return queueSize == 0;
}

template <typename T>
size_t priority_queue<T>::size()
{
	return queueSize;
}

template <typename T>
T priority_queue<T>::top()
{
	if(empty())
	{
		cout<<"Error: Empty queue"<<endl;
		exit(0);
	}
	return elements[1];
}

template <typename T>
void priority_queue<T>::push(const T& newVal)
{
	resizeQueue();
	int pos;
	for(pos = ++queueSize; pos > 1 && elements[pos/2] > newVal; pos /= 2)
		elements[pos] = elements[pos/2];
	elements[pos] = newVal;
}

template <typename T>
void priority_queue<T>::pop()
{
	if(empty())
		exit(0);
	T temp = elements[queueSize--];
	int child, i;
	for(i = 1; 2*i <= queueSize; i = child)
	{
		child = 2*i;
		if(elements[child+1] < elements[child] && child != queueSize)
			++child;

		if(elements[child] < temp)
			elements[i] = elements[child];
		else
			break;
	}
	elements[child] = temp;
}
