//二叉堆
//数据结构与算法分析C语言描述
#include <iostream>
using namespace std;
#define ElementType int//定义元素的类型
#define MAX_SIZE (100)//堆的最大容量
#define MIN_DATA (0)//定义数组0位置的元素，用于插入时终止循环

typedef struct Heap
{
	int capacity;//堆的最大值
	int size;//当前堆的大小
	ElementType *elements;
}Heap;

Heap* InitHeap(Heap *heap)
{
	if(heap != NULL)//heap有原值，需要释放内存
	{
		if(heap->elements != NULL)
		{
			free(heap->elements);
		}
		free(heap);
	}

	heap = (Heap*)malloc(sizeof(Heap));
	if(NULL == heap)//申请内存失败
	{
		cout<<"error!"<<endl;
		return NULL;
	}

	heap->elements = (ElementType *)malloc(MAX_SIZE*sizeof(ElementType));
	if(NULL == heap->elements)//申请内存失败
	{
		cout<<"error!"<<endl;
		return NULL;
	}

	heap->capacity = MAX_SIZE;//堆容量最大值
	heap->size = 0;//堆当前有0个元素
	heap->elements[0] = MIN_DATA;
	return heap;
}

void PercolateUp(Heap *heap, int hole)//上滤
{
	ElementType temp = heap->elements[hole];
	int parent = hole>>1;
	while(temp < heap->elements[parent])
	{
		heap->elements[hole] = heap->elements[parent];
		hole = parent;
		parent = parent>>1;
	}
	heap->elements[hole] = temp;
}

void PercolateDown(Heap *heap, int hole)//下滤 //hole空穴
{
	if(NULL == heap)
	{
		cout<<"error"<<endl;
		return;
	}

	ElementType temp = heap->elements[hole];//空穴的值
	int child = hole * 2;
	
	while(child <= heap->size)//判断孩子是否存在
	{
		if(child != heap->size)//hole有两个child
		{//如果相等，则只有一个child
			if(heap->elements[child+1] < heap->elements[child])//选两个child最小的一个
			{
				child = child + 1;
			}
		}
		if(temp > heap->elements[child])//空穴 大于 孩子结点
		{
			heap->elements[hole] = heap->elements[child];//交换
		}
		else//空穴 小于等于 孩子结点
		{
			break;
		}
		hole = child;
		child = child * 2;
	}
	heap->elements[hole] = temp;
}

Heap* BuildHeap(Heap *heap, ElementType *InputElement, int n)
{
	heap = InitHeap(heap);//初始化空堆，包括elements[0]=0
	for(int i=0; i<n; i++)
	{
		heap->elements[i+1] = InputElement[i];
	}
	heap->size = n;

	for(int i=n/2; i>0; i--)//从最后一个元素的父结点开始比较
	{
		PercolateDown(heap, i);//下滤
	}
	return heap;
}

bool isFull(Heap* heap)
{
	return (heap->size == heap->capacity);
}

Heap* InsertHeap(Heap* heap, ElementType x)
{
	int i = 0;
	if( isFull(heap))//堆已满，不能插入
	{
		cout<<"heap is full."<<endl;
		return heap;
	}

	for(i=++heap->size; heap->elements[i>>1]>x; i=i>>1)//上滤
	{//在堆的最后创建空穴  父结点大于插入结点x
		heap->elements[i] = heap->elements[i>>1];//父结点向下移动
	}//利用elements[0]=MIN_DATA进行循环停止
	heap->elements[i] = x;
	return heap;
}

ElementType DeleteMin(Heap *heap)
{
	ElementType min_ele = 0, last_ele = 0;
	if(heap->size == 0)//堆为空
	{
		cout<<"heap is empty."<<endl;
		return heap->elements[0];
	}

	min_ele = heap->elements[1];
	last_ele = heap->elements[heap->size--];//最后一个元素

	int child = 2;//初始为根的左孩子
	while(child <= heap->size)//是否存在孩子
	{
		if(child != heap->size)//有两个child
		{//如果相等，则只有一个child
			if(heap->elements[child+1] < heap->elements[child])//选两个child最小的一个
			{
				child = child + 1;
			}
		}

		if(last_ele > heap->elements[child])//如果最后的元素大于孩子结点，空穴下移
		{
			heap->elements[child>>1] = heap->elements[child];
		}
		else//找到插入最后元素的位置
		{
			break;
		}
		child = child * 2;
	}
	heap->elements[child>>1] = last_ele;
	return min_ele;
}

Heap* DecreaseKey(int pos, ElementType delta, Heap *heap)
{//降低关键字的值，pos关键字位置，delta降幅
	heap->elements[pos] -= delta;
	PercolateUp(heap, pos);//上滤
	return heap;
}

Heap* IncreaseKey(int pos, ElementType delta, Heap *heap)
{//增加关键字的值，pos关键字位置，delta升幅
	heap->elements[pos] += delta;
	PercolateDown(heap, pos);//下滤
	return heap;
}

ElementType Delete(int pos, Heap *heap)
{//删除位置pos处的节点
	ElementType temp = heap->elements[pos];
	DecreaseKey(pos, temp, heap);//降低关键字的值为0
	if(DeleteMin(heap) != 0)//删除最小值
	{
		cout<<"error!"<<endl;
		return 0;
	}
	return temp;
}

void print(Heap *heap)
{
	for(int i=0; i<heap->size; i++)
	{
		cout<<heap->elements[i+1]<<' ';
	}
	cout<<endl<<endl;
}

int main()//二叉堆算法
{
	int NumElements = 15;//初始元素的个数
	ElementType InputElements[] = {150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
	Heap *heap = NULL;
	cout << "=======构建堆=======" << endl;
	heap = BuildHeap(heap, InputElements, NumElements);//构建堆，包括初始化堆
	print(heap);

	ElementType x = 50;
	cout << "插入元素x = " << x << endl;
	heap = InsertHeap(heap, x);
	print(heap);

	x = 100;
	cout << "插入元素x = " << x << endl;
	heap = InsertHeap(heap, x);
	print(heap);

	x = 200;
	cout << "插入元素x = " << x << endl;
	heap = InsertHeap(heap, x);
	print(heap);

	cout<<"=======降低关键字的值========"<<endl;
	heap = DecreaseKey(6, 21, heap);
	print(heap);

	cout<<"=======增加关键字的值========"<<endl;
	heap = IncreaseKey(5, 1000, heap);
	print(heap);

	cout<<"=========删除关键字========="<<endl;
	Delete(5, heap);
	print(heap);

	x = DeleteMin(heap);
	cout << "删除最小元x = " << x << endl;
	print(heap);

	return 0;
}
