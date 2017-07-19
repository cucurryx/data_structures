#include"set_b.h"
#include<time.h>

int main()
{
    Set custom_set;
    for (int i = 1; i != 100000; ++i) {
        auto num = (long long)rand()*100000;
        num %=i;

        custom_set.insert((double) i);
        custom_set.insert((double) (-i));
    //    custom_set.erase((double)(num));

		//custom_set.count((double)i);
	//	custom_set.count((double)-i);
    }
	cout<<"End insert"<<endl;
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
