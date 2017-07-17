#include"RBtree.h"

int main()
{
	RedBlackBST<double> myTree;
	for(double i = 0; i < 10; ++i)
	{
		myTree.insert(i*0.5);
	}
	cout<<myTree.size()<<endl;
	if(!myTree.empty())
		cout<<"hello world"<<endl;
	cout<<myTree.findMin()->key<<endl;
	cout<<myTree.findMax()->key<<endl;

	myTree.print();
	cout<<endl;
	myTree.deleteMin();
	myTree.deleteMax();
	myTree.deleteKey(1);
	myTree.print();

	return 0;
}
