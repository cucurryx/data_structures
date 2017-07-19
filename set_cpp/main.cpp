#include"set.h"
#include<time.h>
#include <stdlib.h>

int main()
{
    Set custom_set;
    for (int i = 0; i != 100000; ++i) {
	//	long long num = (long long)rand()*100000;
	//	num %= i;
        custom_set.insert((double) i);
        custom_set.insert((double) (i));
     //   custom_set.erase((double)(rand()%i));

		custom_set.count((double)i);
		custom_set.count((double)-i);
    }
	cout<<custom_set.size()<<endl;
	cout<<custom_set.findMax()<<" "<<custom_set.findMin()<<endl;
	custom_set.deleteMax();
	custom_set.deleteMin();
	cout<<"End insert"<<endl;
	cout<<custom_set.size()<<endl;
	custom_set.print();

	if(custom_set.contain(6))
		cout<<"Get it"<<endl;
	for(int i = 1; i != 100000; ++i)
	{
		auto num = (long long)rand()*100000;
		num %= i;
		cout<<num<<" "<<i<<endl;
		custom_set.erase((double)num);
	}
	cout<<"end";
    return 0;
}
