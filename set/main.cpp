#include"set.h"

int main()
{
	mySet<double> testSet;
	for(int i = 0; i < 10; ++i)
		testSet.insert(i + 0.5);
	testSet.erase(1.5);
	for(int i = 0; i < 8; ++i)
		testSet.erase(i+0.5);
//	testSet.clear();
	cout<<testSet.size()<<endl;
	return 0;
}
