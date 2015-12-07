#include <iostream>
#include <string.h>
using namespace std;

typedef struct treenode//哈夫曼树结点的结构
{
	int weight;
	int lchild, rchild, parent;
}treenode;

typedef struct htree
{
	//int root;//哈夫曼树根在数组中的坐标
	treenode ht[100];//最多容纳100个结点
}htree, *phtree;

phtree create_huffman(int m, int *w)
{
	phtree tree;
	int x1, x2, w1, w2;
	tree = (phtree)malloc(sizeof(htree));
	if(NULL == tree)
	{
		cout<<"overflow!"<<endl;
		return NULL;
	}
	for(int i=0; i<2*m-1; ++i)//初始化所有结点，共2m-1个
	{
		tree->ht[i].parent = -1;
		tree->ht[i].lchild = -1;
		tree->ht[i].rchild = -1;
		if(i < m)
			tree->ht[i].weight = w[i];//0到m-1的结点被赋权重
		else
			tree->ht[i].weight = -1;
	}
	for(int i=0; i<m-1; ++i)//每循环一次合并两个结点，构造一个内部结点
	{//共需构造m-1个内部结点
		w1 = 1000;//最小的权重，用于比较下一个结点
		w2 = 1000;//第二小的权重
		x1 = -1;//最小权重的结点位置
		x2 = -1;//第二小权重的结点位置
		for(int j=0; j<m+i; j++)//找两个权重最小且无父结点的结点
		{
			if(tree->ht[j].weight < w1 && tree->ht[j].parent == -1)
			{//当前结点的权重比之前最小的权重w1还小
				w2 = w1;//更新权重
				w1 = tree->ht[j].weight;//更新权重
				x2 = x1;//更新结点位置
				x1 = j;//更新结点位置
			}//endif
			else if(tree->ht[j].weight < w2 && tree->ht[j].parent == -1)
			{//当前结点的权重比第二小的权重w2小
				w2 = tree->ht[j].weight;//更新权重
				x2 = j;//更新结点位置
			}//end elseif
	   	}//end for(j)找两个权重最小
		tree->ht[x1].parent = m+i;//设置两个权重最小结点的父结点
		tree->ht[x2].parent = m+i;
		tree->ht[m+i].lchild= x1;//设置新的内部结点
		tree->ht[m+i].rchild= x2;
		tree->ht[m+i].weight= w1 + w2;
		//tree->root = m+i;
	}//end for(i) 
	return tree;
}

int main()//霍夫曼树和霍夫曼编码
{
	//测试数据 m=6, w=9,12,6,3,5,15
	int m = 0;//带权叶子结点数
	int w[50];//权重数组
	memset(w, -1, sizeof(m));
	phtree tree = NULL;
	/*cout<<"输入带权叶子结点数m=";//输入叶子个数
	while(1)
	{
		cin>>m;
		if(m > 1)
			break;
		else
			cout<<"重新输入"<<endl;
	}
	w = (int *)malloc(sizeof(int)*m);
	if(NULL == w) cout<<"overflow!"<<endl;

	cout<<"输入权重："<<endl;//输入每个叶子权重
	for(int i=0; i<m; ++i)
	{
		cin>>w[i];
	}*/
	m=7;
	w[0] = 10;
	w[1] = 15;
	w[2] = 12;
	w[3] = 3;
	w[4] = 4;
	w[5] = 13;
	w[6] = 1;

	tree = create_huffman(m, w);//创建霍夫曼树
	cout<<"打印结点"<<endl;	
	for(int i=0; i<2*m-1; i++)
	{
		cout<<tree->ht[i].weight<<':'<<tree->ht[i].lchild<<','
		    <<tree->ht[i].rchild<<','<<tree->ht[i].parent<<endl;
	}
	cout<<"*************"<<endl;

	//霍夫曼编码
	int code[100];
	memset(code, -1, sizeof(code));
	int parent, code_pos, i;
	for(int j=0; j<m; j++)//共有m个外部结点
	{
		code_pos = 0;
		i = j;
		cout<< tree->ht[i].weight <<":";
		while(tree->ht[i].parent != -1)//从叶子遍历到根结束
		{
			parent = tree->ht[i].parent;
			if(tree->ht[parent].lchild == i)
				code[code_pos++] = 0;
			else
				code[code_pos++] = 1;
			i = parent;
		}
		for(int tmp=code_pos-1; tmp>=0; tmp--)
		{
			cout<<code[tmp];
		}
		cout<<endl;
	}

	return 0;
}
