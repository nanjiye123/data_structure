#include <iostream>
#include <stack>
using namespace std;

typedef struct treenode
{
	int element;
	struct treenode *lchild, *rchild;
}treenode, *bitree;

//二叉查找树的插入（递归）
bool inserttree(int x, bitree &T)
{
	if(NULL == T)//当前二叉查找树为空，则插入元素为根节点
	{
		T = (bitree)malloc(sizeof(treenode));//新申请根节点空间
		if(NULL == T) 
		{
			return false;
		}
		T->element=x;//初始化根节点
		T->lchild = T->rchild = NULL;//初始化根节点
		return true;
	}
	else if(x > T->element)
	{
		return inserttree(x, T->rchild);
	}
	else if(x < T->element)
	{
		return inserttree(x, T->lchild);
	}
	else
	{
		return false;//如果x已经在tree中，则返回false
	}
}

//二叉查找树的插入（非递归）
bool inserttree_norecursion(int x, bitree &T)
{
	if(NULL == T)//当前二叉查找树为空，则插入元素为根节点
	{
		T = (bitree)malloc(sizeof(treenode));//新申请根节点空间
		if(NULL == T) 
		{	
			return false;
		}
		T->element=x;//初始化根节点
		T->lchild = T->rchild = NULL;//初始化根节点
		return true;
	}

	bitree pT = T;//非递归过程会改变指针T指向，需要用其他变量接下T
	bitree pcur = T;//定义一个当前指针
	while(pT)
	{//查找插入位置，找到要插入到pcur的下面
		pcur = pT;
		if(x > pT->element)
		{
			pT = pT->rchild;
		}
		else if(x < pT->element)
		{
			pT = pT->lchild;
		}
		else
		{
			return false;//x已经在树中
		}
	}//while end
	if(x > pcur->element)
	{//大于，则插在pcur的右孩子
		pcur->rchild = (bitree)malloc(sizeof(treenode));
		if(NULL == pcur->rchild)
		{
			return false;
		}
		pcur->rchild->element = x;
		pcur->rchild->lchild = pcur->rchild->rchild = NULL;
	}
	else if(x < pcur->element)
	{//小于，则插在pcur的左孩子
		pcur->lchild = (bitree)malloc(sizeof(treenode));
		if(NULL == pcur->lchild)
		{
			return false;
		}
		pcur->lchild->element = x;
		pcur->lchild->lchild = pcur->lchild->rchild = NULL;
	}
	return true;
}

//二叉搜索树的查找（递归），返回查找到元素的指针
bitree findtree(int x, bitree &T)
{
	if(NULL == T)
	{
		return NULL;
	}
	if(x < T->element)//小于
		return findtree(x, T->lchild);
	else if(x > T->element)//大于
		return findtree(x, T->rchild);
	else if(x == T->element)//找到了
		return T;
	else//未找到
		return NULL;
}

//二叉搜索树的查找（非递归），返回查找到元素的指针
bitree findtree_norecursion(int x, bitree &T)
{
	if(NULL == T)
	{
		return NULL;
	}
	bitree pT = T;
	while(pT)
	{
		if(x < pT->element)//小于
			pT = pT->lchild;
		else if(x > pT->element)//大于
			pT = pT->rchild;
		else//找到
			return pT;
	}
	return NULL;//未找到
}

bitree findmax(bitree T)
{
	if(T!=NULL)
	{
		while(T->rchild != NULL)
		{
			T = T->rchild;
		}
	}
	return T;
}

bitree findmin(bitree T)
{
	if(T!=NULL)
	{
		while(T->lchild != NULL)
		{
			T = T->lchild;
		}
	}
	return T;
}

//前序遍历（递归）
void preorder(bitree &T)
{
	if(NULL == T)
		return;
	cout<< T->element <<' ';
	preorder(T->lchild);//先遍历左子树
	preorder(T->rchild);//再遍历右子树
}

//前序遍历（非递归）
void preorder_norecursion(bitree &T)
{
	if(NULL == T)
		return;
	stack<bitree> s;//建立一个栈
	s.push(T);//根压栈
	bitree pcur;
	while(!s.empty())//栈非空
	{//压栈顺序保证从右向左
		pcur = s.top();//读栈顶元素
		s.pop();//出栈
		cout<< pcur->element <<' ';
		if(pcur->rchild)//右孩子非空
			s.push( pcur->rchild );
		if(pcur->lchild)//左孩子非空
			s.push( pcur->lchild );
	}
}

//中序遍历（递归）
void inorder(bitree &T)
{
	if(NULL == T)
		return;
	inorder(T->lchild);
	cout<< T->element <<' ';
	inorder(T->rchild);
}

//中序遍历（非递归）
void inorder_norecursion(bitree &T)
{
	stack<bitree> s;//建立一个栈
	bitree pcur = T;
	while(pcur || !s.empty())
	{
		while(pcur)//找最左孩子
		{
			s.push(pcur);
			pcur = pcur->lchild;
		}
		if(!s.empty())
		{
			pcur = s.top();//读左孩子为空的结点
			s.pop();
			cout<< pcur->element <<' ';
			pcur = pcur->rchild;//转向右孩子
		}
	}
}

