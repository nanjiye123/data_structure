//堆排序
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int

void HeadAdjust(ElementType *A, int start, int end)
{
	ElementType tmp = A[start];
	for(int i=2*start; i<=end; i*=2)
	{//根节点的序号是i=1,则i节点左孩子和右孩子为2i和2i+1
		if(i<end && A[i]<A[i+1])//左右孩子的比较
		{                       //i<end为保证A[i+1]有意义
			i++;//i记录较大孩子的下标
		}
		if(tmp > A[i])
		{
			break;
		}

		//将孩子结点上位，则以孩子结点的位置进行下一轮的筛选
		A[start] = A[i];
		start = i;
	}//end_for
	A[start] = tmp;
}

void HeapSort(ElementType *A, int num)//堆排序入口
{
	//建立大顶堆
	for(int i=num/2; i>=1; i--)//从最后一个叶子的父结点开始比较
	{
		HeadAdjust(A, i, num);	
	}

	//进行排序
	for(int i=num; i>=1; i--)
	{
		//最后一个元素和第一个元素交换
		ElementType tmp = A[i];
		A[i] = A[1];
		A[1] = tmp;

		//将剩下的无序元素继续调整为大顶堆
		HeadAdjust(A, 1, i-1);
	}
}

int main()//堆排序(大顶堆)
{
	ElementType A[] = {0,70,60,12,40,30,8,10};
	int num = 7;//注意，A[0]是设定的最小值，不是元素值
	HeapSort(A, num);//堆排序

	//打印排序后的序列
	for(int i=1; i<=num; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;
	return 0;
}


