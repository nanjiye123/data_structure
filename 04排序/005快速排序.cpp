//快速排序
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int
#define tmp_num (3)//用于设定小于几，使用插入排序；大于才使用快速排序

void printA(ElementType *A)
{
	for(int i=0; i<8; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;
}

void swap(ElementType *a, ElementType *b)
{
	ElementType tmp;
	tmp = *a;
	*a  = *b;
	*b  = tmp;
}

void InsertionSort(ElementType *A, int num)//插入排序
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

ElementType Median3(ElementType *A, int Left, int Right)//三数中值分割
{
	int center = (Left + Right) / 2;
	
	if(A[Left] > A[center])//左>中
	{
		swap(&A[Left], &A[center]);
	}
	if(A[Left] > A[Right])//左>右
	{
		swap(&A[Left], &A[Right]);
	}
	if(A[center] > A[Right])//中>右
	{
		swap(&A[center], &A[Right]);
	}
	//排序后 左 <= 中 <= 右

	swap(&A[center], &A[Right-1]);//隐藏privot
	return A[Right-1];//返回privot的值，其位置是Right-1
}

void Qsort(ElementType *A, int Left, int Right)
{
	if(Left + tmp_num <= Right)//大于tmp_num才使用快速排序
	{
		ElementType pivot;//中值、枢纽值
		int i, j;
		pivot = Median3(A, Left, Right);//三数中值分割
		//cout<<pivot<<endl;
		i = Left;
		j = Right - 1;
		while(1)
		{
			while( A[++i] < pivot ){}
			while( A[--j] > pivot ){}
			if(i < j)
			{
				swap(&A[i], &A[j]);
			}
			else
			{
				break;
			}
		}//endwhile(1)
		swap(&A[i], &A[Right-1]);
		//printA(A);
		Qsort(A, Left, i-1);
		Qsort(A, i+1, Right);
	}//end if
	else
	{
		InsertionSort(A+Left, Right-Left+1);
	}
}

void Quicksort(ElementType *A, int num)//快速排序的驱动程序
{
	Qsort(A, 0, num-1);//范围从0到num-1
}

int main()
{
	ElementType A[] = {24,13,26,1,2,27,38,15};
	int num = 8;
	
	Quicksort(A, num);

	for(int i=0; i<num; i++)
	{
		cout<<A[i]<<' ';
	}
	cout<<endl;

    return 0;
}




