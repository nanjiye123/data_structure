#include <iostream>
using namespace std;

typedef struct treenode
{
	int element;
	struct treenode *lchild, *rchild;
	int height;

}treenode,*bitree;

int getHeight(bitree T)
{
	if(T==NULL)
		return -1;
	else
		return T->height;
}

bitree SingleRotateRight(bitree k2)//单右旋
{
	bitree k1;
	k1 = k2->lchild;//初始化k1
	k2->lchild = k1->rchild;
	k1->rchild = k2;
	//比较的是左右孩子的高度，求父节点高度要加1
	k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild))+1;
	k1->height = max(getHeight(k1->lchild), k2->height)+1;
	return k1;
}

bitree SingleRotateLeft(bitree k2)//单左旋
{
	bitree k1;
	k1 = k2->rchild;//初始化k1
	k2->rchild = k1->lchild;
	k1->lchild = k2;
	k2->height = max(getHeight(k2->lchild),getHeight(k2->rchild))+1;
	k1->height = max(k2->height,getHeight(k1->rchild))+1;
	return k1;
}

bitree DoubleRotateRightLeft(bitree k1)//双右左旋
{
	k1->rchild = SingleRotateRight(k1->rchild);
	return SingleRotateLeft(k1);
}

bitree DoubleRotateLeftRight(bitree k3)//双左右旋
{
	k3->lchild = SingleRotateLeft(k3->lchild);
	return SingleRotateRight(k3);
}

void inserttree(int x, bitree &T)
{
	if(T==NULL)//插入根节点
	{
		T = (bitree)malloc(sizeof(treenode));
		if(T==NULL) exit(1);
		else
		{
			T->element = x;
			T->lchild = T->rchild = NULL;
			T->height = 0;
		}
	}
	else if(x < T->element)//插在左儿子
	{
		inserttree(x, T->lchild);
		if(getHeight(T->lchild)-getHeight(T->rchild)==2)
		{//插入元素后，若左子树比右子树高度差2，不符合AVL，需要调整
			if(x < T->lchild->element)//插在左儿子的左子树
			{
				T = SingleRotateRight(T);//单右旋
			}
			else//插在左儿子的右子树
			{
				T = DoubleRotateLeftRight(T);
			}
		}
	}
	else if(x > T->element)//插在右儿子
	{
		inserttree(x, T->rchild);
		if(getHeight(T->rchild)-getHeight(T->lchild)==2)
		{//插入元素后，若右子树比左子树高度差2，不符合AVL，需要调整
			if(x < T->rchild->element)//插在右儿子的左子树
			{
				T = DoubleRotateRightLeft(T);
			}
			else//插在右儿子的右子树
			{
				T = SingleRotateLeft(T);//单左旋
			}
		}
	}
	//每次新插入节点都要更新所有节点的height
	T->height = max(getHeight(T->lchild), getHeight(T->rchild))+1;
}

void printtree(bitree T)
{//先序遍历打印
	if(T != NULL)
	{
		cout<<T->element<<' ';
		printtree(T->lchild);
		printtree(T->rchild);
	}
}

int main()//AVL树
{
	bitree tree = NULL;
	int x=0;
	while(cin>>x)//win:ctrl+z linux:ctrl+x
	{
		inserttree(x, tree);
	}
	printtree(tree);

	return 0;	
}

