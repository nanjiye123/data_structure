//希尔排序
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int

void ShellSort(ElementType *A, int num)
{
	ElementType tmp;
	int gap, i, j;

	for(gap=num/2; gap>0; gap/=2)//步长
	{
		for(i=gap; i<num; i++)//直接插入排序
		{
			tmp = A[i];
			for(j=i; j>=gap; j-=gap)
			{
				if(tmp < A[j-gap])
					A[j] = A[j-gap];
				else
					break;
			}
			A[j] = tmp;
		}
	}

}

int main()//希尔排序
{
	const int num = 10;
	ElementType A[num] = {49,38,65,97,26,13,27,49,55,4};
	ShellSort(A, num);

	for(int i=0; i<num; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;
    return 0;
}




