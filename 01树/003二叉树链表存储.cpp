//二叉树链表存储
#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef struct treenode
{
	char data;
	struct treenode *lchild, *rchild;
}treenode, *bitree;

void createTree(bitree &T)
{
	char data;
	scanf("%c", &data);
	if('#' == data)
	{
		T = NULL;
	}
	else
	{
		T = (bitree)malloc(sizeof(treenode));
		if(!T) exit(1);
		T->data = data;
		createTree(T->lchild);
		createTree(T->rchild);
	}
}

void preorder(bitree &T)
{
	if(NULL == T)
		return;
	cout<< T->data;
	preorder(T->lchild);
	preorder(T->rchild);
}

void inorder(bitree &T)
{
	if(NULL == T)
		return;
	inorder(T->lchild);
	cout<< T->data;
	inorder(T->rchild);
}

void postorder(bitree &T)
{
	if(NULL == T)
		return;
	postorder(T->lchild);
	postorder(T->rchild);
	cout<< T->data;
}

int main()//二叉树链表存储
{//输入为ab##c##,即孩子为空时data默认为#
	bitree tree;
	createTree(tree);
	preorder(tree);cout<<endl;
	inorder(tree);cout<<endl;
	postorder(tree);cout<<endl;

	return 0;
}
















