//Kruskal算法
//数据结构与算法分析C语言描述
//在一个无向图中找出一棵最小生成树
#include <iostream>
#include <algorithm>
using namespace std;
typedef char NodeType;//顶点的数据类型
typedef int AdjType;//边权重的数据类型
#define MAX_VEX 100 //最大顶点数
#define MAX 10000//相当于无穷

NodeType inputNodeValue[] = {'a','b','c','d','e','f','g'};
const int NodeNum = 7;//顶点数
const int AdjNum = 12;//边数
int InputEdge[AdjNum][3]={{0,1,2},//边的信息，由两个顶点的序号组成
					      {0,2,4},//第一个顶点序号小于第二个
					      {0,3,1},//第三个数字是权重值
					      {1,3,3},//有权重的无向图，需要生成对称阵
					      {1,4,10},
	                      {2,3,2},
						  {2,5,5},
						  {3,5,8},
						  {3,6,4},
						  {3,4,7},
						  {4,6,6},
						  {5,6,1}};

typedef struct Edge//边的信息
{
	int     startnode, endnode;//边的起点和终点
	AdjType weight;//边的权重
}Edge;
Edge edge[AdjNum];

typedef struct Graph
{//图的基本信息，包括顶点值和邻接矩阵
	NodeType node[MAX_VEX];//顶点
	AdjType  arcs[MAX_VEX][MAX_VEX];//带权重的邻接矩阵，无向图，对称阵
	                                //不改变，仅表示顶点的连接情况
}Graph;

bool compare(Edge a, Edge b)//用于sort函数排序
{
	return a.weight < b.weight;
}

Graph* init(Graph *G)//初始化顶点值和邻接矩阵
{
	G = (Graph*)malloc(sizeof(Graph));
	//图的顶点初始化
	for(int i=0; i<NodeNum; i++)
	{
		G->node[i] = inputNodeValue[i];
	}

	//构建邻接矩阵，有权无项图，对称
	for(int i=0; i<MAX_VEX; i++)//初始化邻接矩阵
	{
		for(int j=0; j<MAX_VEX; j++)
		{
			G->arcs[i][j] = (i==j ? 0 : MAX);
		}
	}
	for(int j=0; j<AdjNum; j++)//初始化有连接的点
	{
		int x = InputEdge[j][0];
		int y = InputEdge[j][1];
		G->arcs[x][y] = InputEdge[j][2];
		G->arcs[y][x] = InputEdge[j][2];
		edge[j].startnode = x;
		edge[j].endnode = y;
		edge[j].weight = InputEdge[j][2];
	}

	//边集合按照权重从小到大排序
	sort(edge, edge+AdjNum, compare);
	cout<<"边按权重的排序结果："<<endl;
	for(int i=0; i<AdjNum; i++)
	{
		cout<<edge[i].startnode<<','<<edge[i].endnode<<' ';
		cout<<edge[i].weight<<endl;
	}
	return G;
}

int Find(int *parent, int f)
{
	while(parent[f]>0)
	{
		f = parent[f];//这条边的终点变成下一条边的起点
	}
	return f;//直到树的叶子节点
}

void Kruskal(Graph *G)
{
	int i, n, m;
	int edgenum = 0;//用于计数已选的边
	int parent[AdjNum];
	for(i=0; i<AdjNum; i++)//初始化数组为0
	{
		parent[i] = 0;// (i, parent[i])代表一条已选边
	}
	for(i=0; i<AdjNum; i++)//循环每一条边
	{
		n = Find(parent, edge[i].startnode);
		m = Find(parent, edge[i].endnode);
	
		if(n != m)//假设不等，则没有与现有生成树形成环路
		{
			edgenum++;
			parent[n] = m;//将这条边放入parent
						  //表明此顶点已经在生成树集合中
			cout<<edge[i].startnode<<','<<edge[i].endnode;
			cout<<' '<<edge[i].weight<<endl;
		/*	for(int j=0; j<AdjNum; j++)//打印parent
			{
				cout<<parent[j]<<' ';
			}
			cout<<endl;*/
		}
		if(edgenum == NodeNum-1)//已选的边数 等于 顶点数-1
		{
			break;
		}
	}
}

int main()//Kruskal算法
{//无向图
	Graph *G = NULL;
	G = init(G);
	cout<<"初始化图完成。"<<endl<<endl;
	cout<<"======Kruskal过程======="<<endl;
	Kruskal(G);
	cout<<endl;

	return 0;
}
