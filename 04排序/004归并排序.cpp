//归并排序
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int

void Merge(ElementType *A, ElementType *tmpArray, int Lpos, int Rpos, int RightEnd)
{//Lpos是左半部分的start，Rpos是右半部分的start，RightEnd是右半部分的end
	int LeftEnd = Rpos - 1;
	int TmpPos = Lpos;//tmpArray的下标
	int NumElements = RightEnd - Lpos + 1;

	while( Lpos <= LeftEnd && Rpos <= RightEnd)//主循环
	{//从左半部分和右半部分选择最小的元素放入tmpArray
		if(A[Lpos] <= A[Rpos])//从小到大排序
		{
			tmpArray[TmpPos++] = A[Lpos++];
		}
		else
		{
			tmpArray[TmpPos++] = A[Rpos++];
		}
	}
	while(Lpos <= LeftEnd)//复制剩下的左半部分
	{
		tmpArray[TmpPos++] = A[Lpos++];
	}
	while(Rpos <= RightEnd)//复制剩下的右半部分
	{
		tmpArray[TmpPos++] = A[Rpos++];
	}

	//将排好序的tmpArray复制到A
	for(int i=0; i<NumElements; i++, RightEnd--)
	{
		A[RightEnd] = tmpArray[RightEnd];
	}
}

void MSort(ElementType *A, ElementType *tmpArray, int left, int right)
{
	int center;
	if(left < right)
	{
		center = (left + right) / 2;
		MSort(A, tmpArray, left, center);//左半部分start和end
		MSort(A, tmpArray, center+1, right);//右半部分start和end
		Merge(A, tmpArray, left, center+1, right);//左半部分start、右半部分start、右半部分end
	}
}

void Mergesort(ElementType *A, int num)//归并排序入口
{
	ElementType *tmpArray;
	tmpArray = (ElementType*)malloc(num * sizeof(ElementType));
	if(NULL == tmpArray)
	{
		cout<<"No space for tmparray."<<endl;
		return;
	}
	
	MSort(A, tmpArray, 0, num-1);
	free(tmpArray);
}

int main()
{
	ElementType A[] = {24,13,26,1,2,27,38,15};
	int num = 8;
	Mergesort(A, num);

	for(int i=0; i<num; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;

    return 0;
}




