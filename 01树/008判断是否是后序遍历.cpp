#include <iostream>
using namespace std;

bool CanPostOrder(const int *a, int size)
{
	if(size <= 1)//如果只有一个节点，则一定是后序的结果
	{
		return true;
	}
	int root = a[size-1];//序列末尾是根节点
	//根据root将整个序列分成两部分
	int nleft = 0;//分割前半部分序列的位置
	while(nleft < size-1)
	{
		if(a[nleft] > root)
			break;
		else
			nleft++;
	}
	int nright = size-2;//分割后半部分序列的位置
	//size-1是根节点
	while(nright >= 0)
	{
		if(a[nright] < root)
			break;
		else
			nright--;
	}
	if(nright != nleft-1)//无法根据root分成两部分
		return false;

	return CanPostOrder(a, nleft)            //左子树
	&& CanPostOrder(a+nleft, size-nleft-1);  //右子树
}

int main()//给一个序列，判断是否是二叉查找树的后序遍历
{
	int a[] = {1,2,5,4,3};//给定的序列
	bool b = CanPostOrder(a, sizeof(a)/sizeof(int));//判断函数
	cout<< b <<endl;
	return 0;
}
