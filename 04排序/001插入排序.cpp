//直接插入排序
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int

void InsertionSort(ElementType *A, int num)
{
	int pos, i;
	ElementType tmp;
	for(pos=1; pos<num; pos++)//从1开始，因为位置0不需要向前面比较
	{
		tmp = A[pos];
		for(i=pos; i>0 && A[i-1]>tmp; i--)//依次向后移动，从小到大排序
		{
			A[i] = A[i-1];
		}
		A[i] = tmp;
	}
}

int main()//插入排序
{
	const int num = 6;
	ElementType A[num] = {34,8,64,51,32,21};
	InsertionSort(A, num);

	for(int i=0; i<num; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;
    return 0;
}




