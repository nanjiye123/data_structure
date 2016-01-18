//左式堆
//数据结构与算法分析C语言描述
#include <iostream>
using namespace std;
#define ElementType int//定义元素的类型

typedef struct LeftHeap
{
	ElementType elements;
	struct LeftHeap *lchild;
	struct LeftHeap *rchild;
	int npl;//零路径长
}LeftHeap;

LeftHeap *Merge(LeftHeap *H1, LeftHeap *H2);
LeftHeap *Merge1(LeftHeap *H1, LeftHeap *H2);
void SwapChildren(LeftHeap *H);
LeftHeap *Insert(LeftHeap *H, ElementType x);
void InOrder(LeftHeap *H);

void SwapChildren(LeftHeap *H)
{//交换H的左右子堆
	LeftHeap *tmp = H->lchild;
	H->lchild = H->rchild;
	H->rchild = tmp;
}

LeftHeap *Merge1(LeftHeap *H1, LeftHeap *H2)//合并左式堆的实际例程
{//H1, H2有顺序限制  //H1根小，H2根大
	if(NULL == H1->lchild)//H1是单个节点
	{
		H1->lchild = H2;
	}
	else
	{
		H1->rchild = Merge(H1->rchild, H2);//合并后赋给小根右子堆
		if(H1->lchild->npl < H1->rchild->npl)//如果小根左npl小于小根右npl，交换
		{
			SwapChildren(H1);
		}
		H1->npl = H1->rchild->npl + 1;//npl是其右孩子npl加1
	}
	return H1;
}

LeftHeap *Merge(LeftHeap *H1, LeftHeap *H2)//合并左式堆的驱动例程
{//合并左式堆
	if(NULL == H1)//如果两个堆中有一个空，返回另一个堆
	{
		return H2;
	}
	if(NULL == H2)
	{
		return H1;
	}

	if(H1->elements < H2->elements)//小根右子堆与大根合并
	{
		return Merge1(H1, H2);//H1根小，H2根大
	}
	else
	{
		return Merge1(H2, H1);//H2根小，H1根大
	}
	
}

LeftHeap *Insert(LeftHeap *H, ElementType x)
{//插入是合并的特殊情况，将插入的节点看作一棵树
	LeftHeap *node;
	node = (LeftHeap*)malloc(sizeof(LeftHeap));
	if(NULL == node)
	{
		cout<<"out of space."<<endl;
		return NULL;
	}

	node->elements = x;
	node->lchild = NULL;
	node->rchild = NULL;
	node->npl = 0;
	H = Merge(node, H);//合并入口
	return H;
}

LeftHeap *DeleteMin(LeftHeap *H)
{//删除最小值
	LeftHeap *leftheap, *rightheap;
	if(NULL == H)
	{
		cout<<"heap is empty."<<endl;
		return NULL;
	}

	leftheap = H->lchild;
	rightheap = H->rchild;
	free(H);
	return Merge(leftheap, rightheap);
}

ElementType findMin(LeftHeap *H)
{
	if(H)
	{
		return H->elements;
	}
	else
	{
		cout<<"Heap is empty."<<endl;
	}
	return -1;
}

void InOrder(LeftHeap *H)
{//中序遍历
	if(H)
	{
		InOrder(H->lchild);
		cout << H->elements << ' ';
		InOrder(H->rchild);
	}
}

int main()//左式堆算法
{
	LeftHeap *H1 = NULL, *H2 = NULL;
	cout << "=======构建左式堆=======" << endl;
	ElementType input1[] = {3,10,8,17,26,21,14,23};
	ElementType input2[] = {6,12,7,18,24,37,18,33};
	for(int i=0; i<8; i++)
	{
		H1 = Insert(H1, input1[i]);
		H2 = Insert(H2, input2[i]);
	}
	cout << "=======打印左式堆=======" << endl;
	cout << "H1: ";
	InOrder(H1);//中序遍历
	cout<<endl<<"H2: ";
	InOrder(H2);//中序遍历
	cout<<endl<<endl;

	cout << "=======合并H1和H2=======" << endl;
	LeftHeap *HH = Merge(H1, H2);
	cout<<"HH: ";
	InOrder(HH);//中序遍历
	cout<<endl<<endl;


	cout << "=======删除HH最小节点=======" << endl;
	cout << "HH的最小节点是：" << findMin(HH) << endl;
	HH = DeleteMin(HH);
	cout << "删除后HH： ";
	InOrder(HH);//中序遍历
	cout<<endl;

	return 0;
}
