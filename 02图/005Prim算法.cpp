//Prim算法
//数据结构与算法分析C语言描述
//在一个无向图中找出一棵最小生成树
//与Dijkstra相似
#include <iostream>
using namespace std;
typedef char NodeType;//顶点的数据类型
typedef int AdjType;//边权重的数据类型
#define MAX_VEX 100 //最大顶点数
#define MAX 10000//相当于无穷

NodeType inputNodeValue[] = {'a','b','c','d','e','f','g'};
const int NodeNum = 7;
const int AdjNum = 12;
int InputEdge[AdjNum][3]={{0,1,2},//边的信息，由两个顶点的序号组成
					      {0,2,4},//第三个数字是权重值
					      {0,3,1},//有权重的无向图，需要生成对称阵
					      {1,3,3},
					      {1,4,10},
	                      {2,3,2},
						  {2,5,5},
						  {3,5,8},
						  {3,6,4},
						  {3,4,7},
						  {4,6,6},
						  {5,6,1}};

typedef struct Node//图的顶点
{
	NodeType NodeValue;//顶点的数值
	bool     isKnown;//该顶点是否已被选取
	int      length;//当前情况下起始顶点至该顶点的最短路径,初始化为无穷大，权重
	int      pre;//导致length改变的最后的顶点
}Node;

typedef struct Graph
{//图的基本信息，包括顶点值和邻接矩阵
	Node*    node[MAX_VEX];//顶点
	AdjType  arcs[MAX_VEX][MAX_VEX];//带权重的邻接矩阵，无向图，对称阵
	                                //不改变，仅表示顶点的连接情况
}Graph;



Graph* init(Graph *G)//初始化顶点值和邻接矩阵
{
	G = (Graph*)malloc(sizeof(Graph));
	//图的顶点初始化
	for(int i=0; i<NodeNum; i++)
	{
		Node* nodetmp = (Node*)malloc(sizeof(Node));
		nodetmp->NodeValue = inputNodeValue[i];
		nodetmp->isKnown = false;
		nodetmp->length = MAX;
		nodetmp->pre = -1;
		G->node[i] = nodetmp;
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
	}

	return G;
}

Graph* Prim(Graph *G, int startNode)
{
	G->node[startNode]->length = 0;//起始点到其本身的距离为0
	while(true)//如果所有顶点的最短路径都known，则跳出循环
	{
		bool ok = true;
		for(int i=0; i<NodeNum; i++)
		{
			if(!G->node[i]->isKnown)
			{
				ok = false;
				break;//如果所有顶点的最短路径都known，则跳出循环
			}
		}//end for
		if(ok) break;//所有顶点都known，退出while循环

		//==================================================
		int tmpMinPos = -1;//路径最短的顶点序号
		AdjType tmpMinAdj = MAX;
		for(int i=0; i<NodeNum; i++)//在未知点中，搜索路径最短的
		{
			if(!G->node[i]->isKnown && tmpMinAdj > G->node[i]->length)
			{
				tmpMinAdj = G->node[i]->length;
				tmpMinPos = i;
			}
		}//此段可以用最小堆来实现
		//===================================================
		cout<<"当前选中的顶点为："<< G->node[tmpMinPos]->NodeValue <<endl;
		G->node[tmpMinPos]->isKnown = true;//更新为known
		
		//将以tmpMinPos为起始点的所有路径length更新
		for(int i=0; i<NodeNum; i++)
		{
			if(!G->node[i]->isKnown)
			{
				if(G->node[i]->length > G->arcs[i][tmpMinPos])
				{//寻找 min(length, arcsweight)
					G->node[i]->length = G->arcs[i][tmpMinPos];
					G->node[i]->pre = tmpMinPos;
				}
			}
		}
	}//end while(true)

	return G;
}


int main()//Prim算法
{//无向图
	Graph *G = NULL;
	G = init(G);
	cout<<"初始化图完成。"<<endl<<endl;
	cout<<"======Prim过程======="<<endl;
	G = Prim(G, 0);////设定起始点为a，其下标为0
	cout<<endl;

	cout<<"====打印最小生成树===="<<endl;
	for(int k=1; k<NodeNum; k++)
	{
		cout<< G->node[k]->NodeValue <<"到"<< G->node[G->node[k]->pre]->NodeValue;
		cout<<",权重为"<<G->node[k]->length<<endl;
	}

	return 0;
}
