//线索二叉树
#include <iostream>
using namespace std;
typedef char EleType;
typedef enum PointerTag{link,thread}; //link=0孩子,thread=1线索
typedef struct BiThrNode
{
	EleType data;
	struct BiThrNode *rchild, *lchild;
	PointerTag ltag, rtag;
}BiThrNode, *BiThrTree;

BiThrTree pre; // 全局变量,始终指向刚刚访问过的结点

void createTree(BiThrTree &T)//先序创建二叉树
{
	EleType inputData;
	cin>>inputData;
	if(inputData=='#')
	{
		T=NULL;
	}
	else
	{
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		if(!T) exit(1);
		T->data = inputData;
		createTree(T->lchild);
		if(T->lchild)  T->ltag = link;
		else           T->ltag = thread;
		createTree(T->rchild);
		if(T->rchild)  T->rtag = link;
		else           T->rtag = thread;
	}
}

void inThreading(BiThrTree p)//中序线索化
{
	if(p)
	{
		inThreading(p->lchild);//左子树线索化
		if(!p->lchild){p->ltag=thread; p->lchild=pre;}//前驱线索
		if(!pre->rchild){pre->rtag=thread; pre->rchild=p;}//后续线索
		pre = p;//保持pre指向p的前驱
		inThreading(p->rchild);//右子树线索化
	}
}

void midOrderThreading(BiThrTree &Thrt, BiThrTree T)//中序遍历，建立头结点，并在其中中序线索化
{                               //Thrt是线索化树的头结点
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if(!Thrt) exit(1);
	Thrt->data = NULL; //初始化头结点
	Thrt->ltag = link; //初始化头结点
	Thrt->rtag = thread;//初始化头结点
	Thrt->rchild = Thrt;//初始化头结点
	if(!T)
		Thrt->lchild = Thrt;//若二叉树为空，则左子树回指
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		inThreading(T);//进行中序线索化
		pre->rchild = Thrt;
		pre->rtag = thread;
		Thrt->rchild = pre;
	}
	
}

void inOrderTraverse_Thr(BiThrTree T)//中序遍历打印
{
	BiThrTree p;
	p = T->lchild;//p指向头节点的左孩子，即第一个有数据的节点
	while(p!=T)//空树或遍历结束时p==T
	{
		while(p->ltag==link) 
		{
			p = p->lchild;//遍历到没有左孩子为止
		}
		cout<<p->data<<' ';//访问左子树为空的节点
		while(p->rtag==thread && p->rchild!=T)
		{
			p = p->rchild;
			cout<<p->data<<' ';
		}
		p = p->rchild;
	}
}

int main()//线索二叉树示例程序，输入为AB##C##，即孩子为空时data默认为#
{
	BiThrTree tree;
	BiThrTree thrt;//tree是创建的树，thrt是中序线索化树的头结点
	createTree(tree);//先序创建树
	midOrderThreading(thrt,tree);//中序线索化
	inOrderTraverse_Thr(thrt);//中序遍历打印
	return 0;
}


