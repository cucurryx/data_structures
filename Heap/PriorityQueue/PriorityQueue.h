#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;
using T = double;

class Priority_queue
{
public:
	Priority_queue(): count(0){}
    bool empty() const;
    size_t size() const;
    const T& top() const;
    void push(const T& val);
    void pop();
private:
	void reSize();
	size_t count;
 	vector<T> vec;
};

void Priority_queue::reSize()
{
	if(vec.size() == 0)
		vec.resize(1);
	if(count == vec.size()-1)
		vec.resize(vec.size()*2);
}

bool Priority_queue::empty() const
{
	return size() == 0;
}

size_t Priority_queue::size() const
{
	return count;
}

const T& Priority_queue::top() const
{
	return *(++vec.begin());
}

void Priority_queue::push(const T& val)
{
	reSize();
	int i = ++count;
	for(; vec[i/2] > val && i > 1; i /= 2)
		vec[i] = vec[i/2];
	vec[i] = val;
}

void Priority_queue::pop()
{
	if(empty())
		return;

	T tmp = vec[count--];
	int i, child;
	for(i = 1; 2*i <= count; i = child)
	{
		child = 2*i;
		if(vec[child] > vec[child+1] && child != count)
			++child;
		if(tmp > vec[child])
			vec[i] = vec[child];
		else
			break;
	}
	vec[i] = tmp;
}