//后序遍历（递归）
void postorder(bitree &T)
{
	if(NULL == T)
		return;
	postorder(T->lchild);
	postorder(T->rchild);
	cout<< T->element <<' ';
}

//后序遍历（非递归）
void postorder_norecursion(bitree &T)
{
	if(NULL == T)
		return;
	stack<pair<bitree, int>> s;
	s.push( make_pair(T, 0) );
	int times;
	bitree pcur;
	while(!s.empty())
	{
		pcur  = s.top().first;
		times = s.top().second;
		s.pop();
		if(0 == times)//第一次压栈
		{
			s.push( make_pair(pcur, 1) );//第二次压栈
			if(pcur->rchild)
			{
				s.push( make_pair(pcur->rchild, 0) );
			}
			if(pcur->lchild)
			{
				s.push( make_pair(pcur->lchild, 0) );
			}
		}
		else
		{
			cout<< pcur->element <<' ';
		}
	}
}

bool deletetree(int x, bitree &T)
{
	if(NULL == T)
	{
		cout<<"树空！"<<endl;
		return false;
	}
	bitree p = T;//临时把T接下来
	bitree pre_node = NULL;//p的父亲节点
	while(p)//查找将要删除元素位置
	{
		if(x < p->element)//小于，移向左孩子
		{
			pre_node = p;
			p = p->lchild;
		}
		else if(x > p->element)//大于，移向右孩子
		{
			pre_node = p;
			p = p->rchild;
		}
		else//等于，找到了，退出循环
		{
			break;
		}
	}
	if(NULL == p)//搜索到最后也未找到元素
	{
		cout<<"no found!"<<endl;
		return false;
	}

	//删除过程，三种情况
	if(p->lchild==NULL && p->rchild==NULL)//p删除目标为叶子节点
	{
		if(p == T)//p删除目标为根节点
		{
			T = NULL;
		}
		else if(pre_node->lchild == p)//p删除目标为左叶子
		{
			pre_node->lchild = NULL;
		}
		else//p删除目标为右叶子
		{
			pre_node->rchild = NULL;
		}
		free(p);
	}
	else if(p->lchild==NULL || p->rchild==NULL)//p有一个儿子
	{
		bitree p_son = p->lchild ? p->lchild : p->rchild;//找出p的左孩子还是右孩子非空
		if(p == T)//p为根节点，p无父亲
		{
			T = p_son;
		}
		else if(pre_node->lchild == p)//p本身是左孩子
		{
			pre_node->lchild = p_son;
		}
		else//p本身是右孩子
		{
			pre_node->rchild = p_son;
		}
		free(p);
	}
	else//p的左右子树都不为空：用右子树的最小数据代替该节点
	{
		bitree minnode = findmin(p->rchild);
		p->element = minnode->element;
		deletetree(minnode->element, p->rchild);
	}
	return true;
}

int main()//二叉查找树
{
	//*******二叉查找树（非递归）操作**********
	cout<<"*****二叉查找树（非递归）操作*****"<<endl;
	bitree tree = NULL;
	int x;
	int node[]={15,5,3,12,16,20,23,13,18,10,6,7};
	for(int i=0; i<sizeof(node)/sizeof(node[0]); i++)
	{
		inserttree_norecursion(node[i], tree);//插入操作
	}

	cout<<"前序遍历";//遍历操作
	preorder_norecursion(tree);
	cout<<endl;
	cout<<"中序遍历";
	inorder_norecursion(tree);
	cout<<endl;
	cout<<"后序遍历";
	postorder_norecursion(tree);
	cout<<endl;

	cout<<"输入查找元素：";
	cin>>x;
	bitree findtr = findtree_norecursion(x, tree);//查找操作
	if(findtr)
	{
		cout<< findtr->element <<endl;
	}
	else
	{
		cout<<"no found!"<<endl;
	}
	
	cout<<"要删除的元素：";
	cin>>x;
	if(deletetree(x, tree))//删除操作
	{
		preorder_norecursion(tree);
		cout<<endl;
	}
	else
	{
		cout<<"删除失败"<<endl;
	}
	
	//*******二叉查找树（递归）操作**********
	cout<<endl<<endl<<"*****二叉查找树（递归）操作*****"<<endl;
	bitree tree1 = NULL;
	int y;
	int node1[]={15,5,3,12,16,20,23,13,18,10,6,7};
	for(int i=0; i<sizeof(node1)/sizeof(node1[0]); i++)
	{
		inserttree(node1[i], tree1);//插入操作
	}

	cout<<"前序遍历";//遍历操作
	preorder(tree1);
	cout<<endl;
	cout<<"中序遍历";
	inorder(tree1);
	cout<<endl;
	cout<<"后序遍历";
	postorder(tree1);
	cout<<endl;

	cout<<"输入查找元素：";
	cin>>y;
	bitree findtr1 = findtree(y, tree1);//查找操作
	if(findtr1)
	{
		cout<< findtr1->element <<endl;
	}
	else
	{
		cout<<"no found!"<<endl;
	}

	cout<<"要删除的元素：";
	cin>>y;
	if(deletetree(y, tree1))//删除操作
	{
		preorder(tree1);
		cout<<endl;
	}
	else
	{
		cout<<"删除失败"<<endl;
	}
	
	return 0;
}






