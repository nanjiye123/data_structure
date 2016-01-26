//二项队列
//数据结构与算法分析
#include <iostream>
using namespace std;
#define ElementType int
#define MaxTrees (14)//二项队列中的二项树高度最大为13
#define capacity (16383)//高度0,1，...，13的二项树节点数目之和 2^k
//一个满二项队列只存在高度0,1，...，13的二项树各一个，共14个树

typedef struct BinNode//二项树
{
	ElementType Element;
	struct BinNode *LeftChild;//左孩子
	struct BinNode *NextSibling;//右兄弟，从高度最大的兄弟开始
}BinNode, *BinTree;//二项树指针

typedef struct Collection
{
	int size;
	BinTree TheTrees[MaxTrees];
}Collection, *BinQueue;//二项队列

BinQueue init()//初始化二项队列BinQueue
{
	BinQueue H = (BinQueue)malloc(sizeof(Collection));
	if(NULL == H)
	{
		cout<<"out of space!"<<endl;
		return NULL;
	}

	H->size = 0;
	for(int i=0; i<MaxTrees; i++)
	{
		H->TheTrees[i] = NULL;
	}
	return H;
}

bool isEmpty(BinQueue H)
{
	if(0 == H->size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BinTree CombineTrees(BinTree T1, BinTree T2)
{//合并同样大小的两棵二项树
	if(T1->Element > T2->Element)
	{
		return CombineTrees(T2, T1);
	}
	//保证T1的Element小于T2
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}

BinQueue Merge(BinQueue H1, BinQueue H2)
{//H1是原二项队列，H2是欲插入的二项队列，合并结果放在H1，清空H2
	if(H1->size + H2->size > capacity)//若合并后大于最大容量
	{
		cout<<"Merge would exceed capacity."<<endl;
		return H1;
	}
	H1->size += H2->size;

	BinTree T1, T2, Carry = NULL;
	for(int i=0,j=1; j<=H1->size; i++,j*=2)//遍历H1,H2的所有二项树
	{//i既代表二项树在队列中位置，也代表二项树的高度或秩
		T1 = H1->TheTrees[i];
		T2 = H2->TheTrees[i];
		//T1若为空，!!T1为0。T1若存在，!!T1为1。
		//Carry由上一步合并得到的树
		switch(!!T1 + 2 * (!!T2) + 4 * (!!Carry) )
		{
			case 0://T1和T2都没有树
			case 1://只T1存在
				break;//情况1和情况2退出switch
			case 2://只T2存在，直接将T2放入H1中对应位置
				H1->TheTrees[i] = T2;
				H2->TheTrees[i] = NULL;
				break;
			case 3://T1和T2均存在，合并相同大小的二项树
				Carry = CombineTrees(T1, T2);
				H1->TheTrees[i] = NULL;
				H2->TheTrees[i] = NULL;
				break;
			case 4://只存在上一步合并得到的二项树Carry 作为二项队列H1的一部分
				H1->TheTrees[i] = Carry;
				Carry = NULL;
				break;
			case 5://存在T1和Carry
				Carry = CombineTrees(T1, Carry);
				H1->TheTrees[i] = NULL;
				break;
			case 6://存在T2和Carry
				Carry = CombineTrees(T2, Carry);
				H2->TheTrees[i] = NULL;
				break;
			case 7://存在T1 T2 Carry
				H1->TheTrees[i] = Carry;
				Carry = CombineTrees(T1, T2);
				H2->TheTrees[i] = NULL;
				break;
		}//switch end
	}//for end
	return H1;
}

BinQueue Insert(ElementType x, BinQueue H)
{
	//创建BinTree
	BinTree newnode;
	newnode = (BinTree)malloc(sizeof(BinNode));
	if(NULL == newnode)
	{
		cout<<"out of space!"<<endl;
		return NULL;
	}
	newnode->Element = x;
	newnode->LeftChild = newnode->NextSibling = NULL;

	//创建BinQueue
	BinQueue OneItem;//只有单个节点树的二项队列
	OneItem = init();
	OneItem->size = 1;
	OneItem->TheTrees[0] = newnode;
	return Merge(H, OneItem);//合并单个节点树和H
}

ElementType DeleteMin(BinQueue H)
{//删除最小的根元素
	if( isEmpty(H) )
	{
		cout<<"empty queue."<<endl;
		return -1;
	}

	ElementType  MinItem;//最小的根元素
	int          MinTree;//根元素最小的二项树
	BinTree      DeleteRoot, DeleteTree;
	BinQueue     DeleteQueue;
	int i = 0;

	//为最小值赋初值，找到第一个不为空的位置
	while( !H->TheTrees[i++] ){}
	MinItem = H->TheTrees[i-1]->Element;
	MinTree = i-1;

	//遍历二项队列，找出根元素最小的二项树
	for(; i<MaxTrees; i++)
	{
		if(H->TheTrees[i] && H->TheTrees[i]->Element < MinItem)
		{
			MinItem = H->TheTrees[i]->Element;
			MinTree = i;
		}
	}
	
	DeleteRoot = H->TheTrees[MinTree];//准备删除的根元素
	DeleteTree = H->TheTrees[MinTree]->LeftChild;//删除后保留的二项树
	free(DeleteRoot);//删除根元素
	
	DeleteQueue = init();//删除后剩下的部分，组成一个二项队列
	//因为高度为k的二项树大小是2^k==1<<min，减1是因为删除了根
	DeleteQueue->size = (1<<MinTree) - 1;
	for(int j=MinTree-1; j>=0; j--)
	{
		DeleteQueue->TheTrees[j] = DeleteTree;
		DeleteTree = DeleteTree->NextSibling;//高度只小1的右兄弟
		DeleteQueue->TheTrees[j]->NextSibling = NULL;
	}

	H->TheTrees[MinTree] = NULL;
	H->size -= DeleteQueue->size + 1;//删除后的二项队列的大小
	Merge(H, DeleteQueue);//将删除后H和剩余的二项树合并

	return MinItem;
}

void preOrder(BinTree root)
{//二项树的先根遍历
	if(!root)
		return;
	cout << root->Element << ' ';
	BinTree p;
	for(p=root->LeftChild; p!=NULL; p=p->NextSibling)
	{
		preOrder(p);
	}
}

int main()//二项队列
{
	const int in_num1 = 6;//初始化元素个数
	const int in_num2 = 7;//初始化元素个数
	ElementType input1[in_num1] = {12,21,24,65,16,18};
	ElementType input2[in_num2] = {23,51,24,65,14,26,13};
	BinQueue H1, H2;
	H1 = init();
	H2 = init();
	
	//=====构建H1=====
	for(int i=0; i<in_num1; i++)
	{
		H1 = Insert(input1[i], H1);
		
		cout<<"=====打印二项队列="<<i<<endl;
		for(int j=0; j<in_num1; j++)
		{
			cout << j << ":";
			preOrder(H1->TheTrees[j]);
			cout<<endl;
		}
	}

	//=====构建H2=====
	for(int i=0; i<in_num2; i++)
	{
		H2 = Insert(input2[i], H2);
		
		cout<<"=====打印二项队列="<<i<<endl;
		for(int j=0; j<in_num2; j++)
		{
			cout << j << ":";
			preOrder(H2->TheTrees[j]);
			cout<<endl;
		}
	}

	//======打印H1=====
	cout<<"======打印二项队列H1======"<<endl;
	for(int i=0; i<in_num1; i++)
	{
		cout << i << ":";
		preOrder(H1->TheTrees[i]);
		cout<<endl;
	}
	//======打印H2=====
	cout<<"======打印二项队列H2======"<<endl;
	for(int i=0; i<in_num2; i++)
	{
		cout << i << ":";
		preOrder(H2->TheTrees[i]);
		cout<<endl;
	}

	//合并H1和H2
	H1 = Merge(H1, H2);

	//======打印H3=====
	cout<<"=====打印合并后的队列H3====="<<endl;
	for(int i=0; i<in_num1+in_num2; i++)
	{
		cout << i << ":";
		preOrder(H1->TheTrees[i]);
		cout<<endl;
	}
	
	//H3删除最小元素
	ElementType z;
	z = DeleteMin(H1);

	//=====打印删除最小元素后的二项队列=====
	cout<<"=====删除最小元素后的二项队列====="<<endl;
	cout<<"删除的最小元素是："<<z<<endl;
	for(int i=0; i<H1->size; i++)
	{
		cout << i << ":";
		preOrder(H1->TheTrees[i]);
		cout<<endl;
	}

    return 0;
}




